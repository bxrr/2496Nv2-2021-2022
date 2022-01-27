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

void competition_initialize() {auton = auton_selector();}

void autonomous() 
{
    (*auton)(); 
}

void opcontrol() 
{
    bool disabled = false;
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
            if(time % 1000 == 0) print_temp(chas);
        }
        else
        {
            if(time % 500 == 0) glb::con.print(0, 0, "%d", glb::PTO.status());
            mtr::stop();
        }   

        pros::delay(1);
        time++;
    }
}
