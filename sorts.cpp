/*
 * sorts.cpp
 *
 *  Created on: Mar 13, 2019
 *      Author: Nicholas Leung
 *      		nml170001
 */

#include <string>
#include <iostream>
#include <array>
#include <chrono>

#include "stats.h"

// Insertion sort functions
stats insertion(int ar[], int size, std::string type);

// Selection sort functions
stats selection(int ar[], int size, std::string type);

// Quick sort functions
stats quick(int ar[], int size, std::string type);
void quickRecursion(int ar[], int low, int high);
int quickPartition(int ar[], int low, int high);
void quickSwap(int* a, int* b);

// Merge sort functions
stats merge(int ar[], int size, std::string type);
void mergeRecursion(int ar[], int left, int right);
void mergePartition(int ar[], int left, int middle, int right);

// Heap sort functions
stats heap(int ar[], int size, std::string type);
void heapRecursion(int ar[], int size);
void heapify(int ar[], int size, int node);

// Radix sort functions
stats radix(int ar[], int size, std::string type);
void radixCall(int ar[], int size);
void radixCount(int ar[], int size, int exp);

// Array functions
int* inOrderArray(int size);
int* reverseOrderArray(int size);
int* almostOrderArray(int size);
int* randomArray(int size);
int* copyArray(int ar[], int size);
void displayArray(int* ar, int size);

// Comparison and movement counters
static int cmp;
static int mv;

// Static array of sort names
static std::string nameArray[6] = {"Insertion", "Selection", "Quick", "Merge", "Heap", "Radix"};

// Driver method
int main()
{
	std::cout << "Project 2: Sorting techniques\n" << std::endl;
	// Main loop for program
	while (true)
	{
		int arrayType;
		int arraySize;

		// Get array type
		while(true)
		{
			while (true)
			{
				std::cout << "1: In Order\n2: Almost Order\n3: Reverse Order\n4: Random" << std::endl;
				std::cout << "Enter array type: ";
				std::cin >> arrayType;
				// Determine if array type given is valid
				if (arrayType >= 1 && arrayType <= 4)
				{
					break;
				}
				else
				{
					std::cout << "Invalid entry, must be an integer from 1 to 4. Please try again" << std::endl;
				}
			}
			// Get array size
			while (true)
			{
				std::cout << "Enter array size: ";
				std::cin >> arraySize;
				// Determine if array size given is valid
				if (arraySize > 0)
				{
					break;
				}
				else
				{
					std::cout << "Invalid entry, must be an integer greater than 0. Please try again" << std::endl;
				}
			}
			break;
		}

		// Arrays to sort
		int* insertionArray;
		int* selectionArray;
		int* quickArray;
		int* mergeArray;
		int* heapArray;
		int* radixArray;
		std::string arrayTypeUsed;

		// Create arrays with given types
		if (arrayType == 1)
		{
			insertionArray = inOrderArray(arraySize);
			selectionArray = inOrderArray(arraySize);
			quickArray = inOrderArray(arraySize);
			mergeArray = inOrderArray(arraySize);
			heapArray = inOrderArray(arraySize);
			radixArray = inOrderArray(arraySize);
			arrayTypeUsed = "In Order";
		}
		else if (arrayType == 2)
		{
			insertionArray = almostOrderArray(arraySize);
			selectionArray = almostOrderArray(arraySize);
			quickArray = almostOrderArray(arraySize);
			mergeArray = almostOrderArray(arraySize);
			heapArray = almostOrderArray(arraySize);
			radixArray = almostOrderArray(arraySize);
			arrayTypeUsed = "Almost Order";
		}
		else if (arrayType == 3)
		{
			insertionArray = reverseOrderArray(arraySize);
			selectionArray = reverseOrderArray(arraySize);
			quickArray = reverseOrderArray(arraySize);
			mergeArray = reverseOrderArray(arraySize);
			heapArray = reverseOrderArray(arraySize);
			radixArray = reverseOrderArray(arraySize);
			arrayTypeUsed = "Reverse Order";
		}
		else
		{
			int* array = randomArray(arraySize);
			insertionArray = copyArray(array, arraySize);
			selectionArray = copyArray(array, arraySize);
			quickArray = copyArray(array, arraySize);
			mergeArray = copyArray(array, arraySize);
			heapArray = copyArray(array, arraySize);
			radixArray = copyArray(array, arraySize);
			arrayTypeUsed = "Random";
		}

		// Sort the arrays
		stats insertionInfo = insertion(insertionArray, arraySize, arrayTypeUsed);
		stats selectionInfo = selection(selectionArray, arraySize, arrayTypeUsed);
		stats quickInfo = quick(quickArray, arraySize, arrayTypeUsed);
		stats mergeInfo = merge(mergeArray, arraySize, arrayTypeUsed);
		stats heapInfo = heap(heapArray, arraySize, arrayTypeUsed);
		stats radixInfo = radix(radixArray, arraySize, arrayTypeUsed);

		std::cout << "\nFastest algorithm(s): " << std::endl;

		// Determine the fastest sort
		double timeArray[6];
		timeArray[0] = insertionInfo.getTime();
		timeArray[1] = selectionInfo.getTime();
		timeArray[2] = quickInfo.getTime();
		timeArray[3] = mergeInfo.getTime();
		timeArray[4] = heapInfo.getTime();
		timeArray[5] = radixInfo.getTime();
		double min = timeArray[0];
		for (int a = 0; a < 6; a++)
		{
			if (timeArray[a] < min)
			{
				min = timeArray[a];
			}
		}
		for (int a = 0; a < 6; a++)
		{
			if (timeArray[a] == min)
			{
				std::cout << nameArray[a] << std::endl;
			}
		}

		// Display for sort info
		while (true)
		{
			int sortType;
			std::cout << "\n1: Insertion\n2: Selection\n3: Quick\n4: Merge\n5: Heap\n6: Radix\n7: All\n8: Exit" << std::endl;
			std::cout << "Enter sort type to display: ";
			std::cin >> sortType;
			// Display given sort infos
			if (sortType == 1)
				insertionInfo.display();
			else if (sortType == 2)
				selectionInfo.display();
			else if (sortType == 3)
				quickInfo.display();
			else if (sortType == 4)
				mergeInfo.display();
			else if (sortType == 5)
				heapInfo.display();
			else if (sortType == 6)
				radixInfo.display();
			else if (sortType == 7)
			{
				std::cout << "\nType of array: " << arrayTypeUsed << std::endl;
				std::cout << "Array size: " << arraySize << std::endl << std::endl;
				insertionInfo.displayAll();
				selectionInfo.displayAll();
				quickInfo.displayAll();
				mergeInfo.displayAll();
				heapInfo.displayAll();
				radixInfo.displayAll();
			}
			else if (sortType == 8)
			{
				break;
			}
			else
			{
				std::cout << "Invalid entry, must be an integer from 1 to 8. Please try again" << std::endl;
			}
		}
		// Exit program loop
		bool end = false;
		while (true)
		{
			int exit;
			std::cout << std::endl << std::endl;
			std::cout << "0: Exit program\n1: Continue program\n";
			std::cout << "Enter decision: ";
			std::cin >> exit;
			// Determine if program exits, continues, or error has occurred
			if (exit == 0)
			{
				end = true;
				break;
			}
			else if (exit == 1)
			{
				break;
			}
			else
			{
				std::cout << "Invalid entry, must be either 0 or 1. Please try again" << std::endl;
			}
		}
		std::cout << std::endl << std::endl;
		if (end)
			break;
	}
	return 0;
}

// Insertion sort
stats insertion(int ar[], int size, std::string type)
{
	cmp = 0;
	mv = 0;
	std::chrono::duration<double> ms;

	int	i;
	int j;
	int key;

	auto startTime = std::chrono::high_resolution_clock::now();

	for (i = 1; i < size; i++)
	{
		key = ar[i];
		j = i - 1;
		int temp = i - 1;
		while (j >= 0 && ar[j] > key)
		{
			mv += 2;
			ar[j + 1] = ar[j];
			j--;
		}
		cmp = cmp + (temp - j + 1);
		if (temp - j != 0)
		{
			mv++;
			ar[j + 1] = key;
		}
	}

	auto endTime = std::chrono::high_resolution_clock::now();
	ms = endTime - startTime;
	stats info(size, type, "Insertion", cmp, mv, ms);
	return info;
}

// Selection sort
stats selection(int ar[], int size, std::string type)
{
	cmp = 0;
	mv = 0;
	std::chrono::duration<double> ms;

	int i;
	int j;
	int min;

	auto startTime = std::chrono::high_resolution_clock::now();

	for (i = 0; i < size - 1; i++)
	{
		min = i;
		for (j = i + 1; j < size; j++)
		{
			cmp++;
			if (ar[j] < ar[min])
			{
				min = j;
			}
		}
		if (min != i)
		{
			mv += 2;
			int temp = ar[i];
			ar[i] = ar[min];
			ar[min] = temp;
		}
	}

	auto endTime = std::chrono::high_resolution_clock::now();
	ms = endTime - startTime;
	stats info(size, type, "Selection", cmp, mv, ms);
	return info;
}

// Quick sort start
stats quick(int ar[], int size, std::string type)
{
	cmp = 0;
	mv = 0;
	std::chrono::duration<double> ms;
	auto startTime = std::chrono::high_resolution_clock::now();

	quickRecursion(ar, 0, size - 1);

	auto endTime = std::chrono::high_resolution_clock::now();
	ms = endTime - startTime;
	stats info(size, type, "Quick", cmp, mv, ms);
	return info;
}

// Quick sort recursion function
void quickRecursion(int ar[], int low, int high)
{
	if (low < high)
	{
		int partition = quickPartition(ar, low, high);
		quickRecursion(ar, low, partition - 1);
		quickRecursion(ar, partition + 1, high);
	}
}

// Quick sort partition
int quickPartition(int ar[], int low, int high)
{
	int pivot = ar[high];
	int i = (low - 1);
	int j;

	for (j = low; j <= high - 1; j++)
	{
		cmp++;
		if (ar[j] <= pivot)
		{
			i++;
			quickSwap(&ar[i], &ar[j]);
		}
	}
	quickSwap(&ar[i + 1], &ar[high]);
	return (i + 1);
}

// Quick sort swap function
void quickSwap(int* x, int* y)
{
	mv += 2;
	int temp = *x;
	*x = *y;
	*y = temp;
}

// Merge sort start
stats merge(int ar[], int size, std::string type)
{
	cmp = 0;
	mv = 0;
	std::chrono::duration<double> ms;
	auto startTime = std::chrono::high_resolution_clock::now();

	mergeRecursion(ar, 0, size - 1);

	auto endTime = std::chrono::high_resolution_clock::now();
	ms = endTime - startTime;
	stats info(size, type, "Merge", cmp, mv, ms);
	return info;
}

// Merge sort recursion function
void mergeRecursion(int ar[], int left, int right)
{
	if (left < right)
	{
		int middle = (left + (right - 1)) / 2;
		mergeRecursion(ar, left, middle);
		mergeRecursion(ar, middle + 1, right);
		mergePartition(ar, left, middle, right);
	}
}

// Merge sort partition
void mergePartition(int ar[], int left, int middle, int right)
{
	int i;
	int j;
	int k;
	int n1 = middle - left + 1;
	int n2 = right - middle;

	int lArray[n1];
	int rArray[n2];

	for (i = 0; i < n1; i++)
	{
		lArray[i] = ar[left + i];
	}
	for (j = 0; j < n2; j++)
	{
		rArray[j] = ar[middle + 1 + j];
	}

	i = 0;
	j = 0;
	k = left;

	while (i < n1 && j < n2)
	{
		cmp++;
		if (lArray[i] <= rArray[j])
		{
			mv++;
			ar[k] = lArray[i];
			i++;
		}
		else
		{
			mv++;
			ar[k] = rArray[j];
			j++;
		}
		k++;
	}

	while (i < n1)
	{
		mv++;
		ar[k] = lArray[i];
		i++;
		k++;
	}
	while (j < n2)
	{
		mv++;
		ar[k] = rArray[j];
		j++;
		k++;
	}
}

// Heap sort start
stats heap(int ar[], int size, std::string type)
{
	cmp = 0;
	mv = 0;
	std::chrono::duration<double> ms;
	auto startTime = std::chrono::high_resolution_clock::now();

	heapRecursion(ar, size);

	auto endTime = std::chrono::high_resolution_clock::now();
	ms = endTime - startTime;
	stats info(size, type, "Heap", cmp, mv, ms);
	return info;
}

// Heap sort recursion function
void heapRecursion(int ar[], int size)
{
	for (int i = (size / 2) - 1; i >= 0; i--)
	{
		heapify(ar, size, i);
	}
	for (int i = size - 1; i >= 0; i--)
	{
		mv++;
		std::swap(ar[0], ar[i]);
		heapify(ar, i, 0);
	}
}

// Heap sort heapify function
void heapify(int ar[], int size, int node)
{
	int largest = node;
	int left = (2 * node) + 1;
	int right = (2 * node) + 2;

	cmp += 3;
	if (left < size && ar[left] > ar[largest])
	{
		largest = left;
	}
	if (right < size && ar[right] > ar[largest])
	{
		largest = right;
	}
	if (largest != node)
	{
		mv++;
		std::swap(ar[node], ar[largest]);
		heapify(ar, size, largest);
	}
}

// Radix sort start
stats radix(int ar[], int size, std::string type)
{
	cmp = 0;
	mv = 0;
	std::chrono::duration<double> ms;
	auto startTime = std::chrono::high_resolution_clock::now();

	radixCall(ar, size);

	auto endTime = std::chrono::high_resolution_clock::now();
	ms = endTime - startTime;
	stats info(size, type, "Radix", cmp, mv, ms);
	return info;
}

// Radix sort call function
void radixCall(int ar[], int size)
{
	int max = ar[0];
	for (int i = 1; i < size; i++)
	{
		if (ar[i] > max)
		{
			max = ar[i];
		}
	}
	for (int j = 1; max/j > 0; j *= 10)
	{
		radixCount(ar, size, j);
	}
}

// Radix sort count function
void radixCount(int ar[], int size, int exp)
{
	int array[size];
	int i;
	int count[10] = {0};

	for (i = 0; i < size; i++)
	{
		int index = (ar[i] / exp) % 10;
		count[index]++;
	}
	for (int i = 1; i < 10; i++)
	{
		count[i] += count[i - 1];
	}
	for (i = size - 1; i >= 0; i--)
	{
		int index = (ar[i] / exp) % 10;
		array[count[index] - 1] = ar[i];
		count[index]--;
	}
	for (i = 0; i < size; i++)
	{
		mv++;
		ar[i] = array[i];
	}
}

// Create an in order array
int* inOrderArray(int size)
{
	int* array = new int[size];
	for (int a = 0; a < size; a++)
	{
		array[a] = a + 1;
	}
	return array;
}

// Create a reverse order array
int* reverseOrderArray(int size)
{
	int* array = new int[size];
	for (int a = 0; a < size; a++)
	{
		array[a] = size - a;
	}
	return array;
}

// Create an almost ordered array
int* almostOrderArray(int size)
{
	int* array = new int[size];
	for (int a = 0; a < size; a++)
	{
		array[a] = a + 1;
	}
	int temp = array[0];
	array[0] = array[size - 1];
	array[size - 1] = temp;
	return array;
}

// Create a random ordered array
int* randomArray(int size)
{
	srand((int) time(0));
	int* array = new int[size];
	for (int a = 0; a < size; a++)
	{
		array[a] = (rand() % size) + 1;
	}
	return array;
}

// Deep copy an array
int* copyArray(int ar[], int size)
{
	int* array = new int[size];
	for (int a = 0; a < size; a++)
	{
		array[a] = ar[a];
	}
	return array;
}

// Display array
void displayArray(int ar[], int size)
{
	for (int a = 0; a < size; a++)
	{
		std::cout << ar[a] << " ";
	}
	std::cout << std::endl;
}
