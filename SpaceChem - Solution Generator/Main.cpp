//SpaceChem Problem Solver - Written by David Harkins
#include <iostream>
#include <stdlib.h>
#include <fstream>

	// Each core part of the program.
#include "Simulation_Controller.h"

	// Commonly used definitions for all core parts of the program.
#include "Definitions.h"
#include "Problem_Definiton.h"

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
	printf("SpaceChem Problem Solver - written by David Harkins");

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
	
		// Create the simulation controller
	Simulation_Controller Debug;

	Debug.Set_Problem_Definition(debugging_def);

		// Start the simulator.
	int Result = Debug.Tick();

	return Result;
}