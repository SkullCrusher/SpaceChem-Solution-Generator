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
	Handle_Input.h - Used to take the input and move it to the correct simulation path.
*/

#ifndef Handle_Input_H
#define Handle_Input_H

#include <string>

	// Used to dump the result to a file.
#include "File_IO.h"

	// The two possible paths from the input file.
#include "Create_Solution.h"
#include "Solution_Validate.h"
	
	// Takes a problem definition and processes it and exits the program.
int Handle_Input(Problem_Definition Simulation_Definition) {

	std::string Result = "Invalid";

		// The input is a problem to solve.
	if (Simulation_Definition.Simulation_Type == "Solve") {
		Result = Create_Solution(Simulation_Definition);
	}

		// The input is a solution to simulate.
	if (Simulation_Definition.Simulation_Type == "Validate") {
		Result = Solution_Validate(Simulation_Definition);
	}

		// Check for errors.
	if (Result == "Invalid") {
		return -10;
	}

		// Dump the results.
	DumpFile(Simulation_Definition.FileInfo_Simulation_Name + ".txt", Result);
	
	return 0;
}

#endif