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
	Common_Functions.h - Stores simple functions that can be used by any class.
*/

#ifndef Common_Functions_H
#define Common_Functions_H

#include <string>
#include <sstream>

std::string ConvertITS(int argument) {
	std::stringstream temp;
	temp << argument;
	return temp.str();
}

	// Looks up a keyword and converts it into a int value based off the defines.
int Lookup_Code(std::string argument) {

			// TO DO
		if (argument == "Instruction_NOP") {
			return Instruction_NOP;
		}

		if (argument == "Instruction_Start_Left") {
			return Instruction_Start_Left;
		}

		if (argument == "Instruction_Start_Right") {
			return Instruction_Start_Right;
		}
		
		if (argument == "Instruction_Start_Up") {
			return Instruction_Start_Up;
		}
		
		if (argument == "Instruction_Start_Down") {
			return Instruction_Start_Down;
		}

		if (argument == "Instruction_Left") {
			return Instruction_Left;
		}

		if (argument == "Instruction_Right") {
			return Instruction_Right;
		}

		if (argument == "Instruction_Down") {
			return Instruction_Down;
		}

		if (argument == "Instruction_Up") {
			return Instruction_Up;
		}

		if (argument == "Instruction_Bond_Add") {
			return Instruction_Bond_Add;
		}

		if (argument == "Instruction_Bond_Remove") {
			return Instruction_Bond_Remove;
		}

		if (argument == "Instruction_In_Alpha") {
			return Instruction_In_Alpha;
		}

		if (argument == "Instruction_In_Beta") {
			return Instruction_In_Beta;
		}

		if (argument == "Instruction_Out_Omega") {
			return Instruction_Out_Omega;
		}

		if (argument == "Instruction_Out_Psi") {
			return Instruction_Out_Psi;
		}

		if (argument == "Instruction_Rotate_R") {
			return Instruction_Rotate_R;
		}

		if (argument == "Instruction_Rotate_L") {
			return Instruction_Rotate_L;
		}
		
		if (argument == "Instruction_Grab") {
			return Instruction_Grab;
		}

		if (argument == "Instruction_Drop") {
			return Instruction_Drop;
		}

		if (argument == "Instruction_GrabDrop") {
			return Instruction_GrabDrop;
		}

		if (argument == "Instruction_Sync") {
			return Instruction_Sync;
		}

		return -1;
	}


	// Convert the string to a int.
int ConvertSTI(std::string argument) {
	
		// Check to ensure each character is a number.
	for (unsigned int i = 0; i < argument.size(); i++) {
		if (argument[i] < '0' || argument[i] > '9') {
			return 0;
		}
	}

	return std::stoi(argument);
}

#endif