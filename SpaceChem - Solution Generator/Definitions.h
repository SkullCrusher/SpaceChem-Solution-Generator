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


	// The list of errors.
#define Error_Incorrect_Argument_Count	1
#define Error_Set_Int_Tile_OOB			2

	// (Main) The range of arguments that are required to process a problem.
#define Minimum_Argument_Count			3
#define Maximum_Argument_Count			5

	// Red and blue so it's easier to remember.
#define Red_Tile						true
#define Blue_Tile						false

		// -- Error --

	// Simulation Results.
#define Simulation_Continue				0
#define Simulation_Complete				1	// Accepted
#define Simulation_OutOfCycles			2
#define Simulation_InvalidSimulation	3
#define Simulation_Collision			4
#define Simulation_Waldo_Pulled_Wrong	5	// Both waldos are holding the same molecule and they go different directions.
#define Simulation_Invalid_Output		6
#define Simulation_Atom_OutOfBounds		7

#define Remove_Bond_NoError				0
#define Remove_Bond_BreakUpMolecule		1		

	// Add bonding pad.
#define Add_BondPad_NoError				0
#define Add_BondPad_Error_Duplicate_Pos 1




	// Simulation Add_To_Input
#define Simulation_Add_To_Input_Alpha	1
#define Simulation_Add_To_Input_Beta	2
#define Simulation_Add_To_Input_Full	3
#define Simulation_Add_To_Input_Worked	4
#define Simulation_Add_To_Input_ExeErr	5

	// Waldo Definitons (same as instruction).
#define Waldo_Direction_Left			5
#define Waldo_Direction_Right			6
#define Waldo_Direction_Down			7
#define Waldo_Direction_Up				8

	// Collision check definitons.
#define Collision_No_Collision			0
#define Collision_Yes_Collision			1

	// Solution Definitions (status codes).
#define Solution_Unprocessed			1	// The solution has not been processed in a simulation
#define Solution_Invalid_Collision		2	// The solution is invalid because it has a collision
#define Solution_Invalid_NoStart		3	// The solution is invalid because there is not start (requires 1)
#define Solution_Out_Of_Cycles			4	// The solution went past the cycle cap.
#define Solution_Accepted				5	// The solution is a valid solution.

	// Execution Definitions
#define Execution_NoError				0

	// Atom IsSidebySide Definitions
#define Atom_Invalid					0
#define Atom_One_Is_Above_Two			1
#define	Atom_Two_Is_Above_One			2
#define Atom_One_Is_Right_Two			3
#define Atom_Two_Is_Right_One			4

	// Atom CanAddBonds Definitions
#define Atom_CanAddBonds_Left			1
#define	Atom_CanAddBonds_Right			2
#define Atom_CanAddBonds_Up				3
#define	Atom_CanAddBonds_Down			4



// Instruction list-----------------------------------------------

	// No instruction.
#define Instruction_NOP					0

	// The starting point of the waldo and what direction it goes.
#define Instruction_Start_Left			1
#define Instruction_Start_Right			2
#define Instruction_Start_Up			3
#define Instruction_Start_Down			4

	// Which direction to change the waldo's path to.
#define Instruction_Left				5
#define Instruction_Right				6
#define Instruction_Down				7
#define Instruction_Up					8

	// Triggers the bond tiles on the map.
#define Instruction_Bond_Add			9
#define Instruction_Bond_Remove			10

	// The input and output instrctions.
#define Instruction_In_Alpha			11
#define Instruction_In_Beta				12
#define Instruction_Out_Omega			13
#define Instruction_Out_Psi				14

	// The rotation instructions if the waldo is holding an atom.
#define Instruction_Rotate_R			15
#define Instruction_Rotate_L			16

	// The pick up or drop instructions for a waldo.
#define Instruction_Grab				17
#define Instruction_Drop				18
#define Instruction_GrabDrop			19

	// The sync instruction requires both sync to be activated.
#define Instruction_Sync				20