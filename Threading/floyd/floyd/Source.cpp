#include <iostream>
#include <ctime>
#include <thread>
#include <vector>
using namespace std;
#define _inf 9999;

const int Size = 700;
int GR[Size][Size];
int new_val[Size][Size];
int GR2[Size][Size];
int routeMatrix[Size][Size];

int min(int a, int b)
{
	if (a < b) { return a; }
	else { return b; }
}

void FU(int D[][Size], int b, int bound)
{
	for (int k = b; k < bound; k++)
	{
		for (int i = 0; i < Size; i++)
		{
			for (int j = 0; j < Size; j++)
			{
				if (D[i][j] != min(D[i][j], D[i][k] + D[k][j]))
				{
					routeMatrix[i][j] = k + 1;
				}
				D[i][j] = min(D[i][j], D[i][k] + D[k][j]);
				new_val[i][j] = D[i][j];
				
			}
		}

	}
}

void insert()
{
	srand(time(NULL));
	for (int i = 0; i < Size; i++)

		for (int j = 0; j < Size; j++)
		{
			if (i == j)
			{
				GR[i][j] = 0;
				GR2[i][j] = 0;
			}
			else
			{
				GR[i][j] = rand() % 10;
				if (GR[i][j] == 0) { GR[i][j] = _inf; }
				GR2[i][j] = GR[i][j];
			}
			//cin >> GR[i][j];
		}
}
void output()
{
	for (int i = 0; i < Size; i++)
	{
		for (int j = 0; j < Size; j++)
		{

			cout << GR[i][j] << '\t';
		}
		cout << endl;
	}

}

void output_shortest()
{

	for (int i = 0; i<Size; i++)
	{
		for (int j = 0; j<Size; j++) cout << new_val[i][j] << "\t";
		cout << endl;
	}
	cout << endl;

}

void buildRoute(int routeMatrix[][Size], int size, int u, int v, vector<int> &vec)
{
	vec.push_back(u);
	while (true)
	{
		if (routeMatrix[u - 1][v - 1] == 0)
		{
			vec.push_back(v);
			break;
		}
		vec.push_back(routeMatrix[u - 1][v - 1]);
		u = routeMatrix[u - 1][v - 1];

		if (routeMatrix[u - 1][v - 1] == v)
		{
			vec.push_back(routeMatrix[u - 1][v - 1]);
			break;
		}


	}
}

void main()
{
	int start = 0;
	int end = 0;
	double one_thread_total_time = 0;
	double many_threads_total_time = 0;

	for (int i = 0; i < Size; i++)
	{
		for (int j = 0; j < Size; j++)
		{
			routeMatrix[i][j] = 0;
		}
	}

	insert();
	//output();
	cout << "shortest ways:" << endl;

	start = clock();
	FU(GR, 0, Size);
	end = clock();
	one_thread_total_time = (double)(end - start) / 1000;
	start = 0;
	end = 0;

	//output_shortest();
	//-------------------------------------------------------------------------

	/*for (int i = 0; i < Size; i++)
	{
		for (int j = 0; j < Size; j++)
		{
			if (routeMatrix[i][j] == 0 && i != j) { cout << i+1 << " "; }
			else 
			{
				cout << routeMatrix[i][j] << " ";
			}
			
		} cout << endl;
	}*/
	/*vector<int> vec;
	int u, v;
	
		cout << "start node: "; cin >> u;
		cout << "end node: "; cin >> v;

		buildRoute(routeMatrix, Size, u, v, vec);

		for (int i = 0; i < vec.size(); i++)
		{
			cout << vec[i] << " ";
		}cout << endl;
*/
	//-------------------------------------------------------------------------

		const int potok = 4;
		thread threads[potok];

		int b = 0;
		int bound;

		start = clock();
		if (Size%potok == 0)
		{
			bound = Size / potok;
			for (int k = 0; k < potok; k++)
			{
				threads[k] = thread(FU, GR2, b, bound);

				b = bound;
				bound += Size / potok;

			}
		}

		else
		{
			bound = ceil((double)Size / potok);
			if (bound*(potok - 1) < Size)
			{
				for (int k = 0; k < potok; k++)
				{
					if (bound > Size)
					{
						bound = Size;
					}

					threads[k] = thread(FU, GR2, b, bound);

					b = bound;
					bound += ceil((double)Size / potok);

				}
			}
			else
			{
				bound = floor((double)Size / potok);
				for (int k = 0; k < potok; k++)
				{
					if (k == (potok - 1))
					{
						bound = Size;
					}

					threads[k] = thread(FU, GR2, b, bound);

					b = bound;
					bound += floor((double)Size / potok);

				}
			}
		}

		for (int i = 0; i < potok; i++)
		{
			if (threads[i].joinable()) { threads[i].join(); }
		}
		end = clock();
		many_threads_total_time = (double)(end - start) / 1000;

		//output_shortest();

		cout << "one thread time: " << one_thread_total_time << endl;
		cout << "many threads time: " << many_threads_total_time << endl;
		system("pause");
}
