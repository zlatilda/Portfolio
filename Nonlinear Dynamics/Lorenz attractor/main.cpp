#include <iostream>
#include <math.h>
#include <windows.h>
#include <graphics.h>
using namespace std;

struct state_condition{
  double x;
  double y;
  double z;
};

double x_def(double sigma, state_condition obj)
{
    return sigma * (obj.y - obj.x);
}

double y_def(double ro, state_condition obj)
{
    return obj.x * (ro - obj.z) - obj.y;
}

double z_def(double beta, state_condition obj)
{
    return obj.x * obj.y - beta * obj.z;
}

state_condition trapezoidal(state_condition init, double delta_t, double sigma, double ro, double beta)
{
    state_condition next;
    state_condition def;
    state_condition xFE;

    def.x = x_def(sigma, init);
    def.y = y_def(ro, init);
    def.z = z_def(beta, init);

    xFE.x = init.x + delta_t * def.x;
    xFE.y = init.y + delta_t * def.y;
    xFE.z = init.z + delta_t * def.z;

    next.x =  init.x + (delta_t/2)*(def.x + x_def(sigma, xFE));
    next.y =  init.y + (delta_t/2)*(def.y + y_def(ro, xFE));
    next.z =  init.z + (delta_t/2)*(def.z + x_def(beta, xFE));

    return next;
}

state_condition isometric_projection(state_condition point)
{
    double matrix[3][3] = {{sqrt(3),     0,   -(sqrt(3))},
                           {1,           2,            1},
                           {sqrt(2), -(sqrt(2)), sqrt(2)}
                          };
    double a = 1/sqrt(6);

    state_condition new_point;
    state_condition temp;

    temp.x = point.x*matrix[0][0] + point.y*matrix[0][1] + point.z*matrix[0][2];
    temp.y = point.x*matrix[1][0] + point.y*matrix[1][1] + point.z*matrix[1][2];
    temp.z = point.x*matrix[2][0] + point.y*matrix[2][1] + point.z*matrix[2][2];

    new_point.x = temp.x;
    new_point.y = temp.y;
    new_point.z = 0;

    return new_point;
}

void display(double steps_n, state_condition init, double delta_t, double sigma, double ro, double beta, double scale)
{
    state_condition t_res;
    double step = 0;

    state_condition a;

    while(step < steps_n)
    {
        t_res = trapezoidal(init, delta_t, sigma, ro, beta);  //trapezoidal method

        a = isometric_projection(t_res);
        putpixel(scale*a.x+550, scale*a.y+150, MAGENTA);
        //putpixel(10*t_res.x+350, 10*t_res.y+350, MAGENTA);  //xy
        //putpixel(10*t_res.x+350, 10*t_res.z+50, MAGENTA);   //xz

        init = t_res;

        step += delta_t;
    }
}

int main()
{
    double delta_t = 0.01;
    double sigma = 10; //10
    double ro = 28;  //28
    double beta = 2.67;  //2.67
    state_condition init;
    double steps_n = 500;

    init.x = 0.5;
    init.y = 1;
    init.z = 1;

    initwindow(700, 700);

    display(steps_n, init, delta_t, sigma, ro, beta, 4);

    /*for(double i = 0; i<=70; i += 0.1)                        //ro -> inf animation
    {
        display(steps_n, init, delta_t, sigma, i, beta, 4);
        cleardevice();
    }*/

    getch();

    return 0;
}
