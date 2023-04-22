#include <stdio.h> 
#include <limits.h> 
#include<stdbool.h> 
#include <ctime>
#include <iostream>
#include <thread>
using namespace std;

#define V 10000

int *parent = new int[V];

int *key = new int[V];
 
bool *mstSet = new bool[V];

int minKey(int *key, bool *mstSet)
{
	int min = INT_MAX, min_index;

	for (int v = 0; v < V; v++)
		if (mstSet[v] == false && key[v] < min)
			min = key[v], min_index = v;

	return min_index;
}


void printMST(int *parent, int n, int **graph)
{
	int mindist = 0;
	printf("Edge \tWeight\n");
	for (int i = 1; i < V; i++)
	{
		printf("%d - %d \t%d \n", parent[i], i, graph[i][parent[i]]);
		mindist += graph[i][parent[i]];
	}
	cout << "minimum distance: " << mindist << endl;
}

void primMST(int **graph, int b, int bound)
{
	
	key[0] = 0;
	parent[0] = -1;
 
	for (int count = b; count < bound - 1; count++)                     
	{
		int u = minKey(key, mstSet);

		mstSet[u] = true;

		for (int v = 0; v < V; v++)

			if (graph[u][v] && mstSet[v] == false && graph[u][v] < key[v])
				parent[v] = u, key[v] = graph[u][v];
	}

}

void insert(int **graph)
{
	srand(time(NULL));
	for (int i = 0; i < V; i++)
	{
		for (int j = i; j < V; j++)
		{
			if (i == j){graph[i][j] = 0;}
			else { graph[i][j] = rand() % 10; graph[j][i] = graph[i][j]; }
		}
	}
}

void print(int **graph)
{
	for (int i = 0; i < V; i++)
	{
		for (int j = 0; j < V; j++)
			cout << graph[i][j] << '\t';
		cout << endl;
	}

}

int main()
{
	int start = 0;
	int end = 0;
	double one_thread_total_time = 0;
	double many_threads_total_time = 0;

	for (int i = 0; i < V; i++)
		key[i] = INT_MAX, mstSet[i] = false;

	int **graph = new int*[V];
	for (int i = 0; i < V; i++)
	{
		graph[i] = new int[V];
	}

	insert(graph);
	//print(graph);

	start = clock();
	primMST(graph, 0, V - 1);
	end = clock();
	one_thread_total_time = (double)(end - start) / 1000;
	start = 0;
	end = 0;

	//printMST(parent, V, graph);
	cout << endl;

	for (int i = 0; i < V; i++)
	{
		key[i] = INT_MAX, mstSet[i] = false;
		parent[i] = 0;
	}

	const int potok = 16;
	thread threads[potok];

	int b = 0;
	int bound;

	start = clock();
	if (V%potok == 0)
	{
		bound = V / potok;
		for (int k = 0; k < potok; k++)
		{
			threads[k] = thread(primMST, graph, b, bound);

			b = bound;
			bound += V / potok;

		}
	}
	
	else
	{
		bound = ceil((double)V / potok);
		if (bound*(potok - 1) < V)
		{
			for (int k = 0; k < potok; k++)
			{
				if (bound > V)
				{
					bound = V;
				}

				threads[k] = thread(primMST, graph, b, bound);

				b = bound;
				bound += ceil((double)V / potok);

			}
		}
		else
		{
			bound = floor((double)V / potok);
			for (int k = 0; k < potok; k++)
			{
				if (k == (potok - 1))
				{
					bound = V;
				}

				threads[k] = thread(primMST, graph, b, bound);

				b = bound;
				bound += floor((double)V / potok);

			}
		}
	}

	
	for (int i = 0; i < potok; i++)
	{
		if (threads[i].joinable()) { threads[i].join(); }
	}
	end = clock();
	many_threads_total_time = (double)(end - start) / 1000;

	//printMST(parent, V, graph);

	cout << "one thread time: " << one_thread_total_time << endl;
	cout << "many threads time: " << many_threads_total_time << endl;
	system("pause");
	return 0;
}