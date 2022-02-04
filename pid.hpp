#ifndef __PID_H__
#define __PID_H__

#include "main.h"
#include "global.hpp"


namespace pid
{
    double global_heading = 0;

    obj::PID drive_pid(3, 0, 0, 0.01);
    obj::PID auto_straight_pid(2.0);
    obj::PID rotate_pid(1.1, 0, 0);

    void drive(double distance, bool eight_motor=true, int timeout=5000, double multiplier=1.0, double error_range=25)
    {
        if(eight_motor) glb::PTO.set(false);
        else glb::PTO.set(true);

        glb::imu.set_heading(180);
        double target = mtr::pos() + distance;
        double start_heading = glb::imu.get_heading();
        long long timer = 0;

        bool within_range = false;
        int within_range_time;

        bool slow = false;

        while(timer <= timeout)
        {
            // calculate error/speed
            double cur_pos = mtr::pos();
            bool start_integral = abs(target - cur_pos) < 20;
            double base_speed = multiplier * drive_pid.calculate(target, cur_pos, start_integral);
            double correction_speed = auto_straight_pid.calculate(start_heading, glb::imu.get_heading());
            // apply speeds
            mtr::spin_left(base_speed + correction_speed, mtr::chas);
            mtr::spin_right(base_speed - correction_speed, mtr::chas);

            // print error
            if(timer % 50 == 0) { glb::con.print(0, 0, "Err: %lf        ", target - cur_pos); }


            if((abs(target - cur_pos) <= error_range) && (slow == false))
            {
                slow = true;
                multiplier /= 3;
            }

            // check loop break condition
            if(abs(target - cur_pos) <= error_range)
            {
                if(!within_range)
                {
                    within_range_time = timer + 350;
                    within_range = true;
                }
                else if(timer >= within_range_time) break;
            }
            else within_range = false;

            // increment timer
            timer += 5;
            pros::delay(5);
        }
        // stop chassis once out of loop
        mtr::stop(mtr::chas);

        global_heading += glb::imu.get_heading() - start_heading;
    }

    void rotate(double degrees, bool eight_motor=true, int timeout=5000, double multiplier=1.0, double error_range=0.3)
    {
        if(eight_motor) glb::PTO.set(false);
        else glb::PTO.set(true);

        if(degrees > 0) glb::imu.set_heading(10);
        else glb::imu.set_heading(350);
        double start_heading = glb::imu.get_heading();
        double target_heading = start_heading + degrees;
        long long timer = 0;

        bool within_range = false;
        double within_range_time;

        while(timer <= timeout)
        {
            // calculate error
            double cur_heading = glb::imu.get_heading();
            double error = target_heading - cur_heading;

            // calculate speed
            double speed = multiplier * rotate_pid.calculate(target_heading, cur_heading);
            if(abs(speed) < 50)
            {
                if(speed < 0) speed = -50;
                else speed = 50;
            }

            if(abs(error) < 20)
            {
                speed *= 0.7;
            }

            // apply speeds
            mtr::spin_left(speed);
            mtr::spin_right(-speed);

            // print error
            if(timer % 50 == 0) { glb::con.print(0, 0, "Err: %lf       ", error); }

            // check loop break condition
            if(abs(error) <= error_range)
            {
                if(!within_range)
                {
                    within_range = true;
                    within_range_time = timer;
                }
                else if(within_range_time + 350 <= timer)
                {
                    break;
                }
            }

            timer += 5;
            pros::delay(5);
        }
        mtr::stop(mtr::chas);

        global_heading += glb::imu.get_heading() - start_heading;
    }

    void rotate_to(double degree_to, bool eight_motor=true, int timeout=5000, double multiplier=1.0, double error_range=0.3)
    {
        rotate(degree_to - global_heading, eight_motor, timeout, multiplier, error_range);
    }
}

#endif