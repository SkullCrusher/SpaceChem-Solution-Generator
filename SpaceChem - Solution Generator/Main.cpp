/*
	SpaceChem Solution Generator - Solves problems using the genetic algorithm.
					Copyright(C) 2016 by David Harkins.

	This program is free software : you can redistribute it and / or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation version 3 of the License.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include <iostream>
#include <stdlib.h>

	// Each core part of the program.
#include "Simulation_Controller.h"
#include "Generation.h"

	// Commonly used definitions for all core parts of the program.
#include "Definitions.h"
#include "Problem_Definiton.h"
#include "Fitness_Calculator.h"

	// Handle the input from the user.
#include "Handle_Input.h"

	// Functions that are used by the main.
#include "Utilities.h"

	// Used to load and save the problem definitons.
#include "File_IO.h"


int main(int argc, char *argv[]) {

		// Validate the arguments.
	if (argc < Minimum_Argument_Count || argc > Maximum_Argument_Count){
		
			// Print how to use the software.
		PrintUsage();
		
			// Exit because of a lack of arguments.
		return Error_Incorrect_Argument_Count;
	}

		// Process the input to the program.
	CommandLine User_Input = ParseCommandLine(argc, argv);

		// If the start infomation is not disabled, output it.
	if (!User_Input.Flag_ShouldDisableStartInfo){
		PrintStartInfomation();
	}

		// If there is no task quit.
	if (User_Input.Operation == Command_Line_OP_NOP || User_Input.Status_Code != Command_Line_NoError){
		return User_Input.Status_Code;
	}

		// If a standard simulation is the operation.
	if (User_Input.Operation == Command_Line_OP_CS || Command_Line_OP_SAF){

			// Load the file argument. Create the definition of the problem that needs to be solved.
		Problem_Definition Simulation_Definition = LoadProblemDefinitionFile("testinput.txt");

			// Check if the problem_definition which was loaded is invalid.
		if (Simulation_Definition.Get_Invalid()) {

			return 1000; // Exit with simulation code.
		}else{

				// Handle the input file.
			int Result_Code = Handle_Input(Simulation_Definition);

				// Exit with simulation code.
			return Result_Code;
		}		
	}
	
		// Return the code.
	return User_Input.Status_Code;
}