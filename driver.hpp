#ifndef __DRIVER_H__
#define __DRIVER_H__

#include "main.h"
#include "global.hpp"
#include "autons.hpp"
using namespace glb;
using namespace mtr;
using namespace aut;


typedef void(*fptr)(); // function pointer declaration

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

void init_pistons()
{
    glb::left_PTO.initialize();
    glb::right_PTO.initialize();
    glb::back_hook.initialize();
    glb::front_lift.initialize();
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
            if(timer % 55 == 0) glb::con.print(0, 1, "Select: %s", aut::auton_names.at(selected));

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
            glb::con.clear();
            pros::delay(50);
            glb::con.print(0, 1, "Selected");
            pros::delay(200);
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
    Mode mode = all;
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

bool PTO_control()
{
    static bool first_press = true;
    if(glb::con.get_digital(pros::E_CONTROLLER_DIGITAL_R1))
    {
        if(first_press)
        {
            first_press = false;
            glb::left_PTO.set(false);
            glb::right_PTO.set(false);
            mtr::stop(front);
        }
    }
    else first_press = true;
    return !(glb::left_PTO.status());
}

void chainbar_control()
{
    if(glb::con.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) 
    {
        glb::left_PTO.set(true);
        glb::right_PTO.set(true);
        mtr::spin(127, front);
    }
    else if(glb::con.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) 
    {
        glb::left_PTO.set(true);
        glb::right_PTO.set(true);
        mtr::spin(-127, front);
    }
    else mtr::stop(front);
}

void print_temp(Mode mode=chas, int line=1)
{
    glb::con.print(0, line, "%.2f", mtr::get_temp(mode));
}

#endif