#include "main.h"
#include "driver.hpp"
#include "global.hpp"
#include "autons.hpp"
using namespace pros;
using namespace glb; // global variables


// global variables
void (*auton)() = aut::auton_list.at(0);

// functions
void initialize() 
{
    con.clear();
    pros::lcd::set_text(0, "2496NextLevelNinjas");
    mtr::set_brake(coast, all);

    auton = auton_selector();
    glb::con.clear();
    mtr::set_brake(hold, front);
    mtr::reset_pos();
    glb::init_pistons();
}

void disabled() {}

void competition_initialize() 
{
    auton = auton_selector();
    glb::init_pistons();
}

void autonomous() 
{
    (*auton)(); 
}

void opcontrol() 
{
    bool disabled = false;
    bool print_battery = false;
    bool run_once = true;
    long long time = 0;

    while(true)
    {
        disabled = disable_all();

        if(!disabled)
        {
            // driver.hpp control functions
            PTO_control();
            arcade_drive(!PTO.status());
            chainbar_control();
            twobar_control();
            clamp_control();

            if(glb::con.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)) autonomous();
            if(glb::con.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT)) print_battery = true;
            if(glb::con.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT)) print_battery = false;

            std::string eight_motor;
            if(PTO.status())
                eight_motor = "false";
            else
                eight_motor = "true";
            if(time % 50 == 0 && time % 500 != 0) glb::con.print(0, 0, "8M DRIVE: %s           ", eight_motor);
            if(time % 500 == 0 && time % 1000 != 0) 
            {
                if(print_battery)
                    glb::con.print(1, 0, "BATTERY: %.0f         ", battery::get_capacity());
                else
                    glb::con.print(1, 0, "INERTIAL: %.5f         ", glb::imu.get_pitch());
            }
            if(time % 1000 == 0) print_temp(chas, 2);
        }
        else
        {
            if(time % 50 == 0) glb::con.print(0, 0, "DISABLED         ");
            mtr::stop();
        }   

        pros::delay(1);
        time++;
    }
}
