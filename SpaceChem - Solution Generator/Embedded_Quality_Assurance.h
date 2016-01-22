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
	Embedded_Quality_Assurance is built to make sure the simulation works correctly.
		It uses solutions with a known result and checks those results against the simulations.
	
	Planet list:

	Sernimir II -
	Sernimir IV -
	Danopth		-
	Alkonost	-
	Sikutar		-
	Hephaestus IV -
	Atropos Station -


*/

#ifndef Embedded_Quality_Assurance_H
#define Embedded_Quality_Assurance_H

#include "Sernimir_II_Testing.h"

struct Expected_Result{

	int Result_Code = 0;

	int Cycle_Count = 0;
};


class Embedded_Quality_Assurance{

	private: bool Test_Sernimir_II(int Total_Successful, int &Total_Tests){

	}

	public:	Embedded_Quality_Assurance(){

	}

private: std::string GenerateResultFormat(std::string MapName, ){

		return "";
	}

		// Generates all of the test data.
	public: std::string ValidateAll() {

		std::string Result = "Self Test\n";
		
			// Sernimir II
		bool Sernimir_II_Result = Test_Sernimir_II();

		Result += "Sernimir II: ";

		if (Sernimir_II_Result){

		}
		
		// Sernimir IV
		// Danopth
		// Alkonost
		// Sikutar
		// Hephaestus IV
		// Atropos Station





		return "";
	}

};

#endif