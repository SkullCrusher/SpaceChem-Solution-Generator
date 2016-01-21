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
#include <fstream>

	// Each core part of the program.

#include "Simulation_Controller.h"
#include "Generation.h"

	// Commonly used definitions for all core parts of the program.
#include "Definitions.h"
#include "Problem_Definiton.h"
#include "Fitness_Calculator.h"

	// Functions that are used by the main.
#include "Utilities.h"

	// Used for testing.
#include "Embedded_Quality_Assurance.h"

Odds Debug_Generate_Odds() {
	Odds Temp;

		// The odds to mutate.
	Temp.OddsTo_Mutate				= 10;  // (1 out of 10)

		// The odds on mutation to add a new instruction.
	Temp.Mutate_Add_Instruction		= 5;
	Temp.Mutate_Remove_Instruction	= 5;
	Temp.Mutate_Change_Instruction	= 5;
	Temp.Mutate_Move_Instruction	= 5;
	Temp.Mutate_Change_Color		= 5;
	Temp.Mutate_Change_Direction	= 1;

		// Randomly generate
	Temp.Set_Instruction			= 7;
	Temp.Set_Direction				= 7;
	Temp.Color						= 2;

	return Temp;
}

Problem_Definition LoadProblemDefinitionFile(std::string Path) {

		// For debugging the definition is just hard coded.
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
	debugging_def.Set_Cycle_Limit_Simulation(200);

		// The hard cap for the number of simulations that can run before halting.
	debugging_def.Set_Simulation_Max(10000);

		// The hard cap for the of number of solutions found before halting.
	debugging_def.Set_Simulation_Solution_Max(1);

		// How many solutions to dump on halting.
	debugging_def.Set_Simulation_Solution_Toaccept(1);

		// --- The odds for generation. ---
	debugging_def.Solution_Pool_Size = 500;
	debugging_def.Odds_Table.Random_ToPlace = 5;

		// -- Odds for randomly generating. ---
	debugging_def.Odds_Table.Set_Instruction = 7;
	debugging_def.Odds_Table.Set_Direction = 7;
	debugging_def.Odds_Table.Color = 2;

		// Generate the odds table.
	debugging_def.Odds_Table = Debug_Generate_Odds();

		// There are two bonding pads in a standard reactor.
	debugging_def.Reactor_Limit_Standard = 2;


	return debugging_def;
}

int Handle_Input(Problem_Definition Simulation_Definition){

	// Create the simulation controller that handles all simulations.
	Simulation_Controller Simulation_Handle;

	// Set the definition into the simulation controller.
	Simulation_Handle.Set_Problem_Definition(Simulation_Definition);


	// The pool of solutions that need to be simulated.
	std::vector<Solution_Reactor> Solution_Pool;

	// The class that handles the generation and mutation of solutions.
	Generation Generation_Handle;

	// The class that handles post processing of the solutions.
	Fitness_Calculator Fitness_Handle;


	bool Accepted_Solution = false;

	while (!Accepted_Solution) {

		// Handle generation.
		Generation_Handle.Generate_Single_Reactor(Simulation_Definition, Solution_Pool);

		// Simulate the pool.
		Simulation_Handle.Tick(Solution_Pool);

		// Process the results, Note this should have the Solution_Pool as an argument.
		Fitness_Handle.Calculate_Fitness(Solution_Pool);
	}

	return 0;
}

	// A structure to hold all the information provided by Command Line.
struct CommandLine{

		// What operation should be done.
	int Operation = Command_Line_OP_NOP;

		// For the error code.
	int Status_Code = Command_Line_NoError;

		// The path to the definition problem. 
	std::string In_FilePath = "";
		
		// The path to dump the results to.
	std::string Out_FilePath = "";

	// Flags and values - These override the problem defined in the file.

		// The results of the simulation should be output to a file.
	bool Flag_ShouldDumpToFile = false;

		// The results of the simulation should be output to console.
	bool Flag_ShouldDumpToConsole = false;

		// Should the information that displays at the start be disabled. 
		// This is to be able to dump the console without having to remove a header.
	bool Flag_ShouldDisableStartInfo = false;

		// Should the debugging infomation be output to console.
	bool Flag_ShouldDisplayDebugging = false;

		// Should the program use the cache file to keep a buffer of the current work that has been done.
/*Future maybe*/bool Flag_ShouldProtectFromPowerloss = false;

		// Should for large pools the data be dumped to the hard drive unless in use.
/*Future maybe*/bool Flag_ShouldCache = false;
	

};

	// Take the commandline arguments and decide what to
CommandLine ParseCommandLine(int argc, char *argv[]){

	CommandLine Result;

	for (int i = 1; i < argc; i++){
		// Operations:
			// -OP_Test  : Simulates the testing data to check the validation of the current version.
		if (strcmp(argv[i], "-OP_Test") == 0){
			Result.Operation = Command_Line_OP_TEST;
			continue;
		}
			// -OP_SAF   : Loads a problem definition from a file and simulates it until a solution is found.
		if (strcmp(argv[i], "-OP_SAF") == 0){
			Result.Operation = Command_Line_OP_SAF;
			continue;
		}
			// -OP_CS	 : Load a solution and simulate it and give the result if it is valid.
		if (strcmp(argv[i], "-OP_CS") == 0){
			Result.Operation = Command_Line_OP_CS;
			continue;
		}
		
			// -h or --help  : provide the usage for the user.
		if (strcmp(argv[i], "-h") == 0){
				// Print the usage and exit.
			PrintUsage();

			Result.Operation = Command_Line_OP_NOP;
			return Result;
		}

			// -f <filepath> : the input file.
		if (strcmp(argv[i], "-f") == 0){

			// The file command has to be followed by a path.
			if ((i + 1) < argc){

					// Set the filepath and increase i;
				Result.In_FilePath = argv[i + 1];
				
				i++;

				continue;
			}else{
					// Return with the error code.
				Result.Status_Code = Command_Line_Missing_Path;

				return Result;
			}
		}
			// -r <filepath> : the output file.
		if (strcmp(argv[i], "-r") == 0){

			// The file command has to be followed by a path.
			if ((i + 1) < argc){

				// Set the filepath and increase i;
				Result.Out_FilePath = argv[i + 1];

				i++;

				continue;
			}else{
				// Return with the error code.
				Result.Status_Code = Command_Line_Missing_Path;

				return Result;
			}
		}

			// -c : Output result to console.
		if (strcmp(argv[i], "-c") == 0){
			Result.Flag_ShouldDumpToConsole = true;
			continue;
		}

			// -d or --debugging : enable debugging infomation.
		if (strcmp(argv[i], "-d") == 0 || strcmp(argv[i], "--debugging") == 0){
			Result.Flag_ShouldDisplayDebugging = true;
			continue;
		}
	}

	return Result;
}

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
		Problem_Definition Simulation_Definition = LoadProblemDefinitionFile("debugging");

			// Handle the input file.
		int Result_Code = Handle_Input(Simulation_Definition);

			// Exit with simulation code.
		return Result_Code;
	}
	
		// If the embedded testing is requested give control to that.
	if (User_Input.Operation == Command_Line_OP_TEST){

		Embedded_Quality_Assurance Quality;



	}

		// Return the code.
	return User_Input.Status_Code;
}