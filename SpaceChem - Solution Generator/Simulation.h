// A simulation of a reactor.

#ifndef Simulation_Header
#define Simulation_Header

	// Required for definitions and global class.
#include "Definitions.h"

#include "Waldo.h"
#include "Solution.h"
#include "Atom.h"

#include <vector>

class Simulation{
	
		// The cap on cycles.
	private: unsigned long Cycle_Limit_Simulation;

		// How many cycles have been simulated,
	//private: unsigned long Cycles;

		// The solution to be simulated.
	private: Solution_Reactor Solution;
			 

		// The red and blue waldo which are the controlling parts of the simulation.
	private: Waldo Red_Waldo;
	private: Waldo Blue_Waldo;

	/* 
				The in and out containers for molecules.
		It is a buffer that the controller for the simulation has to handle.
		We know that only two Molecule can be pulled in and pushed out on each cycle.
	*/

	private: Packed_Molecule In_Alpha[2];
	private: Packed_Molecule Out_Omega[2];
	
	private: Packed_Molecule In_Beta[2];
	private: Packed_Molecule Out_Phi[2];

		// The molecules currently in the reactor.
	private: std::vector<Molecule> Active_Molecules;

		// The order of placement, has the index of it.
	private: std::vector<unsigned int> Output_Omega_Order;
	private: std::vector<unsigned int> Output_Phi_Order;




		// Add a new molecule to the input (This will have to be changed later)
	public: short Add_To_Input(Packed_Molecule argument, short IsAlphaOrBeta);
	
		// This will be replaced later, it is only used for debugging.
	private: short Add_To_Output(Packed_Molecule argument, short IsAlphaOrBeta);

	public: Packed_Molecule Remove_From_Output();

		// Default constructor.
	public: Simulation();

		// Default destructor.
	public: ~Simulation();

		// Finds the starting instruction in the solution for the waldo.
	private: short FindStart(bool RedorBlue, Waldo &argument);

		// Generates the requirements to start the simulation.
	private: int GenerateDefaults();

		// Moves the waldo based off the direction inside it.
	private: void MoveWaldo(Waldo &argument);

		// Searches the Active_Molecules and returns the index to it if found.
	private: int FindIfMoleculeIsAtTile(int X, int Y);

		// Because the waldo works off index and the stack needs to be cleaned recalculate the index.
	private: void RecalculateWaldoHeld(Waldo &argument, bool RedorBlue);

		// This is pointed to a position on the tilemap and it follows the atom bonds and returns the attached. 
	private: void TraceAtom(std::vector<Position> &Results, Molecule argument, short X, short Y);

		// Creates new molecules based off the argument molecule. (Warning do not pass the molecule by reference it deletes data)
	private: std::vector<Molecule> Break_Molecule(Molecule argument);

		// Uses the index list to change the Active_Molecule list into multiple molecules.
	private: int BreakUpMolecules(std::vector<unsigned int> &Index_List);

		// ------------------------------ Handles all of the instructions. ----------------------------------------
	private: void Handle_Instruction_In_Alpha(Waldo &argument, bool RedorBlue);

		// Triggers all of the bonding pads to remove the bonds and it might split the molecule.
	private: void Handle_Instruction_Bond_Remove(Waldo &argument, bool RedorBlue);

		//  Pack the molecules into a Packed_Molecule and put it in the output
	private: void Handle_Instruction_Out_Omega(Waldo &argument, bool RedorBlue);

		// Grab the molecule so the waldo will move it with it.
	private: void Handle_Instruction_Grab(Waldo &argument, bool RedorBlue);

		// Have the waldo let go of the molecule.
	private: void Handle_Instruction_Drop(Waldo &argument, bool RedorBlue);

		// Trigger the sync requirement for the Waldo. This puts the Waldo in a state of idle until both hit it.
	private: void Handle_Instruction_Sync(Waldo &argument, bool RedorBlue);
		// ------------------------------     End of the instructions.     ----------------------------------------

		// Checks if the molecule's atoms are out of the bounds of the reactor.
	private: bool Is_Molecule_OutOfBounds(Molecule &argument);

		// Used by CheckForCollision to see if any Molecules overlap.
	private: bool Do_Molecules_Overlap(Molecule &A, Molecule &B);

		// Checks the entire Reactor to see if there is a collision 
			 // (Note to self, you might be able to reduce the processing time here by only checking the change)
	private: short CheckForCollision();

		// Runs the instruction that is provided in Instruction_1 and used Instruction_2 for direction.
	private: short Execute_Instruction(Waldo &argument, bool RedorBlue);

		// This simulates a single cycle for both the Red Waldo and the Blue Waldo.
	private: int Simulate_Cycle();

		// Process the simulation.
	public: int Tick();

		// Accept a new solution.
	public: void Set_Solution(Solution_Reactor argument);

		// Set how many cycles can be simulated before a force halt.
	public: void Set_Cycle_Limit_Simulation(int argument);

	public: void Set_Simulation_Status(int argument) {
		Solution.Set_Status(argument);
	}

	public: int Get_Simulation_Status() {
		return Solution.Get_Status();
	}

	public: bool Get_Is_Simulated() {
		return Solution.Get_HasBeenSimulated();
	}

	public: void Set_Is_Simulated(bool argument) {
		Solution.Set_HasBeenSimulated(argument);
	}

	public: Solution_Reactor GetSolution() {
		return Solution;
	}
			
};
#endif