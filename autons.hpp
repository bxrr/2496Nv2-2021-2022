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
        drive(1500);
        drive(-1500);
    }

    void half_awp()
    {
        drive(500);
        chain_clamp.toggle();
        drive(-1000);
    }

    void awp()
    {
        spin_dist(500, 50);
        chain_clamp.toggle();
        spin_lift(5000);
        drive(-400, 1000);
        rotate_to(-90, 1800);
        drive(600, 120, 1300);
        rotate_to(0, 1200);
        drive(4000, 110, 3100, 1600);
        drive(-1000, 100, 2000);
        rotate_to(-130, 1800);
        spin_dist(800);
        drive(300);
        delay(100);
        front_clamp.toggle();
        delay(100);
        spin_dist(-1300);
    }

    void elev() // start forward; half awp + alliance goal -> middle goal -> neutral goal
    {
        drive(500);
        chain_clamp.toggle();
        delay(100);
        spin_lift(200);
        delay(100);
        drive(-700);
        rotate(135);
        spin_lift(-200);
        delay(400);
        chain_clamp.toggle();
        toggle_2bar();
        drive(-2400);
        toggle_2bar();
        spin_dist(-150, -70);
        drive(600);
        rotate_to(45);
        drive(700);
        front_clamp.toggle();
        spin_dist(50, 60);
        drive(-750);
    }

    void elev_neu() // start backward; neutral goal -> middle goal -> alliance goal
    {
        spin_dist(-250);
        toggle_2bar();
        spin_dist(-1350);
        toggle_2bar();
        goal_cover.toggle();
        //delay(75);
        spin_dist(100, 80);
        drive(500);
        rotate_to(125);
    }

    void elev_tree() // start backward; middle goal -> neutral goal -> alliance goal
    {
        spin_dist(-200);
        toggle_2bar();
        spin_dist(-1800);
        toggle_2bar();
        spin_dist(-150);
        drive(450);
        rotate_to(-102);
        spin_dist(800, 80);
        chain_clamp.toggle();
        spin_dist(40, 60);
        drive(-400);
        rotate_to(-192);
        drive(1000);
        front_clamp.toggle();
    }

    void back_neu()
    {
        spin_dist(-200);
        toggle_2bar();
        spin_dist(-1250);
        toggle_2bar();
        spin_dist(-300);
        rotate_to(-45);
        drive(-200);
        rotate_to(-90);
        drive(-1400);
        rotate_to(-45);
        spin_dist(100);
        chain_clamp.toggle();
        spin_lift(6000);
        drive(1000);


    }

    void back_tree()
    {
        spin_dist(-200);
        toggle_2bar();
        spin_dist(-1400);
        toggle_2bar();
        spin_dist(-150);
        drive(900);
    }

    void rush_neu()
    {
        spin_dist(1400, 127, 2000);
        spin_dist(100, 80, 200);
        chain_clamp.toggle();
        spin_dist(40, 127, 100);
        spin_lift(5000);
        spin_dist(-700);
    }

    void rush_neu2()
    {
        spin_dist(1600, 127, 2000);
        spin_dist(100, 80, 200);
        chain_clamp.toggle();
        spin_dist(40, 127, 100);
        spin_lift(5000);
        spin_dist(-800);
    }

    void rush_tree()
    {
        spin_dist(2100, 127, 2000);
        spin_dist(100, 80, 200);
        chain_clamp.toggle();
        spin_dist(40, 127, 100);
        spin_lift(5000);
        spin_dist(-700);
    }

    // callable list of autons
    std::vector<void (*)()>  auton_calls{ test,   half_awp,   awp,  elev,   elev_neu,   back_neu,   back_tree,   rush_neu,   rush_neu2,   rush_tree };
    std::vector<std::string> auton_names{"test", "half_awp", "awp", "elev", "elev_neu", "back_neu", "back_tree", "rush_neu", "rush_neu2", "rush_tree"};
}


#endif
