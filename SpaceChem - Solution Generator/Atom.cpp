#ifndef Atom_Header_C
#define Atom_Header_C

#include "Atom.h"

	// Checks if a location has an atom.
bool Molecule::CheckIfAtom(short X, short Y) {

		// Catch.
	if (X > 10 || Y > 10 || X < 0 || Y < 0) {
		return false;
	}

		// If something is a placeholder we know it's not a atom.
	return !Structure[Y][X].Placeholder;
}

/*
	// Checks if a location has an atom based on a position on the reactor.
bool Molecule::CheckIfAtom_Relative(short X_arg, short Y_arg) {
		// Catch.
		if (X > 10 || Y > 10 || X < 0 || Y < 0) {
			return false;
		}

		// If something is a placeholder we know it's not a atom.
		return !Structure[(Y_arg - Y)][(X_arg - X)].Placeholder;
	}
*/

	// Checks if a location has an atom based on a position on the reactor.
bool Molecule::CheckIfAtom_Relative(short X_arg, short Y_arg) {
	/*// Catch.
	if (X > 10 || Y > 10 || X < 0 || Y < 0) {
		return false;
	}*/

		// If the offset is more then the position then skip.
	if (X > X_arg || Y > Y_arg || Y_arg < 0 || X_arg < 0) {
		return false;
	}






	// If something is a placeholder we know it's not a atom.
	return !Structure[(Y_arg - Y)][(X_arg - X)].Placeholder;
}

	// Checks for on output in a sqaure area (the entire atom has to be in the area). (Used for the output instruction to assemble a Packed_Molecule)
bool Molecule::CheckIfAtom_IsInLocation(short X_arg_1, short Y_arg_1, short X_arg_2, short Y_arg_2) {
		// Catch.
		if (X > 10 || Y > 10 || X < 0 || Y < 0) {
			return false;
		}

		// We need to check every sqaure and make sure all of the atoms are in the area.
		for (unsigned int i = 0; i < 11; i++) {
			for (unsigned int g = 0; g < 11; g++) {
				// If the atom is not a placeholder (empty).
				if (!Structure[i][g].Placeholder) {

					// Check if inside outside our area.
					if ((X_arg_1 - X + g) <= (X_arg_2 - X) && (Y_arg_1 - Y + i) <= (Y_arg_2 - Y)) {
						// (log)?
						// Is inside, do nothing.
						int debug = 0;
					}
					else {
						// (log)
						// Is outside so invalidate the output of this atom
						return false;
					}
				}
			}
		}

		// If all of the atoms are inside the area return true. 
		return true;
	}

	// Check if any of the atoms are out of the bounds of the reactor.
bool Molecule::CheckIfAtom_IsOutOfBounds() {

		for (unsigned int i = 0; i < 11; i++) {
			for (unsigned int g = 0; g < 11; g++) {

				// If the atom is not a placeholder
				if (!Structure[i][g].Placeholder) {
					// If the atom is out of bounds, return with out of bounds.
					if ((X + g) < 0 || (X + g) > 10 || (Y + i) < 0 || (Y + i) > 10) {
						return true;
					}
				}
			}
		}

		return false;
	}

	// Checks to make sure the two atoms are within bonding range.
short Molecule::IsSidebySide(short X1, short Y1, short X2, short Y2) {

		// (log)

		// Left Right
		if ((X1 + 1) == X2 && Y1 == Y2) { return Atom_Two_Is_Right_One; }
		// Right Left
		if ((X1 - 1) == X2 && Y1 == Y2) { return Atom_One_Is_Right_Two; }
		// Up Down
		if (X1 == X2 && (Y1 + 1) == Y2) { return Atom_Two_Is_Above_One; }
		// Down Up
		if (X1 == X2 && (Y1 - 1) == Y2) { return Atom_One_Is_Above_Two; }

		return Atom_Invalid;
	}

	// Checks the max bond count to see if it will allow it.
bool Molecule::CanAddBonds(short X1, short Y1, short Direction) {

		Atom Argument = Structure[Y1][X1];

		if (Direction == Atom_CanAddBonds_Up) {
			// If the number of current bonds is less then max return true else false.
			if (Argument.Up_Bond < Argument.Details.Max_Bonds) {
				return true;
			}
			else {
				return false;
			}
		}

		if (Direction == Atom_CanAddBonds_Down) {
			// If the number of current bonds is less then max return true else false.
			if (Argument.Down_Bond < Argument.Details.Max_Bonds) {
				return true;
			}
			else {
				return false;
			}
		}

		if (Direction == Atom_CanAddBonds_Right) {
			// If the number of current bonds is less then max return true else false.
			if (Argument.Right_Bond < Argument.Details.Max_Bonds) {
				return true;
			}
			else {
				return false;
			}
		}

		if (Direction == Atom_CanAddBonds_Left) {
			// If the number of current bonds is less then max return true else false.
			if (Argument.Left_Bond < Argument.Details.Max_Bonds) {
				return true;
			}
			else {
				return false;
			}
		}

		return false;
	}

	// Increase the bond count on a atom.
void Molecule::Add_Bond(short X1, short Y1, short X2, short Y2) {

		// (Log) invalid add bonds.
		bool A = CheckIfAtom(X1, Y1);
		bool B = CheckIfAtom(X2, Y2);

		if (A && B) {

			// See if the atoms are connected.
			short Result = IsSidebySide(X1, Y1, X2, Y2);

			// The atoms are too far away so drop this add bond.
			if (Result == Atom_Invalid) {
				return;
			}

			// If there would be more then max bonds ignore.
			if (Result == Atom_One_Is_Above_Two) {
				if (CanAddBonds(X1, Y1, Atom_CanAddBonds_Down) && CanAddBonds(X2, Y2, Atom_CanAddBonds_Up)) {
					// (log)
					Structure[Y1][X1].Down_Bond++;
					Structure[Y2][X2].Up_Bond++;
				}
				else {
					// (log)
				}
			}
			if (Result == Atom_Two_Is_Above_One) {
				if (CanAddBonds(X1, Y1, Atom_CanAddBonds_Up) && CanAddBonds(X2, Y2, Atom_CanAddBonds_Down)) {
					// (log)
					Structure[Y1][X1].Up_Bond++;
					Structure[Y2][X2].Down_Bond++;
				}
				else {
					// (log)
				}
			}
			if (Result == Atom_Two_Is_Right_One) {
				if (CanAddBonds(X1, Y1, Atom_CanAddBonds_Right) && CanAddBonds(X2, Y2, Atom_CanAddBonds_Left)) {
					// (log)
					Structure[Y1][X1].Right_Bond++;
					Structure[Y2][X2].Left_Bond++;
				}
				else {
					// (log)
				}
			}
			if (Result == Atom_One_Is_Right_Two) {
				if (CanAddBonds(X1, Y1, Atom_CanAddBonds_Left) && CanAddBonds(X2, Y2, Atom_CanAddBonds_Right)) {
					// (log)
					Structure[Y2][X2].Right_Bond++;
					Structure[Y1][X1].Left_Bond++;
				}
				else {
					// (log)
				}
			}

			int debug = 0;
		}
	}

	// Returns the bond count for that direction.
int Molecule::BondCount(short X1, short Y1, short Direction) {

		Atom Argument = Structure[Y1][X1];

		// Which direction is the caller interested in.

		if (Direction == Atom_CanAddBonds_Up) {
			return Argument.Up_Bond;
		}

		if (Direction == Atom_CanAddBonds_Down) {
			return Argument.Down_Bond;
		}

		if (Direction == Atom_CanAddBonds_Right) {
			return Argument.Right_Bond;
		}

		if (Direction == Atom_CanAddBonds_Left) {
			return Argument.Left_Bond;
		}

		return 0;
	}

	// Remove the bond, this may cause the breakage of the molecule into multiple.
int Molecule::Remove_Bond(short X1, short Y1, short X2, short Y2) {

		// (Log) Check if valid points.
		bool A = CheckIfAtom(X1, Y1);
		bool B = CheckIfAtom(X2, Y2);

		if (A && B) {

			// See if the atoms are connected.
			short Result = IsSidebySide(X1, Y1, X2, Y2);

			// The atoms are too far away so drop this add bond.
			if (Result == Atom_Invalid) {
				return Remove_Bond_NoError;
			}

			// If there would be more then max bonds ignore. (log)
			if (Result == Atom_One_Is_Above_Two) {

				// If there is no bond return with breakup trigger.
				if (Structure[Y1][X1].Down_Bond == 0) {
					return Remove_Bond_BreakUpMolecule;
				}

				// If we only have one bond then we return with the trigger to break the molecule.
				if (Structure[Y1][X1].Down_Bond == 1) {

					Structure[Y1][X1].Down_Bond--;
					Structure[Y2][X2].Up_Bond--;

					return Remove_Bond_BreakUpMolecule;
				}
				else {
					Structure[Y1][X1].Down_Bond++;
					Structure[Y2][X2].Up_Bond++;

					return Remove_Bond_NoError;
				}
			}
			if (Result == Atom_Two_Is_Above_One) {

				// If there is no bond return with breakup trigger.
				if (Structure[Y1][X1].Up_Bond == 0) {
					return Remove_Bond_BreakUpMolecule;
				}

				// If we only have one bond then we return with the trigger to break the molecule.
				if (Structure[Y1][X1].Up_Bond == 1) {

					Structure[Y1][X1].Up_Bond--;
					Structure[Y2][X2].Down_Bond--;

					return Remove_Bond_BreakUpMolecule;
				}
				else {
					Structure[Y1][X1].Up_Bond--;
					Structure[Y2][X2].Down_Bond--;

					return Remove_Bond_NoError;
				}
			}
			if (Result == Atom_Two_Is_Right_One) {

				// If there is no bond return with breakup trigger.
				if (Structure[Y1][X1].Right_Bond == 0) {
					return Remove_Bond_BreakUpMolecule;
				}

				// If we only have one bond then we return with the trigger to break the molecule.
				if (Structure[Y1][X1].Right_Bond == 1) {

					Structure[Y1][X1].Right_Bond--;
					Structure[Y2][X2].Left_Bond--;

					return Remove_Bond_BreakUpMolecule;
				}
				else {
					Structure[Y1][X1].Right_Bond--;
					Structure[Y2][X2].Left_Bond--;

					return Remove_Bond_NoError;
				}
			}
			if (Result == Atom_One_Is_Right_Two) {

				// If there is no bond return with breakup trigger.
				if (Structure[Y1][X1].Right_Bond == 0) {
					return Remove_Bond_BreakUpMolecule;
				}

				// If we only have one bond then we return with the trigger to break the molecule.
				if (Structure[Y2][X2].Right_Bond == 1) {

					Structure[Y2][X2].Right_Bond--;
					Structure[Y1][X1].Left_Bond--;

					return Remove_Bond_BreakUpMolecule;
				}
				else {
					Structure[Y2][X2].Right_Bond--;
					Structure[Y1][X1].Left_Bond--;

					return Remove_Bond_NoError;
				}
			}
		}

		int debug = 0;
		return Remove_Bond_NoError;
	}

	// Set the atom at a X and Y to the argument.
void Molecule::Set_Atom(short X, short Y, Atom argument) {

		// Catch
	if (X < 0 || Y < 0 || Y > 10 || X > 10) { return; }

	Structure[Y][X] = argument;
}


	// Get the atom at a X and Y.
Atom Molecule::Get_Atom(short X, short Y) {

		// Catch
		if (X < 0 || Y < 0 || Y > 10 || X > 10) {
			Atom Trash;

			return Trash;
		}

		return Structure[Y][X];
	}

	// Fill the structure of the atom with NULL atoms and resets the data.
void Molecule::Reset() {

		IsEmpty = true;
		X = 0;
		Y = 0;

		Atom Trash;

		for (unsigned int i = 0; i < 11; i++) {
			for (unsigned int g = 0; g < 11; g++) {
				Structure[i][g] = Trash;
			}
		}
	}

	// Used in simulation.h to "delete" a molecule from the input with a simple flip of false to true.
void Molecule::Set_IsEmpty(bool argument) { IsEmpty = argument; }

	// Basic utilities.
bool Molecule::Get_IsEmpty() { return IsEmpty; }

int Molecule::Get_X() { 
	return X; 
}

int Molecule::Get_Y() { 
	return Y; 
}

void Molecule::Set_X(int argument) { 
	X = argument; 
}

void Molecule::Set_Y(int argument) { 
	Y = argument; 
}

	// Used for the overloaded operator to move the atoms to the top left.
void Molecule::Align_Top_Left() {

		bool Atom_Top = false;
		bool Atom_Left = false;

		// Keep moving everything left until a atom is at the edge.
		while (Atom_Left == false) {

			// Copy everything over 1.
			for (unsigned int i = 1; i < 11; i++) {
				for (unsigned int g = 0; g < 11; g++) {
					Structure[g][i - 1] = Structure[g][i];
				}
			}

			// Check for an atom.
			for (unsigned int i = 0; i < 11; i++) {
				if (Structure[i][0].Placeholder == false) {
					Atom_Left = true;
					break;
				}
			}
		}

		// Keep moving everything up until a atom is at the edge.
		while (Atom_Top == false) {

			// Copy everything over 1.
			for (unsigned int i = 1; i < 11; i++) {
				for (unsigned int g = 0; g < 11; g++) {
					Structure[i - 1][g] = Structure[i][g];
				}
			}

			// Check for an atom.
			for (unsigned int i = 0; i < 11; i++) {
				if (Structure[0][i].Placeholder == false) {
					Atom_Top = true;
					break;
				}
			}
		}
	}


#endif