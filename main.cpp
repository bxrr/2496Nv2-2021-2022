#include "main.h"
#include "driver.hpp"
#include "global.hpp"
using namespace pros;
using namespace glb; // global variables
using namespace mtr; // motor functions



void initialize() 
{
    con.clear();
    pros::lcd::set_text(0, "2496NextLevelNinjas");
    mtr::set_brake(coast);
}

void disabled() {}

void competition_initialize() {}

void autonomous() {}

void opcontrol() 
{
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
        timer += 1;
    }
}
