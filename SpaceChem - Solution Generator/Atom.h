#pragma once

#ifndef Atom_Header
#define Atom_Header

	// Used in the Molecule class to create the structure.
struct Atom {
	int Atomic_Number;

	int Max_Bonds;
};

class Molecule {

		// If the molecule is actually just a empty place holder.
	private: bool IsEmpty;

		// Default constructor.
	public: Molecule(){
		IsEmpty = true;
	}

		// Basic utilities
	public: bool GetIsEmpty(){ return IsEmpty; }
};

#endif