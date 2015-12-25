#ifndef Waldo_Header
#define Waldo_Header

class Waldo{

	short X;
	short Y;

		// Which direction the waldo is heading.
	short Direction;

	/*
			// Waldo Definitons.
		#define Waldo_Direction_Left	1
		#define Waldo_Direction_Right	2
		#define Waldo_Direction_Up		3
		#define Waldo_Direction_Down	4
	*/

		// If there is an active waldo for that color.
	bool Active;

	public: Waldo(){
		X = 0;
		Y = 0;

		Active = false;
	}

		// Basic utilities
	public: void Set_Direction(short argument){
		Direction = argument;
	}

	public: void SetX(short argument){ X = argument; }
	public: void SetY(short argument){ Y = argument; }
	public: void SetActive(bool argument){ Active = argument; }

	public: short GetX(){ return X; }
	public: short GetY(){ return Y; }
};


#endif