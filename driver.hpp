#ifndef __DRIVER_H__
#define __DRIVER_H__

#include "main.h"
#include "global.hpp"
#include "autons.hpp"
#include <string>

using namespace glb;
using namespace mtr;


 
typedef void(*fptr)(); // function pointer declaration

void PTO_on() // access lift
{
    if(glb::PTO.set(true)) 
    {
        glb::con.set_text(3, 0, "."); 
        mtr::set_brake(mtr::hold, mtr::front);
        mtr::stop(mtr::front);
    }
}

void PTO_off() // 8 motor drive
{
    if(glb::PTO.set(false)) 
    {
        glb::con.set_text(3, 0, "..");
        mtr::set_brake(mtr::coast, mtr::front);
        mtr::stop(mtr::front);
    }
}

bool disable_all()
{
    static bool disabled = false;
    static bool first_press = true;
    if(glb::con.get_digital(pros::E_CONTROLLER_DIGITAL_UP))
    {
        if(first_press)
        {
            first_press = false;
            disabled = !disabled;
        }
    }
    else first_press = true;
    return disabled;
}

fptr auton_selector(std::string &aut_name)
{
    short int selected = 0;
    long long timer = 0;

    bool left_first = true;
    bool right_first = true;

    while(true)
    {
        if(!glb::con.get_digital(pros::E_CONTROLLER_DIGITAL_A))
        {
            if(timer % 10 == 0) glb::con.print(0, 0, "Select: %s         ", aut::auton_names.at(selected));

            if(glb::con.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT))
            {
                if(left_first)
                {
                    left_first = false;
                    if(selected > 0) selected--;
                }
            }
            else left_first = true;

            if(glb::con.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT))
            {
                if(right_first)
                {
                    right_first = false;
                    if(selected < aut::auton_names.size()-1) selected++;
                }
            }
            else right_first = true;
        }
        else
        {
            pros::delay(50);
            glb::con.print(0, 0, "Selected           ");
            pros::delay(2000);
            aut_name = aut::auton_names.at(selected);
            return aut::auton_calls.at(selected);
        }

        pros::delay(1);
        timer++;
    }
}

void arcade_drive(bool all_motors)
{
    Mode mode;
    if(all_motors) mode = all;
    else mode = chas;
    
    if(abs(glb::con.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y)) > 10 || abs(glb::con.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X)) > 10)
    {
        mtr::spin_left(con.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y) + glb::con.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X), mode);
        mtr::spin_right(con.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y) - glb::con.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X), mode);
    }
    else
    {
        if(abs(glb::imu.get_roll()) > 6 && imu.get_roll() < 25)
        {
            mtr::spin(-glb::imu.get_roll() * 1.5, mode);
        }
        else
        {
            mtr::stop(mode);
        }
    }
}

void tank_drive(bool all_motors)
{
    Mode mode = all;
    if(all_motors) mode = all;
    else mode = chas;
    
    if(abs(glb::con.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y)) > 10 || abs(glb::con.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y)) > 10)
    {
        mtr::spin_left(glb::con.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y), mode);
        mtr::spin_right(glb::con.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y), mode);
    }
    else
    {
        if(abs(glb::imu.get_roll()) > 6)
        {
            mtr::spin(-glb::imu.get_roll() * 1.5, mode);
        }
        else
        {
            mtr::stop(mode);
        }
    }
}

// controls
void PTO_control()
{
    static bool first_press = true;
    if(glb::con.get_digital(pros::E_CONTROLLER_DIGITAL_L1) && glb::con.get_digital(pros::E_CONTROLLER_DIGITAL_R2))
    {
        if(first_press)
        {
            first_press = false;
            if(glb::PTO.status())
            {
                PTO_off();
            }
            else
            {
                PTO_on();
            }
            mtr::stop(front);
        }
    }
    else first_press = true;
}

void chainbar_control()
{
    if(glb::con.get_digital(pros::E_CONTROLLER_DIGITAL_R1) && !glb::con.get_digital(pros::E_CONTROLLER_DIGITAL_L1) && !glb::con.get_digital(pros::E_CONTROLLER_DIGITAL_L2) && !glb::con.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) 
    {
        PTO_on();
        mtr::spin(127, front);
    }
    else if(glb::con.get_digital(pros::E_CONTROLLER_DIGITAL_R2) && !glb::con.get_digital(pros::E_CONTROLLER_DIGITAL_L1) && !glb::con.get_digital(pros::E_CONTROLLER_DIGITAL_L2) && !glb::con.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) 
    {
        PTO_on();
        mtr::spin(-127, front);
    }
    else if(glb::PTO.status())
    {
        mtr::stop(front);
    }

    static bool first_press = true;
    if(glb::con.get_digital(pros::E_CONTROLLER_DIGITAL_L2) && glb::con.get_digital(pros::E_CONTROLLER_DIGITAL_R2))
    {
        if(first_press)
        {
            first_press = false;
            glb::chain_clamp.toggle();
        }
    }
    else first_press = true;

}

void twobar_control()
{
    static bool first_press = true;
    if(glb::con.get_digital(pros::E_CONTROLLER_DIGITAL_L2) && glb::con.get_digital(pros::E_CONTROLLER_DIGITAL_R1))
    {
        if(first_press)
        {
            first_press = false;
            glb::lback_lift.toggle();
            glb::rback_lift.toggle();
        }
    }
    else first_press = true;
}

void clamp_control()
{
    static bool first_press = true;
    if(glb::con.get_digital(pros::E_CONTROLLER_DIGITAL_L2) && glb::con.get_digital(pros::E_CONTROLLER_DIGITAL_L1))
    {
        if(first_press)
        {
            first_press = false;
            front_clamp.toggle();
        }
    }
    else first_press = true;
}

void cover_control()
{
    static bool first_press = true;
    if(glb::con.get_digital(pros::E_CONTROLLER_DIGITAL_L1) && glb::con.get_digital(pros::E_CONTROLLER_DIGITAL_R1))
    {
        if(first_press)
        {
            first_press = false;
            goal_cover.toggle();
        }
    }
    else first_press = true;
}

void print_info(int time) // lines: 0-2
{
    std::string eight_motor;

    if(glb::PTO.status())
        eight_motor = "false";
    else
        eight_motor = "true";

    if(time % 400 == 0 && time % 500 != 0 && time % 1000 != 0) glb::con.print(0, 0, "8M DRIVE: %s           ", eight_motor);
    if(time % 500 == 0 && time % 1000 != 0) glb::con.print(1, 0, "inert: %.2f           ", glb::imu.get_heading());
    if(time % 1000 == 0) glb::con.print(2, 0, "TEMP: %.1lf        ", mtr::get_temp(mtr::chas));
}

#endif 