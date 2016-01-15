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

// This is used to calculate the overall fitness of a solution after the simulation.

#ifndef Fitness_Calculator_Header
#define Fitness_Calculator_Header

#include "Solution.h"
#include <vector>
#include "Definitions.h"

#include "Fitness_Data.h"

class Fitness_Calculator{

	public: Fitness_Calculator() {


	}

		// This generates the fitness of the input reactor.
	private: void Generate_Reactor_Fitness(Solution_Reactor &argument){

	}
		// Process the input pool and generate a fitness for each of the elements if they were simualated.
	public: void Calculate_Fitness(std::vector<Solution_Reactor> &argument) {
	
			// Process each of the solutions to see how fit it is.
		for (unsigned int i = 0; i < argument.size(); i++){
				// Check if the solution has been simulated.
			if (argument[i].Get_HasBeenSimulated()){
					// Generate fitness data about it.
				Generate_Reactor_Fitness(argument[i]);
			}
		}
	}



};

#endif