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
	public: LexicalAnalyzer() {}

		// Checks if char is newline.
	private: bool IsNewline(char argument) {
		if (argument == '\n') {
			return true;
		}else {
			return false;
		}
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
		return isalpha((int)argument) || (argument == '_');
	}

		// Checks if the char is a number.
	private: bool IsCharacterNumber(char argument) {

		if (argument >= '0' && argument <= '9') {
			return true;
		}

		return false;
	}

		// Takes a string input and continues until a *\ is found or -1 if one is not contained.
	private: int SkipComment(std::string argument, int i) {

		for (unsigned int g = i + 2; g < argument.size() - 1; g++) {

			if (argument[g] == '*' && argument[(g + 1)] == '/') {
					return (g + 1);
			}
		}

		return -1;
	}

		// Look up extra characters.
	private: void Lookup(char argument, int LineNumber, std::vector<LexicalUnit> &Result) {

		LexicalUnit Temp;
		Temp.lexeme = argument;

		switch (argument) {
			case '{':
				Temp.Token = Token_Left_Bracket;
				break;

			case '}':
				Temp.Token = Token_Right_Bracket;
				break;

			case ',':
				Temp.Token = Token_Comma;			
				break;

			case '=':			
				Temp.Token = Token_Equals;
				break;

			default:			
				Temp.Token = Token_Unknown;
				break;
		}

		Temp.LineNumber = LineNumber;

		Result.push_back(Temp);
	}

		// Convert the string to LexicalUnits.
	public: std::vector<LexicalUnit> Process(std::string argument) {

		std::vector<LexicalUnit> Result;

			// What line the input is currently on.
		int Linenumber = 0;

			// Process each character.
		for (unsigned int i = 0; i < argument.size(); i++) {

				// Skip white spaces and tabs.
			if (IsWhitespace(argument[i])) {
				continue;
			}

				// Skip newlines and increase line count.
			if (IsNewline(argument[i])){
				Linenumber++;
				continue;
			}

				// Skip comments.
			if (argument[i] == '/') {

					// Check to see if the size if big enough 
				if ((i + 1) < argument.size()) {
					if (argument[i + 1] == '*') {
						int Offset = SkipComment(argument, i);

						if (Offset != -1) {
							i = Offset;
							continue;
						}else {
							LexicalUnit Temp;
							Temp.Token = Token_Missing_Comment_Tag;
							Temp.lexeme = "Error.";
							Temp.LineNumber = Linenumber;
							Result.push_back(Temp);
							continue;
						}
					}
				} else {
						// A without a matching * so dump it as a unknown.
					LexicalUnit Temp;

					Temp.lexeme = "/";
					Temp.Token = Token_Unknown;
					Temp.LineNumber = Linenumber;
					Result.push_back(Temp);
					continue;
				}
			}

				// Do function with ""
			if (argument[i] == '\"') {
				LexicalUnit Temp;
				Temp.Token = Token_Identifier;
				Temp.lexeme = "";
				Temp.LineNumber = Linenumber;

				i++;

					// Continue until it is a whitespace or an invalid character.
				while (i < argument.size()) {
					if (argument[i] != '\"') {
						Temp.lexeme += argument[i];
						i++;
					} else {
						break;
					}
				}

				Result.push_back(Temp);
				continue;
			}

				// Is Identifier?
			if (IsCharacterLetter(argument[i])) {
				LexicalUnit Temp;
				Temp.Token = Token_Identifier;
				Temp.lexeme = "";
				Temp.lexeme += argument[i];
				Temp.LineNumber = Linenumber;

				i++;

					// Continue until it is a whitespace or an invalid character.
				while (i < argument.size()) {
					if (IsCharacterLetter(argument[i]) || IsCharacterNumber(argument[i])) {
						Temp.lexeme += argument[i];
						i++;
					} else {
						break;
					}
				}

				i--;

				Result.push_back(Temp);
				continue;
			}

				// Is it a number.
			if (IsCharacterNumber(argument[i])) {
				LexicalUnit Temp;
				Temp.Token = Token_Identifier;
				Temp.lexeme = "";
				Temp.lexeme += argument[i];
				Temp.LineNumber = Linenumber;

				i++;

					// Continue until it is a whitespace or an invalid character.
				while (i < argument.size()) {
					if (IsCharacterNumber(argument[i])) {
						Temp.lexeme += argument[i];
						i++;
					} else {
						break;
					}
				}

				i--;

				Result.push_back(Temp);
				continue;
			}

				// The character has not been found so look it up.
			Lookup(argument[i], Linenumber, Result);
		}
		
		return Result;
	}

};

#endif
