//SpaceChem Problem Solver - Written by David Harkins
#include <iostream>
#include <stdlib.h>
#include <fstream>

	// Each core part of the program.
#include "Simulation_Controller.h"

	// Commonly used definitions for all core parts of the program.
#include "Definitions.h"
#include "Problem_Definiton.h"

	// To be done after.
void PrintUsage(){
	printf("--\n");
	printf("--\n");

}

	// Load file by full path and return a pointer to a char *str or null.
char *LoadFileByName(std::string argument){

	std::streampos size;
	char * memblock;

	std::ifstream file(argument.c_str(), std::ios::in | std::ios::binary | std::ios::ate);
	if (file.is_open()){

		size = file.tellg();
		memblock = new char[size];
		file.seekg(0, std::ios::beg);
		file.read(memblock, size);
		file.close();

	}else{ return NULL; }

	return memblock;
}

int main(int argc, char *argv[]) {

		// Debugging - Change later.
	printf("SpaceChem Solution Generator - written by David Harkins.\n");

		// Validate the arguments
	if (argc < Minimum_Argument_Count || argc > Maximum_Argument_Count){
		PrintUsage();

			// Debugging - Disabled the return.
		// return Error_Incorrect_Argument_Count;
	}

		// Load the file argument.
	//not sure of the format yet so we will skip this.


		//Debugging. We are going to work on the simulation first.
	
	Problem_Definition debugging_def;

	debugging_def.Add_Instruction(Instruction_Start_Left);
	debugging_def.Add_Instruction(Instruction_Start_Right);
	debugging_def.Add_Instruction(Instruction_Start_Up);
	debugging_def.Add_Instruction(Instruction_Start_Down);
	debugging_def.Add_Instruction(Instruction_Left);
	debugging_def.Add_Instruction(Instruction_Right);
	debugging_def.Add_Instruction(Instruction_Down);
	debugging_def.Add_Instruction(Instruction_Up);
	debugging_def.Add_Instruction(Instruction_Bond_Add);
	debugging_def.Add_Instruction(Instruction_Bond_Remove);
	debugging_def.Add_Instruction(Instruction_In_Alpha);
	debugging_def.Add_Instruction(Instruction_Out_Omega);
	debugging_def.Add_Instruction(Instruction_Rotate_R);
	debugging_def.Add_Instruction(Instruction_Rotate_L);
	debugging_def.Add_Instruction(Instruction_Grab);
	debugging_def.Add_Instruction(Instruction_Drop);
	debugging_def.Add_Instruction(Instruction_GrabDrop);

		// The hard cap for the total cycles allow in the entire simulation.
	debugging_def.Set_Cycle_Limit_Total(1000000);

		// The hard cap for a single simulation.
	debugging_def.Set_Cycle_Limit_Simulation(100);

		// The hard cap for the number of simulations that can run before halting.
	debugging_def.Set_Simulation_Max(10000);

		// The hard cap for the of number of solutions found before halting.
	debugging_def.Set_Simulation_Solution_Max(1);

		// How many solutions to dump on halting.
	debugging_def.Set_Simulation_Solution_Toaccept(1);

	
		// Create the simulation controller
	Simulation_Controller Debug;

	Debug.Set_Problem_Definition(debugging_def);

		// Start the simulator.
	int Result = Debug.Tick();

	return Result;
}