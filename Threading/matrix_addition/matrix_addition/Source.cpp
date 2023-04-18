#include <iostream>
#include <string>
#include <thread>
#include <ctime>
#include <time.h>

using namespace std;

int **insert(int **m, const int s, int step)
{
	for (int i = 0; i < s; i++)
	{
		for (int j = 0; j < s; j++)
		{
			m[i][j] = j + step;
		}
	}
	return m;
}

void output(int **m, const int s)
{
	for (int i = 0; i<s; i++)
	{
		for (int j = 0; j<s; j++)
		{
			cout << m[i][j] << " ";
		}
		cout << endl;
	}
}

int **crm(int **m, const int s)
{
	for (int i = 0; i < s; i++)
	{
		m[i] = new int[s];
	}
	return m;
}

void matrix_sum(int **one, int **two, const int size)
{
	int **sum = new int*[size];
	sum = crm(sum, size);
	for (int i = 0; i<size; i++)
	{
		for (int j = 0; j<size; j++)
			sum[i][j] = one[i][j] + two[i][j];

	}
	//output(sum, size);
}

int **sum;

void add(int **one, int **two, const int size, int bound, int b)
{
	
	for (int i = 0; i < size; i++)
	{
		for (int j = b; j <bound; j++)
		{
			//cout << one[i][j] + two[i][j] << " ";
			sum[i][j] = one[i][j] + two[i][j];
		}
		//cout << endl;
	}
}

double main_algorithm(const int potok, const int size, int **one, int **two, thread *threads)
{
	int b = 0;
	int bound;
	double time_sum = 0;

	int start;
	int end;
	if (size%potok == 0)
	{
		bound = size / potok;
		for (int k = 0; k < potok; k++)
		{
			//add(one, two, size, bound, b);
			start = clock();

		    threads[k] = thread(add, one, two, size, bound, b);

			end = clock();

			time_sum += (double)(end - start) / 1000;
			
			b = bound;
			bound += size / potok;

			cout << "__________________________" << endl;
		}
	}

	else
	{
		bound = ceil((double)size / potok);
		if (bound*(potok - 1) < size)
		{
			for (int k = 0; k < potok; k++)
			{
				if (bound > size)
				{
					bound = bound - (bound - size);
				}
			    //add(one, two, size, bound, b);
				start = clock(); 

				threads[k] = thread(add, one, two, size, bound, b);

				end = clock();

				time_sum += (double)(end - start) / 1000;
				
				b = bound;
				bound += ceil((double)size / potok);

				cout << "__________________________" << endl;
			}
		}
		else
		{
			bound = floor((double)size / potok);
			for (int k = 0; k < potok; k++)
			{
				if (k == (potok - 1))
				{
					bound = size;
				}

				//add(one, two, size, bound, b);
				start = clock();

				threads[k] = thread(add, one, two, size, bound, b);

				end = clock();

				time_sum += (double)(end - start) / 1000;
				
				b = bound;
				bound += floor((double)size / potok);

				cout << "__________________________" << endl;
			}
		}
	}

	for (int i = 0; i < potok; i++)
	{
		if (threads[i].joinable()) { threads[i].join(); }
	}
	return time_sum;
}


int main()
{
	
	const int size = 10000;
	int **one = new int*[size];
	int **two = new int*[size];

	cout << "first matrix: " << endl;
	one = crm(one, size);
	one = insert(one, size, 1);
	//output(one, size);

	cout << "second matrix: " << endl;
	two = crm(two, size);
	two = insert(two, size, 10);
	//output(two, size);

	cout << "______________________________" << endl;
	cout << "result matrix: " << endl;

	int tStart1 = clock();

	matrix_sum(one, two, size);

	int tStart2 = clock();
	double one_thread = (double)(tStart2 - tStart1)/1000;

	cout << endl;

	const int potok = 100;
	
	thread threads[potok];
	sum = new int*[size];
	sum = crm(sum, size);

	double many_threads = main_algorithm(potok, size, one, two, threads);

	cout << "***************************************************" << endl;
	
	//output(sum, size);
	cout << endl << endl;

	cout << "-----------------------------------------------" << endl;
	cout << "one thread: " << one_thread << endl;
	cout << "many threads: " << many_threads << endl;
	system("pause");
}

