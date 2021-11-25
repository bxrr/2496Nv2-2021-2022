#include "main.h"
#include "driver.hpp"
using namespace pros;
using namespace glb;



void initialize() 
{
    con.clear();
    pros::lcd::set_text(0, "2496NextLevelNinjas");
    chas::set_brake(COAST);
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
            arcade_drive(PTO_control());
            chainbar_control(PTO_control());
        }
        else
        {
            glb::con.clear();
            if(timer % 100 == 0) glb::con.set_text(1, 0, "DISABLED");
            
            chas::stop();
        }

        pros::delay(1);
        timer += 1;
    }
}
