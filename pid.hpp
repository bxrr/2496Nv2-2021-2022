#ifndef __PID_H__
#define __PID_H__

#include "main.h"
#include "global.hpp"


namespace pid
{
    double global_heading = 0;

    obj::PID drive_pid(2.0, 0, 0, 0.05);
    obj::PID auto_straight_pid(2.0);
    obj::PID rotate_pid(2.0, 0, 0);

    void drive(double distance, int timeout=5000, double multiplier=1.0, double error_range=5)
    {
        glb::imu.set_heading(180);
        double target = mtr::pos() + distance;
        double start_heading = glb::imu.get_heading();
        long long timer = 0;

        bool within_range = false;
        int within_range_time;

        while(timer <= timeout)
        {
            // calculate error/speed
            double cur_pos = mtr::pos();
            bool start_integral = target - cur_pos < 20;
            double base_speed = multiplier * drive_pid.calculate(target, cur_pos, start_integral);
            double correction_speed = auto_straight_pid.calculate(start_heading, glb::imu.get_heading());
            // apply speeds
            mtr::spin_left(base_speed + correction_speed, mtr::chas);
            mtr::spin_right(base_speed - correction_speed, mtr::chas);

            // print error
            if(timer % 50 == 0) { glb::con.print(0, 0, "Err: %lf        ", target - cur_pos); }

            // check loop break condition
            if(target - cur_pos <= error_range)
            {
                if(!within_range)
                {
                    within_range_time = timer + 200;
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

    void rotate(double degrees, int timeout=5000, double multiplier=1.0, double error_range=0.3)
    {
        if(degrees > 0) glb::imu.set_heading(10);
        else imu.set_heading(350);
        double start_heading = glb::imu.get_heading();
        double target_heading = start_heading + degrees;
        long long timer = 0;

        bool count_integral = false;
        bool integral_range = 2;

        bool within_range = false;
        double within_range_time;

        while(timer <= timeout)
        {
            // calculate error
            double cur_heading = glb::imu.get_heading();
            double error = target_heading - cur_heading;

            // calculate speed
            if(abs(error) < integral_range)
                count_integral = true;
            double speed = multiplier * rotate_pid.calculate(target_heading, cur_heading, count_integral);

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
                else if(within_range_time + 200 <= timer)
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

    void rotate_to(double degree_to, int timeout=5000, double multiplier=1.0, double error_range=0.3)
    {
        rotate(degree_to - global_heading, timeout, multiplier, error_range);
    }
}

#endif