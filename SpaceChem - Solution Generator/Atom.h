#pragma once

#ifndef Atom_Header
#define Atom_Header

#include <vector>

	// Used in the Molecule class to create the structure.
struct Atom_Info {
	int Atomic_Number;

	int Max_Bonds;
};

struct Atom{

		// Atomic number and the max bonds for it.
	Atom_Info Details;

		// If this is just an empty atom.
	bool Placeholder;
		
		// The list of bond numbers.
	short Left_Bond;
	short Right_Bond;
	short Up_Bond;
	short Down_Bond;
	
		// Default constructor.
	Atom(){
		Left_Bond = 0;
		Right_Bond = 0;
		Up_Bond = 0;
		Down_Bond = 0;
		Placeholder = true;
	}

};

class Molecule {

		// If the molecule is actually just a empty place holder (changed by Set_Atom).
	private: bool IsEmpty;

		// The structure is the layout of the atoms. Note, there is a center but the waldo changes the center rotation.
	private: Atom Structure[11][11];

		// The position.
	private: int X;
	private: int Y;

		// Default constructor.
	public: Molecule(){
		Reset();	// Makes sure all the data is clear.
	}

		// Basic utilities.
	public: bool GetIsEmpty(){ return IsEmpty; }

		// Checks if a location has an atom.
	public: bool CheckIfAtom(short X, short Y){
			// Catch.
		if (X > 10 || Y > 10 || X < 0 || Y < 0){
			return false;
		}

			// If something is a placeholder we know it's not a atom.
		return !Structure[Y][X].Placeholder;
	}

		// Checks if a location has an atom based on a position on the reactor.
	public: bool CheckIfAtom_Relative(short X_arg, short Y_arg) {
			// Catch.
		if (X > 10 || Y > 10 || X < 0 || Y < 0) {
			return false;
		}

			// If something is a placeholder we know it's not a atom.
		return !Structure[(Y_arg - Y)][(X_arg - X)].Placeholder;
	}

		// Checks for on output in a sqaure area (the entire atom has to be in the area). (Used for the output instruction to assemble a Packed_Molecule)
	public: bool CheckIfAtom_IsInLocation(short X_arg_1, short Y_arg_1, short X_arg_2, short Y_arg_2){
		// Catch.
		if (X > 10 || Y > 10 || X < 0 || Y < 0) {
			return false;
		}

			// We need to check every sqaure and make sure all of the atoms are in the area.
		for (unsigned int i = 0; i < 11; i++){
			for (unsigned int g = 0; g < 11; g++){
					// If the atom is not a placeholder (empty).
				if (!Structure[i][g].Placeholder){
					
						// Check if inside outside our area.
					if ((X_arg_1 - X + g) <= (X_arg_2 - X) && (Y_arg_1 - Y + i) <= (Y_arg_2 - Y)){
						// (log)?
							// Is inside, do nothing.
						int debug = 0;
					}else{
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
	public: bool CheckIfAtom_IsOutOfBounds() {

		for (unsigned int i = 0; i < 11; i++) {
			for (unsigned int g = 0; g < 11; g++) {

					// If the atom is not a placeholder
				if (!Structure[i][g].Placeholder) {
						// If the atom is out of bounds, return with out of bounds.
					if ((X + g) < 0 || (X + g) > 10 || (Y + i) < 0 || (Y + i) > 10){
						return true;
					}
				}
			}
		}

		return false;
	}

		// Checks to make sure the two atoms are within bonding range.
	private: short IsSidebySide(short X1, short Y1, short X2, short Y2){
		
		// (log)

			// Left Right
		if ((X1 + 1) == X2 && Y1 == Y2){ return Atom_Two_Is_Right_One; }
			// Right Left
		if ((X1 - 1) == X2 && Y1 == Y2){ return Atom_One_Is_Right_Two; }
			// Up Down
		if (X1 == X2 && (Y1 + 1) == Y2){ return Atom_Two_Is_Above_One; }
			// Down Up
		if (X1 == X2 && (Y1 - 1) == Y2){ return Atom_One_Is_Above_Two; }

		return Atom_Invalid;
	}

		// Checks the max bond count to see if it will allow it.
	private: bool CanAddBonds(short X1, short Y1, short Direction) {

		Atom Argument = Structure[Y1][X1];

		if (Direction == Atom_CanAddBonds_Up) {
				// If the number of current bonds is less then max return true else false.
			if (Argument.Up_Bond < Argument.Details.Max_Bonds) {
				return true;
			}else {
				return false;
			}
		}

		if (Direction == Atom_CanAddBonds_Down) {
				// If the number of current bonds is less then max return true else false.
			if (Argument.Down_Bond < Argument.Details.Max_Bonds) {
				return true;
			}else {
				return false;
			}
		}

		if (Direction == Atom_CanAddBonds_Right) {
				// If the number of current bonds is less then max return true else false.
			if (Argument.Right_Bond < Argument.Details.Max_Bonds) {
				return true;
			}else {
				return false;
			}
		}

		if (Direction == Atom_CanAddBonds_Left) {
				// If the number of current bonds is less then max return true else false.
			if (Argument.Left_Bond < Argument.Details.Max_Bonds) {
				return true;
			}else {
				return false;
			}
		}

		return false;
	}

		// Increase the bond count on a atom.
	public: void Add_Bond(short X1, short Y1, short X2, short Y2){
			
			// (Log) invalid add bonds.
		bool A = CheckIfAtom(X1, Y1);
		bool B = CheckIfAtom(X2, Y2);

		if (A && B){

				// See if the atoms are connected.
			short Result = IsSidebySide(X1, Y1, X2, Y2);

				// The atoms are too far away so drop this add bond.
			if(Result == Atom_Invalid){
				return;
			}

				// If there would be more then max bonds ignore.
			if (Result == Atom_One_Is_Above_Two) {
				if (CanAddBonds(X1, Y1, Atom_CanAddBonds_Down) && CanAddBonds(X2, Y2, Atom_CanAddBonds_Up)) {
					// (log)
					Structure[Y1][X1].Down_Bond++;
					Structure[Y2][X2].Up_Bond++;
				}else {
					// (log)
				}
			}
			if (Result == Atom_Two_Is_Above_One) {		
				if (CanAddBonds(X1, Y1, Atom_CanAddBonds_Up) && CanAddBonds(X2, Y2, Atom_CanAddBonds_Down)) {
					// (log)
					Structure[Y1][X1].Up_Bond++;
					Structure[Y2][X2].Down_Bond++;
				}else {
					// (log)
				}
			}
			if (Result == Atom_Two_Is_Right_One) {
				if (CanAddBonds(X1, Y1, Atom_CanAddBonds_Right) && CanAddBonds(X2, Y2, Atom_CanAddBonds_Left)) {
					// (log)
					Structure[Y1][X1].Right_Bond++;
					Structure[Y2][X2].Left_Bond++;
				}else {
					// (log)
				}
			}
			if (Result == Atom_One_Is_Right_Two) {
				if (CanAddBonds(X1, Y1, Atom_CanAddBonds_Left) && CanAddBonds(X2, Y2, Atom_CanAddBonds_Right)) {
					// (log)
					Structure[Y2][X2].Right_Bond++;
					Structure[Y1][X1].Left_Bond++;
				}else {
					// (log)
				}
			}

			int debug = 0;
		}
	}

		// Returns the bond count for that direction.
	public: int BondCount(short X1, short Y1, short Direction){

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
/*TOTEST*/public: int Remove_Bond(short X1, short Y1, short X2, short Y2){

		// (Log) Check if valid points.
	bool A = CheckIfAtom(X1, Y1);
	bool B = CheckIfAtom(X2, Y2);

	if (A && B){

		// See if the atoms are connected.
		short Result = IsSidebySide(X1, Y1, X2, Y2);

		// The atoms are too far away so drop this add bond.
		if (Result == Atom_Invalid){
			return Remove_Bond_NoError;
		}

		// If there would be more then max bonds ignore. (log)
		if (Result == Atom_One_Is_Above_Two) {

				// If there is no bond return with breakup trigger.
			if (Structure[Y1][X1].Down_Bond == 0){
				return Remove_Bond_BreakUpMolecule;
			}

				// If we only have one bond then we return with the trigger to break the molecule.
			if (Structure[Y1][X1].Down_Bond == 1){

				Structure[Y1][X1].Down_Bond--;
				Structure[Y2][X2].Up_Bond--;

				return Remove_Bond_BreakUpMolecule;
			}else{
				Structure[Y1][X1].Down_Bond++;
				Structure[Y2][X2].Up_Bond++;

				return Remove_Bond_NoError;
			}
		}
		if (Result == Atom_Two_Is_Above_One) {

				// If there is no bond return with breakup trigger.
			if (Structure[Y1][X1].Up_Bond == 0){
				return Remove_Bond_BreakUpMolecule;
			}

				// If we only have one bond then we return with the trigger to break the molecule.
			if (Structure[Y1][X1].Up_Bond == 1){

				Structure[Y1][X1].Up_Bond--;
				Structure[Y2][X2].Down_Bond--;

				return Remove_Bond_BreakUpMolecule;
			}else{
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
	public: void Set_Atom(short X, short Y, Atom argument) {

		// Catch
		if (X < 0 || Y < 0 || Y > 10 || X > 10) { return; }

		Structure[Y][X] = argument;
	}

		// Get the atom at a X and Y.
	public: Atom Get_Atom(short X, short Y) {

		// Catch
		if (X < 0 || Y < 0 || Y > 10 || X > 10) {
			Atom Trash;

			return Trash;
		}

		return Structure[Y][X];
	}

		// Fill the structure of the atom with NULL atoms and resets the data.
	public: void Reset() {

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
	public: void Set_IsEmpty(bool argument) { IsEmpty = argument; }

	public: int Get_X() { return X; }
	public: int Get_Y() { return Y; }
	public: void Set_X(int argument) { X = argument; }
	public: void Set_Y(int argument) { Y = argument; }

			// Used for the overloaded operator to move the atoms to the top left.
	public: void Align_Top_Left() {

		bool Atom_Top = false;
		bool Atom_Left = false;

			// Keep moving everything left until a atom is at the edge.
		while (Atom_Left == false){

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

};


	// To check if a molecule matches for solution. (they just have to have molecule the same).
 bool operator==(Molecule a, Molecule b){
	 
		// Find the first atom and move it all the way to the top left.
	a.Align_Top_Left();
	b.Align_Top_Left();

	for (unsigned int i = 0; i < 11; i++) {
		for (unsigned int g = 0; g < 11; g++) {

			Atom a_temp = a.Get_Atom(i, g);
			Atom b_temp = b.Get_Atom(i, g);

				// Make sure both placeholder values match.
			if (a_temp.Placeholder != b_temp.Placeholder) {
				return false;
			}

				// Make sure the atomic numbers match.
			if (a_temp.Details.Atomic_Number != b_temp.Details.Atomic_Number) {
				return false;
			}

				// Check all four of the bonds to make sure they match.
			if (a_temp.Down_Bond != b_temp.Down_Bond ||
				a_temp.Left_Bond != b_temp.Left_Bond ||
				a_temp.Right_Bond != b_temp.Right_Bond ||
				a_temp.Up_Bond != b_temp.Up_Bond) {

				return false;
			}
		}
	}


	// TO DO Future, rotate the molecule to handle different rotations.
	
	return true;
}
 

	// How the molecules are transported for input/output
 struct Packed_Molecule {
	std::vector<Molecule> Items;

	bool IsEmpty = true;

	public: bool GetIsEmpty() { return IsEmpty; }

		// Used in simulation.h to "delete" a molecule from the input with a simple flip of false to true.
	public: void Set_IsEmpty(bool argument) { IsEmpty = argument; }

	public: void Set_X(int Argument) {
		for (unsigned int i = 0; i < Items.size(); i++) {
			Items[i].Set_X(Argument);
		}
	}
	public: void Set_Y(int Argument) {
		for (unsigned int i = 0; i < Items.size(); i++) {
			Items[i].Set_Y(Argument);
		}
	}
};

#endif