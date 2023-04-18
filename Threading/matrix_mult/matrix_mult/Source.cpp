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
			m[i][j] = i+step/*j + step*/;
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
			printf("%d ", m[i][j], " ");
		}
		printf("\n");
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

int **sum;

void one_thread_multiplication(int **one, int **two, const int size)
{
	int s;
	for (int i = 0; i<size; i++) {
		for (int l = 0; l<size; l++) {
			s = 0;
			for (int j = 0; j<size; j++) {
				s += one[i][j] * two[j][l];
			}
			sum[i][l] = s;
		}
	}
}

void row(int **two, int **one, const int size, int bound, int b)
{
	int k = 0;
	int s;

	for (int i = b; i < bound; i++)
	{
		for (int l = 0; l < size; l++) {
			s = 0;
			for (int j = 0; j < size; j++)
			{
				s += one[i][j] * two[j][l];
			}
			sum[b][l] = s;
			//printf("%d ", one[i][l]);
			//printf("%d ", sum[b][l]);
		}
		b++;
		//printf("\n");
	}

}

double main_algorithm(const int potok, const int size, int **one, int **two, thread *threads)
{
	int b = 0;
	int bound;

	int start;
	int end;
	double time_sum = 0;

	start = clock();
	if (size%potok == 0)
	{
		bound = size / potok;
		for (int k = 0; k < potok; k++)
		{
			

		    threads[k] = thread(row, two, one, size, bound, b);
			//row(two, one, size, bound, b);

			
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
					bound = size;
				}

				threads[k] = thread(row, two, one, size, bound, b);

				

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
				
				threads[k] = thread(row, two, one, size, bound, b);
			
				
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

	end = clock();
	time_sum += (double)(end - start) / 1000;

	return time_sum;
}


int main()
{
	const int size = 1000;
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

	sum = new int*[size];
	sum = crm(sum, size);

	int tStart1 = clock();

	one_thread_multiplication(one, two, size);

	int tStart2 = clock();
	double one_thread = (double)(tStart2 - tStart1) / 1000;

	cout << endl;

	const int potok = 2;

	thread threads[potok];
	
	double many_threads = main_algorithm(potok, size, one, two, threads);

	cout << "***************************************************" << endl;
	
    //output(sum, size);
	cout << endl << endl;

	cout << "-----------------------------------------------" << endl;
	printf("one thread: %f\n", one_thread);
	printf("many threads: %f\n", many_threads);

	system("pause");
}
