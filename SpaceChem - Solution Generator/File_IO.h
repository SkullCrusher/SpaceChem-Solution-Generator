#pragma once

#ifndef File_IO_H
#define File_IO_H

#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>

// Each core part of the program.
#include "Simulation_Controller.h"
#include "Generation.h"

// Commonly used definitions for all core parts of the program.
#include "Definitions.h"
#include "Problem_Definiton.h"
#include "Fitness_Calculator.h"

// Include the classes to process the input into lexical chunks.
#include "LexicalAnalyzer.h"


	// Loads a entire file from the path provided.
std::string LoadFile(std::string Filepath) {

	std::string Result = "";

	std::string line;
	std::ifstream myfile(Filepath.c_str());
	if (myfile.is_open()){
		while (getline(myfile, line)){
			Result += line + "\n";
		}
		myfile.close();
	}else {
		return "Unable to open file.";
	}

	return Result;
}


// Handles loading a new file and returns the problem_definition from it.
Problem_Definition LoadProblemDefinitionFile(std::string Path) {

	Problem_Definition Result;

		// Load the input file.
	std::string InputFile = LoadFile(Path);

		// Check there was an error loading the tile.
	if (InputFile == "Unable to open file.") {
		Result.Set_Invalid(true);
		return Result;
	}

	LexicalAnalyzer Lexical_Processor;

		// Process the input file.
	std::vector<LexicalUnit> Step_One_Result = Lexical_Processor.Process(InputFile);






	int debug = 0;


	/*

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

	*/
	return Result;
}



#endif