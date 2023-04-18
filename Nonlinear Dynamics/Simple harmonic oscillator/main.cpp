#include<stdio.h>
#include <iostream>
#include <cmath>
#include <graphics.h>
#include <stdlib.h>
#include <time.h>
#include <random>
#include <windows.h>
using namespace std;

struct state_condition{
  double x;
  double v;
};

double x_def(state_condition obj)
{
    return obj.v;
}

double v_def(double g, double k, double m, double b, state_condition obj)
{
    return (g - (k/m)*obj.x - (b/m)*obj.v);
}

state_condition forward_euler(state_condition init, double delta_t, double g, double k, double m , double b)
{
    state_condition next;
    state_condition def;

    def.x = x_def(init);
    def.v = v_def(g, k, m, b, init);

    next.x = init.x + delta_t*def.x;
    next.v = init.v + delta_t*def.v;

    return next;
}

state_condition backward_euler(state_condition init, double delta_t, double g, double k, double m , double b)
{
    state_condition next;

    state_condition res = forward_euler(init, delta_t, g, k, m , b);

    next.x = init.x + delta_t*x_def(res);
    next.v = init.v + delta_t*v_def(g, k, m, b, res);

    return next;
}

state_condition trapezoidal(state_condition init, double delta_t, double g, double k, double m , double b)
{
    state_condition next;
    state_condition def;
    state_condition xFE;

    def.x = x_def(init);
    def.v = v_def(g, k, m, b, init);

    xFE.x = init.x + delta_t * def.x;
    xFE.v = init.v + delta_t * def.v;

    next.x =  init.x + (delta_t/2)*(def.x + x_def(xFE));
    next.v =  init.v + (delta_t/2)*(def.v + v_def(g, k, m, b, xFE));

    return next;
}

void harmonic_oscillator_phase_space(double g, double k, double m, double b, double delta_t, state_condition init, double steps_n, double scale)
{
    double step = 0;
    state_condition res;
    state_condition b_res;
    state_condition t_res;

    state_condition init_1 = init;
    state_condition init_2 = init;

    while(step < steps_n)
    {
        res = forward_euler(init, delta_t, g, k, m , b);  // foward euler

        b_res = backward_euler(init_1, delta_t, g, k, m , b); // backward euler

        t_res = trapezoidal(init_2, delta_t, g, k, m , b);  //trapezoidal method

        //cout << t_res.x << " " << t_res.v << endl;
        //cout << res.x << " " << res.v << endl;
        //cout << b_res.x << " " << b_res.v << endl;

        setcolor(GREEN);
        line(scale*init.x+250, scale*init.v+250, scale*res.x+250, scale*res.v+250);   // forward euler

        setcolor(MAGENTA);
        line(scale*b_res.x+250, scale*b_res.v+250, scale*init_1.x+250, scale*init_1.v+250);  // backward euler

        setcolor(YELLOW);
        line(scale*t_res.x+250, scale*t_res.v+250, scale*init_2.x+250, scale*init_2.v+250); //trapezoidal method

        init = res;
        init_1 = b_res;
        init_2 = t_res;

        step += delta_t;
    }

    getch();
}

int main()
{
    initwindow(500, 500);

    state_condition obj;
    obj.x = -10;
    obj.v = -20;

    double delta_t = 0.01;
    double g = 0;
    double b = 0;
    double k = 2;
    double m = 0.5;

    harmonic_oscillator_phase_space(g, k, m, b, delta_t, obj, 50, 5);

    return 0;
}
