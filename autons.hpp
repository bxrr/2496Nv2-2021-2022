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
        drive(-200);
        drive(50);
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
        spin_dist(1460);
        chain_clamp.toggle();
        spin_dist(50, 50);
        spin_lift(5000);
        rotate_to(90, 1100);
        toggle_2bar();
        spin_dist(-800);
        goal_cover.toggle();
        spin_dist(-100, 100, 300);
        toggle_2bar();
        rotate_to(135, 1500);
        drive(1700, 3000);
        rotate_to(87, 1500, 1.2);
        drive(800, 125, 2000);
    }

    void elev_tree() // start backward; middle goal -> neutral goal -> alliance goal
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

    void back_neu() // start backward; neutral goal -> middle goal -> alliance goal
    {
        spin_lift(2500);
        spin_dist(-580, 124.5, 2000);
        toggle_2bar();
        spin_dist(-860, 124.5, 2500);
        goal_cover.toggle();
        spin_lift(-2000);
        spin_dist(-120, 124.5, 500);
        toggle_2bar();
        rotate_to(87, 1500);
        spin_dist(300, 90);
        spin_dist(500, 70);
        mtr::stop(mtr::chas);
        spin_lift(-700);
        delay(400);
        spin_dist(150, 70);
        chain_clamp.toggle();
        drive(0, 0, 0);
        delay(300);
        spin_lift(4300);
        delay(400);
        rotate_to(130, 1500, 1.3);
        drive(-1700, 100, 2200);
        rotate_to(280, 1500);
        drive(800, 120, 1500);
    }

    void elev_half()
    {
        spin_dist(300, 50);
        chain_clamp.toggle();
        delay(300);
        spin_lift(3000);
        drive(-300, 2000);
        rotate_to(130, 2000);
        toggle_2bar();
        spin_dist(-2600);
        goal_cover.toggle();
        spin_dist(-100, 50, 100);
        toggle_2bar();
        drive(2000);
    }

    void tree_de_elev()
    {
        spin_lift(2500);
        spin_dist(-600);
        toggle_2bar();
        spin_dist(-1800);
        goal_cover.toggle();
        spin_dist(-100, 50);
        toggle_2bar();
        drive(1400, 124, 2500);
    }

    void rush_elev()
    {
        spin_dist(1460);
        chain_clamp.toggle();
        spin_dist(50, 50);
        drive(-100, 120, 15000);
    }

    void rush_de_elev()
    {
        spin_dist(1500);
        chain_clamp.toggle();
        spin_dist(50, 50);
    }

    void fake_neu() // FAKE TREE, GOES FOR NEU
    {
        rotate(45, 2000);
        spin_dist(2040);
        chain_clamp.toggle();
        spin_dist(50, 50);
        drive(-1200, 124.5, 15000);
    }

    void fake_tree() // FAKE NEU, GOES FOR TREE
    {
        rotate(45, 2000);
        spin_dist(2040);
        chain_clamp.toggle();
        spin_dist(50, 50);
        drive(-720, 124.5, 15000);
    }

    void half_awp_only()
    {
        spin_dist(200, 50);
        chain_clamp.toggle();
        delay(1000);
        chain_clamp.toggle();
        drive(-300);
    }


    // callable list of autons
    std::vector<void (*)()>  auton_calls{ test,   solo_awp,   elev_neu,   elev_tree,   back_neu,   elev_half, tree_de_elev,   rush_elev,   rush_de_elev,   fake_neu,   fake_tree, half_awp_only};
    std::vector<std::string> auton_names{"test", "solo_awp", "elev_neu", "elev_tree", "back_neu", "elev_half", "tree_de_elev", "rush_elev", "rush_de_elev", "fake_neu", "fake_tree", "half only"};
}


#endif
