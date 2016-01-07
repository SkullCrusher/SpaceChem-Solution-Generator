// This is a class to contain a possible solution (for just the reactor) to the problem.
// Once a solution is made it cannot be change only new ones will be made based off the fitness.

#ifndef Solution_Reactor_Header
#define Solution_Reactor_Header

#include <vector>

struct Tile {
		// true = red, false = blue
	bool RedorBlue; // Might not be required.
		
		// The tile can only contain two instructions,
		//		Instruction_1: used for an action instruction.
		//		Instruction_2: used for an direction (not including the start)
	int Instruction_1;
	int Instruction_2;

	Tile() {
		Instruction_1 = Instruction_NOP;
		Instruction_2 = Instruction_NOP;
	}
};

struct Position {
	int X;
	int Y;
};

class Solution_Reactor {

		// The status of the solution, holds the error code if any.
	private: short Status;

		// If the reactor has been simulated skip resimulating.
	private: bool HasBeenSimulated;

		// The amount of cycles used on the simulation.
	private: unsigned long Cycles;

		// The level of fitness based off settings.
	private: double Fitness;

		// How many cycles the Solution has lived, the higher the life span the better chance it is good.
	private: unsigned long long Life_Span;

		// The toal count of symbols, red + blue.
	private: unsigned Symbol_Count_Total;
	
		// The count of the blue symbols.
	private: unsigned Symbol_Count_Red;
		
		// The count of the red symbols.
	private: unsigned Symbol_Count_Blue;

		// The position of the bonding pads.
	private: std::vector < Position > Bonding_Pad;

		// The reactor instruction layout for red and blue.
	private: Tile Red[8][10];
	private: Tile Blue[8][10];
			 
		// The positions of the bond tiles.
	std::vector<Position> BondTiles;

		// Default constructor.
	public: Solution_Reactor() {
		HasBeenSimulated = false;
		Fitness = 0;
		Life_Span = 0;

		Cycles = 0;

		Status = Solution_Unprocessed;
	}

		// Default destructor.
	public: ~Solution_Reactor(){}

	public: Tile GetTile(short X, short Y, bool RedorBlue){
			// Force inside the limit.
		if (X < 0){ X = 0; }
		if (X >= 10){ X = 9; }
		if (Y < 0){ Y = 0; }
		if (Y >= 8){ Y = 7; }

		if (RedorBlue == Red_Tile){
			return Red[Y][X];
		}else{
			return Blue[Y][X];
		}
	}

		// Set an instruction to a tile. true = red, false = blue
	public: int Set_Instruction_For_Tile(int x, int y, bool RedorBlue, int Instruction_1 = Instruction_NOP, int Instruction_2 = Instruction_NOP) {

			// Catch
		if (x < 0 || y < 0 || x > 9 || y > 7) {
			return Error_Set_Int_Tile_OOB;
		}

			// Used for the fitness calculation (starts do not count to the value.)
		if (Instruction_1 != Instruction_Start_Left && Instruction_1 != Instruction_Start_Right 
		 && Instruction_1 != Instruction_Start_Up   && Instruction_1 != Instruction_Start_Down) {
			Symbol_Count_Total++;
		}		

		if (RedorBlue) {
			Red[y][x].Instruction_1 = Instruction_1;
			Red[y][x].Instruction_2 = Instruction_2;

				// starts do not count to the value.
			if (Instruction_1 != Instruction_Start_Left && Instruction_1 != Instruction_Start_Right
			 && Instruction_1 != Instruction_Start_Up   && Instruction_1 != Instruction_Start_Down) {
				Symbol_Count_Red++;
			}
		}else{
			Blue[y][x].Instruction_1 = Instruction_1;
			Blue[y][x].Instruction_2 = Instruction_2;

				// starts do not count to the value.
			if (Instruction_1 != Instruction_Start_Left && Instruction_1 != Instruction_Start_Right
			 && Instruction_1 != Instruction_Start_Up   && Instruction_1 != Instruction_Start_Down) {
				Symbol_Count_Blue++;
			}
		}

		return Simulation_Continue;
	}

	public: unsigned int Get_BondingPadCount(){ return Bonding_Pad.size(); }
	public: std::vector<Position> Get_BondingPads(){ return BondTiles; }

		// Add a new bonding pad to the solution.
	public:	short Add_BondingPad(short X, short Y){

			// Prevent placeing two at the same position
		for (unsigned int i = 0; i < BondTiles.size(); i++){
			if (BondTiles[i].X == X && BondTiles[i].Y == Y){
				return Add_BondPad_Error_Duplicate_Pos;
			}
		}
	
			// Add to the bond tile.
		Position Temp;
		Temp.X = X;
		Temp.Y = Y;

		BondTiles.push_back(Temp);

			// Return no error.
		return Add_BondPad_NoError;
	}

	public: void Set_Status(short argument){ Status = argument; }
	public: short Get_Status(){ return Status; }
	public: void Set_HasBeenSimulated(bool argument){ HasBeenSimulated = argument; }
	public: bool Get_HasBeenSimulated(){ return HasBeenSimulated; }

	public: unsigned long Get_Cycles() {
		return Cycles;
	}

	public: void Set_Cycles(unsigned long argument) {
		Cycles = argument;
	}

	public: void Increment_Cycles() {
		Cycles++;
	}
};

#endif