#ifndef __PID_H__
#define __PID_H__

#include "main.h"
#include "global.hpp"
#include <string.h>
#include <math.h>


namespace fnc
{
    #define AUTO_STRAIGHT_KP 4
    #define AUTO_STRAIGHT_KI 0.05

    double global_heading = 0;

    double drive(double distance, double max_speed=120, int timeout=5000, double multiplier=1.0)
    {
        // variables
        #define DRIVE_KP 0.5
        #define DRIVE_KI 0.004
        #define DRIVE_KD 9

        mtr::Mode mode = glb::PTO.status() ? mtr::chas : mtr::all;
        glb::imu.set_heading(180);
        double start_heading = glb::imu.get_heading();
        
        double target = mtr::pos() + distance;
        double error = target - mtr::pos();
        double integral = 0;
        double last_error;

        double straight_integral = 0;

        bool within_range = false;
        double within_range_err = 1.0;
        int within_range_exit = 5000;
        int within_range_time;

        int time = 0;
        // control loop
        while(time < timeout)
        {
            // update variables
            last_error = error;
            error = target - mtr::pos();
            integral += (abs(error) * DRIVE_KP < 30) * error;
            double derivative = error - last_error;
            straight_integral += start_heading - glb::imu.get_heading();

            // speed variables
            double base_speed = error * DRIVE_KP + integral * DRIVE_KI + derivative * DRIVE_KD;
            double correction_speed = (start_heading - glb::imu.get_heading()) * AUTO_STRAIGHT_KP + (straight_integral * AUTO_STRAIGHT_KI);
            
            // apply speeds
            if(abs(base_speed) > max_speed) base_speed = multiplier * (base_speed > 0 ? max_speed : -max_speed);
            mtr::spin_left(base_speed + correction_speed, mode);
            mtr::spin_right(base_speed - correction_speed, mode);

            // print error
            if(time % 50 == 0) { glb::con.print(0, 0, "Err: %lf        ", error); }

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
            pros::delay(5);
            time += 5;
        }
        // stop motors once out of loop
        mtr::stop(mode);
        global_heading += glb::imu.get_heading() - start_heading;
        return error;
    }

    void spin_dist(double distance, double speed=124.5, int timeout=5000)
    {
        // variables
        glb::imu.set_heading(180);
        double start_heading = glb::imu.get_heading();
        double target = mtr::pos() + distance;
        mtr::Mode mode = glb::PTO.status() ? mtr::chas : mtr::all;
        speed = distance < 0 ? -abs(speed) : abs(speed);

        double straight_integral = 0;

        int time = 0;

        // control loop
        while((distance < 0 ? mtr::pos() > target : mtr::pos() < target) && time < timeout)
        {
            // calculate auto straight and apply speeds
            straight_integral += start_heading - glb::imu.get_heading();
            double auto_straight = (start_heading - glb::imu.get_heading()) * AUTO_STRAIGHT_KP + (straight_integral * AUTO_STRAIGHT_KI);
            mtr::spin_left(speed + auto_straight, mode);
            mtr::spin_right(speed - auto_straight, mode);

            pros::delay(1);
            time += 1;
        }

        // stop motors once out of loop
        mtr::stop(mode);
        global_heading += glb::imu.get_heading() - start_heading;
    }
   
    void rotate(double degrees, int timeout=3000, float multiplier=1.0)
    {
        #define ROTATE_KP 1.2
        #define ROTATE_KI 0.005
        #define ROTATE_KD 5

        // variables
        mtr::Mode mode = glb::PTO.status() ? mtr::chas : mtr::all;
        double start_heading = degrees > 0 ? 25 : 335;
        glb::imu.set_heading(start_heading);

        double target = glb::imu.get_heading() + degrees;
        double error = target - glb::imu.get_heading();
        double integral = 0;
        double last_error;

        bool within_range = false;
        double within_range_err = 0.05;
        int within_range_exit = 50;
        int within_range_time;

        int time = 0;

        // control loop
        while(time < timeout)
        {
            // update variables
            last_error = error;
            error = target - glb::imu.get_heading();
            if(abs(error) < 45) integral += error;
            double derivative = error - last_error;

            // speed variables
            double speed = multiplier * (error * ROTATE_KP + integral * ROTATE_KI + derivative * ROTATE_KD);
            
            // apply speeds
            mtr::spin_left(speed, mode);
            mtr::spin_right(-speed, mode);

            // print error
            if(time % 50 == 0) { glb::con.print(0, 0, "Err: %f        ", speed); }

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
            pros::delay(5);
            time += 5;
        }
        // stop robot after loop
        mtr::stop(mode);
        global_heading += glb::imu.get_heading() - start_heading;
    }

    void rotate_to(double degree_to, int timeout=5000, float multiplier=1.0)
    {
        double degree = degree_to - global_heading;
        degree = (degree > 180) ? -(360 - degree) : (360 + degree); // optimize the turn direction
        rotate(degree, timeout, multiplier);
    }

    inline void spin_lift(double distance, double speed=600) // negative = up, positive = down
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
