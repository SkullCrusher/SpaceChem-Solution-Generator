


	// The list of errors.
#define Error_Incorrect_Argument_Count 1
#define Error_Set_Int_Tile_OOB 2

	// The range of arguments that are required to process a problem.
#define Minimum_Argument_Count 3
#define Maximum_Argument_Count 5

	// Red and blue so it's easier to remember.
#define Red_Tile true
#define Blue_Tile false

	// Simulation Results.
#define Simulation_Continue 0
#define Simulation_Complete 1
#define Simulation_OutOfCycles 2
#define Simulation_InvalidSimulation 3

	// Waldo Definitons.
#define Waldo_Direction_Left	1
#define Waldo_Direction_Right	2
#define Waldo_Direction_Up		3
#define Waldo_Direction_Down	4



// Instruction list-----------------------------------------------

	// No instruction.
#define Instruction_NOP			0

	// The starting point of the waldo and what direction it goes.
#define Instruction_Start_Left	1
#define Instruction_Start_Right 2
#define Instruction_Start_Up	3
#define Instruction_Start_Down	4

	// Which direction to change the waldo's path to.
#define Instruction_Left		5
#define Instruction_Right		6
#define Instruction_Down		7
#define Instruction_Up			8

	// Triggers the bond tiles on the map.
#define Instruction_Bond_Add	9
#define Instruction_Bond_Remove 10

	// The input and output instrctions.
#define Instruction_In_Alpha	11
#define Instruction_In_Beta		12
#define Instruction_Out_Omega	13
#define Instruction_Out_Psi		14

	// The rotation instructions if the waldo is holding an atom.
#define Instruction_Rotate_R	15
#define Instruction_Rotate_L	16

	// The pick up or drop instructions for a waldo.
#define Instruction_Grab		17
#define Instruction_Drop		18
#define Instruction_GrabDrop	19

	// The sync instruction requires both sync to be activated.
#define Instruction_Sync		20