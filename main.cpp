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
}

void disabled() {}

void competition_initialize() {auton = auton_selector();}

void autonomous() { (*auton)(); }

void opcontrol() 
{
    glb::con.clear();
    init_pistons();
    mtr::set_brake(hold, front);
    mtr::reset_pos();

    long long timer = 0;
    bool disabled = false;
    bool run_once = true;

    while(true)
    {
        disabled = disable_all();

        if(!disabled)
        {
            // driver.hpp control functions
            arcade_drive(PTO_control());
            chainbar_control();
            twobar_control();
            clamp_control();


            if(timer % 50 == 0) print_temp(chas, 2);
        }
        else
        {
            if(timer % 50 == 0) glb::con.set_text(1, 0, "DISABLED       ");
            mtr::stop();
        }

        pros::delay(1);
        timer++;
    }
}
