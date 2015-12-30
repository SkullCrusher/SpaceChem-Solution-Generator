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
	private: unsigned long Cycles;

		// The solution to be simulated.
	private: Solution_Reactor Solution;

		// The red and blue waldo which are the controlling parts of the simulation.
	private: Waldo Red_Waldo;
	private: Waldo Blue_Waldo;

	/* 
				The in and out containers for molecules.
		It is a buffer that the controller for the simulation has to handle.
		We know that only two Molecule can be pulled in and pushed out on each cycle.

		Note: The reason why it is not one is if the molecules happen to be different
		they might not collide so it requires a double buffer.
	*/

	private: Packed_Molecule In_Alpha[2];
	private: Packed_Molecule Out_Omega[2];
	
	private: Packed_Molecule In_Beta[2];
	private: Packed_Molecule Out_Phi[2];

		// The molecules currently in the reactor.
	private: std::vector<Molecule> Active_Molecules;

		// Add a new molecule to the input (This will have to be changed later)
	public: short Add_To_Input(Packed_Molecule argument, short IsAlphaOrBeta) {

		if (IsAlphaOrBeta == Simulation_Add_To_Input_Alpha) {
			// There are four cases, empty, full, last is empty, first is empty.

				// Empty
			if (In_Alpha[0].GetIsEmpty() && In_Alpha[1].GetIsEmpty()) {
				In_Alpha[0] = argument;
				return Simulation_Add_To_Input_Worked;
			}

				// Full
			if (!In_Alpha[0].GetIsEmpty() && !In_Alpha[1].GetIsEmpty()) {
				return Simulation_Add_To_Input_Full;
			}

				// First is empty, move the last to the first.
			if (In_Alpha[0].GetIsEmpty() && !In_Alpha[1].GetIsEmpty()) {
				In_Alpha[0] = In_Alpha[1];
			}

				// First is empty
			if (In_Alpha[0].GetIsEmpty()) {
				In_Alpha[0] = argument;
				return Simulation_Add_To_Input_Worked;
			}

				// Last is empty
			if (In_Alpha[1].GetIsEmpty()) {
				In_Alpha[1] = argument;
				return Simulation_Add_To_Input_Worked;
			}
		}
		
		if(IsAlphaOrBeta == Simulation_Add_To_Input_Beta){
			// There are four cases, empty, full, last is empty, first is empty.

				// Empty
			if (In_Beta[0].GetIsEmpty() && In_Beta[1].GetIsEmpty()) {
				In_Beta[0] = argument;
				return Simulation_Add_To_Input_Worked;
			}

				// Full
			if (!In_Beta[0].GetIsEmpty() && !In_Beta[1].GetIsEmpty()) {
				return Simulation_Add_To_Input_Full;
			}

			// First is empty, move the last to the first.
			if (In_Beta[0].GetIsEmpty() && !In_Beta[1].GetIsEmpty()) {
				In_Beta[0] = In_Beta[1];
			}

				// First is empty (This might not be required)
			if (In_Beta[0].GetIsEmpty()) {
				In_Beta[0] = argument;
				return Simulation_Add_To_Input_Worked;
			}

				// Last is empty
			if (In_Beta[1].GetIsEmpty()) {
				In_Beta[1] = argument;
				return Simulation_Add_To_Input_Worked;
			}
		}

		return Simulation_Add_To_Input_Worked;
	}
	
		// Default constructor.
	public: Simulation(){
		Cycle_Limit_Simulation = 0;
		Cycles = 0;
	}

		// Default destructor.
	public: ~Simulation(){}

		// Finds the starting instruction in the solution for the waldo.
	private: short FindStart(bool RedorBlue, Waldo &argument){

		for (int w = 0; w < 10; w++){
			for (int h = 0; h < 8; h++){				
				Tile Result = Solution.GetTile(w, h, RedorBlue);
					
					// If the tile is a starting point, set it.
				if (Result.Instruction_1 == Instruction_Start_Left  || 
					Result.Instruction_1 == Instruction_Start_Right ||
					Result.Instruction_1 == Instruction_Start_Up	||
					Result.Instruction_1 == Instruction_Start_Down){

					short Direction = -1;

					if (Result.Instruction_1 == Instruction_Start_Left){Direction = Instruction_Left;}
					if (Result.Instruction_1 == Instruction_Start_Right){Direction = Instruction_Right;}
					if (Result.Instruction_1 == Instruction_Start_Up){Direction = Instruction_Up;}
					if (Result.Instruction_1 == Instruction_Start_Down){Direction = Instruction_Down;}

					argument.SetX(w);
					argument.SetY(h);
					argument.SetActive(true);
					argument.Set_Direction(Direction);

					return Simulation_Continue;
				}							
			}
		}		

		return Simulation_Continue;
	}

		// Generates the requirements to start the simulation.
	private: int GenerateDefaults(){
			// Find the starting point and direction of the waldos.
		
		int RedStart_R = FindStart(Red_Tile, Red_Waldo);
		int BlueStart_R = FindStart(Blue_Tile, Blue_Waldo);

		return Simulation_Continue;
	}

		// Moves the waldo based off the direction inside it.
	private: void MoveWaldo(Waldo &argument){

			// The waldo is waiting for input so loop.
		if (argument.GetIdle_For_Input()) {
			return;
		}
		
		if (argument.GetDirection() == Waldo_Direction_Left){
				// Check if the waldo is at the edge, if so do nothing.
			if (argument.GetX() > 0){
				argument.SetX(argument.GetX() - 1);

					// If the Waldo is holding a molecule move it also.
				if (argument.GetGrabbing_Molecule()) {
					Active_Molecules[argument.GetGrabbing_Molecule_Index()].Set_X(Active_Molecules[argument.GetGrabbing_Molecule_Index()].Get_X() - 1);
				}
			}
		}

		if (argument.GetDirection() == Waldo_Direction_Right){
				// Check if the waldo is at the edge, if so do nothing.
			if (argument.GetX() < 9){
				argument.SetX(argument.GetX() + 1);

					// If the Waldo is holding a molecule move it also.
				if (argument.GetGrabbing_Molecule()) {
					Active_Molecules[argument.GetGrabbing_Molecule_Index()].Set_X(Active_Molecules[argument.GetGrabbing_Molecule_Index()].Get_X() + 1);
				}
			}
		}

		if (argument.GetDirection() == Waldo_Direction_Up){
				// Check if the waldo is at the edge, if so do nothing.
			if (argument.GetY() > 0){
				argument.SetY(argument.GetY() - 1);

					// If the Waldo is holding a molecule move it also.
				if (argument.GetGrabbing_Molecule()) {
					Active_Molecules[argument.GetGrabbing_Molecule_Index()].Set_Y(Active_Molecules[argument.GetGrabbing_Molecule_Index()].Get_Y() - 1);
				}
			}
		}

		if (argument.GetDirection() == Waldo_Direction_Down){
				// Check if the waldo is at the edge, if so do nothing.
			if (argument.GetY() < 7){
				argument.SetY(argument.GetY() + 1);

					// If the Waldo is holding a molecule move it also.
				if (argument.GetGrabbing_Molecule()) {
					Active_Molecules[argument.GetGrabbing_Molecule_Index()].Set_Y(Active_Molecules[argument.GetGrabbing_Molecule_Index()].Get_Y() + 1);
				}
			}
		}

	}

		// Searches the Active_Molecules and returns the index to it if found.
/*TOTEST*/private: int FindIfMoleculeIsAtTile(int X, int Y) {

			// Search Active_Molecules.
		for (unsigned int i = 0; i < Active_Molecules.size(); i++) {
			if (Active_Molecules[i].CheckIfAtom_Relative(X, Y)) {
					// A atom is found at that position so return.
				return i;
			}
		}

			// No molecule found.
		return -1; 
	}


		// ------------------------------ Handles all of the instructions. ----------------------------------------
	private: void Handle_Instruction_In_Alpha(Waldo &argument, bool RedorBlue) {
		
		// Pull the first one from the input and move the second to the first.
		//If we don't have an input triggle a idle loop until we do.
		if (In_Alpha[0].GetIsEmpty() && In_Alpha[1].GetIsEmpty()) {
			// Set the waldo to idle.
			argument.SetIdle_For_Input(true);
			return;
		}

			// If there is a input in first use that.
		if (!In_Alpha[0].GetIsEmpty()) {
				// Center the molecule in the top left.
			In_Alpha[0].Set_X(0);
			In_Alpha[0].Set_Y(0);

				// Add the molecule to the active list.
			Packed_Molecule Temp = In_Alpha[0];

			for (unsigned int i = 0; i < Temp.Items.size(); i++) {
				Active_Molecules.push_back(Temp.Items[i]);
			}
			// Active_Molecules.push_back(In_Alpha[0]); // Old way
			
				// Set the trash flag on the input to "delete" it.
			In_Alpha[0].Set_IsEmpty(true);

				// Just shift them because it wont hurt anything.
			In_Alpha[0] = In_Alpha[1];

			return;
		}

		if (!In_Alpha[1].GetIsEmpty()) {
				// Center the molecule in the top left.
			In_Alpha[1].Set_X(0);
			In_Alpha[1].Set_Y(0);

				// Add the molecule to the active list.
			Packed_Molecule Temp = In_Alpha[1];

			for (unsigned int i = 0; i < Temp.Items.size(); i++) {
				Active_Molecules.push_back(Temp.Items[i]);
			}
			// Active_Molecules.push_back(In_Alpha[1]); // Old way
			
				// Set the trash flag on the input to "delete" it.
			In_Alpha[1].Set_IsEmpty(true);

			return;
		}

	}

/*TODO*/private: void Handle_Instruction_Bond_Remove(Waldo &argument, bool RedorBlue) {

		int debug = 0;
	}

/*TODO*/private: void Handle_Instruction_Out_Omega(Waldo &argument, bool RedorBlue) {

			// Go through each molecule and check if any is in the output area for omega.
			// Make a list of the output and put them into a single output.

		int debug = 0;
	}

			// Grab the molecule so the waldo will move it with it.
/*TOTEST*/private: void Handle_Instruction_Grab(Waldo &argument, bool RedorBlue) {
		
		int Result = FindIfMoleculeIsAtTile(argument.GetX(), argument.GetY());
		
			// There is no atom at this position.
		if (Result == -1) {
			return;
		}

		argument.SetGrabbing_Molecule(true);
		argument.SetGrabbing_Molecule_Index(Result);
		
		int debug = 0;
	}

			// Have the waldo let go of the molecule.
/*TOTEST*/private: void Handle_Instruction_Drop(Waldo &argument, bool RedorBlue) {

		argument.SetGrabbing_Molecule(false);
		argument.SetGrabbing_Molecule_Index(-1);
		
		int debug = 0;
	}

		// Trigger the sync requirement for the Waldo. This puts the Waldo in a state of idle until both hit it.
	private: void Handle_Instruction_Sync(Waldo &argument, bool RedorBlue) {
		
			// The only requirement is to set the sync bit on the waldo, the rest is handled in the Simulate_Cycle()
		argument.Set_Idle_For_Sync(true);
	}

		// ------------------------------     End of the instructions.     ----------------------------------------

			// Checks if the molecule's atoms are out of the bounds of the reactor.
/*TODO*/private: bool Is_Molecule_OutOfBounds(Molecule &argument) {

		return false;
	}

			// Used by CheckForCollision to see if any Molecules overlap.
/*TODO*/private: bool Do_Molecules_Overlap(Molecule &A, Molecule &B) {

		return false;
	}

		// Checks the entire Reactor to see if there is a collision 
			 // (Note to self, you might be able to reduce the processing time here by only checking the change)
	private: short CheckForCollision(){

			// Check each molecule against the rest, honestly this is a pretty slow way of doing it but
			// hopefully because active molecules is small enough it will not effect the speed.
		for (unsigned int i = 0; i < Active_Molecules.size(); i++) {
			for (unsigned int g = i + 1; g < Active_Molecules.size(); g++) {
					// Check for overlap
				if (Do_Molecules_Overlap(Active_Molecules[i], Active_Molecules[g])) {
						// Yes, a overlap was detected. This simulation proves the solution is invalid.
					return Collision_Yes_Collision;
				}
			}
		}
			// Check if any Molecules are out of bounds.
		for (unsigned int i = 0; i < Active_Molecules.size(); i++) {
			if (Is_Molecule_OutOfBounds(Active_Molecules[i])) {
					//Yes, this molecule is out of bounds. This simulation proves the solution is invalid.
				return Collision_Yes_Collision;
			}
		}
		
		return Collision_No_Collision;
	}

		// Runs the instruction that is provided in Instruction_1 and used Instruction_2 for direction.
	private: short Execute_Instruction(Waldo &argument, bool RedorBlue){
		
			// Pull the instructions for that tile.
		Tile Instruction = Solution.GetTile(argument.GetX(), argument.GetY(), RedorBlue);

			// Attempt to run the instruction in Instruction_1.
		switch (Instruction.Instruction_1){

			case Instruction_NOP:
				// Do nothing.
				break;
			case Instruction_Bond_Add:
					// Not required for prototype
				break;
			case Instruction_Bond_Remove: 
				Handle_Instruction_Bond_Remove(argument, RedorBlue);
				break;
			case Instruction_In_Alpha:					
				Handle_Instruction_In_Alpha(argument, RedorBlue);				
				break;
			case Instruction_In_Beta: 
					// Not required for prototype.
				break;
			case Instruction_Out_Omega: 
				Handle_Instruction_Out_Omega(argument, RedorBlue);
				break;
			case Instruction_Out_Psi: 
					// Not required for prototype.
				break;
			case Instruction_Rotate_R: 
					// Not required for prototype.
				break;
			case Instruction_Rotate_L: 
					// Not required for prototype.
				break;
			case Instruction_Grab: 
				Handle_Instruction_Grab(argument, RedorBlue);
				break;
			case Instruction_Drop: 
				Handle_Instruction_Drop(argument, RedorBlue);
				break;
			case Instruction_GrabDrop: 
					// Not required for prototype.
				break;
			case Instruction_Sync: 
				Handle_Instruction_Sync(argument, RedorBlue);
				break;
		}

			// Change the direction to the instruction in Instruction_2.
		switch (Instruction.Instruction_2) {
			case Instruction_NOP:
				// Do nothing.
				break;
			case Instruction_Left: 
				argument.Set_Direction(Waldo_Direction_Left);
				break;
			case Instruction_Right:
				argument.Set_Direction(Waldo_Direction_Right);
				break;
			case Instruction_Up:
				argument.Set_Direction(Waldo_Direction_Up);
				break;
			case Instruction_Down: 
				argument.Set_Direction(Waldo_Direction_Down);
				break;			
		}
		
		return Execution_NoError;
	}

		// This simulates a single cycle for both the Red Waldo and the Blue Waldo.
	private: int Simulate_Cycle(){

			// Pre-step: If both are waiting on sync, reset the sync.
		if (Red_Waldo.Get_Idle_For_Sync() && Blue_Waldo.Get_Idle_For_Sync()) {
			Red_Waldo.Set_Idle_For_Sync(false);
			Blue_Waldo.Set_Idle_For_Sync(false);
		}

			// The steps of the simulation:

			// Check if there is a red track we need to simulate. Also if the waldo is idling for sync skip.
		if (Red_Waldo.GetActive() && !Red_Waldo.Get_Idle_For_Sync()){

				// 1. Move Red Waldo.
			MoveWaldo(Red_Waldo);
			/*TODO: only call checkforcollision if a instruction that caused it is executed.*/
				// 2. Check for collision (only if holding molecule or inserting a new one).
			if (Red_Waldo.GetGrabbing_Molecule()){
				int Result = CheckForCollision();

					// If there is a collision, halt.
				if (Result == Collision_Yes_Collision){

						// Set the information on the simulation.
					Solution.Set_Status(Solution_Invalid_Collision);
					Solution.Set_HasBeenSimulated(true);

					return Simulation_Collision;
				}
			}

				// 3. Execute Red Waldo instruction_1.
				// 4. Set new direction if there instruction_2.
			int Result = Execute_Instruction(Red_Waldo, Red_Tile);

			if (Result != Execution_NoError) {
				// Set the information on the simulation.
				Solution.Set_Status(Simulation_Add_To_Input_ExeErr);
				Solution.Set_HasBeenSimulated(true);

				return Simulation_Add_To_Input_ExeErr;
			}

				/*TODO: only call checkforcollision if a instruction that caused it is executed.*/
			// 5. Check for collision (only if there was an instruction that could cause).	
			int Result_Collision = CheckForCollision(); 

				// If there is a collision, halt.
			if (Result_Collision == Collision_Yes_Collision) {

				// Set the information on the simulation.
				Solution.Set_Status(Solution_Invalid_Collision);
				Solution.Set_HasBeenSimulated(true);

				return Simulation_Collision;
			}
		}
		
			// Check if there is a blue track we need to simulate. Also if the waldo is idling for sync skip.
		if (Blue_Waldo.GetActive() && !Blue_Waldo.Get_Idle_For_Sync()){
			
				// 6. Move Blue Waldo.
			MoveWaldo(Blue_Waldo);

			/*TODO: only call checkforcollision if a instruction that caused it is executed.*/
				// 7. Check for collision (only if holding molecule or inserting a new one).
			if (Blue_Waldo.GetGrabbing_Molecule()) {
				int Result = CheckForCollision();

					// If there is a collision, halt.
				if (Result == Collision_Yes_Collision) {

						// Set the information on the simulation.
					Solution.Set_Status(Solution_Invalid_Collision);
					Solution.Set_HasBeenSimulated(true);

					return Simulation_Collision;
				}
			}

				// 8. Execute Blue Waldo instruction_1.
				// 9. Set new direction if there instruction_2.
			int Result = Execute_Instruction(Blue_Waldo, Blue_Tile);

			if (Result != Execution_NoError) {
					// Set the information on the simulation.
				Solution.Set_Status(Simulation_Add_To_Input_ExeErr);
				Solution.Set_HasBeenSimulated(true);

				return Simulation_Add_To_Input_ExeErr;
			}

			/*TODO: only call checkforcollision if a instruction that caused it is executed.*/
				// 10. Check for collision (only if there was an instruction that could cause).	
			int Result_Collision = CheckForCollision();

				// If there is a collision, halt.
			if (Result_Collision == Collision_Yes_Collision) {

					// Set the information on the simulation.
				Solution.Set_Status(Solution_Invalid_Collision);
				Solution.Set_HasBeenSimulated(true);

				return Simulation_Collision;
			}
		}
			
		

		return Simulation_Continue;
	}

		// Process the simulation.
	public: int Tick(){
	
			// Halt the simulation if the cycles have reached the cap.
		if (Cycles >= Cycle_Limit_Simulation){
			return Simulation_OutOfCycles;
		}

			// If this is the first tick run the requirements to fill in the waldo.
		if (Cycles == 0){
			int Result = GenerateDefaults();

				// If there was an error.
			if (Result == Simulation_InvalidSimulation){
				return Simulation_InvalidSimulation;
			}
		}

			// Simulate a single cycle.
		int Result = Simulate_Cycle();
				
		Cycles++;

		return Result; // Normally Simulation_Continue
	}

		// Accept a new solution.
	public: void Set_Solution(Solution_Reactor argument) {
		Solution = argument;
	}

	public: void Set_Cycle_Limit_Simulation(int argument){
		Cycle_Limit_Simulation = argument;
	}

};
#endif