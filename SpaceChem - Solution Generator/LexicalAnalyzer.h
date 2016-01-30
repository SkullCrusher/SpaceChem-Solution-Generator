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
	LexicalAnalyzer.h - Takes a input string and splits it into lexical units.
*/
#ifndef LexicalAnalyzer_H
#define LexicalAnalyzer_H

#include "Lexical_Unit.h"

#include <vector>

class LexicalAnalyzer{

		// Default constructor.
	public: LexicalAnalyzer() {
	
	}

		// Run.
	public: std::vector<LexicalUnit> Process(std::string argument) {

		std::vector<LexicalUnit> Result;


		return Result;
	}

};



#endif
