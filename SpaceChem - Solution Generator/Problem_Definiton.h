// The goal of this class is to store all of the parameters 
//		used in the program that were loaded from a file.

#ifndef Problem_Definition_Header
#define Problem_Definition_Header

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
		Cycle_Limit_Total = 1;
		Cycle_Limit_Simulation = 1;


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
};

#endif