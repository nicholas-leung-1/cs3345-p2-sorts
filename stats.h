/*
 * stats.h
 *
 *  Created on: Mar 13, 2019
 *      Author: Nicholas Leung
 *      		nml170001
 */

#ifndef STATS_H_
#define STATS_H_

#include <string>
#include <iostream>
#include <array>
#include <chrono>

// Return info and stats for the searches
class stats
{
	public:
		// Size of array
		int size;
		// Array type
		std::string type;
		// Sort type
		std::string sort;
		// Number of comparisons
		int comparisons;
		// Number of movements
		int movements;
		// Time elapsed
		std::chrono::duration<double> milliseconds;
		// Constructors
		stats();
		stats(int aSize, std::string aType, std::string aSort,
				int cp, int mv, std::chrono::duration<double> ms);
		// Functions
		void display();
		void displayAll();
		double getTime();
};

// Default constructor
stats::stats()
{

}

// Constructor for all variables
stats::stats(int aSize, std::string aType, std::string aSort,
		int cp, int mv, std::chrono::duration<double> ms)
{
	size = aSize;
	type = aType;
	sort = aSort;
	comparisons = cp;
	movements = mv;
	milliseconds = ms;
}

// Display all info
void stats::display()
{
	std::cout << std::endl;
	std::cout << "Type of array: " << type << std::endl;
	std::cout << "Array size: " << size << std::endl;
	std::cout << "Sort: " << sort << std::endl;
	std::cout << "Comparisons: " << comparisons << std::endl;
	std::cout << "Movements: " << movements << std::endl;
	std::cout << "Runtime: " << milliseconds.count() << std::endl << std::endl;
}

// Display sort info, no array info
void stats::displayAll()
{
	std::cout << "Sort: " << sort << std::endl;
	std::cout << "Comparisons: " << comparisons << std::endl;
	std::cout << "Movements: " << movements << std::endl;
	std::cout << "Runtime: " << milliseconds.count() << std::endl << std::endl;
}

// Convert time to double
double stats::getTime()
{
	double temp = milliseconds.count();
	return temp;
}

#endif /* STATS_H_ */
