#pragma once

#ifndef Atom_Header
#define Atom_Header

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

		// If the molecule is actually just a empty place holder.
	private: bool IsEmpty;

		// The structure is the layout of the atoms. Note, there is a center but the waldo changes the center rotation.
	private: Atom Structure[11][11];

		// Default constructor.
	public: Molecule(){
		IsEmpty = true;
	}

		// Basic utilities
	public: bool GetIsEmpty(){ return IsEmpty; }

		// Checks if a location has an atom.
	private: bool CheckIfAtom(short X, short Y){
			// Catch.
		if (X > 10 || Y > 10 || X < 0 || Y < 0){
			return false;
		}

			// If something is a placeholder we know it's not a atom.
		return !Structure[X][Y].Placeholder;
	}

		// Increase the bond count on a atom.
	private: void IncreaseBondCount(short X1, short Y1, short X2, short Y2){

	}
		// Checks to make sure the two atoms are within bonding range.
	private: short IsSidebySide(short X1, short Y1, short X2, short Y2){
		
			// Left Right
		if ((X1 + 1) == X2 && Y1 == Y2){
			return Atom_Two_Is_Right_One;
		}
			// Right Left
		if ((X1 - 1) == X2 && Y1 == Y2){
			return Atom_One_Is_Right_Two;
		}

			// Up Down
		if (X1 == X2 && (Y1 + 1) == Y2){
			return Atom_Two_Is_Above_One;
		}
			// Down Up
		if (X1 == X2 && (Y1 - 1) == Y2){
			return Atom_One_Is_Above_Two;
		}

		return Atom_Invalid;
	}

	public: void Add_Bond(short X1, short Y1, short X2, short Y2){
		// (Log) invalid add bonds.
		bool A = CheckIfAtom(X1, Y1);
		bool B = CheckIfAtom(X2, Y2);

		if (A && B){

		}
	}

	public: void Remove_Bond(short X1, short Y1, short X2, short Y2){

	}

};

#endif