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
        drive(2000);
        drive(-1000);
        drive(500);
        drive(-250);
        
        rotate(90);
        rotate_to(45);
        rotate_to(-45);
    }

    void solo_awp()
    {
        spin_dist(500, 50);
        chain_clamp.toggle();

        spin_lift(5000);
        drive(-390, 124.5, 1400);
        rotate_to(-90, 1500, 1.1);
        drive(530, 120, 1600);
        rotate_to(-1.5, 1800, 1.05);
        drive(3650, 124.5, 3200, 2000);
        front_clamp.toggle();
        toggle_2bar();
        rotate_to(35, 1800, 1.2);
        spin_dist(-1800);
        toggle_2bar();
        goal_cover.toggle();
        spin_dist(-140);
        rotate_to(40, 1000, 1.4);
        spin_dist(1600);
        front_clamp.toggle();
        
    }

    void elev_neu()
    {
        double initial_rush = 1460;
        double rush_return = 500;
        double turn_to_tree = -55.222; // turn
        double tree_rush = 880.584;
        double tree_return = 300;
        double alliance_align = -45; // turn
        double alliance_grab = -900;

        initial_rush -= drive(initial_rush);
        chain_clamp.toggle();
        spin_lift(5000);
        rush_return -= drive(rush_return - initial_rush);
        rotate_to(turn_to_tree);
        tree_rush -= drive(tree_rush);
        front_clamp.toggle();
        tree_return -= drive(tree_return - tree_rush);
        rotate_to(alliance_align);
        alliance_grab -= drive(alliance_grab);
    }

    void elev_tree()
    {
        spin_dist(2250);
        chain_clamp.toggle();
        spin_lift(5000);
        rotate_to(-50, 1500);
        toggle_2bar();
        spin_dist(-1000);
        goal_cover.toggle();
        spin_dist(-150, 125, 150);
        toggle_2bar();
        rotate_to(-125, 1500, 1.3);
        drive(1200, 3000);
        rotate_to(117, 2000, 1.2);
        drive(900);
    }


    // callable list of autons
    std::vector<void (*)()>  auton_calls{ test,   solo_awp,   elev_neu,   elev_tree, };
    std::vector<std::string> auton_names{"test", "solo_awp", "elev_neu", "elev_tree" };
}


#endif
