#include "main.h"
#include "driver.hpp"
#include "global.hpp"
#include "autons.hpp"
#include <string>
using namespace glb; // global variables


// global variables
void (*auton)() = aut::auton_calls.at(1);
std::string aut_name = aut::auton_names.at(1);

// functions
void initialize() 
{
    con.clear();
    pros::lcd::set_text(0, "2496NextLevelNinjas");
    mtr::set_brake(coast, chas);
    mtr::set_brake(hold, front);

    auton = auton_selector(aut_name);
    bool start_8m = (aut_name == "solo_awp" || aut_name == "slow_awp" || aut_name == "half_tree" || aut_name == "half_awp") ? false : true;

    glb::con.clear();
    mtr::reset_pos();
    glb::init_pistons();
    glb::PTO.set(start_8m);
}

void competition_initialize() 
{
    mtr::set_brake(coast, all);
    mtr::reset_pos();
    glb::init_pistons();
    glb::con.clear();
    delay(50);
    glb::con.print(0, 0, "%s          ", aut_name);
}

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
            arcade_drive(PTO.status(), s_hold_control());
            chainbar_control();
            twobar_control();
            clamp_control();
            cover_control();
            print_info(time, aut_name);
            
            if(glb::con.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)) autonomous();
            if(glb::con.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT)) calibrate_robot();
            
        }
        else
        {
            if(time % 50 == 0) glb::con.print(0, 0, "DISABLED             ");
            mtr::stop();
        }   

        pros::delay(1);
        time++;
    }
}
