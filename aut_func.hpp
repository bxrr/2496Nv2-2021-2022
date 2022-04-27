#ifndef __PID_H__
#define __PID_H__

#include "main.h"
#include "global.hpp"
#include <string.h>
#include <math.h>


namespace fnc
{
    #define IMU_STRAIGHT_KP 40
    #define MTR_STRAIGHT_KP 0

    double global_heading = 0;

    double drive(double distance, double max_speed=120, int timeout=3500, double multiplier=1.0, int within_range_exit=100)
    {
        // variables
        #define DRIVE_KP 0.6
        #define DRIVE_KI 0.02
        #define DRIVE_KD 9

        mtr::Mode mode = glb::PTO.status() ? mtr::all : mtr::chas;
        mtr::set_brake(mtr::coast, mode);

        glb::imu.set_heading(180);
        double start_heading = glb::imu.get_heading();
        
        double target = mtr::pos() + distance;
        double error = target - mtr::pos();
        double integral = 0;
        double last_error;

        double left_start = mtr::left_pos();
        double right_start = mtr::right_pos();

        bool within_range = false;
        double within_range_err = 1.5;
        int within_range_time;

        bool negative = distance < 0;
        bool start_integral = false;

        int time = 0;
        // control loop
        while(time < timeout)
        {
            // update variables
            last_error = error;
            error = target - mtr::pos();
            integral += (start_integral) ? error : 0;
            double derivative = error - last_error;
            
            double straight_error = start_heading - glb::imu.get_heading();
            
            if(negative && error > 0)
            {
                start_integral = true;
            }
            else if(!negative && error < 0)
            {
                start_integral = true;
            }

            // speed variables
            double base_speed = error * DRIVE_KP + integral * DRIVE_KI + derivative * DRIVE_KD;
            if(abs(base_speed) > max_speed) base_speed = multiplier * (base_speed > 0 ? max_speed : -max_speed);
            double correction_speed = abs(base_speed / max_speed) * (straight_error * IMU_STRAIGHT_KP + 
                                      ((mtr::right_pos() - right_start) - (mtr::left_pos() - left_start)) * MTR_STRAIGHT_KP);
            
            // apply speeds
            mtr::spin_left(base_speed + correction_speed, mode);
            mtr::spin_right(0.92 * base_speed - correction_speed, mode);

            // print error
            if(time % 50 == 0) { glb::con.print(0, 0, "Err: %lf        ", error); }

            // check for exit
            if(abs(error) <= within_range_err || (abs(error) < 300 && abs(glb::left_back.get_actual_velocity()) < 2))
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
        mtr::Mode mode = glb::PTO.status() ? mtr::all : mtr::chas;
        mtr::set_brake(mtr::coast, mode);

        speed = distance < 0 ? -abs(speed) : abs(speed);

        double straight_integral = 0;
        float correction_slew = 0.0;
        double left_start = mtr::left_pos();
        double right_start = mtr::right_pos();

        int time = 0;

        // control loop
        while((distance < 0 ? mtr::pos() > target : mtr::pos() < target) && time < timeout)
        {
            // calculate auto straight and apply speeds
            if(correction_slew < 1) correction_slew += 0.01;
            double correction_speed = correction_slew * (start_heading - glb::imu.get_heading()) * IMU_STRAIGHT_KP + 
                                      ((mtr::right_pos() - right_start) - (mtr::left_pos() - left_start)) * MTR_STRAIGHT_KP;
            mtr::spin_left(speed + correction_speed, mode);
            mtr::spin_right(speed - correction_speed, mode);

            if(abs(target - mtr::pos()) < 300 && abs(glb::left_back.get_actual_velocity()) < 2 && time > 1000)
            {
                break;
            }

            pros::delay(1);
            time += 1;
        }

        // stop motors once out of loop
        mtr::stop(mode);
        global_heading += glb::imu.get_heading() - start_heading;
    }
   
    void rotate(double degrees, int timeout=3500, float multiplier=1.0, double within_range_err=0.2)
    {
        // variables
        double start_heading = degrees > 0 ? 25 : 335;
        glb::imu.set_heading(start_heading);
        double target = glb::imu.get_heading() + degrees;
        mtr::Mode mode = glb::PTO.status() ? mtr::all : mtr::chas;
        mtr::set_brake(mtr::coast, mode);

        bool within_range = false;
        int within_range_exit = 200;
        int within_range_time;

        int time = 0;

        // control loop
        while(time < timeout)
        {
            // calculate variables
            double error = target - glb::imu.get_heading();
            double speed = multiplier * 25.5 * log(0.25 * (abs(error) + 4)) + 5;
            speed = error < 0 ? -speed : speed;

            // apply speeds
            mtr::spin_left(speed, mode);
            mtr::spin_right(-speed, mode);

            // print error
            if(time % 50 == 0) glb::con.print(0, 0, "err: %f      ", error);

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

        global_heading += glb::imu.get_heading() - start_heading;
    }

    void rotate_to(double degree_to, int timeout=3500, float multiplier=1.0, double within_range_err=0.2)
    {
        double degree = degree_to - global_heading;
        degree = (degree > 180) ? -(360 - degree) : ((degree < -180) ? (360 + degree) : (degree)); // optimize the turn direction
        rotate(degree, timeout, multiplier, within_range_err);
    }

    inline void spin_lift(double distance, double speed=600) // negative = up, positive = down
    {
        glb::PTO.set(false);
        speed = distance < 0 ? -abs(speed) : abs(speed);
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
