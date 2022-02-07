#ifndef __AUTONS_H__
#define __AUTONS_H__

#include "main.h"
#include "aut_func.hpp"
#include "global.hpp"
#include <vector>
#include <string>

using namespace pros;
using namespace fnc;
using namespace glb;

namespace aut
{
    void test()
    {
        spin_lift(-5000)
        drive(1000);
        rotate(90);
    }

    void elev() // half awp + middle goal
    {
        drive(500);
        front_clamp.toggle();
        delay(100);
        spin_lift(-5000);
        delay(100);
        drive(-500);
        rotate_to(135);
        toggle_2bar();
        drive(-2400);
        toggle_2bar();
        spin_dist(-50, -70)
        drive(500);
        rotate_to(45);
        drive(700);
        front_clamp.toggle();
        spin_dist(50, 60);
        drive(-750);
    }

    // callable list of autons
    std::vector<void (*)()>  auton_calls{ test,   half_awp };
    std::vector<std::string> auton_names{"test", "half_awp"};
}


#endif
