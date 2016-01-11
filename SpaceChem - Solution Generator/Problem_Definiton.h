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

// The goal of this class is to store all of the parameters 
//		used in the program that were loaded from a file.

#ifndef Problem_Definition_Header
#define Problem_Definition_Header

	// Used for the required output. 
#include "Atom.h"

#include <vector>

	// A structure to contain all of the odds because of how many there are.
struct Odds {

		// Odds for random mutations.			
	int OddsTo_Mutate;
	int Mutate_Add_Instruction;
	int Mutate_Remove_Instruction;
	int Mutate_Change_Instruction;
	int Mutate_Move_Instruction;
	int Mutate_Change_Color;
	int Mutate_Change_Direction;
		// End of random odds of mutation.


		// Odds for if the Generate_Mate_Reactor.
	int How_Many_To_Mate;

		// What are the odds to randomly generate a new one.
	int Randomly_Generate;

		// The odds on randomly generating to place an instruction object.
	int Random_ToPlace;

		// -- Random --

		// The odds on randomly generating to place an instuction.
	int Set_Instruction;

		// Used by random generation to determine if a new direction should be placed.
	int Set_Direction;

		// Used by random, if it is not red it will be blue. (normally 50/50 so 1 out of 2);
	int Color;

		// -- Random --


	Odds() {
		Mutate_Add_Instruction		= 1;
		Mutate_Remove_Instruction	= 1;
		Mutate_Change_Instruction	= 1;
		Mutate_Move_Instruction	= 1;
		Mutate_Change_Color		= 2;
				
		Random_ToPlace		= 1;
	}
};

class Problem_Definition{

		// The hard cap for the total cycles allow in the entire simulation.
	private: unsigned long long Cycle_Limit_Total; //Max of 18,446,744,073,709,551,615, 0 for unlimited.

		// The hard cap for a single simulation.
	private: unsigned long Cycle_Limit_Simulation; //Max of 4,294,967,295, 0 for unlimited.

		// The hard cap for the number of simulations that can run before halting.
	private: unsigned long Simulation_Max; //Max of 4,294,967,295, 0 for unlimited.

		// The hard cap for the of number of solutions found before halting.
	private: unsigned long Simulation_Solution_Max; //Max of 4,294,967,295, 0 for unlimited.

		// How many solutions to dump on halting.
	private: unsigned long Simulation_Solution_Toaccept; //Max of 4,294,967,295, 0 for unlimited.

		// The instructions that are possible to use.
	private: std::vector<short> Allow_Instructions;

		// Get an allowed instruction by index.
	public: short Get_Instruction(unsigned int index) {

			// Catch.
		if (index >= Allow_Instructions.size()) {
			return Instruction_NOP;
		}

		return Allow_Instructions[index];
	}
	public: short Get_Instruction_Size() { return Allow_Instructions.size(); }



		// How many solutions should be paired.
	private: int Number_To_Crossover; // not sure what this was for. Debugging

		// The number of simulations to work with.
	public: unsigned int Solution_Pool_Size;

		// Odds are calculated 1 out of odds. For 100% chance the odds would be 1, 1 out of 1.
	public: Odds Odds_Table;








	
//---------- For future use ------------
		// What is the max number of reactors that can be placed.
	int Reactor_Max;
	short Reactor_Limit_Standard;
	short Reactor_Limit_Assembly;
	short Reactor_Limit_Disassembly;
	short Reactor_Limit_Sensor;
	short Reactor_Limit_Fusion;

		// Used in some missions for storing atoms.
	int Storage_Tank_Max;

		// How many Recycling Plants there are.
	int Recycling_Plant_Count;

		// The percent of cycle decrease that is required to share.
	double Sharing_Req_Percent;

		// The symbol reduction decrease that is required to share.
	int Share_Req_Symbol_Reduction;

		// The simulation count required before a force share. 
	int Share_Req_Simulation_Count;

		// How many nodes to trade with when sharing is possible.
	int Share_Node_Trade_Count;

		// Only trade if there is a percent increase.
	double Share_Node_Trade_Percent;

		// Share with nodes at random.
	bool Share_Node_Randomly;

//---------- End of future use ------------

		// Default constructor.
	public: Problem_Definition(){

			// These need to be set by the user.
		Cycle_Limit_Total			= 1;
		Cycle_Limit_Simulation		= 1;

		Number_To_Crossover			= 1;
		Solution_Pool_Size			= 1;


			//----- Future use --------
		Reactor_Max					= -1;
		Reactor_Limit_Standard		= -1;
		Reactor_Limit_Assembly		= -1;
		Reactor_Limit_Disassembly	= -1;
		Reactor_Limit_Sensor		= -1;
		Reactor_Limit_Fusion		= -1;
		Storage_Tank_Max			= -1;
		Recycling_Plant_Count		= -1;
		Sharing_Req_Percent			= -1;
		Share_Req_Symbol_Reduction	= -1;
		Share_Req_Simulation_Count	= -1;
		Share_Node_Trade_Count		= -1;
		Share_Node_Trade_Percent	= -1;
		Share_Node_Randomly			= false;

	}

		// Default destructor.
	public: ~Problem_Definition(){}

	public: void Add_Instruction(int InstructionID)						{ Allow_Instructions.push_back(InstructionID); }
	public: void Set_Cycle_Limit_Total(unsigned long long argument)		{ Cycle_Limit_Total = argument; }
	public: void Set_Cycle_Limit_Simulation(unsigned long argument)		{ Cycle_Limit_Simulation = argument;  }
	public: void Set_Simulation_Max(unsigned long argument)				{ Simulation_Max = argument; }
	public: void Set_Simulation_Solution_Max(unsigned long argument)	{ Simulation_Solution_Max = argument; }
	public: void Set_Simulation_Solution_Toaccept(unsigned long argument)	{ Simulation_Solution_Toaccept = argument;}


	public: unsigned long long Get_Cycle_Limit_Total()		    { return Cycle_Limit_Total; }
	public: unsigned long Get_Cycle_Limit_Simulation()		{ return Cycle_Limit_Simulation; }
	public: unsigned long Get_Simulation_Max()				{ return Simulation_Max; }
	public: unsigned long Get_Simulation_Solution_Max()	    { return Simulation_Solution_Max; }
	public: unsigned long Get_Simulation_Solution_Toaccept()	{ return Simulation_Solution_Toaccept; }
};

#endif