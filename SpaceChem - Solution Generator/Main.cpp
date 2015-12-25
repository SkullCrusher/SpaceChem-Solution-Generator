//SpaceChem Problem Solver - Written by David Harkins
#include <iostream>
#include <stdlib.h>

	// Each core part of the program.
#include "Generation.h"
#include "Simulation.h"

	// Commonly used definitions for all core parts of the program.
#include "Definitions.h"
#include "Problem_Definiton.h"

void PrintUsage(){
	printf("--\n");
	printf("--\n");

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

	// Load the file
	
	//

	return 0;
}