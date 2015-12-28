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

		// When the input is not there, wait and loop input until input.
	bool Idle_For_Input;

		// Waiting for the other waldo so it will sync.
	bool Idle_For_Sync;

	public: Waldo(){
		X = 0;
		Y = 0;

		Active = false;
		Grabbing_Molecule = false;
		Idle_For_Input = false;

		Idle_For_Sync = false;
	}

		// Basic utilities
	public: void Set_Direction(short argument){
		Direction = argument;
	}

	public: void Set_Idle_For_Sync(bool argument) { Idle_For_Sync = argument; }
	public: void SetX(short argument){ X = argument; }
	public: void SetY(short argument){ Y = argument; }
	public: void SetActive(bool argument){ Active = argument; }
	public: void SetGrabbing_Molecule(bool argument){ Grabbing_Molecule = argument; }
	public: void SetIdle_For_Input(bool Argument) { Idle_For_Input = Argument; }

	public: bool Get_Idle_For_Sync() { return Idle_For_Sync; }
	public: short GetX(){ return X; }
	public: short GetY(){ return Y; }
	public: bool GetActive(){ return Active; }
	public: short GetDirection(){ return Direction; }
	public: bool GetGrabbing_Molecule(){ return Grabbing_Molecule; }
	public: bool GetIdle_For_Input() { return Idle_For_Input; }


};


#endif