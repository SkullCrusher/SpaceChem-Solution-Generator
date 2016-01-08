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

#ifndef Simulation_C
#define Simulation_C

#include "Simulation.h"

	// Add a new molecule to the input (This will have to be changed later)
short Simulation::Add_To_Input(Packed_Molecule argument, short IsAlphaOrBeta) {

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

	if (IsAlphaOrBeta == Simulation_Add_To_Input_Beta) {
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

	// This will be replaced later, it is only used for debugging.
short Simulation::Add_To_Output(Packed_Molecule argument, short IsAlphaOrBeta) {

	Out_Omega[0] = argument;

	return Simulation_Continue;
}

Packed_Molecule Simulation::Remove_From_Output() {

	Packed_Molecule Result;

	Result = Out_Omega[0];

	Out_Omega[0].Set_IsEmpty(true);

	return Result;
}

	// Default constructor.
Simulation::Simulation() {
	Cycle_Limit_Simulation = 0;
	//Cycles = 0;
}

	// Default destructor.
Simulation::~Simulation() {

}

	// Finds the starting instruction in the solution for the waldo.
short Simulation::FindStart(bool RedorBlue, Waldo &argument) {

	for (int w = 0; w < 10; w++) {
		for (int h = 0; h < 8; h++) {
			Tile Result = Solution.GetTile(w, h, RedorBlue);

			// If the tile is a starting point, set it.
			if (Result.Instruction_1 == Instruction_Start_Left ||
				Result.Instruction_1 == Instruction_Start_Right ||
				Result.Instruction_1 == Instruction_Start_Up ||
				Result.Instruction_1 == Instruction_Start_Down) {

				short Direction = -1;

				if (Result.Instruction_1 == Instruction_Start_Left) { Direction = Instruction_Left; }
				if (Result.Instruction_1 == Instruction_Start_Right) { Direction = Instruction_Right; }
				if (Result.Instruction_1 == Instruction_Start_Up) { Direction = Instruction_Up; }
				if (Result.Instruction_1 == Instruction_Start_Down) { Direction = Instruction_Down; }

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
int Simulation::GenerateDefaults() {
	// Find the starting point and direction of the waldos.

	int RedStart_R = FindStart(Red_Tile, Red_Waldo);
	int BlueStart_R = FindStart(Blue_Tile, Blue_Waldo);

	return Simulation_Continue;
}

	// Moves the waldo based off the direction inside it.
void Simulation::MoveWaldo(Waldo &argument) {

	// The waldo is waiting for input so loop.
	if (argument.GetIdle_For_Input()) {
		return;
	}

	// If the waldo is waiting for the output to finish.
	if (argument.GetIdle_For_Output()) {
		return;
	}

	if (argument.GetDirection() == Waldo_Direction_Left) {
		// Check if the waldo is at the edge, if so do nothing.
		if (argument.GetX() > 0) {
			argument.SetX(argument.GetX() - 1);

			// If the Waldo is holding a molecule move it also.
			if (argument.GetGrabbing_Molecule()) {
				Active_Molecules[argument.GetGrabbing_Molecule_Index()].Set_X(Active_Molecules[argument.GetGrabbing_Molecule_Index()].Get_X() - 1);
			}
		}
	}

	if (argument.GetDirection() == Waldo_Direction_Right) {
		// Check if the waldo is at the edge, if so do nothing.
		if (argument.GetX() < 9) {
			argument.SetX(argument.GetX() + 1);

			// If the Waldo is holding a molecule move it also.
			if (argument.GetGrabbing_Molecule()) {
				Active_Molecules[argument.GetGrabbing_Molecule_Index()].Set_X(Active_Molecules[argument.GetGrabbing_Molecule_Index()].Get_X() + 1);
			}
		}
	}

	if (argument.GetDirection() == Waldo_Direction_Up) {
		// Check if the waldo is at the edge, if so do nothing.
		if (argument.GetY() > 0) {
			argument.SetY(argument.GetY() - 1);

			// If the Waldo is holding a molecule move it also.
			if (argument.GetGrabbing_Molecule()) {
				Active_Molecules[argument.GetGrabbing_Molecule_Index()].Set_Y(Active_Molecules[argument.GetGrabbing_Molecule_Index()].Get_Y() - 1);
			}
		}
	}

	if (argument.GetDirection() == Waldo_Direction_Down) {
		// Check if the waldo is at the edge, if so do nothing.
		if (argument.GetY() < 7) {
			argument.SetY(argument.GetY() + 1);

			// If the Waldo is holding a molecule move it also.
			if (argument.GetGrabbing_Molecule()) {
				Active_Molecules[argument.GetGrabbing_Molecule_Index()].Set_Y(Active_Molecules[argument.GetGrabbing_Molecule_Index()].Get_Y() + 1);
			}
		}
	}

}

	// Searches the Active_Molecules and returns the index to it if found.
int Simulation::FindIfMoleculeIsAtTile(int X, int Y) {

	// Search Active_Molecules.
	for (unsigned int i = 0; i < Active_Molecules.size(); i++) {

		// Prevent the usage of NULL molecules.
		if (Active_Molecules[i].Get_IsEmpty()) {
			continue;
		}

		if (Active_Molecules[i].CheckIfAtom_Relative(X, Y)) {
			// A atom is found at that position so return.
			return i;
		}
	}

	// No molecule found.
	return -1;
}

	// Because the waldo works off index and the stack needs to be cleaned recalculate the index.
void Simulation::RecalculateWaldoHeld(Waldo &argument, bool RedorBlue) {

}

	// This is pointed to a position on the tilemap and it follows the atom bonds and returns the attached. 
void Simulation::TraceAtom(std::vector<Position> &Results, Molecule argument, short X, short Y) {

	// Check if the argument is an atom.
	if (argument.CheckIfAtom(X, Y)) {

		// It is a valid atom so add to the valid and then check it's bonds to see if they will be followed.
		Position Current;

		Current.X = X;
		Current.Y = Y;

		Results.push_back(Current);

		// Check left.
		if (argument.BondCount(X, Y, Atom_CanAddBonds_Left) > 0) {
			TraceAtom(Results, argument, X - 1, Y);
		}

		// Check Right.
		if (argument.BondCount(X, Y, Atom_CanAddBonds_Right) > 0) {
			TraceAtom(Results, argument, X + 1, Y);
		}

		// Check Up.
		if (argument.BondCount(X, Y, Atom_CanAddBonds_Up) > 0) {
			TraceAtom(Results, argument, X, Y - 1);
		}

		// Check Down.
		if (argument.BondCount(X, Y, Atom_CanAddBonds_Down) > 0) {
			TraceAtom(Results, argument, X, Y + 1);
		}
	}
}

	// Creates new molecules based off the argument molecule. (Warning do not pass the molecule by reference it deletes data)
std::vector<Molecule> Simulation::Break_Molecule(Molecule argument) {
	std::vector<Molecule> Split;

	// Go though every possible atom in the molecule.
	for (unsigned int i = 0; i < 11; i++) {
		for (unsigned int g = 0; g < 11; g++) {

			std::vector<Position> Result;

			// Trace the atom to find what it is connected to.
			TraceAtom(Result, argument, g, i);

			// If it is connected to anything copy it and null it on argument.
			if (Result.size() > 0) {

				Molecule New;

				// I am not sure why but data is lasting through loops so clear all the data.
				New.Reset();

				// Set general information.
				New.Set_X(argument.Get_X());
				New.Set_Y(argument.Get_Y());

				New.Set_IsEmpty(false);

				// Copy the atoms to the molecule.
				for (unsigned int z = 0; z < Result.size(); z++) {

					// Copy the atom.
					New.Set_Atom(Result[z].X, Result[z].Y, argument.Get_Atom(Result[z].X, Result[z].Y));

					Atom Trash;

					// Null the atom.
					argument.Set_Atom(Result[z].X, Result[z].Y, Trash);
				}

				Split.push_back(New);
			}
		}
	}

	return Split;
}

	// Uses the index list to change the Active_Molecule list into multiple molecules.
int Simulation::BreakUpMolecules(std::vector<unsigned int> &Index_List) {

	// Note, this needs to check waldos to make sure they are not holding the atom. If they are
	// Fix thier index. Also there might be a chance where two waldos grab the same molecule and split it
	// That case should be looked into.

	// Go through each molecule.
	for (unsigned int i = 0; i < Index_List.size(); i++) {

		// Break the molecule up.
		std::vector<Molecule> Results = Break_Molecule(Active_Molecules[Index_List[i]]);

		// Delete the old molecule.
		Active_Molecules.erase(Active_Molecules.begin() + Index_List[i]);

		// Put in the new molecules.
		for (unsigned int g = 0; g < Results.size(); g++) {
			Active_Molecules.push_back(Results[g]);
		}

		// We check if it is attached to a waldo, if so recalculate it's index.
		if (Red_Waldo.GetGrabbing_Molecule_Index() == Index_List[i]) {
			RecalculateWaldoHeld(Red_Waldo, Red_Tile);
		}

		// We check if it is attached to a waldo, if so recalculate it's index.
		if (Blue_Waldo.GetGrabbing_Molecule_Index() == Index_List[i]) {
			RecalculateWaldoHeld(Blue_Waldo, Blue_Tile);
		}
	}

	return 0;
}

	// ------------------------------ Handles all of the instructions. ----------------------------------------
void Simulation::Handle_Instruction_In_Alpha(Waldo &argument, bool RedorBlue) {

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

	// Triggers all of the bonding pads to remove the bonds and it might split the molecule.
void Simulation::Handle_Instruction_Bond_Remove(Waldo &argument, bool RedorBlue) {

	// A local list of bonding pads.
	std::vector<Position> Bonding_Pad_Pos = Solution.Get_BondingPads();

	// The molecules that need to break into multiple.
	std::vector<unsigned int> Break_Molecule_Index;

	// Go through every molecule that is active.
	for (unsigned int i = 0; i < Active_Molecules.size(); i++) {

		// The indexes of the bonding pads so duplication of data is not required.
		std::vector<unsigned int> Bonding_Pads_Connected;

		// Go through all of the bonding pads.
		for (unsigned int g = 0; g < Bonding_Pad_Pos.size(); g++) {

			// The current bonding pad we are testing against.
			Position Temp = Bonding_Pad_Pos[g];

			// Check if the bonding pad position effects this molecule. 
			if (Active_Molecules[i].CheckIfAtom_Relative(Temp.X, Temp.Y)) {
				Bonding_Pads_Connected.push_back(g);
			}
		}

		// All the bonding pads have been checked against the molecule.
		// If two or more were found on the same molecule debond them.
		if (Bonding_Pads_Connected.size() >= 2) {

			// Attempt to debond every molecule against every bonding pad, validation in the molecule
			// function will catch invalid calls.
			for (unsigned int j = 0; j < Bonding_Pads_Connected.size(); j++) {
				for (unsigned int t = j + 1; t < Bonding_Pads_Connected.size(); t++) {

					// Splitting them out like this makes it more human readable.
					unsigned int X_1 = Bonding_Pad_Pos[Bonding_Pads_Connected[j]].X;
					unsigned int Y_1 = Bonding_Pad_Pos[Bonding_Pads_Connected[j]].Y;

					unsigned int X_2 = Bonding_Pad_Pos[Bonding_Pads_Connected[t]].X;
					unsigned int Y_2 = Bonding_Pad_Pos[Bonding_Pads_Connected[t]].Y;

					int Result = Active_Molecules[i].Remove_Bond(X_1, Y_1, X_2, Y_2);

					// No error, do nothing.
					if (Remove_Bond_NoError == Result) {
						continue;
					}

					// The molecule needs to be flagged to be split up after all the bonds are removed.
					if (Remove_Bond_BreakUpMolecule == Result) {
						Break_Molecule_Index.push_back(i);
					}
				}
			}
		}
	}

	// Split the molecules up that require it.
	BreakUpMolecules(Break_Molecule_Index);
}

	//  Pack the molecules into a Packed_Molecule and put it in the output
void Simulation::Handle_Instruction_Out_Omega(Waldo &argument, bool RedorBlue) {

	// The argument to be sent into the pipe.
	Packed_Molecule Output;

	// std::stack<unsigned int> Output_Omega_Order;
	bool Output_TF = false;

	bool Output_already = false;

	int Left_To_Output = 0;

	// Go through each molecule and check if any is in the output area for omega.
	// Make a list of the output and put them into a single output.

	//for (unsigned int i = 0; i < Active_Molecules.size(); i++){
	for (unsigned int i = 0; i < Output_Omega_Order.size(); i++) {
		//Output_Omega_Order
		// Skip the molecule if it is empty. (Note is this to keep the same index for references later I will patch it to fix that)
		if (Active_Molecules[Output_Omega_Order[i]].Get_IsEmpty()) {
			continue;
		}

		// Skip the molecule if it is being held by a waldo.
		if (Red_Waldo.GetGrabbing_Molecule_Index() == Output_Omega_Order[i] || Blue_Waldo.GetGrabbing_Molecule_Index() == Output_Omega_Order[i]) {
			continue;
		}

		// Check if the molecule is inside the output area.
		bool Result = Active_Molecules[Output_Omega_Order[i]].CheckIfAtom_IsInLocation(6, 0, 9, 4);

		if (Result) {
				// If there is another molecule ready to be output but one was already output idle.
			if (Output_already) {
				argument.SetIdle_For_Output(true);
				Left_To_Output++;
			} else {

				// Add to the output pack.
				Output.Items.push_back(Active_Molecules[Output_Omega_Order[i]]);

				// "Delete" the element from the active list.
				Active_Molecules[Output_Omega_Order[i]].Set_IsEmpty(true);

				// Remove the active item from the output.
				Output_Omega_Order.erase(Output_Omega_Order.begin() + i);

				i--;

				// There was an output.
				Output_TF = true;

				// forces it to be a single in the output.
				Output_already = true;
			}
		}
	}

		// Make sure the output is not empty.
	if (Output.Items.size() >= 1) {
		Output.Set_IsEmpty(false);
	}

		// Set the output
	Out_Omega[0] = Output;

		// If there was no output release the waldo.
	if (!Output_TF || Output_Omega_Order.size() == 0 || Left_To_Output == 0) {
		argument.SetIdle_For_Output(false);
	}


	int debug = 0;
}

	// Grab the molecule so the waldo will move it with it.
void Simulation::Handle_Instruction_Grab(Waldo &argument, bool RedorBlue) {

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
void Simulation::Handle_Instruction_Drop(Waldo &argument, bool RedorBlue) {

		// If the waldo is not grabbing a molecule skip.
	if (!argument.GetGrabbing_Molecule()) {
		return;
	}

	// Omega
	//if (Active_Molecules[argument.GetGrabbing_Molecule_Index()].Get_X() > 5 && Active_Molecules[argument.GetGrabbing_Molecule_Index()].Get_Y() < 4) {
	if (argument.GetX() > 5 && argument.GetY() < 4) {
		//Output_Omega_Order.push_back(argument.GetGrabbing_Molecule_Index());
		Output_Omega_Order.insert(Output_Omega_Order.begin(), argument.GetGrabbing_Molecule_Index());
		
		for (unsigned int i = 1; i < Output_Omega_Order.size(); i++) {
			if (Output_Omega_Order[i] == argument.GetGrabbing_Molecule_Index()) {
				Output_Omega_Order.erase(Output_Omega_Order.begin() + i);
			}
		}
	}

	// Phi
	//if (Active_Molecules[argument.GetGrabbing_Molecule_Index()].Get_X() > 5 && Active_Molecules[argument.GetGrabbing_Molecule_Index()].Get_Y() >= 4) {
	if (argument.GetX() > 5 && argument.GetY() >= 4) {
		//Output_Phi_Order.push_back(argument.GetGrabbing_Molecule_Index());
		Output_Phi_Order.insert(Output_Phi_Order.begin(), argument.GetGrabbing_Molecule_Index());

		for (unsigned int i = 1; i < Output_Phi_Order.size(); i++) {
			if (Output_Phi_Order[i] == argument.GetGrabbing_Molecule_Index()) {
				Output_Phi_Order.erase(Output_Phi_Order.begin() + i);
			}
		}
	}

	argument.SetGrabbing_Molecule(false);
	argument.SetGrabbing_Molecule_Index(-1);

	int debug = 0;
}

	// Trigger the sync requirement for the Waldo. This puts the Waldo in a state of idle until both hit it.
void Simulation::Handle_Instruction_Sync(Waldo &argument, bool RedorBlue) {
	argument.Set_Idle_For_Sync(true); // The only requirement is to set the sync bit on the waldo, the rest is handled in the Simulate_Cycle()
}
	// ------------------------------     End of the instructions.     ----------------------------------------

	// Checks if the molecule's atoms are out of the bounds of the reactor.
bool Simulation::Is_Molecule_OutOfBounds(Molecule &argument) {

	// Only the molecules attached to the waldos have to be checked for out of bounds.
	if (Red_Waldo.GetGrabbing_Molecule()) {
		bool IsOutOfBounds = Active_Molecules[Red_Waldo.GetGrabbing_Molecule_Index()].CheckIfAtom_IsOutOfBounds();

		if (IsOutOfBounds) {
			return true;
		}
	}

	// Only the molecules attached to the waldos have to be checked for out of bounds.
	if (Blue_Waldo.GetGrabbing_Molecule()) {
		bool IsOutOfBounds = Active_Molecules[Blue_Waldo.GetGrabbing_Molecule_Index()].CheckIfAtom_IsOutOfBounds();

		if (IsOutOfBounds) {
			return true;
		}
	}

	return false;
}

	// Used by CheckForCollision to see if any Molecules overlap.
bool Simulation::Do_Molecules_Overlap(Molecule &A, Molecule &B) {

		// One of the molecules is empty so do nothing.
	if (A.Get_IsEmpty() || B.Get_IsEmpty()) {
		return false;
	}


	// Go through all of the reactor.
	for (unsigned int i = 0; i < 8; i++) {
		for (unsigned int g = 0; g < 10; g++) {

				// Compare each atom and see if they match.
			if (A.CheckIfAtom_Relative(g, i) == true && B.CheckIfAtom_Relative(g, i) == true) {
				return true;
			}			
		}
	}

	return false;
}

	// Checks the entire Reactor to see if there is a collision 
		// (Note to self, you might be able to reduce the processing time here by only checking the change)
short Simulation::CheckForCollision() {

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
short Simulation::Execute_Instruction(Waldo &argument, bool RedorBlue) {

		// Pull the instructions for that tile.
	Tile Instruction = Solution.GetTile(argument.GetX(), argument.GetY(), RedorBlue);

		// Attempt to run the instruction in Instruction_1.
	switch (Instruction.Instruction_1) {

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
int Simulation::Simulate_Cycle() {

	// Pre-step: If both are waiting on sync, reset the sync.
	if (Red_Waldo.Get_Idle_For_Sync() && Blue_Waldo.Get_Idle_For_Sync()) {
		Red_Waldo.Set_Idle_For_Sync(false);
		Blue_Waldo.Set_Idle_For_Sync(false);
	}

		// Check if both waldos are holding the same molecule and are going different directions.
	if (Red_Waldo.GetGrabbing_Molecule() && Blue_Waldo.GetGrabbing_Molecule()) {
		
			// Catch if their index is not real and they match.			
		if (Blue_Waldo.GetGrabbing_Molecule_Index() != -1 && 
			Red_Waldo.GetGrabbing_Molecule_Index() != -1 &&
			Red_Waldo.GetGrabbing_Molecule_Index() == Blue_Waldo.GetGrabbing_Molecule_Index()){
			
				// Make sure they are going the same direction.
			if (Red_Waldo.GetDirection() != Blue_Waldo.GetDirection()) {
				return Simulation_Waldo_Pulled_Wrong;
			}
		}
	}

	// The steps of the simulation:

	// Check if there is a red track we need to simulate. Also if the waldo is idling for sync skip.
	if (Red_Waldo.GetActive() && !Red_Waldo.Get_Idle_For_Sync()) {

		// 1. Move Red Waldo.
		MoveWaldo(Red_Waldo);
		/*TODO: only call checkforcollision if a instruction that caused it is executed.*/
		// 2. Check for collision (only if holding molecule or inserting a new one).
		if (Red_Waldo.GetGrabbing_Molecule()) {
			int Result = CheckForCollision();

			// If there is a collision, halt.
			if (Result == Collision_Yes_Collision) {

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
	if (Blue_Waldo.GetActive() && !Blue_Waldo.Get_Idle_For_Sync()) {

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
int Simulation::Tick() {

		// Halt the simulation if the cycles have reached the cap.
	if (Solution.Get_Cycles() >= Cycle_Limit_Simulation) {

			// Set the status and it has been simulated.
		Solution.Set_Status(Simulation_OutOfCycles);
		Solution.Set_HasBeenSimulated(true);

		return Simulation_OutOfCycles;
	}

		// If this is the first tick run the requirements to fill in the waldo.
	if (Solution.Get_Cycles() == 0) {
		int Result = GenerateDefaults();

			// If there was an error.
		if (Result == Simulation_InvalidSimulation) {

				// Set the status and it has been simulated.
			Solution.Set_Status(Simulation_InvalidSimulation);
			Solution.Set_HasBeenSimulated(true);
			
			return Simulation_InvalidSimulation;
		}
	}

		// Simulate a single cycle.
	int Result = Simulate_Cycle();

		// Cycles++;
	Solution.Increment_Cycles();

	Solution.Set_Status(Result);

	return Result; // Normally Simulation_Continue
}

	// Accept a new solution.
void Simulation::Set_Solution(Solution_Reactor argument) {
	Solution = argument;
}

	// Set how many cycles can be simulated before a force halt.
void Simulation::Set_Cycle_Limit_Simulation(int argument) {
	Cycle_Limit_Simulation = argument;
}

#endif