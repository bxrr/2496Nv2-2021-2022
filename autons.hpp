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
    void half_awp()
    {
        PTO.set(true);
        drive(350, false, 1500);
        chain_clamp.toggle();
        rotate(-45, false);
    }

    void elev()
    {
        PTO.set(true);
        drive(550, false, 1500, 0.3);
        drive(-550, false, 1500, 0.3);
        rotate(-45, false, 1500);
        spin_dist(2200, false, 90);
        spin_dist(300, false, 60);
        chain_clamp.toggle();
        spin_dist(40, false, 50);
        PTO.set(true);
        left_front.move_relative(-5000, -600);
        right_front.move_relative(-5000, -600);
        drive(-2100, false);
        front_clamp.toggle();
        rotate(60, false);
    }

    void elev_neu()
    {
        spin_dist(1000);
        spin_dist(600, 60);
        chain_clamp.toggle();
        spin_dist(60, 60);
        PTO.set(true);
        left_front.move_relative(-5000, -600);
        right_front.move_relative(-5000, -600);
        drive(-720, false, 1500, 0.3);
        front_clamp.toggle();
        rotate_to(-49, false, 1500, 2, 0.3, 1.3);
        spin_dist(800, false, 100);
        spin_dist(620, false, 50);
        front_clamp.toggle();
        spin_dist(30, false, 40);
        lback_lift.toggle();
        rback_lift.toggle();
        rotate_to(-54, false, 1200, 3);
        drive(-1960, false, 6000, 0.4);
        time_fwd(1000,-35);
    }

    void elev_tree()
    {
        spin_dist(1440, true);
        spin_dist(700, true, 65);
        chain_clamp.toggle();
        spin_dist(60, true, 60);
        PTO.set(true);
        left_front.move_relative(-5000, -600);
        right_front.move_relative(-5000, -600);
        drive(-380, false, 1200);
        front_clamp.toggle();
        rotate_to(78, false, 2000);
        spin_dist(900, false, 80);
        front_clamp.toggle();
        spin_dist(40, false, 60);
        spin_dist(-400, false, 90);
    }

    void rush_elev()
    {
        spin_dist(1100);
        spin_dist(500, 60);
        chain_clamp.toggle();
        spin_dist(60, 60);
        PTO.set(true);
        left_front.move_relative(-5000, -600);
        right_front.move_relative(-5000, -600);
        drive(-950, false, 1500, 0.3);
        rotate(-45, false);
    }

    void rush_de()
    {
        spin_dist(1300);
        spin_dist(500, 60);
        chain_clamp.toggle();
        spin_dist(60, 60);
        PTO.set(true);
        left_front.move_relative(-5000, -600);
        right_front.move_relative(-5000, -600);
        drive(-950, false, 1500, 0.3);
        rotate(45, false);
    }

    void rush_tree()
    {
        spin_dist(1400);
        spin_dist(700, 60);
        chain_clamp.toggle();
        spin_dist(60, 60);
        PTO.set(true);
        left_front.move_relative(-5000, -600);
        right_front.move_relative(-5000, -600);
        drive(-1400, false, 1500, 0.3);
        rotate(35, false);
    }

    void skills()
    {
        rotate(45);
    }

    // callable list of autons
    std::vector<void (*)()> auton_list{half_awp, elev, elev_neu, elev_tree, rush_elev, rush_de, rush_tree, skills};
    std::vector<std::string> auton_names{"half_awp", "elev", "elev_neu", "elev_tree", "rush_elev", "rush_de", "rush_tree", "skills"};
}


#endif
