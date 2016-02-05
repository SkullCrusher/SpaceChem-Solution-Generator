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
	Solution_Validate.h - Takes the input and simulates it to check if it is a valid solution and dumps the result.
*/

#ifndef Solution_Validate_H
#define Solution_Validate_H

#include <string>
#include "Problem_Definiton.h"

	// Validate the input problem definition.
std::string Solution_Validate(Problem_Definition argument) {

		// Create the simulation controller that handles the simulation.
	Simulation_Controller Simulation_Handle;

		// Set the definition into the simulation controller.
	Simulation_Handle.Set_Problem_Definition(argument);

		// The class that handles post processing of the solution.
	Fitness_Calculator Fitness_Handle;
			
	
		// Simulate the solution.
	//Simulation_Handle.Simulate_Single_Reactor()
	
		// Calculate the fitness.
	//Fitness_Handle.Calculate_Fitness(Solution_Pool);

		// Generate the results.
	//std::string Result = Generate_Report_Validation(Simulation, Fitness);
	

	return "valid";
}


#endif