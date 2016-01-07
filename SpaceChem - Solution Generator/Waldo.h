#ifndef Waldo_Header
#define Waldo_Header

class Waldo{

	short X;
	short Y;

		// Which direction the waldo is heading.
	short Direction;

		// If there is an active waldo for that color.
	bool Active;

		// If the waldo is holding onto a modlecule.
	bool Grabbing_Molecule;
	int Grabbing_Molecule_Index;

		// When the input is not there, wait and loop input until input.
	bool Idle_For_Input;

		// Delays while the waits for the output to finish.
	bool Idle_For_Output;

		// Waiting for the other waldo so it will sync.
	bool Idle_For_Sync;

		// Default construct.
	public: Waldo(){
		X = 0;
		Y = 0;

		Active = false;

		Grabbing_Molecule = false;
		Grabbing_Molecule_Index = -1;

		Idle_For_Input = false;
		Idle_For_Output = false;
		Idle_For_Sync = false;
	}

		// Basic utilities
	public: void  Set_Direction(short argument){
		Direction = argument;
	}

	public: void  Set_Idle_For_Sync(bool argument) { Idle_For_Sync = argument; }
	public: void  SetX(short argument){ X = argument; }
	public: void  SetY(short argument){ Y = argument; }
	public: void  SetActive(bool argument){ Active = argument; }
	public: void  SetIdle_For_Input(bool Argument) { Idle_For_Input = Argument; }
	public: void  SetIdle_For_Output(bool Argument) { Idle_For_Output = Argument; }
	
	public: void  SetGrabbing_Molecule(bool argument) { Grabbing_Molecule = argument; }
	public: void  SetGrabbing_Molecule_Index(int index) { Grabbing_Molecule_Index = index; }
	public: int   GetGrabbing_Molecule_Index() { return Grabbing_Molecule_Index; }
	public: bool  GetGrabbing_Molecule() { return Grabbing_Molecule; }

	public: bool  Get_Idle_For_Sync() { return Idle_For_Sync; }
	public: short GetX(){ return X; }
	public: short GetY(){ return Y; }
	public: bool  GetActive(){ return Active; }
	public: short GetDirection(){ return Direction; }
	public: bool  GetIdle_For_Input() { return Idle_For_Input; }
	public: bool  GetIdle_For_Output() { return Idle_For_Output; }


};


#endif