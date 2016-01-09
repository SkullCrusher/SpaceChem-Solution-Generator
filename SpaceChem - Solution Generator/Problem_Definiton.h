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

	//(TO DO) Used for the required output. 
#include "Atom.h"

#include <vector>

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

		// Odds are calculated 1 out of odds. For 100% chance the odds would be 1, 1 out of 1.
	private: int Odds_To_Add_Instruction;
	private: int Odds_To_Remove_Instruction;
	private: int Odds_To_Change_Instruction;
	private: int Odds_To_Move_Instruction;
	private: int Odds_To_Change_Color;
	private: int Odds_To_Change_Direction;
		
		// Used by random generation to determine if a new direction should be placed.
	private: int Odds_To_Set_Direction;

		// If it is not red it will be blue. (normally 50/50 so 1 out of 2);
	private: int Odds_To_Be_Red;

		// How many solutions should be paired.
	private: int Number_To_Crossover;

		// The number of simulations to work with.
	private: unsigned int Solution_Pool_Size;

	public: unsigned int Get_Solution_Pool_Size() { return Solution_Pool_Size; }
	public: void Set_Solution_Pool_Size(unsigned int argument) { Solution_Pool_Size = argument; }
	
		// What are the odds to randomly generate a new one.
	private: int Odds_To_Randomly_Generate;
				
		// The odds on randomly generating to place an instruction.
	private: int Odds_On_Random_ToPlace;

	public: int Get_Odds_On_Random_ToPlace() { return Odds_On_Random_ToPlace; }
	public: void Set_Odds_On_Random_ToPlace(int argument) {
		if (argument == 0) {
			Odds_On_Random_ToPlace = -1;
		}else{
			Odds_On_Random_ToPlace = argument;
		}
	}













	
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

		Odds_To_Add_Instruction		= 0;
		Odds_To_Remove_Instruction	= 0;
		Odds_To_Change_Instruction	= 0;
		Odds_To_Move_Instruction	= 0;
		Odds_To_Change_Color		= 0;
		Number_To_Crossover			= 0;
		Solution_Pool_Size			= 0;
		Odds_On_Random_ToPlace		= 0;


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