
#ifndef Simulation_Controller_Header
#define Simulation_Controller_Header

// Required for definitions and global class.
#include "Definitions.h"
#include "Problem_Definiton.h"


class Simulation_Controller{
	Problem_Definition Problem_Rules;

		// Default constructor
	public: Simulation_Controller(){

	}
		// Default destructor
	public: ~Simulation_Controller(){

	}

		// Run the program.
	public: int Tick(){



		int debug = 0;

		return 0;
	}


		//Basic Utilities
	public: void Set_Problem_Definition(Problem_Definition argument){
		Problem_Rules = argument;
	}
	//public: void 

};


#endif