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
        rotate(-45);
    }

    void elev()
    {
        spin_dist(1680);
        chain_clamp.toggle();
        PTO.set(true);
        left_front.move_relative(-3000, 127);
        right_front.move_relative(-3000, 127);
        drive(-550, false);
        rotate_to(90, false);
        drive(400, false);
        front_clamp.toggle();
        drive(-350, false);
    }

    void de_elev()
    {
        spin_dist(1680);
        chain_clamp.toggle();
        PTO.set(true);
        left_front.move_relative(-3000, 127);
        right_front.move_relative(-3000, 127);
        drive(-600, false);
        rotate(-14, false);
        drive(-800, false);
        drive(60, false);
        rotate(90, false);
        drive(250, false);
        front_clamp.toggle();
    }

    void elev_neu()
    {
        spin_dist(1300);
        spin_dist(300, 70);
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
        rotate_to(-58, false, 1200, 3);
        drive(-1960, false, 6000, 0.4);
        time_fwd(1000,-35);
        lback_lift.toggle();
        rback_lift.toggle();
    }

    void de_elev_neu()
    {
        spin_dist(1680);
        chain_clamp.toggle();
        PTO.set(true);
        left_front.move_relative(-3000, 127);
        right_front.move_relative(-3000, 127);
        drive(-400, false, 2000);
        rotate_to(39, false, 1500);
        drive(550, true, 2000);
        front_clamp.toggle();
        drive(-600, true, 2500);
    }

    void elev_tree()
    {
        spin_dist(1560);
        chain_clamp.toggle();
        spin_dist(40);
        PTO.set(true);
        left_front.move_relative(-5000, -600);
        right_front.move_relative(-5000, -600);
        drive(-400, false, 1500);
        rotate_to(60);
        spin_dist(450);
        spin_dist(300, 70);
        front_clamp.toggle();
        spin_dist(20, 70);
        drive(-700, false, 2000);
    }

    void win_point()
    {
        return;
    }

    void rush()
    {
        spin_dist(1100);
        chain_clamp.toggle();
        PTO.set(true);
        left_front.move_relative(-3000, 127);
        right_front.move_relative(-3000, 127);
        drive(-700, false);
    }

    void skills()
    {
        rotate(45);
    }

    // callable list of autons
    std::vector<void (*)()> auton_list{half_awp, elev, de_elev, elev_neu, de_elev_neu, win_point, rush, skills};
    std::vector<std::string> auton_names{"half_awp", "elev", "de_elev", "elev_neu", "de_elev_neu", "win_point", "rush", "skills"};
}


#endif
