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

void arcade_drive(bool eight_motor)
{
    if(abs(con.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y)) > 10 || abs(con.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X)) > 10)
    {
        chas::spin_left(con.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y) + con.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X), eight_motor);
        chas::spin_right(con.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y) - con.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X), eight_motor);
    }
    else
    {
        chas::stop(eight_motor);
    }
}

void tank_drive(bool eight_motor)
{
    if(abs(con.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y)) > 10 || abs(con.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y)) > 10)
    {
        chas::spin_left(con.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y), eight_motor);
        chas::spin_right(con.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y), eight_motor);
    }
    else
    {
        chas::stop(eight_motor);
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
            chas::stop_front();
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
        lb::right_PTO.set(true);
        chas::spin_front(127);
    }
    else if(glb::con.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) 
    {
        glb::left_PTO.set(true);
        glb::right_PTO.set(true);
        chas::spin_front(-127);
    }
    else chas::stop_front();
}

#endif