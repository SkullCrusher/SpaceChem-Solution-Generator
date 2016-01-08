#pragma once

#ifndef Atom_Header
#define Atom_Header

#include "Definitions.h"

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

		// Default constructor, makes sure all the data is clear.
	public: Molecule() { Reset(); }	

		// Checks if a location has an atom.
	public: bool CheckIfAtom(short X, short Y);

		// Checks if a location has an atom based on a position on the reactor.
	public: bool CheckIfAtom_Relative(short X_arg, short Y_arg);

	//	// Checks if a location has an atom based on a position on the reactor.
	//public: bool CheckIfAtom_Relative_V2(short X_arg, short Y_arg);

		// Checks for on output in a sqaure area (the entire atom has to be in the area). (Used for the output instruction to assemble a Packed_Molecule)
	public: bool CheckIfAtom_IsInLocation(short X_arg_1, short Y_arg_1, short X_arg_2, short Y_arg_2);

		// Check if any of the atoms are out of the bounds of the reactor.
	public: bool CheckIfAtom_IsOutOfBounds();

		// Checks to make sure the two atoms are within bonding range.
	private: short IsSidebySide(short X1, short Y1, short X2, short Y2);

		// Checks the max bond count to see if it will allow it.
	private: bool CanAddBonds(short X1, short Y1, short Direction);

		// Increase the bond count on a atom.
	public: void Add_Bond(short X1, short Y1, short X2, short Y2);

		// Returns the bond count for that direction.
	public: int BondCount(short X1, short Y1, short Direction);

		// Remove the bond, this may cause the breakage of the molecule into multiple.
	public: int Remove_Bond(short X1, short Y1, short X2, short Y2);

		// Set the atom at a X and Y to the argument.
	public: void Set_Atom(short X, short Y, Atom argument);

		// Get the atom at a X and Y.
	public: Atom Get_Atom(short X, short Y);

		// Fill the structure of the atom with NULL atoms and resets the data.
	public: void Reset();

		// Used for the overloaded operator to move the atoms to the top left.
	public: void Align_Top_Left();


		// Basic utilities.
	public: void Set_IsEmpty(bool argument); // Used in simulation.h to "delete" a molecule from the input with a simple flip of false to true.
	public: bool Get_IsEmpty();
	public: int  Get_X();
	public: int  Get_Y();
	public: void Set_X(int argument);
	public: void Set_Y(int argument);
	
};


	// To check if a molecule matches for solution. (they just have to have molecule the same).
 inline bool operator==(Molecule a, Molecule b){
	 
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