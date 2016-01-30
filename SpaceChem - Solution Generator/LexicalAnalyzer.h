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

#include <stdio.h>
#include <ctype.h>
#include <vector>

class LexicalAnalyzer{

		// Default constructor.
	public: LexicalAnalyzer() {
	
	}
		// Checks if char is a space or tab.
	private: bool IsWhitespace(char argument) {
		if (argument == ' ' || argument == '\t') {
			return true;
		}else {
			return false;
		}
	}

		// Checks if char is a letter.
	private: bool IsCharacterLetter(char argument) {
		return isalpha((int) argument);
	}

		// Checks if the char is a number.
	private: bool IsCharacterNumber(char argument) {

		if (argument >= '0' && argument <= '9') {
			return true;
		}

		return false;
	}

		// Convert the string to LexicalUnits.
	public: std::vector<LexicalUnit> Process(std::string argument) {

		std::vector<LexicalUnit> Result;

			// Process each character.
		for (unsigned int i = 0; i < argument.size(); i++) {

			//bool Debug = IsCharacterLetter(argument[i]);

			//bool Tru = IsCharacterNumber('0');

				// Skip white spaces.
			if (IsWhitespace(argument[i])) {
				continue;
			}

				// Skip comments.
			if (argument[i] == '*') {

					// Check to see if the size if big enough 
				if () {

				}
				//argument[i + 1] = "";
				

			}


			int debug = 0;

		}


		return Result;
	}

};



#endif
