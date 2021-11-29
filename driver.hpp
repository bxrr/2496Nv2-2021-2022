#ifndef __DRIVER_H__
#define __DRIVER_H__

#include "main.h"
#include "global.hpp"
using namespace glb;
using namespace mtr;



bool disable_all()
{
    static bool disabled = false;
    static bool first_press = true;
    if(con.get_digital(pros::E_CONTROLLER_DIGITAL_UP))
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

void arcade_drive(bool all_motors)
{
    Mode mode = all;
    if(all_motors) mode = all;
    else mode = chas;
    
    if(abs(con.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y)) > 10 || abs(con.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X)) > 10)
    {
        mtr::spin_left(con.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y) + con.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X), mode);
        mtr::spin_right(con.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y) - con.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X), mode);
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
    
    if(abs(con.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y)) > 10 || abs(con.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y)) > 10)
    {
        mtr::spin_left(con.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y), mode);
        mtr::spin_right(con.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y), mode);
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