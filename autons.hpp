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
        drive(-500);
        rotate_to(90);
        rotate_to(0);
    }

    void solo_awp()
    {
        drive(350, 100, 1200);
        chain_clamp.toggle();
        drive(0, 0, 0);
        delay(300);
        spin_lift(-4500);
        drive(-220, 120, 1200);
        delay(400);
        rotate_to(90, 1500, 1.15);
        drive(-725, 120, 3000);
        rotate_to(0, 2000, 1.15);
        drive(3480, 100, 4000);
        front_clamp.toggle();
        rotate_to(-5, 1000, 2.5);
        drive(-2000, 90, 3000);
        front_clamp.toggle();
    }

    void elev_neu()
    {
        spin_dist(1400);
        spin_dist(100, 90);
        chain_clamp.toggle();
        spin_lift(-4800);
        drive(-600, 120, 1000, 1.3);
        rotate_to(-64.222, 1400, 1.3);
        spin_dist(1050);
        spin_dist(450, 80);
        front_clamp.toggle();
        spin_dist(50, 80);
        toggle_2bar();
        drive(-1400, 120, 2500);
        rotate_to(-45, 1500, 1.3);
        drive(-1200);
    }

    void elev_tree()
    {
        spin_dist(2060);
        chain_clamp.toggle();
        spin_dist(25);
        spin_lift(-4500);
        drive(-800, 120, 1800);
        rotate_to(70, 2200, 1.2);
        spin_dist(750);
        spin_dist(100, 90);
        front_clamp.toggle();
        spin_dist(40, 90);
        drive(-700, 120, 1500);
        toggle_2bar();
        rotate_to(-35);
        drive(-1250);
    }

    void deelev_neu()
    {
        spin_dist(1550);
        spin_dist(100, 90);
        chain_clamp.toggle();
        spin_lift(-4800);
        drive(-750, 120, 1500);
        rotate_to(43, 1500, 1.3);
        spin_dist(1300);
        spin_dist(290, 90);
        front_clamp.toggle();
        spin_dist(40, 90);
        drive(-2000, 120, 3000);
        rotate_to(0, 2000, 1.3);
        drive(-900, 120, 2000);
        rotate_to(-90, 2000, 1.3);
        delay(500);
        toggle_2bar();
        drive(-600);
    }

    void deelev_tree()
    {
        spin_dist(2260);
        chain_clamp.toggle();
        spin_lift(-4500);
        drive(-800);
        rotate_to(-90);
    }
    
    void b_deelev_neu()
    {
        spin_dist(-1650);
        drive(-5, 120, 4000, 1500);
    }

    // callable list of autons
    std::vector<void (*)()>  auton_calls{ test,   solo_awp,   elev_neu,   elev_tree,   deelev_neu,   deelev_tree,   b_deelev_neu  };
    std::vector<std::string> auton_names{"test", "solo_awp", "elev_neu", "elev_tree", "deelev_neu", "deelev_tree", "b_deelev_neu" };
}


#endif
