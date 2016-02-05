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
	Create_Solution.h - Takes the input and attempts to create a solution for it and dumps the result.
*/

#ifndef Create_Solution_H
#define Create_Solution_H

#include <string>
#include "Problem_Definiton.h"

// Each core part of the program.
#include "Simulation_Controller.h"
#include "Generation.h"

// Commonly used definitions for all core parts of the program.
#include "Definitions.h"
#include "Problem_Definiton.h"
#include "Fitness_Calculator.h"

// Functions that are used by the main.
#include "Utilities.h"

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

	// Create a solution for the input problem.
std::string Create_Solution(Problem_Definition Simulation_Definition) {

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

	return "";
}



#endif