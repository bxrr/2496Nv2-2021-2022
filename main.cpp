#include "main.h"
#include "driver.hpp"
#include "global.hpp"
#include "autons.hpp"
using namespace pros;
using namespace glb; // global variables

// int a, *b, c[5], d(void); // this compiles btw 
// this abomination is a function that returns a function pointer: void (*func())();


// global variables
void (*auton)() = aut::auton_list.at(0);

// functions
void initialize() 
{
    con.clear();
    pros::lcd::set_text(0, "2496NextLevelNinjas");
    mtr::set_brake(coast, all);
}

void disabled() {}

void competition_initialize() {}

void autonomous() { (*auton)(); }

void opcontrol() 
{
    auton = auton_selector();
    delay(500);

    mtr::set_brake(hold, front);
    mtr::reset_pos();
    init_pistons();

    long long timer = 0;
    bool disabled = false;
    bool run_once = true;

    while(true)
    {
        if(timer % 50 == 0) { glb::con.print(0, 1, "Deg: %f", glb::imu.get_heading()); }
        disabled = disable_all();
        if(!disabled)
        {
            run_once = true;
            // driver.hpp control functions
            arcade_drive(PTO_control());
            chainbar_control();

            if(timer % 55 == 0) print_temp(chas);
        }
        else
        {
            if(run_once)
            {
                glb::con.clear();
                run_once = false;
            }
            if(timer % 100 == 0) glb::con.set_text(1, 0, "DISABLED");
            
            mtr::stop();
        }

        pros::delay(1);
        timer++;
    }
}
