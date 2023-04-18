#include<stdio.h>
#include <iostream>
#include <cmath>
#include <graphics.h>
#include <stdlib.h>
#include <time.h>
#include <random>
using namespace std;

double random_double(double lwr_bound, double uppr_bound)
{
    double random_double = (uppr_bound - lwr_bound) * ( (double)rand() / (double)RAND_MAX ) + lwr_bound;

    return random_double;
}


double f(double x_i, double r)
{
    double result;

    result = r * x_i *(1-x_i);

    return result;
}

void draw_trajectory(double* res_arr, int n)
{
    initwindow(1000, 700);

    for(int i=1; i<n; i++)
    {
        line(i*(double(1000)/double(n)), res_arr[i-1]*700, (i+1)*(double(1000)/double(n)), res_arr[i]*700);
    }

    getch();
}

void draw_dots(double* res_arr, int n)
{
    initwindow(1000, 700);

    for(int i=1; i<=n; i++)
    {
        circle(i*(double(1000)/double(n)), res_arr[i-1]*700, 4);
    }

    getch();
}

void draw_attractor(double* transient_x, double* transient_y, int n)
{
    for(int i = n -(int(n*0.1)); i<n; i++)
    {
        line(transient_x[i]*500, transient_y[i]*500, transient_x[i]*500, transient_y[i+1]*500);
        line(transient_x[i]*500, transient_y[i+1]*500, transient_x[i+1]*500, transient_y[i+1]*500);
    }
}

void draw_return_map(double r, double x0, int n)
{
    initwindow(600, 600);

    //parabola + y=x line
    double x = 0.001;   // 0 < x < 1
    while(x <= 1)
    {
        putpixel(x*500, f(x, r) * 500, GREEN); // <--- X_i+1
        putpixel(x*500, x * 500, RED);  // X_i+1 = X_i
        x += 0.001;
    }

    //intersection point

    /*double intersection_x = 0.001;
    while(intersection_x <= f(intersection_x, r))
    {
        intersection_x += 0.001;
    }*/
    double intersection_x = ((r - 1) / r);  // system of equations { x_n+1 = x_n; x_n+1 = r*x_n*(1-x_n) . To solve it make this equations equal to each other ==> x_n = r*x_n*(1-x_n)
    double intersection_y = f(intersection_x, r);
    circle(intersection_x*500, intersection_y*500, 3);  // draw the intersection point

    // for transient removal
    double* transient_x = new double[n+1];
    double* transient_y = new double[n+1];

    int cycle = 0;

    transient_x[cycle] = x0;
    transient_y[cycle] = 0;

    double eps = 0.00001;
    double y = eps;
    while (cycle < n)
    {
        //vertical line
        if(y < f(x0, r))
        {
            while(y <= f(x0, r))
            {
                putpixel(x0*500, y * 500, BLUE);
                y += eps;
            }
        }

        else
        {
            while(y >= f(x0, r))
            {
                putpixel(x0*500, y * 500, BLUE);
                y -= eps;
            }
        }
        transient_y[cycle+1] = y;

        //horizontal line
        if (x0 < intersection_x)
        {
            while(x0 <= y)
            {
                putpixel(x0*500, y * 500, BLUE);
                x0 += eps;
            }
        }

        else
        {
            while(x0 > y)
            {
                putpixel(x0*500, y * 500, BLUE);
                x0 -= eps;
            }
        }
        transient_x[cycle+1] = x0;

        cycle++;
    }

    // remove a transient part and draw the attractor
    draw_attractor(transient_x, transient_y, n);

    getch();
}

void draw_bifurcation(double r_min, double r_max, double transient_percentage, double steps, double scale)
{
    initwindow(1000, 700);

    //double x0 = eps;
    double x0 = random_double(0, 1);
    int n = 100;
    //double r = r_min;
    double r = random_double(r_min, r_max);

    double* res_arr = new double[n];

    //while(x0 < 1)
    int step = 0;
    int step1 = 0;

    while(step < steps)
    {
        //while(r < r_max)
        while(step1 < steps)
        {
            res_arr[0] = f(x0, r);

            for(int i=1; i<n; i++)
            {
                res_arr[i] = f(res_arr[i-1], r);
            }

            int j = 0;
            for(int i = n - int(transient_percentage*n); i<n; i++)
            {
                putpixel(scale*r*(1000/r_max)-(scale*1000 - 1000), res_arr[i]*600, BLUE);
                j++;
            }

            //r += eps;
            r = random_double(r_min, r_max);

            step1++;
        }
        //r = r_min;
        step1 = 0;

        x0 = random_double(0, 1); //x0 += eps;

        step++;
    }

    getch();

    delete res_arr;
}

int main()
{
    printf("~~~~~~~~~ LOGISTIC MAP ~~~~~~~~~ \n\n");

    double x0;
    printf("x0: "); cin >> x0;

    double r;
    printf("r: "); cin >> r;

    int n;
    printf("n: "); cin >> n; printf("\n");

    double* res_arr = new double[n];

    res_arr[0] = f(x0, r);

     cout << res_arr[0] << "   ";

    for(int i=1; i<n; i++)
    {
        res_arr[i] = f(res_arr[i-1], r);
        cout << res_arr[i] << "   ";
    }  cout << endl;

    //draw_trajectory(res_arr, n);
    draw_dots(res_arr, n);

    //draw_return_map(r, x0, n);

    //draw_bifurcation(1, 3.57, 0.5, 500, 2);

    delete res_arr;

    return 0;
}
