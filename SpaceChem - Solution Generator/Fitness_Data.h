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
		This is used to store the overall fitness of a solution after the simulation.
			- This data is stored in the solution and used by the generation and created by the fitness calculator.
	*/

#ifndef Fitness_Data_Header
#define Fitness_Data_Header

struct Fitness {

		// If the fitness calculator has generated the data.
	bool HasBeenProcessed;

	// Order is how important they are to the fitness.

		// 1. How many correct molecules were outputted (Higher the better).
	unsigned int Correct_Molecules_Output;

		// 2. How many correct molecules were created (Higher the better).
	unsigned int Correct_Molecules_Created;

		// 3. How far are the created molecules to the output. (Lower the better)
		// To calculate: (Total distance for all correct molecules) / (Correct_Molecules_Created)	
	double Distance_To_Output_Partial;

		// 4. How long did the simulation take.
	unsigned long Cycle_Time;

		// 5. How many symbols are used (Lower the better).
		// To calculate: Symbol_Count = Red + Blue;
	unsigned int Symbol_Count;

	Fitness() {
		HasBeenProcessed = false;
		Correct_Molecules_Output = 0;
		Correct_Molecules_Created = 0;
		Distance_To_Output_Partial = 0;
		Symbol_Count = 0;
	}


		// After prototype
	double Percent_To_Creating_Correct_Molecule;
	unsigned int Reactor_Count;
	unsigned int Total_Pipe_Length;
	unsigned long Total_Atoms_Trashed;

};

#endif