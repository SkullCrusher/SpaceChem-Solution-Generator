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

/*
	Utilities.h - Used to store functions called directly by main.
*/

#ifndef Handle_Input_H
#define Handle_Input_H

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
	Temp.OddsTo_Mutate = 10;  // (1 out of 10)

							  // The odds on mutation to add a new instruction.
	Temp.Mutate_Add_Instruction = 5;
	Temp.Mutate_Remove_Instruction = 5;
	Temp.Mutate_Change_Instruction = 5;
	Temp.Mutate_Move_Instruction = 5;
	Temp.Mutate_Change_Color = 5;
	Temp.Mutate_Change_Direction = 1;

		// Randomly generate
	Temp.Set_Instruction = 7;
	Temp.Set_Direction = 7;
	Temp.Color = 2;

	return Temp;
}

	// Handles loading a new file and returns the problem_definition from it.
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

bool CheckIfComplete(std::vector<Solution_Reactor> &Solution_Pool) {

	for (unsigned int i = 0; i < Solution_Pool.size(); i++) {
			//Check if there is an answer
			#pragma message ("Handle_Input.h: TDAP - Change to accept only if the definition was met.")
		if (Solution_Pool[i].Get_Status() == Solution_Accepted) {

			int debug = 0;

			return true;
		}
	}

	return false;
}
	
	// Takes a problem definition and processes it and exits the program.
int Handle_Input(Problem_Definition Simulation_Definition) {

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
		Simulation_Handle.Tick(Solution_Pool, &Fitness_Handle);

			// Process the results, Note this should have the Solution_Pool as an argument.
		Fitness_Handle.Calculate_Fitness(Solution_Pool);

			// Check if the problem has been solved based off the problem definition.
		if (CheckIfComplete(Solution_Pool)) {
			Accepted_Solution = true;
		}
	}

	return 0;
}

#endif