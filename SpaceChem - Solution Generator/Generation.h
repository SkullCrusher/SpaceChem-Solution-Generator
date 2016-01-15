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
//#include "Fitness_Calculator.h"

	// Used to mutate solutions.
class Generation_Mutation {

	public: Generation_Mutation() {
			// Generate the random seed that is used.
		srand((unsigned int)time(NULL));
	}
		// Add an instruction for a random mutation.
	private: void Add_Instruction(Problem_Definition &Rules, Solution_Reactor &argument) {

			// Pick a random spot to place the new instruction.
		short X = rand() % 10;
		short Y = rand() % 8;

			// Generate the default instructions.
		short Instruction_1 = Rules.Get_Instruction(rand() % (Rules.Get_Instruction_Size() - 1));
		short Instruction_2 = Instruction_NOP;

			// Default is Blue.
		bool RedorBlue = Blue_Tile;

			// Generate the odds.
		int Odds_Red = rand() % Rules.Odds_Table.Color;

		
			// Pick which direction it goes.
		int Direction_Odds = rand() % 4;

		if (Direction_Odds == 0) { Instruction_2 = Instruction_Left; }
		if (Direction_Odds == 1) { Instruction_2 = Instruction_Right; }
		if (Direction_Odds == 2) { Instruction_2 = Instruction_Down; }
		if (Direction_Odds == 3) { Instruction_2 = Instruction_Up; }
				
			// If the color should be set to red.
		if (Odds_Red == 0) {
			RedorBlue = Red_Tile;
		}

			// Skip if both are empty.
		if (Instruction_1 != Instruction_NOP || Instruction_2 != Instruction_NOP) {
			argument.Set_Instruction_For_Tile(X, Y, RedorBlue, Instruction_1, Instruction_2);
		}
	}

		// Remove an instruction for a random mutation.
	private: void Change_Remove_Instruction(Problem_Definition &Rules, Solution_Reactor &argument) {

		// Pick a random spot to remove instruction.
		short X = rand() % 10;
		short Y = rand() % 8;

		// Generate the default instructions.
		short Instruction_1 = Instruction_NOP;
		short Instruction_2 = Instruction_NOP;

		// Default is Blue.
		bool RedorBlue = Blue_Tile;

		// Generate the odds.
		int Odds_Red = rand() % Rules.Odds_Table.Color;

		// If the color should be set to red.
		if (Odds_Red == 0) {
			RedorBlue = Red_Tile;
		}

		argument.Set_Instruction_For_Tile(X, Y, RedorBlue, Instruction_1, Instruction_2);		
	}

		// Change an instruction for a random mutation.
/*TODO*/private: void Change_Instruction(Problem_Definition &Rules, Solution_Reactor &argument) {
		
	}

		// Move an instruction for a random mutation.
/*TODO*/private: void Move_Instruction(Problem_Definition &Rules, Solution_Reactor &argument) {
		
	}

		// Change the color of an instruction for a mutation.
/*TODO*/private: void Change_Color(Problem_Definition &Rules, Solution_Reactor &argument) {
		
	}

		// Change the direction of an instruction for a mutation.
/*TODO*/private: void Change_Direction(Problem_Definition &Rules, Solution_Reactor &argument) {
		
	}

		// Randomly mutates a single reactor.
	protected: void Generate_Mutation_Reactor(Problem_Definition &Rules, Solution_Reactor argument, std::vector<Solution_Reactor> &Pool) {
		/* Mutation
		- Moving chunks of instructions.
		- Randomly moving single.
		- Randomly changing instructions.
		- Randomly removing instructions.
		- Randomly changing the color of the instruction.
		*/

			// Generate random to see if the reactor should mutate.
		int Should_Mutate = rand() % Rules.Odds_Table.OddsTo_Mutate;

			// Check the odds.
		if (Should_Mutate == 0) {

				// The mutated simulation.
			Solution_Reactor Mutation = argument;

				// Force a resimulation of the solution.
			Mutation.Set_HasBeenSimulated(false);

				// Generate the odds for each mutation.
			int Should_Add_Instruction		= rand() % Rules.Odds_Table.Mutate_Add_Instruction;
			int Should_Remove_Instruction	= rand() % Rules.Odds_Table.Mutate_Remove_Instruction;
			int Should_Change_Instruction	= rand() % Rules.Odds_Table.Mutate_Change_Instruction;
			int Should_Move_Instruction		= rand() % Rules.Odds_Table.Mutate_Move_Instruction;
			int Should_Change_Color			= rand() % Rules.Odds_Table.Mutate_Change_Color;
			int Should_Change_Direction		= rand() % Rules.Odds_Table.Mutate_Change_Direction;

				// Add a random instruction to the solution.
			if (Should_Add_Instruction == 0)	{ Add_Instruction(Rules, Mutation); }
			if (Should_Remove_Instruction == 0) { Change_Remove_Instruction(Rules, Mutation); }
			if (Should_Change_Instruction == 0) { Change_Instruction(Rules, Mutation); }
			if (Should_Move_Instruction == 0)	{ Move_Instruction(Rules, Mutation); }
			if (Should_Change_Color == 0)		{ Change_Color(Rules, Mutation); }
			if (Should_Change_Direction == 0)	{ Change_Direction(Rules, Mutation); }

				// Only add the mutation if there was a mutation.
			if (Should_Add_Instruction == 0		|| 
				Should_Remove_Instruction == 0	|| 
				Should_Change_Instruction == 0	|| 
				Should_Move_Instruction == 0	|| 
				Should_Change_Color == 0		|| 
				Should_Change_Direction == 0) {

					// Add the mutation to the pool.
				Pool.push_back(Mutation);
			}
		}
	}

};

	// Used to combine solutions.
class Generation_Mate {

	public: Generation_Mate() {
			// Generate the random seed that is used.
		srand((unsigned int) time(NULL));
	}
			// Randomly mutates a single reactor.
	protected: void Generate_Mate_Reactor(Problem_Definition &Rules, std::vector<Solution_Reactor> &argument) {

		// We mate the most fit solutions.

	}


};

	// Used to create new random solutions.
class Generation_Random {

	public:	Generation_Random(){
			// Generate the random seed that is used.
		srand((unsigned int)time(NULL));
	}

			// Randomly generates a single reactor.
	protected: void Generate_Random_Reactor(Problem_Definition &Rules, std::vector<Solution_Reactor> &argument) {

	Solution_Reactor Result;

	// Randomly fill the reactor with elements based off the odds.
	for (unsigned int g = 0; g < 8; g++) {
		for (unsigned int i = 0; i < 10; i++) {
			// Use the odds and a random number to get the odds.
			int Random = rand() % Rules.Odds_Table.Random_ToPlace;

			// If the random chance hits.
			if (Random == 0) {

				// Generate the default instructions.
				short Instruction_1 = Instruction_NOP;
				short Instruction_2 = Instruction_NOP;

				// Default is Blue.
				bool RedorBlue = Blue_Tile;

				// Generate the odds.
				int Odds_Instruction_1	= rand() % Rules.Odds_Table.Set_Instruction;
				int Odds_Instruction_2	= rand() % Rules.Odds_Table.Set_Direction;
				int Odds_Red			= rand() % Rules.Odds_Table.Color;

				// If a instruction should be placed.
				if (Odds_Instruction_1 == 0) {
					Instruction_1 = Rules.Get_Instruction(rand() % Rules.Get_Instruction_Size());
				}
				// If a direction change should be placed.
				if (Odds_Instruction_2 == 0) {

					// Pick which direction it goes.
					int Direction_Odds = rand() % 4;

					if (Direction_Odds == 0) { Instruction_2 = Instruction_Left; }
					if (Direction_Odds == 1) { Instruction_2 = Instruction_Right; }
					if (Direction_Odds == 2) { Instruction_2 = Instruction_Down; }
					if (Direction_Odds == 3) { Instruction_2 = Instruction_Up; }

				}
				// If the color should be set to red.
				if (Odds_Red == 0) {
					RedorBlue = Red_Tile;
				}

				// Skip if both are empty.
				if (Instruction_1 != Instruction_NOP || Instruction_2 != Instruction_NOP) {
					Result.Set_Instruction_For_Tile(i, g, RedorBlue, Instruction_1, Instruction_2);
				}
			}
		}
	}

	argument.push_back(Result);
}


};

	// The controller class for all of the generation classes.
class Generation : private Generation_Random, private Generation_Mate, private Generation_Mutation {

	
		// Default constructor.
	public: Generation(){
			// Generate the random seed that is used.
		srand((unsigned int) time(NULL));
	}
			
		// Generates new solutions based off the settings in Problem_Definition.
	public: bool Generate_Single_Reactor(Problem_Definition &Rules, std::vector<Solution_Reactor> &argument) {

			// If the pool size is less then the requirement, force new random ones into it.
		while (argument.size() < Rules.Solution_Pool_Size) {
			Generate_Random_Reactor(Rules, argument);
		}

			// Mutation, changes a solution and added it to the pool.
		for (unsigned int i = 0; i < argument.size(); i++) {
			Generate_Mutation_Reactor(Rules, argument[i], argument);
		}
		


		
		return true;
	}



};


#endif