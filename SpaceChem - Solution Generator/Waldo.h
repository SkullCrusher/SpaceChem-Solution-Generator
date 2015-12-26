#ifndef Waldo_Header
#define Waldo_Header

class Waldo{

	short X;
	short Y;

		// Which direction the waldo is heading.
	short Direction;

		// If there is an active waldo for that color.
	bool Active;

	bool Grabbing_Molecule;

	public: Waldo(){
		X = 0;
		Y = 0;

		Active = false;
		Grabbing_Molecule = false;
	}

		// Basic utilities
	public: void Set_Direction(short argument){
		Direction = argument;
	}

	public: void SetX(short argument){ X = argument; }
	public: void SetY(short argument){ Y = argument; }
	public: void SetActive(bool argument){ Active = argument; }
	public: void SetGrabbing_Molecule(bool argument){ Grabbing_Molecule = argument; }

	public: short GetX(){ return X; }
	public: short GetY(){ return Y; }
	public: bool GetActive(){ return Active; }
	public: short GetDirection(){ return Direction; }
	public: bool GetGrabbing_Molecule(){ return Grabbing_Molecule; }
};


#endif