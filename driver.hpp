#ifndef __DRIVER_H__
#define __DRIVER_H__

#include "main.h"
#include "global.hpp"
#include "autons.hpp"

using namespace glb;
using namespace mtr;



typedef void(*fptr)(); // function pointer declaration

void PTO_on() // access lift
{
    if(glb::PTO.set(true)) glb::con.set_text(3, 0, ".");
}

void PTO_off() // 8 motor drive
{
    if(glb::PTO.set(false)) glb::con.set_text(3, 0, "..");
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

fptr auton_selector()
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
            pros::delay(1500);
            return aut::auton_list.at(selected);
        }

        pros::delay(1);
        timer++;
    }
}

void s_hold(Mode mode=chas)
{
    if(abs(imu.get_pitch()) > 4.0)
    {
        double speed = s_hold_pid.calculate(0, glb::imu.get_pitch());
        mtr::spin(speed, mode);
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
        mtr::stop(mode);
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
        mtr::stop(mode);
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
        mtr::spin(-127, front);
    }
    else if(glb::con.get_digital(pros::E_CONTROLLER_DIGITAL_R2) && !glb::con.get_digital(pros::E_CONTROLLER_DIGITAL_L1) && !glb::con.get_digital(pros::E_CONTROLLER_DIGITAL_L2) && !glb::con.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) 
    {
        PTO_on();
        mtr::spin(127, front);
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

void print_temp(Mode mode=chas, int line=0) // lines: 0-2
{
    glb::con.print(line, 0, "TEMP: %.1lf        ", mtr::get_temp(mode));
}

#endif