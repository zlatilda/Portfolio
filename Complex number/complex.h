#include <iostream>
#include <cmath>
#include <stdexcept>
using namespace std;

double pow_compare( double power ) {
    if ( power < 1 && power > 0 ) {
        throw std::invalid_argument( "received value is in the scope of (0,1)" );
    }
}

class Complex
{
    private:
        double real;
        double img;

    public:

        Complex()
        {
            real = 0;
            img = 0;
        }

        Complex(double real, double img)
        {
            this->real = real;
            this->img = img;
        }

        double getReal()
        {
            return real;
        }

        double getImg()
        {
            return img;
        }

        friend ostream & operator << (ostream &out, const Complex &c)
        {
            if(c.real != 0)
            {
                out << c.real;
            }

            if(c.img > 0)
            {
                out << " + " << c.img << "i" << endl;
            }
            if(c.img < 0)
            {
                    out << " - " << abs(c.img) << "i" << endl;
            }
            return out;
        }

        friend istream & operator >> (istream &in,  Complex &c)
        {
            cout << "Enter Real Part ";
            in >> c.real;
            cout << "Enter Imaginary Part ";
            in >> c.img;
            return in;
        }

        Complex operator+( Complex &other )
        {
            return Complex( real + other.real, img + other.img );
        }

        Complex operator-( Complex &other )
        {
            return Complex( real - other.real, img - other.img );
        }

        Complex operator*( Complex &other )
        {
            double real_1 = real * other.real - img * other.img;
            double img_1 = real * other.img + img * other.real;

            return Complex( real_1, img_1);
        }

        Complex operator/( Complex &other )
        {
            double real_1 = real * other.real - ((-1) * img * other.img);
            double img_1 = (-1) * real * other.img + img * other.real;

            double real_2 = other.real * other.real - ((-1) * other.img * other.img);
            double img_2 = (-1) * other.real * other.img + other.img * other.real;

            double real_res = real_1/(real_2 + img_2);
            double img_res = img_1/(real_2 + img_2);

            return Complex( real_res, img_res);
        }

        Complex operator=( Complex &other )
        {
            return Complex( real = other.real, img = other.img );
        }

        Complex power(double power)
        {
           try{
            pow_compare( power );

            double r = sqrt(pow(real, 2) + pow(img, 2));
            double theta = atan(img/real);

            Complex res;
            res.real = pow(r,power)*cos(power*theta);
            res.img = pow(r,power)*sin(power*theta);
            return res;
           }

            catch( const std::invalid_argument& e ) {
                 throw;
            }
        }

        double absolute_value()
        {
            return sqrt(pow(real,2) + pow(img,2));
        }


};


