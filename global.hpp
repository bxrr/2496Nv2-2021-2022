// What goes into the global file: Any global variables or groupings which allow for more convenient use.
// Calculations, like PIDs and such should not go in here.

#ifndef __GLOBALS_H__
#define __GLOBALS_H__

#include "main.h"


// additional class definitions ================================================================
namespace obj
{
    class Piston
    {
    private: pros::ADIDigitalOut pneu; bool extended;
    public:
    // initialization constructor
        Piston(int port, bool extend=false) : pneu(port), extended(extend) {set(extend);}

        // methods
        void set(bool extend_val)
        {
            extended = extend_val;
            pneu.set_value(extend_val);
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
    pros::Imu imu(P_IMU);
    pros::Controller con(pros::E_CONTROLLER_MASTER);
    // piston
    obj::Piston left_PTO(P_LPTO);
    obj::Piston right_PTO(P_RPTO);
}


// additional function groups ==================================================================
#define COAST 0
#define HOLD 1
namespace chas
{
    void spin_left(double speed, bool eight_motor=false) // value range from -127 to 127
    {
        if(eight_motor) glb::left_front.move(speed);
        glb::left_mid_front.move(speed);
        glb::left_mid_back.move(speed);
        glb::left_back.move(speed);
    }

    void spin_right(double speed, bool eight_motor)
    {
        if(eight_motor) glb::right_front.move(speed);
        glb::right_mid_front.move(speed);
        glb::right_mid_back.move(speed);
        glb::right_back.move(speed);
    }

    void stop(bool eight_motor=true)
    {
        spin_left(0, eight_motor);
        spin_right(0, eight_motor);
    }

    void stop_front()
    {
        glb::right_front.move(0);
        glb::left_front.move(0);
    }

    void spin_front(double speed)
    {
        glb::right_front.move(speed);
        glb::left_front.move(speed);
    }


    void set_brake(short int brake_num) // COAST, HOLD
    {
        auto brake_type = pros::E_MOTOR_BRAKE_COAST;
        if(brake_num == COAST) brake_type = pros::E_MOTOR_BRAKE_COAST;
        if(brake_num == HOLD) brake_type = pros::E_MOTOR_BRAKE_HOLD;

        glb::left_front.set_brake_mode(brake_type);
        glb::left_mid_front.set_brake_mode(brake_type);
        glb::left_mid_back.set_brake_mode(brake_type);
        glb::left_back.set_brake_mode(brake_type);
        glb::right_front.set_brake_mode(brake_type);
        glb::right_mid_front.set_brake_mode(brake_type);
        glb::right_mid_back.set_brake_mode(brake_type);
        glb::right_back.set_brake_mode(brake_type);
    }

    double left_pos()
    {
        return (glb::left_front.get_position() + glb::left_mid_front.get_position() + glb::left_mid_back.get_position() + glb::left_back.get_position()) / 4;
    }

    double right_pos()
    {
        return (glb::right_front.get_position() + glb::right_mid_front.get_position() + glb::right_mid_back.get_position() + glb::right_back.get_position()) / 4;
    }

    double get_temp()
    {
        return (glb::left_front.get_temperature() + glb::left_mid_front.get_temperature() + glb::left_mid_back.get_temperature() + glb::left_back.get_temperature() + 
                glb::right_front.get_temperature() + glb::right_mid_front.get_temperature() + glb::right_mid_back.get_temperature() + glb::right_back.get_temperature()) / 8;
    }
}

#endif