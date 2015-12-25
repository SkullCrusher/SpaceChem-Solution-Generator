// A simulation of a reactor.

#ifndef Simulation_Header
#define Simulation_Header

	// Required for definitions and global class.
#include "Definitions.h"

#include "Waldo.h"
#include "Solution.h"


class Simulation{
	
	/*
		#define Simulation_Continue 0
		#define Simulation_Complete 1
		#define Simulation_OutOfCycles 2
		#define Simulation_InvalidSimulation 3
	*/

		// The cap on cycles.
	unsigned long Cycle_Limit_Simulation;

		// How many cycles have been simulated,
	unsigned long Cycles;

	Solution_Reactor Solution;

	Waldo Red_Waldo;
	Waldo Blue_Waldo;


		// Default constructor.
	public: Simulation(){
		Cycle_Limit_Simulation = 0;
		Cycles = 0;
	}

		// Default destructor.
	public: ~Simulation(){}

		// Finds the starting instruction in the solution for the waldo.
	private: short FindStart(bool RedorBlue, Waldo &argument){

		for (int w = 0; w < 10; w++){
			for (int h = 0; h < 8; h++){				
				Tile Result = Solution.GetTile(w, h, RedorBlue);
					
					// If the tile is a starting point, set it.
				if (Result.Instruction_1 == Instruction_Start_Left  || 
					Result.Instruction_1 == Instruction_Start_Right ||
					Result.Instruction_1 == Instruction_Start_Up	||
					Result.Instruction_1 == Instruction_Start_Down){

					short Direction = -1;

					if (Result.Instruction_1 == Instruction_Start_Left){Direction = Instruction_Left;}
					if (Result.Instruction_1 == Instruction_Start_Right){Direction = Instruction_Right;}
					if (Result.Instruction_1 == Instruction_Start_Up){Direction = Instruction_Up;}
					if (Result.Instruction_1 == Instruction_Start_Down){Direction = Instruction_Down;}

					argument.SetX(w);
					argument.SetY(h);
					argument.SetActive(true);
					argument.Set_Direction(Direction);

					return Simulation_Continue;
				}							
			}
		}		

		return Simulation_Continue;
	}

		// Generates the requirements to start the simulation.
	private: int GenerateDefaults(){
			// Find the starting point and direction of the waldos.
		
		int RedStart_R = FindStart(Red_Tile, Red_Waldo);
		int BlueStart_R = FindStart(Blue_Tile, Blue_Waldo);

		return Simulation_Continue;
	}

		// Process the simulation.
	public: int Tick(){
	
			// Halt the simulation if the cycles have reached the cap.
		if (Cycles >= Cycle_Limit_Simulation){
			return Simulation_OutOfCycles;
		}

			// If this is the first tick run the requirements to fill in the waldo.
		if (Cycles == 0){
			int Result = GenerateDefaults();

				// If there was an error.
			if (Result == Simulation_InvalidSimulation){
				return Simulation_InvalidSimulation;
			}
		}


		
		Cycles++;

		return Simulation_Continue;
	}

		// Accept a new solution.
	public: void Set_Solution(Solution_Reactor argument) {
		Solution = argument;
	}

	public: void Set_Cycle_Limit_Simulation(int argument){
		Cycle_Limit_Simulation = argument;
	}

};


#endif