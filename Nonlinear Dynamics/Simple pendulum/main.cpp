#include<stdio.h>
#include <iostream>
#include <cmath>
#include <graphics.h>
#include <stdlib.h>
#include <time.h>
#include <random>
#include <windows.h>
using namespace std;

const double PI = 3.14159265359;
const double g = 9.8;
const double e = 2.718;

void rotate_pendulum(double x1, double y1, double x2, double y2, double theta, double origin)
{
    double x2_new = x2*cos(theta) - y2*sin(theta);  //using rotation matrix
    double y2_new = x2*sin(theta) + y2*cos(theta);

    line(x1+origin, y1+origin, x2_new+origin, y2_new+origin);
    circle(x2_new+origin, y2*cos(theta)+origin, 15);
}

void oscillating_pendulum(double x1, double y1, double x2, double y2, double theta, double beta, double m, double origin, int t_steps)
{
    double frequency = sqrt(g/y2);
    double T = (2*PI)/frequency;

    double theta_n = theta;
    double t = frequency/T;  // time step

    while(t<t_steps)
    {
        rotate_pendulum(x1, y1, x2, y2, theta_n, origin);
        cleardevice();
        //theta_n = theta*cos(frequency*t);  // endless oscillation
        theta_n = theta*pow(e,(-0.5*(beta/m)*t))*cos(sqrt((g/y2)-(pow(beta,2)/(4*pow(m,2))))*t);
        t += 0.01;
    }
}

void oscillation_trajectory(double x1, double y1, double x2, double y2, double theta, double beta, double m, double origin, int t_steps)
{
    double frequency = sqrt(g/y2);
    double T = (2*PI)/frequency;

    double theta_n;
    double t = frequency/T;  // time step
    double v; // angular velocity

    while(t<t_steps)
    {
        theta_n = theta*pow(e,(-0.5*(beta/m)*t))*cos(sqrt((g/y2)-(pow(beta,2)/(4*pow(m,2))))*t);
        putpixel(t+10, 50*theta_n+origin, GREEN);

        v = ;
        putpixel(t+10, 50*v+origin, RED);

        putpixel(t, origin, BLUE); // y=0, x->

        t += 0.01;
    }
}

void oscillation_trajectory_2(double x1, double y1, double x2, double y2, double theta, double beta, double m, double origin, int t_steps)
{
    double frequency = sqrt(g/y2);
    double T = (2*PI)/frequency;

    double theta_n;
    double t = frequency/T;  // time step

    double x_new;
    double y_new;

    while(t<t_steps)
    {
        theta_n = theta*pow(e,(-0.5*(beta/m)*t))*cos(sqrt((g/y2)-(pow(beta,2)/(4*pow(m,2))))*t);

        x_new = y2*cos(t)/PI;
        y_new = y2*sin(theta_n);

        putpixel(x_new+origin, y_new+origin, BLUE); // Angular velocity theta with respect to time (Oy - theta, Ox - time)

        t += frequency/T;
        //t += 0.00005;
    }
}

void phase_space_portrait(double x1, double y1, double x2, double y2, double theta, double beta, double m, double origin, int t_steps)
{
    double frequency = sqrt(g/y2);
    double T = (2*PI)/frequency;

    double theta_n = theta;
    double t = frequency/T;  // time step

    double x_new;

    while(t<t_steps)
    {
        theta_n = theta*pow(e,(-0.5*(beta/m)*t))*cos(sqrt((g/y2)-(pow(beta,2)/(4*pow(m,2))))*t);  // oscillation affected by frictions, theta_n - angular velocity

        putpixel(10*theta+origin, 10*theta_n + origin, BLUE);

        t += frequency/T;
    }
}

int main()
{
    double theta = PI/4;
    double beta = 0.05;  // friction
    double origin = 250;  // coordinates transportation

    double m = 10; // mass of the ball

    double x1 = 0;
    double y1 = 0;
    double x2 = 0;
    double y2 = 200; // length of pendulum's string

    initwindow(500, 500);

    //oscillating_pendulum(x1, y1, x2, y2, theta, beta, m, origin, 500);
    oscillation_trajectory(x1, y1, x2, y2, theta, beta, m, origin, 500);
    //oscillation_trajectory_2(x1, y1, x2, y2, theta, beta, m, origin, 500);
    //phase_space_portrait(x1, y1, x2, y2, theta, beta, m, origin, 500);


    getch();
    return 0;
}
