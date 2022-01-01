#ifndef __GLOBALS_H__
#define __GLOBALS_H__

#include "main.h"


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
            extended = start_status;
            set(start_status);
        }

        // methods
        void set(bool extend_val)
        {
            if(extended != extend_val)
            {
                extended = extend_val;
                pneu.set_value(extend_val);
            }
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


    class Inertial
    {
    private:
        pros::Imu imu;
        double heading;
        double last_heading;
    public:
        Inertial(int port_num) : imu(port_num), last_heading(180), heading(0)
        {
            imu.set_heading(180);
        }

        void reset()
        {
            imu.set_heading(180);
            heading = 0;
            last_heading = 180;
        }

        void update()
        {
            heading += imu.get_heading() - last_heading;
            last_heading = imu.get_heading();
            imu.set_heading(180);
        }

        double get_heading(bool update_heading=true)
        {
            if(update_heading) update();
            return heading;
        }

        double get_pitch()
        {
            return imu.get_pitch();
        }

        void set_heading(double heading)
        {
            last_heading = heading;
            this->heading = heading;
        }
    };
}


// Global variable and value definitions =======================================================
namespace glb
{
    // motors
    #define P_LEFT_FRONT 1 // PTO left
    #define P_LEFT_MID_FRONT 13
    #define P_LEFT_MID_BACK 19
    #define P_LEFT_BACK 15
    #define P_RIGHT_FRONT 6  // PTO right
    #define P_RIGHT_MID_FRONT 9
    #define P_RIGHT_MID_BACK 11
    #define P_RIGHT_BACK 12
    // pistons
    #define P_LPTO 'A'
    #define P_RPTO 'B'
    #define P_BACK_HOOK 'C'
    #define P_FRONT_LIFT 'D'
    // misc
    #define P_IMU 7

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
    obj::Inertial imu(P_IMU);
    pros::Controller con(pros::E_CONTROLLER_MASTER);
    // piston
    obj::Piston left_PTO(P_LPTO);
    obj::Piston right_PTO(P_RPTO);
    obj::Piston back_hook(P_BACK_HOOK);
    obj::Piston front_lift(P_FRONT_LIFT);
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

    void spin_dist(double distance, double speed=127)
    {
        double target = left_pos() + distance;
        while(left_pos() < target)
        {
            spin(speed);
        }
    }
}

namespace pid
{
    obj::PID drive_pid(2.0, 0, 0, 0.05);
    obj::PID auto_straight_pid(2.0);
    obj::PID rotate_pid(2.0, 0, 0);

    void drive(double distance, int timeout=5000, double multiplier=1.0, double error_range=5)
    {
        double target = mtr::pos() + distance;
        double start_heading = glb::imu.get_heading();
        long long timer = 0;

        bool within_range = false;
        int within_range_time;

        while(timer <= timeout)
        {
            // calculate error/speed
            double cur_pos = mtr::pos();
            bool start_integral = target - cur_pos < 20;
            double base_speed = multiplier * drive_pid.calculate(target, cur_pos, start_integral);
            double correction_speed = auto_straight_pid.calculate(start_heading, glb::imu.get_heading());
            // apply speeds
            mtr::spin_left(base_speed + correction_speed, mtr::chas);
            mtr::spin_right(base_speed - correction_speed, mtr::chas);

            // print error
            if(timer % 50 == 0) { glb::con.print(1, 0, "Err: %lf", target - cur_pos); }

            // check loop break condition
            if(target - cur_pos <= error_range)
            {
                if(!within_range)
                {
                    within_range_time = timer + 200;
                    within_range = true;
                }
                else if(timer >= within_range_time) break;
            }
            else within_range = false;

            // increment timer
            timer += 5;
            pros::delay(5);
        }
        // stop chassis once out of loop
        mtr::stop(mtr::chas);
    }

    void rotate(double degrees, int timeout=5000, double multiplier=1.0, double error_range=0.3)
    {
        double start_heading = glb::imu.get_heading();
        double target_heading = start_heading + degrees;
        long long timer = 0;

        bool count_integral = false;
        bool integral_range = 2;

        bool within_range = false;
        double within_range_time;

        while(timer <= timeout)
        {
            // calculate error
            double cur_heading = glb::imu.get_heading();
            double error = target_heading - cur_heading;

            // calculate speed
            if(abs(error) < integral_range)
                count_integral = true;
            double speed = multiplier * rotate_pid.calculate(target_heading, cur_heading, count_integral);

            // apply speeds
            mtr::spin_left(speed);
            mtr::spin_right(-speed);

            // print error
            if(timer % 50 == 0) { glb::con.print(1, 0, "Err: %lf", error); }

            // check loop break condition
            if(abs(error) <= error_range)
            {
                if(!within_range)
                {
                    within_range = true;
                    within_range_time = timer;
                }
                else if(within_range_time + 200 <= timer)
                {
                    break;
                }
            }

            timer += 5;
            pros::delay(5);
        }
        mtr::stop(mtr::chas);
    }

    void rotate_to(double degree_to, int timeout=5000, double multiplier=1.0, double error_range=0.3)
    {
        rotate(degree_to - glb::imu.get_heading(), timeout, multiplier, error_range);
    }
}

#endif