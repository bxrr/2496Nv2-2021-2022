#ifndef __AUTONS_H__
#define __AUTONS_H__

#include "main.h"
#include "pid.hpp"
#include "global.hpp"
#include <vector>
#include <string>

using namespace pros;
using namespace pid;
using namespace glb;
using namespace mtr;


namespace aut
{
    void drive1000()
    {
        drive(-1000);
        drive(2000);
        chain_clamp.toggle();
        drive(-1000);
        drive_pid.set_kP(0.4);
        lift_spin(127, 2000);
        rotate_to(60);
        drive(1450);
        front_clamp.toggle();
        drive(-2000);
    }

    void de_elev()
    {
        drive(4000);
    }

    void neu_tree()
    {
        rotate(30);
        rotate(180);
    }

    void win_point()
    {
        drive(4000);
    }

    void rush()
    {
        drive(1000);
    }

    void skills()
    {
        rotate(45);
    }

    // callable list of autons
    std::vector<void (*)()> auton_list{drive1000, rotate90, elev, de_elev, neu_tree, win_point, rush, skills};
    std::vector<std::string> auton_names{"drive1000", "rotate90", "elev", "de_elev", "neu_tree", "win_point", "rush", "skills"};
}


#endif
