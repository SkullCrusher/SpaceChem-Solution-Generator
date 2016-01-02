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

	private: int X;
	private: int Y;

		// Default constructor.
	public: Molecule(){
		IsEmpty = true;
		X = 0;
		Y = 0;
	}

		// Basic utilities.
	public: bool GetIsEmpty(){ return IsEmpty; }

		// Checks if a location has an atom.
	private: bool CheckIfAtom(short X, short Y){
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

		// Checks the max bond count to see if it will aloow it.
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

		// Remove the bond, this may cause the breakage of the molecule into multiple.
/*TODO*/public: int Remove_Bond(short X1, short Y1, short X2, short Y2){

//#define Remove_Bond_NoError				0
//#define Remove_Bond_BreakUpMolecule		1	

	//return Remove_Bond_BreakUpMolecule;

	int debug = 0;
		return Remove_Bond_NoError;
	}

		// Set the atom at a X and Y to the argument.
	public: void Set_Atom(short X, short Y, Atom argument) {

		IsEmpty = false;

			// Catch
		if (X < 0 || Y < 0 || Y > 10 || X > 10) { return; }

		Structure[Y][X] = argument;

	}

		// Used in simulation.h to "delete" a molecule from the input with a simple flip of false to true.
	public: void Set_IsEmpty(bool argument) { IsEmpty = argument; }

	public: int Get_X() { return X; }
	public: int Get_Y() { return Y; }
	public: void Set_X(int argument) { X = argument; }
	public: void Set_Y(int argument) { Y = argument; }
};

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