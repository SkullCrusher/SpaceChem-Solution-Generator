
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
		
			// Debugging I am just putting my solution in to test the simulation
		Solution_Reactor TheChosenOne;

			// The blue instructions.
		TheChosenOne.Set_Instruction_For_Tile(1, 0, Blue_Tile, Instruction_Down,		Instruction_NOP);
		TheChosenOne.Set_Instruction_For_Tile(2, 0, Blue_Tile, Instruction_Sync,		Instruction_NOP);
		TheChosenOne.Set_Instruction_For_Tile(3, 0, Blue_Tile, Instruction_Start_Left,	Instruction_NOP);
		TheChosenOne.Set_Instruction_For_Tile(7, 0, Blue_Tile, Instruction_NOP,			Instruction_Left);
		TheChosenOne.Set_Instruction_For_Tile(1, 1, Blue_Tile, Instruction_Grab,		Instruction_NOP);
		TheChosenOne.Set_Instruction_For_Tile(7, 1, Blue_Tile, Instruction_Out_Omega,	Instruction_NOP);
		TheChosenOne.Set_Instruction_For_Tile(1, 2, Blue_Tile, Instruction_NOP,			Instruction_Right);
		TheChosenOne.Set_Instruction_For_Tile(7, 2, Blue_Tile, Instruction_Drop,		Instruction_Up);

			// The red instructions.
		TheChosenOne.Set_Instruction_For_Tile(2, 1, Red_Tile, Instruction_Grab,			Instruction_Down);
		TheChosenOne.Set_Instruction_For_Tile(3, 1, Red_Tile, Instruction_Sync,			Instruction_NOP);
		TheChosenOne.Set_Instruction_For_Tile(4, 1, Red_Tile, Instruction_Bond_Remove,	Instruction_NOP);
		TheChosenOne.Set_Instruction_For_Tile(5, 1, Red_Tile, Instruction_In_Alpha,		Instruction_NOP);
		TheChosenOne.Set_Instruction_For_Tile(6, 1, Red_Tile, Instruction_Start_Left,	Instruction_NOP);
		TheChosenOne.Set_Instruction_For_Tile(7, 1, Red_Tile, Instruction_Out_Omega,	Instruction_Start_Left);
		TheChosenOne.Set_Instruction_For_Tile(2, 2, Red_Tile, Instruction_NOP,			Instruction_Start_Right);
		TheChosenOne.Set_Instruction_For_Tile(7, 2, Red_Tile, Instruction_Drop,			Instruction_Start_Up);

			
		Simulation RunMe;

			// Set the reactor to simulate.
		RunMe.Set_Solution(TheChosenOne);

			// Limit the simulation to prevent unlimited running.
		RunMe.Set_Cycle_Limit_Simulation(Problem_Rules.Get_Cycle_Limit_Simulation());

			// Process the simulation.
		int Results = Simulation_Continue;
		while (Results == Simulation_Continue){
			Results = RunMe.Tick();
		}
		
	
		return 0;
	}


		//Basic Utilities
	public: void Set_Problem_Definition(Problem_Definition argument){ Problem_Rules = argument; }
	

};


#endif