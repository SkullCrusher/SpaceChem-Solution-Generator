
#ifndef Simulation_Controller_Header
#define Simulation_Controller_Header

	// Required for definitions and global class.
#include "Definitions.h"
#include "Problem_Definiton.h"
#include "Solution.h"

	// Core parts of the program.
#include "Simulation.h"
#include "Generation.h"


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
		
		//Debugging I am just putting my solution in to test the simulation

		Solution_Reactor TheChosenOne;


			// The blue instructions.
		TheChosenOne.Set_Instruction_For_Tile(1, 0, false, -1, Instruction_Down);
		TheChosenOne.Set_Instruction_For_Tile(2, 0, false, -1, Instruction_Sync);
		TheChosenOne.Set_Instruction_For_Tile(3, 0, false, -1, Instruction_Start_Left);
		TheChosenOne.Set_Instruction_For_Tile(7, 0, false, -1, Instruction_Left);

		TheChosenOne.Set_Instruction_For_Tile(1, 1, false, Instruction_Grab, -1);
		TheChosenOne.Set_Instruction_For_Tile(7, 1, false, Instruction_Out_Omega, -1);

		TheChosenOne.Set_Instruction_For_Tile(1, 2, false, -1, Instruction_Right);
		TheChosenOne.Set_Instruction_For_Tile(7, 2, false, Instruction_Drop, Instruction_Up);






		Simulation RunMe;

		RunMe.Set_Solution(TheChosenOne);















		int debug = 0;
	
		return 0;
	}


		//Basic Utilities
	public: void Set_Problem_Definition(Problem_Definition argument){ Problem_Rules = argument; }
	

};


#endif