#ifndef __DRIVER_H__
#define __DRIVER_H__

#include "main.h"
#include "global.hpp"
using namespace glb;



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

void arcade_drive()
{
    if(abs(con.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y)) > 10 || abs(con.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X)) > 10)
    {
        chas::spin_left(con.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y) + con.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X));
        chas::spin_right(con.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y) - con.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X));
    }
    else
    {
        chas::stop();
    }
}

void tank_drive()
{
    if(abs(con.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y)) > 10 || abs(con.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y)) > 10)
    {
        chas::spin_left(con.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y));
        chas::spin_right(con.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y));
    }
    else
    {
        chas::stop();
    }
}

void PTO_control()
{
    static bool first_press = true;
    if(glb::con.get_digital(pros::E_CONTROLLER_DIGITAL_A))
    {
        if(first_press)
        {
            first_press = false;
            glb::left_PTO.toggle();
            glb::right_PTO.toggle();
        }
    }
    else first_press = true;
}

#endif