#ifndef __DRIVER_H__
#define __DRIVER_H__

#include "main.h"
#include "global.hpp"
#include "autons.hpp"
#include "aut_func.hpp"
#include <string>

using namespace glb;
using namespace mtr;



void PTO_on() // 8 motor
{
    mtr::set_brake(mtr::coast, mtr::front);
    if(glb::PTO.set(true)) 
    {
        glb::con.set_text(3, 0, ".."); 
        mtr::stop(mtr::front);
    }
}

void PTO_off() // lift
{
    mtr::set_brake(mtr::hold, mtr::front);
    if(glb::PTO.set(false)) 
    {
        glb::con.set_text(3, 0, ".");
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
    double left = abs(con.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y)) > 10 ? con.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y) : 0;
    double right = abs(glb::con.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X)) > 10 ? glb::con.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X) : 0;

    if(left || right)
    {
        mtr::spin_left(left + right, mode);
        mtr::spin_right(left - right, mode);
    }

    else
    {
        if(abs(glb::imu.get_pitch()) > 6 && abs(imu.get_pitch()) < 45)
        {
            mtr::spin(glb::imu.get_pitch() * 1.5, mode);
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
        PTO_off();
        mtr::spin(-127, front);
    }
    else if(glb::con.get_digital(pros::E_CONTROLLER_DIGITAL_R2) && !glb::con.get_digital(pros::E_CONTROLLER_DIGITAL_L1) && !glb::con.get_digital(pros::E_CONTROLLER_DIGITAL_L2) && !glb::con.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) 
    {
        PTO_off();
        mtr::spin(127, front);
    }
    else if(!glb::PTO.status())
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

void print_info(int time, std::string aut_name) // lines: 0-2
{
    std::string motorType;
    if(glb::PTO.status())
        motorType = "8M";
    else
        motorType = "6M";

    if(time % 500 == 0 && time % 200 != 0 && time % 200 != 0) glb::con.print(0, 0, "%s | TEMP: %.1lf         ", motorType , mtr::get_temp(mtr::chas));
    if(time % 200 == 0 && time % 500 != 0 && time % 5000 != 0) glb::con.print(1, 0, "%.2f : %.2f", glb::imu.get_heading(), mtr::pos(mtr::chas));
    if(time % 5000 == 0) glb::con.print(2, 0, "AUTON: %s        ", aut_name);
}


void calibrate_robot()
{
    glb::imu.reset();
    mtr::reset_pos(mtr::chas);
    fnc::global_heading = 0;
    fnc::ideal_degree = 0;
}

#endif 