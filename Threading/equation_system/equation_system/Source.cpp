#include <iostream>
#include <conio.h>
#include <thread>
#include <stdlib.h>     
#include <time.h> 
#include<iomanip>
#include <ctime>
using namespace std;

void output(double **array, int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size + 1; j++)
			cout << setw(3) << array[i][j];
		cout << endl;
	}
	cout << endl;
}

void jordan(double **array, double *x, int m_nCols, int m_nRows, int b1, int b2)
{
	int i, j, k;

	for (k = 0; k<m_nRows - 1; k++)                  
	{
		for (j = m_nCols - 1; j >= 0; j--)
		{
			array[k][j] /= array[k][k];

		}

		for (i = k + 1; i<m_nRows; i++)
			for (j = m_nCols - 1; j >= 0; j--)
			{
				array[i][j] -= array[k][j] * array[i][k];
			}
	}

}

void jordan_additionary(double **array, double *x, int m_nRows, int m_nCols)
{
	double s = 0;
	x[m_nRows - 1] = array[m_nRows - 1][m_nCols - 1] /          
		array[m_nRows - 1][m_nCols - 2];
	for (int i = m_nRows - 2; i >= 0; i--)                       
	{
		s = 0;
		for (int k = i + 1; k<m_nRows; k++)
			s += array[i][k] * x[k];
		x[i] = array[i][m_nCols - 1] - s;
	}
}

void insert(double **array, int size)
{
	srand(time(NULL));
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size + 1; j++)
		{
			array[i][j] = rand() % 10 + 1;
		}
	}
}

int main()
{
	int size = 3;
	int m_nCols = size + 1;
	int m_nRows = size;
	double **array;
	double **additionary_array = new double*[size];

	double total_time = 0;
	double total_time1 = 0;
	int start = 0;
	int end = 0;

	double* x = new double[size];
	array = new double*[m_nRows];
	for (int i = 0; i<m_nRows; i++) {
		array[i] = new double[m_nCols];
	}
	for (int i = 0; i<m_nRows; i++) {
		additionary_array[i] = new double[m_nCols];
	}
	for (int i = 0; i < m_nRows; i++)
	{
		for (int j = 0; j < m_nCols; j++)
		{
			additionary_array[i][j] = array[i][j];
		}
	}
	cout << "matrix: " << endl;
	insert(array, size);

	output(array, size);

	start = clock();
	jordan(additionary_array, x, m_nCols, m_nRows, 0, size);
	jordan_additionary(additionary_array, x, m_nRows, m_nCols);
	end = clock();
	total_time1 = (double)(end - start) / 1000;

	start = 0;
	end = 0;

	const int potok = 2;
	int patial_potok = potok - 1;

	thread threads[potok];
	int lower_bound = 0;
	int upper_bound;

	start = clock();
	if (size%patial_potok == 0)
	{
		upper_bound = size / patial_potok;
		
		for (int k = 0; k < patial_potok; k++)
		{
			
			threads[k] = thread(jordan, array, x, m_nCols, m_nRows, lower_bound, upper_bound);
			

			lower_bound = upper_bound;
			upper_bound += size / patial_potok;

		}
		
	}
	else
	{
		upper_bound = ceil((double)size / patial_potok);
		if (upper_bound*(patial_potok - 1) < size)
		{
			for (int k = 0; k < patial_potok; k++)
			{
				if (upper_bound > size)
				{
					upper_bound = upper_bound - (upper_bound - size);
				}

				
				threads[k] = thread(jordan, array, x, m_nCols, m_nRows, lower_bound, upper_bound);
			

				lower_bound = upper_bound;
				upper_bound += ceil((double)size / patial_potok);

			}
		}
		else
		{
			upper_bound = floor((double)size / patial_potok);
			for (int k = 0; k < patial_potok; k++)
			{
				if (k == (patial_potok - 1))
				{
					upper_bound = size;
				}

				
				threads[k] = thread(jordan, array, x, m_nCols, m_nRows, lower_bound, upper_bound);
				

				lower_bound = upper_bound;
				upper_bound += floor((double)size / patial_potok);

			}
		}
	}
	

	for (int i = 0; i < potok-1; i++)
	{
		if (threads[i].joinable()) { threads[i].join(); }
	}
	/*end = clock();
	total_time += (double)(end - start) / 1000;*/

	//start = clock();
	threads[patial_potok] = thread(jordan_additionary, array, x, m_nRows, m_nCols);

	if (threads[patial_potok].joinable()) { threads[patial_potok].join(); }
	end = clock();
	total_time += (double)(end - start) / 1000;

	cout << "output:\n";
	for (int i = 0; i<m_nRows; i++)
	cout << "X" << i + 1 << "=" << x[i] << endl;

	cout << endl;
	cout << "one thread time: " << total_time1 << endl;
	cout << "many threads time: " << total_time << endl;

	system("pause");
}