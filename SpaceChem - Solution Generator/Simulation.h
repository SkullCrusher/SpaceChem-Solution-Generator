// A simulation of


#ifndef Simulation_Header
#define Simulation_Header

	// Required for definitions and global class.
#include "Definitions.h"

#include "Waldo.h"
#include "Solution.h"


class Simulation{
	
	Solution_Reactor Solution;


		// Default constructor
	public: Simulation(){}

		// Default destructor
	public: ~Simulation(){}

		// Process the simulation.
	public: int Tick(){}

		//Accept a new solution.
	public: void Set_Solution(Solution_Reactor argument) {
		Solution = argument;
	}

};


#endif