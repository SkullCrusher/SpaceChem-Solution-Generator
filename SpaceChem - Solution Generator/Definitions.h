// The list of errors.
#define Error_Incorrect_Argument_Count 1
#define Error_Set_Int_Tile_OOB 2

// The range of arguments that are required to process a problem.
#define Minimum_Argument_Count 3
#define Maximum_Argument_Count 5


// Instruction list-----------------------------------------------

// The starting point of the waldo and what direction it goes.
#define Instruction_Start_Left	0x00
#define Instruction_Start_Right 0x01
#define Instruction_Start_Up	0x02
#define Instruction_Start_Down	0x03

// Which direction to change the waldo's path to.
#define Instruction_Left		0x04
#define Instruction_Right		0x05
#define Instruction_Down		0x06
#define Instruction_Up			0x07

// Triggers the bond tiles on the map.
#define Instruction_Bond_Add	0x08
#define Instruction_Bond_Remove 0x09

// The input and output instrctions.
#define Instruction_In_Alpha	0x10
#define Instruction_In_Beta		0x11
#define Instruction_Out_Omega	0x12
#define Instruction_Out_Psi		0x13

// The rotation instructions if the waldo is holding an atom.
#define Instruction_Rotate_R	0x14
#define Instruction_Rotate_L	0x15

// The pick up or drop instructions for a waldo.
#define Instruction_Grab		0x16
#define Instruction_Drop		0x17
#define Instruction_GrabDrop	0x18

// The sync instruction requires both sync to be activated.
#define Instruction_Sync		0x19