// This is a class to contain a possible solution (for just the reactor) to the problem.
// Once a solution is made it cannot be change only new ones will be made based off the fitness.

#ifndef Solution_Reactor_Header
#define Solution_Reactor_Header

#include <vector>


struct Tile {
		// true = red, false = blue
	bool RedorBlue; // Might not be required.
		
		// The tile can only contain two instructions.
	int Instruction_1;
	int Instruction_2;

	Tile() {
		Instruction_1 = -1;
		Instruction_2 = -1;
	}
};

struct Position {
	int X;
	int Y;
};

class Solution_Reactor {

		// If the reactor has been simulated skip resimulating.
	private: bool HasBeenSimulated;

		// The level of fitness based off settings.
	private: double Fitness;

		// How many cycles the Solution has lived, the higher the life span the better chance it is good.
	private: unsigned long long Life_Span;

		// The reactor instruction layout for red and blue.
	private: Tile Red[8][10];
	private: Tile Blue[8][10];
			 
		// The positions of the bond tiles.
	std::vector<Position> BondTiles;

		// F, Atom number 9, Max Bond 1


		// Default constructor.
	public: Solution_Reactor() {
		HasBeenSimulated = false;
		Fitness = 0;
		Life_Span = 0;
	}

		// Default destructor.
	public: ~Solution_Reactor(){}

		//Set an instruction to a tile. true = red, false = blue
	public: int Set_Instruction_For_Tile(int x, int y, bool RedorBlue, int Instruction_1 = -1, int Instruction_2 = -1) {

			// Catch
		if (x < 0 || y < 0 || x > 9 || y > 7) {
			return Error_Set_Int_Tile_OOB;
		}

		if (RedorBlue) {
			Red[y][x].Instruction_1 = Instruction_1;
			Red[y][x].Instruction_2 = Instruction_2;
		}else{
			Blue[y][x].Instruction_1 = Instruction_1;
			Blue[y][x].Instruction_2 = Instruction_2;
		}
	}

};

#endif