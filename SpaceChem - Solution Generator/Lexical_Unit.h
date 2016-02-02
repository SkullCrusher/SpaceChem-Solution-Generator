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
	Lexical_Unit.h - Lexical units for holding information about the input file.
*/
#ifndef LexicalUnit_H
#define LexicalUnit_H

#include <string>

#define Token_Null					0
#define Token_Integer				1
#define Token_Identifier			2
#define Token_Left_Bracket			3
#define Token_Right_Bracket			4
#define Token_Comma					5
#define Token_Equals				6
#define Token_Unknown				7
#define Token_Missing_Comment_Tag	8
#define Token_NewLine				9


struct LexicalUnit{

		// Holds what kind it is.
	int Token = Token_Null;

		// Holds the value.
	std::string lexeme = "";

		// What line the error is on.
	int LineNumber = 0;

	LexicalUnit() {

	}

};

#endif