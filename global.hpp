#ifndef __GLOBALS_H__
#define __GLOBALS_H__

#include "main.h"
#include <string.h>



// additional class definitions ================================================================
namespace obj
{
    class Piston
    {
    private: 
        pros::ADIDigitalOut pneu; 
        bool start_status;
        bool extended;
    public:
        // initialization constructor
        Piston(int port_num, bool start_extended=false, bool init=false) : pneu(port_num), extended(false), start_status(start_extended)
        {
            if(init) initialize();
        }

        void initialize()
        {
            set(start_status);
        }

        // methods
        bool set(bool extend_val)
        {
            if(extended != extend_val)
            {
                extended = extend_val;
                pneu.set_value(extend_val);
                return true;
            }
            return false;
        }

        void toggle()
        {
            if(extended)
            {
                extended = false;
                pneu.set_value(extended);
            }
            else
            {
                extended = true;
                pneu.set_value(extended);
            }
        }

        bool status()
        {
            return extended;
        }
    };


    class PID
    {
    private:
        double integral;
        double last_error;
        float slew;
        float kP, kI, kD;
        float init_kP, init_kI, init_kD;
    public:
        PID(float kP, float kI=0, float kD=0, float slew=1) : integral(0), last_error(0)
        {
            this->kP = kP;
            this->kI = kI;
            this->kD = kD;

            this->slew = slew;

            init_kP = kP;
            init_kI = kI;
            init_kD = kD;
        }

        void set_kP(float new_kP)
        {
            kP = new_kP;
        }
        
        void set_kI(float new_kI)
        {
            kI = new_kI;
        }
        
        void set_kD(float new_kD)
        {
            kD = new_kD;
        }

        float get_kP()
        {
            return kP;
        }
        
        float get_kI()
        {
            return kI;
        }
        
        float get_kD()
        {
            return kD;
        }

        void increment_slew()
        {
            static float slew_increment = slew;
            static bool first_run = true;
            if(first_run)
            {
                first_run = false;
                return;
            }
            if(slew > 1) slew = 1;
            else slew += slew_increment;
            if(slew > 1) slew = 1;
        }

        double calculate(double target, double current, bool count_integral=false, bool add_slew=true)
        {
            static double error = 0;
            if(add_slew) increment_slew();
            last_error = error;
            error = target - current;
            if(count_integral) integral += error;
            return slew * ((error * kP) + (integral * kI) + ((error - last_error) * kD)); 
        }

        void reset_integral()
        {
            integral = 0;
        }

        void modify(float new_kP=-999, float new_kI=-999, float new_kD=-999)
        {
            if(new_kP != -999) kP = new_kP;
            if(new_kI != -999) kI = new_kI;
            if(new_kD != -999) kD = new_kD;
        }

        void reset()
        {
            kP = init_kP;
            kI = init_kI;
            kD = init_kD;
        }
    };
}


// Global variable and value definitions =======================================================
namespace glb
{
    // motors
    #define P_LEFT_FRONT 15 // PTO left
    #define P_LEFT_MID_FRONT 1
    #define P_LEFT_MID_BACK 4
    #define P_LEFT_BACK 11
    #define P_RIGHT_FRONT 6  // PTO right
    #define P_RIGHT_MID_FRONT 7
    #define P_RIGHT_MID_BACK 19
    #define P_RIGHT_BACK 9
    // pistons
    #define P_PTO 'A'
    #define P_LEFT_BACK_LIFT 'D'
    #define P_RIGHT_BACK_LIFT 'C'
    #define P_CHAIN_CLAMP 'B'
    #define P_FRONT_CLAMP 'E'
    // misc
    #define P_IMU 3

    // chassis
    pros::Motor left_front(P_LEFT_FRONT, pros::E_MOTOR_GEARSET_06, false);
    pros::Motor left_mid_front(P_LEFT_MID_FRONT, pros::E_MOTOR_GEARSET_06, false);
    pros::Motor left_mid_back(P_LEFT_MID_BACK, pros::E_MOTOR_GEARSET_06, true);
    pros::Motor left_back(P_LEFT_BACK, pros::E_MOTOR_GEARSET_06, false);
    pros::Motor right_front(P_RIGHT_FRONT, pros::E_MOTOR_GEARSET_06, true);
    pros::Motor right_mid_front(P_RIGHT_MID_FRONT, pros::E_MOTOR_GEARSET_06, true);
    pros::Motor right_mid_back(P_RIGHT_MID_BACK, pros::E_MOTOR_GEARSET_06, false);
    pros::Motor right_back(P_RIGHT_BACK, pros::E_MOTOR_GEARSET_06, true);
    // misc
    pros::Imu imu(P_IMU);
    pros::Controller con(pros::E_CONTROLLER_MASTER);
    // piston
    obj::Piston PTO(P_PTO);
    obj::Piston front_clamp(P_FRONT_CLAMP);
    obj::Piston lback_lift(P_LEFT_BACK_LIFT, true);
    obj::Piston rback_lift(P_RIGHT_BACK_LIFT, true);
    obj::Piston chain_clamp(P_CHAIN_CLAMP, true);

    void init_pistons()
    {
        glb::PTO.initialize();
        glb::front_clamp.initialize();
        glb::chain_clamp.initialize();
        glb::lback_lift.initialize();
        glb::rback_lift.initialize();
        
    }
}


// additional function groups ==================================================================
namespace mtr
{
    // PID objects
    obj::PID s_hold_pid(0.7, 0, 0, 0);

    // Enumerations
    enum BrakeType {coast, hold};
    enum Mode {all, chas, front};
    
    // Function group
    void spin_left(double speed, Mode mode=all) // value range from -127 to 127
    {
        if(mode != chas) glb::left_front.move(speed);
        if(mode != front)
        {
            glb::left_mid_front.move(speed);
            glb::left_mid_back.move(speed);
            glb::left_back.move(speed);
        }
    }

    void spin_right(double speed, Mode mode=all)
    {
        if(mode != chas) glb::right_front.move(speed);
        if(mode != front)
        {
            glb::right_mid_front.move(speed);
            glb::right_mid_back.move(speed);
            glb::right_back.move(speed);
        }
    }

    void spin(double speed, Mode mode=all)
    {
        spin_left(speed, mode);
        spin_right(speed, mode);
    }

    void stop(Mode mode=all)
    {
        spin_left(0, mode);
        spin_right(0, mode);
    }

    void set_brake(BrakeType type, Mode mode=all) // (COAST, HOLD) ()
    {
        auto brake_type = pros::E_MOTOR_BRAKE_COAST;
        if(type == coast) brake_type = pros::E_MOTOR_BRAKE_COAST;
        if(type == hold) brake_type = pros::E_MOTOR_BRAKE_HOLD;

        if(mode != chas)
        {
            glb::left_front.set_brake_mode(brake_type);
            glb::right_front.set_brake_mode(brake_type);
        }
        if(mode != front)
        {
            glb::left_mid_front.set_brake_mode(brake_type);
            glb::left_mid_back.set_brake_mode(brake_type);
            glb::left_back.set_brake_mode(brake_type);
            glb::right_mid_front.set_brake_mode(brake_type);
            glb::right_mid_back.set_brake_mode(brake_type);
            glb::right_back.set_brake_mode(brake_type);
        }
    }

    BrakeType get_brake(Mode mode=chas)
    {
        if(mode == chas)
        {
            if(pros::E_MOTOR_BRAKE_COAST == glb::left_mid_front.get_brake_mode()) return coast;
            else return hold;
        } 
        else
        {
            if(pros::E_MOTOR_BRAKE_COAST == glb::left_front.get_brake_mode()) return coast;
            else return hold;
        }
    }

    double left_pos(Mode mode=chas)
    {
        if(mode == front) return glb::left_front.get_position();
        else if(mode == chas) return (glb::left_mid_front.get_position() + glb::left_mid_back.get_position() + glb::left_back.get_position()) / 3;
        else return (glb::left_front.get_position() + glb::left_mid_front.get_position() + glb::left_mid_back.get_position() + glb::left_back.get_position()) / 4;
    }

    double right_pos(Mode mode=chas)
    {
        if(mode == front) return glb::right_front.get_position();
        else if(mode == chas) return (glb::right_mid_front.get_position() + glb::right_mid_back.get_position() + glb::right_back.get_position()) / 3;
        else return (glb::right_front.get_position() + glb::right_mid_front.get_position() + glb::right_mid_back.get_position() + glb::right_back.get_position()) / 4;
    }

    double pos(Mode mode=chas)
    {
        return (left_pos(mode) + right_pos(mode)) / 2;
    }

    void reset_pos(Mode mode=all)
    {
        if(mode != chas) 
        {
            glb::right_front.tare_position();
            glb::left_front.tare_position();
        }
        if(mode != front)
        {
            glb::left_mid_front.tare_position();
            glb::left_mid_back.tare_position();
            glb::left_back.tare_position();
            glb::right_mid_front.tare_position();
            glb::right_mid_back.tare_position();
            glb::right_back.tare_position();
        }
    }

    double get_temp(Mode mode=chas)
    {
        double front_avg = (glb::left_front.get_temperature() + glb::right_front.get_temperature()) / 2;
        double chas_avg = (glb::left_mid_front.get_temperature() + glb::left_mid_back.get_temperature() + glb::left_back.get_temperature() + glb::right_mid_front.get_temperature() + glb::right_mid_back.get_temperature() + glb::right_back.get_temperature()) / 6;
        if(mode == front) return front_avg;
        else if(mode == chas) return chas_avg;
        else return (front_avg + chas_avg) / 2;
    }

    void spin_dist(double distance, bool eight_motor=true, double speed=127)
    {
        auto mode = eight_motor ? all : chas;
        double target = left_pos() + distance;
        while(left_pos() < target)
        {
            spin(speed, mode);
        }
    }
    
    void time_fwd(double time, double speed)
    {
        long long timer = 0;
        while(timer <= time)
        {
            spin(speed,chas);
            timer += 5;
            pros::delay(5);
        }
        stop();
        

    }
}   

#endif
