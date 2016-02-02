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
	Lexical_Unit.h - Converts Lexical units into a problem definiton.
*/
#ifndef Interpreter_H
#define Interpreter_H

#include "Lexical_Unit.h"
#include "Problem_Definiton.h"
#include "Common_Functions.h"
#include <vector>

class Interpreter{

		// Default constructor.
	public: Interpreter() {
	};

		// Looks up a keyword and converts it into a int value based off the defines.
	private: int Lookup_Code(std::string argument) {

	}

		// Takes the input and sets the value of the Problem_Definiton based on it.
	private: void Do_Assignment(Problem_Definition &Result, LexicalUnit A, LexicalUnit Sign, std::vector<LexicalUnit> B) {

	}


		// Converts pairs of lexical units into data.
	private: void Process_Identifier(Problem_Definition &Result, std::vector<LexicalUnit> &argument, std::vector<std::string> &ErrorReport, unsigned int &i) {

			// It is impossible to generate anything with less then 3.
		if (argument.size() < 3) {
			return;
		}

			// There are two cases, A = B or A = {b, c, d, e}

			// The (A) = B
		LexicalUnit A = argument[i];		

			// Check the case where A is not a Token_Identifier
		if (A.Token != Token_Identifier) {

			ErrorReport.push_back("Invalid format of assignment (First Term '" + A.lexeme + "'). Linenumber: " + ConvertITS(A.LineNumber));
			return;
		}else {
			i++;
		}

			// The A (=) B
		LexicalUnit Assignment = argument[i];

			// Check the case where Assignment is not a Token_Equals
		if (Assignment.Token != Token_Equals) {

			ErrorReport.push_back("Invalid format of assignment (Missing equals '" + Assignment.lexeme + "'). Linenumber: " + ConvertITS(Assignment.LineNumber));
			return;
		}else {
			i++;
		}

			// The A = (B | {)
		LexicalUnit BorBracket = argument[i];

			// Check to ensure that it is a identifier or left bracket.
		if (BorBracket.Token == Token_Identifier || BorBracket.Token == Token_Integer || BorBracket.Token == Token_Left_Bracket) {

			std::vector<LexicalUnit> List;

				// If the case is Left_Bracket grab all of the elements.
			if (BorBracket.Token == Token_Left_Bracket) {

				i++;

					// False for int or idetifier, true for comma. it must find the bracket on false.
				bool Switch = false;
				bool FoundBracket = false;

					// Continue until a bracket is found.
				while (i < argument.size()) {				
					
						// If it matches a int or identifier.
					if (argument[i].Token == Token_Identifier || argument[i].Token == Token_Integer) {
						
						// If the switch is incorrect error.
						if (Switch == true) {
							ErrorReport.push_back("Invalid format of assignment (Missing or extra comma). Linenumber: " + ConvertITS(Assignment.LineNumber));
							return;
						}else {
							List.push_back(argument[i]);
							Switch = true;
						}
						continue;
					}

						// If the current is a comma.
					if (argument[i].Token == Token_Comma) {
							// If it matches a int or identifier.
						if (Switch == true) {
							ErrorReport.push_back("Invalid format of assignment (Missing or extra comma). Linenumber: " + ConvertITS(Assignment.LineNumber));
							return;
						}else {
							Switch = false;
						}
						continue;
					}

						// If the current is a right bracket.
					if (argument[i].Token == Token_Right_Bracket) {

							// Check for missing right bracket.
						if (Switch == false) {
							FoundBracket = true;
							break;
						}else {
							ErrorReport.push_back("Invalid format of assignment (Incorrect comma count). Linenumber: " + ConvertITS(Assignment.LineNumber));
							return;
						}
					}

					i++;
				}
			}else {
				List.push_back(BorBracket);
			}

				
				// Call the function to set the Problem_Definition.
			Do_Assignment(Result, A, Assignment, List);

		}else {
			ErrorReport.push_back("Invalid format of assignment (Second Term '" + BorBracket.lexeme + "'). Linenumber: " + ConvertITS(Assignment.LineNumber));
			return;
		}	
	}

		
		// Process the LexicalUnits into a Problem_Definiton.
	public: Problem_Definition Process(std::vector<LexicalUnit> argument, std::vector<std::string> &ErrorReport){

		Problem_Definition Result;

		for (unsigned int i = 0; i < argument.size(); i++) {
			
			switch (argument[i].Token) {

					// The only valid token, the rest are a result of an error of formating.
				case Token_Identifier: 
					Process_Identifier(Result, argument, ErrorReport, i);
					break;

				case Token_Null: break;
				case Token_Integer:

					break;
				case Token_Left_Bracket: 	

					break;
				case Token_Right_Bracket:

					break;
				case Token_Comma: 

					break;
				case Token_Equals:

					break;
				case Token_Unknown: 

					break;
				case Token_Missing_Comment_Tag: 

					break;
				case Token_NewLine: 

					break;
				default:					
					
					break;
			}
			
		}


		return Result;
	}

};

#endif