﻿//g++ -c openmpshell.cpp -o openmpshell.o -fopenmp
//g++ openmpshell.cpp openmpshell -fopenmp -lpthread


#include "pch.h"
#include <iostream>
#include "malloc.h"
#include "omp.h"
#include <time.h>
#include <ctime>
#include <cstdlib>

using namespace std;

//a[] is sort , n is size
void ShellSort(int a[], int n)
{
	int gap;
	int j;
	int i;
	int element;

	for (gap = n / 2; gap > 0; gap /= 2)
	{
#pragma omp parallel for shared( a, gap,n) private(i) default(none)
		for (i = gap; i < n; i++)
		{
#pragma omp parallel
			element = a[i];
			for (j = i; j >= gap; j -= gap)
			{
#pragma omp critical
				if (element < a[j - gap])
					a[j] = a[j - gap];
				else
					break;
			}
			a[j] = element;
		}
	}
}


void print(int a[], int size)
{

	for (int i = 0; i < size; i++)
		cout << a[i] << "";
	cout << endl;
}



int main()
{

	int n = 2000;
	int a[2000];
	int i ;
	srand((time(NULL)));

#pragma omp parallel for num_threads(i)
	for (i = 0; i < n; i++)
	{
		a[i] = (rand() % 100000) + 1;

	}

	double startTime = clock();

	cout << "enter element:" << endl;
	cin >> n;
	cout << "enter elements the one that you put earlier:" << endl;
	for (int i = 0; i < n; i++)
	{
		cin >> a[i];
	}
	cout << "array seq before sorting: ";
	print(a, n);
	ShellSort(a, n);
	cout << "array seq after sorting: ";
	print(a, n);



	ShellSort(a, n);
	double endTime = clock();
	int totalTime = endTime - startTime; // The average time to run this

	cout << "This is the time it took to run.\n" << endl; 
	cout<< totalTime / 2000 <<n<< endl;





}



