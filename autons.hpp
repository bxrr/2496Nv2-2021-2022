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
        rotate(90);
    }

    void solo_awp()
    {
        /*
        spin_dist(500, 50);
        chain_clamp.toggle();
        spin_lift(5000);
        drive(-380, 100, 2000);
        rotate_to(-90, 1900, 1.1);
        drive(500, 120);
        rotate_to(-1.5);
        spin_dist(3800);
        */

    
        spin_dist(500, 50);
        chain_clamp.toggle();
        spin_lift(5000);
        drive(-380, 1000);
        rotate_to(-90, 1500, 1.1);
        drive(500, 120, 1300);
        rotate_to(-1.5, 1800, 1.05);
        spin_dist(3000, 125, 4000);
        spin_dist(600, 80, 1000);
        front_clamp.toggle();
        toggle_2bar();
        rotate_to(33, 1800, 1.2);
        spin_dist(-1700);
        toggle_2bar();
        goal_cover.toggle();
        spin_dist(-100);
        rotate_to(-40, 1800, 1.4);
        spin_dist(-1900);
        // front_clamp.toggle();
        // drive(-400);
        
    }

    void awp_elev() // start forward; half awp -> middle goal TODO
    {
        drive(550, 120, 1500);
        drive(-550, 120, 1500);
        rotate(-45, 1500);
        spin_dist(2200, 90);
        spin_dist(300, 60);
        chain_clamp.toggle();
        spin_dist(40, 50);
        spin_lift(5000);
        drive(-2100, 80);
        rotate(60, false);
    }

    void elev_neu()
    {
        spin_dist(1430);
        chain_clamp.toggle();
        spin_dist(50, 50);
        spin_lift(5000);
        drive(-1080);
        rotate_to(-40, 1600);
        spin_dist(1200);
        spin_dist(200, 70);
        front_clamp.toggle();
        spin_dist(100);
        delay(50);
        drive(-1500);
        toggle_2bar();
        rotate_to(-85, 1700);
        drive(-500);
    }

    void back_neu() // start backward; neutral goal -> middle goal -> alliance goal
    {
        spin_lift(2500);
        spin_dist(-500, 124.5, 2000);
        toggle_2bar();
        spin_dist(-880, 124.5, 2500);
        spin_dist(-100, 100, 1500);
        goal_cover.toggle();
        toggle_2bar();
        spin_lift(-1800);
        spin_dist(-150, 124.5, 500);
        rotate_to(83, 2000, 1.1);
        spin_dist(600);
        spin_lift(-800, 600);
        spin_dist(150);
        spin_dist(350, 40);
        spin_lift(-300, 600);
        spin_dist(320, 40);
        chain_clamp.toggle();
        spin_dist(50, 50);
        drive(0, 0, 0);
        spin_lift(4500);
        delay(500);
        rotate_to(120, 1500, 1.3);
        drive(-2150, 100, 2200);
        rotate_to(-90, 1500, 1.2);
        spin_dist(500, 40, 1500);
        front_clamp.toggle();
        /*
        spin_lift(2500);
        spin_dist(-200);
        toggle_2bar();
        spin_dist(-1300);
        spin_dist(-250, 73);
        toggle_2bar();
        goal_cover.toggle();
        spin_dist(-50, 50);
        spin_lift(-2500);
        drive(500, 900);
        rotate_to(115, 1800);
        spin_dist(1000);
        spin_dist(400, 70);
        chain_clamp.toggle();
        spin_dist(50, 50);
        spin_lift(5000);
        drive(-2000);
        rotate_to(-90);
        spin_dist(250, 60);
        front_clamp.toggle();
        */
    }

    void back_tree() // start backward; middle goal -> neutral goal -> alliance goal
    {
        spin_dist(-200);
        toggle_2bar();
        spin_dist(-1800);
        toggle_2bar();
        spin_dist(-70, 80);
        goal_cover.toggle();
        drive(400);
        rotate_to(-102);
        spin_dist(800, 80);
        chain_clamp.toggle();
        spin_dist(40, 60);
        drive(-400);
        rotate_to(-192);
        drive(1000);
        front_clamp.toggle();
    }

    void rush_elev()
    {
        spin_dist(1430);
        chain_clamp.toggle();
        spin_dist(50, 50);
        spin_lift(5000);
        drive(-1400);
    }

    void rush_de_elev()
    {
        spin_lift(2500);
        spin_dist(-800, 124.5, 2000);
        toggle_2bar();
        spin_dist(-1400, 124.5, 2500);
        toggle_2bar();
        goal_cover.toggle();
        drive(60, 100, 100);
        rotate_to(40, 1300);
        drive(400, 120, 1500);
        rotate_to(-17, 1000);
        drive(2100, 100, 4000);
        rotate_to(-108, 1500);
        drive(400, 120, 1500);
        front_clamp.toggle();
        delay(300);
        drive(-200, 100, 500);
        front_clamp.toggle();
        delay(100);
        drive(-100);

    }

    void rush_tree() // elev side
    {
        spin_dist(2000, 127, 2000);
        spin_dist(100, 80, 200);
        chain_clamp.toggle();
        spin_dist(40, 127, 100);
        spin_lift(5000);
        spin_dist(-800);
    }


    // callable list of autons
    std::vector<void (*)()>  auton_calls{ test,   solo_awp,   awp_elev,   elev_neu,   back_neu,   back_tree,   rush_elev,   rush_de_elev,   rush_tree };
    std::vector<std::string> auton_names{"test", "solo_awp", "awp_elev", "elev_neu", "back_neu", "back_tree", "rush_elev", "rush_de_elev", "rush_tree"};
}


#endif
