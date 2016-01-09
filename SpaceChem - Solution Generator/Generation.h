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
- selection
- mutation
	- Moving chunks of instructions.
	- Randomly moving single. //
	- Randomly changing instructions.//
	- Randomly removing instructions.//
	- Randomly changing the color of the instruction.//
- crossover


-- try breeding the most like. (future)
*/

#ifndef Generation_H
#define Generation_H

#include <vector>
#include <time.h>
#include <stdlib.h>
#include "Problem_Definiton.h"
#include "Fitness_Calculator.h"

class Generation{

	
		// Default constructor.
	public: Generation(){
			// Generate the random seed that is used.
		srand((unsigned int) time(NULL));
	}

	private: void Generate_Random_Reactor(Problem_Definition &Rules, std::vector<Solution_Reactor> &argument) {

		Solution_Reactor Result;

			// Randomly fill the reactor with elements based off the odds.
		for (unsigned int g = 0; g < 8; g++) {
			for (unsigned int i = 0; i < 10; i++) {
					// Use the odds and a random number to get the odds.
				int Random = rand() % Rules.Get_Odds_On_Random_ToPlace();

					// If the random chance hits.
				if (Random == 0) {
						// Recalculate the random number based off the number of instructions.
					Random = rand() & Rules.Get_Instruction_Size();

					//Result.Set_Instruction_For_Tile()

				}

				int debug = 0;

			}
		}

		argument.push_back(Result);
	}

		// Generates new solutions based off the settings in Problem_Definition.
	public: bool Generate_Single_Reactor(Problem_Definition &Rules, std::vector<Solution_Reactor> &argument) {

		// If the pool size is less then the requirement, force new random ones into it.
		while (argument.size() < Rules.Get_Solution_Pool_Size()) {
			Generate_Random_Reactor(Rules, argument);
		}

		return true;
	}



};


#endif