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
    mtr::set_brake(coast);
}

void disabled() {}

void competition_initialize() {}

void autonomous() 
{
    (*auton)();
}

void opcontrol() 
{
    auton = auton_selector();
    long long timer = 0;
    bool disabled = false;

    while(true)
    {
        disabled = disable_all();
        if(!disabled)
        {
            // control functions in here
            arcade_drive(PTO_control());
            chainbar_control();

            if(timer % 55 == 0) print_temp(chas);
        }
        else
        {
            glb::con.clear();
            if(timer % 100 == 0) glb::con.set_text(1, 0, "DISABLED");
            
            mtr::stop();
        }

        pros::delay(1);
        timer++;
    }
}
