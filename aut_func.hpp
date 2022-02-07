#ifndef __PID_H__
#define __PID_H__

#include "main.h"
#include "global.hpp"
#include <math.h>

#define PI 3.14159265359

namespace fnc
{
    #define AUTO_STRAIGHT_KP 3
    double global_heading = 0;

    void drive(double distance, int timeout=5000, double max_speed=112, double offset=350)
    {
        // variables
        glb::imu.set_heading(180);
        double start_heading = glb::imu.get_heading();
        mtr::Mode mode = glb::PTO.status() ? mtr::chas : mtr::all;
        double target = mtr::pos(mode) + distance;

        bool within_range = false;
        double within_range_err = 10;
        int within_range_exit = 300;
        int within_range_time;

        int time = 0;
        // control loop
        while(time < timeout)
        {
            // update variables
            double current = mtr::pos(mode);
            double error = target - current; 
            double speed;

            // calculate speeds
            if(abs(error) >= offset)
                speed = max_speed;
            else if(abs(error) >= 50 && abs(error) < offset)
                speed = max_speed * sin((PI * abs(error)) / (2 * offset));
            else
                speed = ((87.5 * abs(error)) / offset) + max_speed * sin((PI * 50) / (2 * offset)) - (4375 / offset);
            
            speed = error < 0 ? -speed : speed;
            double auto_straight = (start_heading - glb::imu.get_heading()) * AUTO_STRAIGHT_KP;
            
            // apply speeds
            mtr::spin_left(speed + auto_straight, mode);
            mtr::spin_right(speed - auto_straight, mode);
            
            // check for exit
            if(abs(error) <= within_range_err)
            {
                if(!within_range)
                {
                    within_range = true;
                    within_range_time = time;
                }
                else if(within_range_time + within_range_exit <= time)
                {
                    break;
                }
            }
            else within_range = false;

            // increment time
            pros::delay(1);
            time += 1;
        }
        // stop motors once out of loop
        mtr::stop(mode);
        global_heading += glb::imu.get_heading() - start_heading;
    }

    void spin_dist(double distance, double speed=127, int timeout=5000)
    {
        // variables
        glb::imu.set_heading(180);
        double start_heading = glb::imu.get_heading();
        double target = mtr::pos() + distance;
        mtr::Mode mode = glb::PTO.status() ? mtr::chas : mtr::all;
        speed = distance < 0 ? -abs(speed) : abs(speed);

        int time = 0;
        // control loop
        while((distance < 0 ? mtr::pos() > target : mtr::pos() < target) && time < timeout)
        {
            // calculate auto straight and apply speeds
            double auto_straight = (start_heading - glb::imu.get_heading()) * AUTO_STRAIGHT_KP;
            mtr::spin_left(speed + auto_straight, mode);
            mtr::spin_right(speed - auto_straight, mode);

            pros::delay(1);
            time += 1;
        }
        // stop motors once out of loop
        mtr::stop(mode);
        global_heading += glb::imu.get_heading() - start_heading;
    }

    void rotate(double degrees, int timeout=5000, float multiplier=1.0)
    {
        // variables
        double start_heading = degrees > 0 ? 310 : 10;
        glb::imu.set_heading(start_heading);
        double target = glb::imu.get_heading() + degrees;
        mtr::Mode mode = glb::PTO.status() ? mtr::chas : mtr::all;

        bool within_range = false;
        bool within_range_err = 0.1;
        bool within_range_exit = 300;
        bool within_range_time;

        int time = 0;
        // control loop
        while(time < timeout)
        {
            // calculate variables
            double error = target - glb::imu.get_heading();
            double speed = (multiplier * 30) * log(0.25 * (abs(error) + 4)) + 5;
            speed = error < 0 ? -speed : speed;

            // apply speeds
            mtr::spin_left(speed, mode);
            mtr::spin_right(speed, mode);

            // check for exit
            if(error <= within_range_err)
            {
                if(!within_range)
                {
                    within_range = true;
                    within_range_time = time;
                }
                else if(within_range_time + within_range_exit <= time)
                {
                    break;
                }
            }
            else within_range = false;

            // increment time
            pros::delay(1);
            time += 1;
        }
    }

    void rotate_to(double degree_to, int timeout=5000, float multiplier=1.0)
    {
        rotate(degree_to - global_heading, timeout, multiplier);
    }

    inline void spin_lift(double distance, double speed=127) // negative = up, positive = down
    {
        speed = distance < 0 ? -abs(speed) : abs(speed);
        glb::PTO.set(true);
        mtr::set_brake(mtr::hold, mtr::front);
        glb::left_front.move_relative(distance, speed);
        glb::right_front.move_relative(distance, speed);
    }

    void toggle_2bar()
    {
        glb::lback_lift.toggle();
        glb::rback_lift.toggle();
    }
}

#endif