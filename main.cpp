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
            arcade_drive();
            PTO_control();
        }
        else
        {
            con.clear();
            if(timer % 50 == 0) con.print(1, 0, "DISABLED");
            
            chas::stop();
        }

        delay(1);
        timer += 1;
    }
}
