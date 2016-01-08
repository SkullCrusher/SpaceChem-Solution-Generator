
#ifndef Debug_Sernimir_II
#define Debug_Sernimir_II

#include "Simulation.h"
#include "Problem_Definiton.h"

	// Fills in the testing data for Sernimir II 001, check Validation of simulations for more details.
void Debug_Test_Sernimir_II_001(Solution_Reactor &TheChosenOne, Problem_Definition &Problem_Rules, Simulation &RunMe, Packed_Molecule &Input_For_Debugging, Molecule &AlphaIn, Molecule &Solution) {

	// I am just putting my solution in to test the simulation

	// The blue instructions.
	TheChosenOne.Set_Instruction_For_Tile(1, 0, Blue_Tile, Instruction_NOP, Instruction_Down);
	TheChosenOne.Set_Instruction_For_Tile(2, 0, Blue_Tile, Instruction_Sync, Instruction_NOP);
	TheChosenOne.Set_Instruction_For_Tile(7, 0, Blue_Tile, Instruction_Start_Left, Instruction_Left);
	TheChosenOne.Set_Instruction_For_Tile(1, 1, Blue_Tile, Instruction_Grab, Instruction_NOP);
	TheChosenOne.Set_Instruction_For_Tile(7, 1, Blue_Tile, Instruction_Out_Omega, Instruction_NOP);
	TheChosenOne.Set_Instruction_For_Tile(1, 2, Blue_Tile, Instruction_NOP, Instruction_Right);
	TheChosenOne.Set_Instruction_For_Tile(7, 2, Blue_Tile, Instruction_Drop, Instruction_Up);

	// The red instructions.
	TheChosenOne.Set_Instruction_For_Tile(2, 1, Red_Tile, Instruction_Grab, Instruction_Down);
	TheChosenOne.Set_Instruction_For_Tile(3, 1, Red_Tile, Instruction_Sync, Instruction_NOP);
	TheChosenOne.Set_Instruction_For_Tile(4, 1, Red_Tile, Instruction_Bond_Remove, Instruction_NOP);
	TheChosenOne.Set_Instruction_For_Tile(5, 1, Red_Tile, Instruction_In_Alpha, Instruction_NOP);
	TheChosenOne.Set_Instruction_For_Tile(6, 1, Red_Tile, Instruction_Start_Left, Instruction_NOP);
	TheChosenOne.Set_Instruction_For_Tile(7, 1, Red_Tile, Instruction_Out_Omega, Instruction_Left);
	TheChosenOne.Set_Instruction_For_Tile(2, 2, Red_Tile, Instruction_NOP, Instruction_Right);
	TheChosenOne.Set_Instruction_For_Tile(7, 2, Red_Tile, Instruction_Drop, Instruction_Up);

	// Debugging, place the bonding pads
	TheChosenOne.Add_BondingPad(1, 1);
	TheChosenOne.Add_BondingPad(2, 1);


	// Set the reactor to simulate.
	RunMe.Set_Solution(TheChosenOne);

	// Limit the simulation to prevent unlimited running.
	RunMe.Set_Cycle_Limit_Simulation(Problem_Rules.Get_Cycle_Limit_Simulation());

		// Debugging Infomation.
	Atom_Info Info;
	Info.Atomic_Number = 9;
	Info.Max_Bonds = 1;

	Atom F;
	F.Placeholder = false;
	F.Details = Info;

		// Create the input molecule.
	AlphaIn.Set_Atom(1, 1, F);
	AlphaIn.Set_Atom(2, 1, F);

	AlphaIn.Add_Bond(1, 1, 2, 1);

		// Create the input molecule.
	Solution.Set_Atom(1, 1, F);

		// Just the input for the simulation.
	Input_For_Debugging.Items.push_back(AlphaIn);
	Input_For_Debugging.Set_IsEmpty(false);

	RunMe.Add_To_Input(Input_For_Debugging, Simulation_Add_To_Input_Alpha);
	RunMe.Add_To_Input(Input_For_Debugging, Simulation_Add_To_Input_Alpha);
	RunMe.Add_To_Input(Input_For_Debugging, Simulation_Add_To_Input_Alpha);
		
}

	// Fills in the testing data for Sernimir II 002, check Validation of simulations for more details.
void Debug_Test_Sernimir_II_002(Solution_Reactor &TheChosenOne, Problem_Definition &Problem_Rules, Simulation &RunMe, Packed_Molecule &Input_For_Debugging, Molecule &AlphaIn, Molecule &Solution) {

	// I am just putting my solution in to test the simulation

		// The blue instructions.
	TheChosenOne.Set_Instruction_For_Tile(7, 0, Blue_Tile, Instruction_Start_Left, Instruction_Left);


		// The red instructions.
	TheChosenOne.Set_Instruction_For_Tile(6, 1, Red_Tile, Instruction_Start_Left, Instruction_NOP);

	// Debugging, place the bonding pads
	TheChosenOne.Add_BondingPad(1, 1);
	TheChosenOne.Add_BondingPad(2, 1);


	// Set the reactor to simulate.
	RunMe.Set_Solution(TheChosenOne);

	// Limit the simulation to prevent unlimited running.
	RunMe.Set_Cycle_Limit_Simulation(Problem_Rules.Get_Cycle_Limit_Simulation());

	// Debugging Infomation.
	Atom_Info Info;
	Info.Atomic_Number = 9;
	Info.Max_Bonds = 1;

	Atom F;
	F.Placeholder = false;
	F.Details = Info;

	// Create the input molecule.
	AlphaIn.Set_Atom(1, 1, F);
	AlphaIn.Set_Atom(2, 1, F);

	AlphaIn.Add_Bond(1, 1, 2, 1);

	// Create the input molecule.
	Solution.Set_Atom(1, 1, F);

	// Just the input for the simulation.
	Input_For_Debugging.Items.push_back(AlphaIn);
	Input_For_Debugging.Set_IsEmpty(false);

	RunMe.Add_To_Input(Input_For_Debugging, Simulation_Add_To_Input_Alpha);
	RunMe.Add_To_Input(Input_For_Debugging, Simulation_Add_To_Input_Alpha);
	RunMe.Add_To_Input(Input_For_Debugging, Simulation_Add_To_Input_Alpha);

}

	// Fills in the testing data for Sernimir II 003, check Validation of simulations for more details.
void Debug_Test_Sernimir_II_003(Solution_Reactor &TheChosenOne, Problem_Definition &Problem_Rules, Simulation &RunMe, Packed_Molecule &Input_For_Debugging, Molecule &AlphaIn, Molecule &Solution) {

	// I am just putting my solution in to test the simulation

	// The blue instructions.
	TheChosenOne.Set_Instruction_For_Tile(9, 4, Blue_Tile, Instruction_Start_Left, Instruction_Left);


	// The red instructions.

	TheChosenOne.Set_Instruction_For_Tile(5, 1, Red_Tile, Instruction_Start_Left,	Instruction_NOP);

	TheChosenOne.Set_Instruction_For_Tile(6, 0, Red_Tile, Instruction_NOP,			Instruction_Left);
	TheChosenOne.Set_Instruction_For_Tile(1, 0, Red_Tile, Instruction_NOP,			Instruction_Down);

	TheChosenOne.Set_Instruction_For_Tile(1, 1, Red_Tile, Instruction_Grab,			Instruction_NOP);
	TheChosenOne.Set_Instruction_For_Tile(2, 1, Red_Tile, Instruction_Grab,			Instruction_Down);
	TheChosenOne.Set_Instruction_For_Tile(3, 1, Red_Tile, Instruction_Bond_Remove,	Instruction_NOP);
	TheChosenOne.Set_Instruction_For_Tile(4, 1, Red_Tile, Instruction_In_Alpha,		Instruction_NOP);
	TheChosenOne.Set_Instruction_For_Tile(6, 1, Red_Tile, Instruction_Drop,			Instruction_NOP);
	TheChosenOne.Set_Instruction_For_Tile(7, 1, Red_Tile, Instruction_Out_Omega,	Instruction_Left);

	TheChosenOne.Set_Instruction_For_Tile(2, 2, Red_Tile, Instruction_NOP,			Instruction_Right);
	TheChosenOne.Set_Instruction_For_Tile(6, 2, Red_Tile, Instruction_NOP,			Instruction_Up);
	TheChosenOne.Set_Instruction_For_Tile(7, 2, Red_Tile, Instruction_Drop,			Instruction_NOP);
	
	TheChosenOne.Set_Instruction_For_Tile(1, 3, Red_Tile, Instruction_NOP,			Instruction_Right);
	TheChosenOne.Set_Instruction_For_Tile(7, 3, Red_Tile, Instruction_NOP,			Instruction_Up);


	// Debugging, place the bonding pads
	TheChosenOne.Add_BondingPad(1, 1);
	TheChosenOne.Add_BondingPad(2, 1);


	// Set the reactor to simulate.
	RunMe.Set_Solution(TheChosenOne);

	// Limit the simulation to prevent unlimited running.
	RunMe.Set_Cycle_Limit_Simulation(Problem_Rules.Get_Cycle_Limit_Simulation());

	// Debugging Infomation.
	Atom_Info Info;
	Info.Atomic_Number = 9;
	Info.Max_Bonds = 1;

	Atom F;
	F.Placeholder = false;
	F.Details = Info;

	// Create the input molecule.
	AlphaIn.Set_Atom(1, 1, F);
	AlphaIn.Set_Atom(2, 1, F);

	AlphaIn.Add_Bond(1, 1, 2, 1);

	// Create the input molecule.
	Solution.Set_Atom(1, 1, F);

	// Just the input for the simulation.
	Input_For_Debugging.Items.push_back(AlphaIn);
	Input_For_Debugging.Set_IsEmpty(false);

	RunMe.Add_To_Input(Input_For_Debugging, Simulation_Add_To_Input_Alpha);
	RunMe.Add_To_Input(Input_For_Debugging, Simulation_Add_To_Input_Alpha);
	RunMe.Add_To_Input(Input_For_Debugging, Simulation_Add_To_Input_Alpha);

}

	// Fills in the testing data for Sernimir II 004, check Validation of simulations for more details.
void Debug_Test_Sernimir_II_004(Solution_Reactor &TheChosenOne, Problem_Definition &Problem_Rules, Simulation &RunMe, Packed_Molecule &Input_For_Debugging, Molecule &AlphaIn, Molecule &Solution) {

	// I am just putting my solution in to test the simulation

	// The blue instructions.
	TheChosenOne.Set_Instruction_For_Tile(9, 4, Blue_Tile, Instruction_Start_Left, Instruction_NOP);


	// The red instructions.

	TheChosenOne.Set_Instruction_For_Tile(5, 1, Red_Tile, Instruction_Start_Left, Instruction_NOP);//

	TheChosenOne.Set_Instruction_For_Tile(8, 0, Red_Tile, Instruction_NOP, Instruction_Left);//
	TheChosenOne.Set_Instruction_For_Tile(1, 0, Red_Tile, Instruction_NOP, Instruction_Down);//

	TheChosenOne.Set_Instruction_For_Tile(1, 1, Red_Tile, Instruction_Grab, Instruction_NOP);//
	TheChosenOne.Set_Instruction_For_Tile(2, 1, Red_Tile, Instruction_Grab, Instruction_Down);//
	TheChosenOne.Set_Instruction_For_Tile(3, 1, Red_Tile, Instruction_Bond_Remove, Instruction_NOP);//
	TheChosenOne.Set_Instruction_For_Tile(4, 1, Red_Tile, Instruction_In_Alpha, Instruction_NOP);//

	TheChosenOne.Set_Instruction_For_Tile(7, 1, Red_Tile, Instruction_Drop, Instruction_Left);//
	TheChosenOne.Set_Instruction_For_Tile(6, 1, Red_Tile, Instruction_Out_Omega, Instruction_NOP);//

	TheChosenOne.Set_Instruction_For_Tile(2, 2, Red_Tile, Instruction_NOP, Instruction_Right);//
	TheChosenOne.Set_Instruction_For_Tile(8, 2, Red_Tile, Instruction_NOP, Instruction_Up);
	TheChosenOne.Set_Instruction_For_Tile(7, 2, Red_Tile, Instruction_Drop, Instruction_NOP);

	
	TheChosenOne.Set_Instruction_For_Tile(1, 3, Red_Tile, Instruction_NOP, Instruction_Right);
	TheChosenOne.Set_Instruction_For_Tile(7, 3, Red_Tile, Instruction_NOP, Instruction_Up);


	// Debugging, place the bonding pads
	TheChosenOne.Add_BondingPad(1, 1);
	TheChosenOne.Add_BondingPad(2, 1);


	// Set the reactor to simulate.
	RunMe.Set_Solution(TheChosenOne);

	// Limit the simulation to prevent unlimited running.
	RunMe.Set_Cycle_Limit_Simulation(Problem_Rules.Get_Cycle_Limit_Simulation());

	// Debugging Infomation.
	Atom_Info Info;
	Info.Atomic_Number = 9;
	Info.Max_Bonds = 1;

	Atom F;
	F.Placeholder = false;
	F.Details = Info;

	// Create the input molecule.
	AlphaIn.Set_Atom(1, 1, F);
	AlphaIn.Set_Atom(2, 1, F);

	AlphaIn.Add_Bond(1, 1, 2, 1);

	// Create the input molecule.
	Solution.Set_Atom(1, 1, F);

	// Just the input for the simulation.
	Input_For_Debugging.Items.push_back(AlphaIn);
	Input_For_Debugging.Set_IsEmpty(false);

	RunMe.Add_To_Input(Input_For_Debugging, Simulation_Add_To_Input_Alpha);
	RunMe.Add_To_Input(Input_For_Debugging, Simulation_Add_To_Input_Alpha);
	RunMe.Add_To_Input(Input_For_Debugging, Simulation_Add_To_Input_Alpha);

}

	// Fills in the testing data for Sernimir II 005, check Validation of simulations for more details.
void Debug_Test_Sernimir_II_005(Solution_Reactor &TheChosenOne, Problem_Definition &Problem_Rules, Simulation &RunMe, Packed_Molecule &Input_For_Debugging, Molecule &AlphaIn, Molecule &Solution) {

	// I am just putting my solution in to test the simulation

		// The blue instructions.
	TheChosenOne.Set_Instruction_For_Tile(5, 0, Blue_Tile, Instruction_Start_Left, Instruction_NOP);

	TheChosenOne.Set_Instruction_For_Tile(1, 0, Blue_Tile, Instruction_NOP, Instruction_Down);
	TheChosenOne.Set_Instruction_For_Tile(6, 0, Blue_Tile, Instruction_NOP, Instruction_Left);

	TheChosenOne.Set_Instruction_For_Tile(1, 1, Blue_Tile, Instruction_Grab, Instruction_NOP);
	TheChosenOne.Set_Instruction_For_Tile(6, 1, Blue_Tile, Instruction_Out_Omega, Instruction_NOP);

	TheChosenOne.Set_Instruction_For_Tile(1, 2, Blue_Tile, Instruction_NOP, Instruction_Right);
	TheChosenOne.Set_Instruction_For_Tile(6, 2, Blue_Tile, Instruction_Drop, Instruction_Up);


		// The red instructions.
	TheChosenOne.Set_Instruction_For_Tile(5, 1, Red_Tile, Instruction_Start_Left, Instruction_NOP);//

	TheChosenOne.Set_Instruction_For_Tile(4, 1, Red_Tile, Instruction_In_Alpha, Instruction_NOP);//
	TheChosenOne.Set_Instruction_For_Tile(3, 1, Red_Tile, Instruction_Bond_Remove, Instruction_NOP);//

	TheChosenOne.Set_Instruction_For_Tile(2, 1, Red_Tile, Instruction_Grab, Instruction_Down);//
	TheChosenOne.Set_Instruction_For_Tile(6, 1, Red_Tile, Instruction_Out_Omega, Instruction_Left);

	TheChosenOne.Set_Instruction_For_Tile(2, 2, Red_Tile, Instruction_NOP, Instruction_Right);
	TheChosenOne.Set_Instruction_For_Tile(6, 2, Red_Tile, Instruction_Drop, Instruction_Up);


	// Debugging, place the bonding pads
	TheChosenOne.Add_BondingPad(1, 1);
	TheChosenOne.Add_BondingPad(2, 1);


	// Set the reactor to simulate.
	RunMe.Set_Solution(TheChosenOne);

	// Limit the simulation to prevent unlimited running.
	RunMe.Set_Cycle_Limit_Simulation(Problem_Rules.Get_Cycle_Limit_Simulation());

	// Debugging Infomation.
	Atom_Info Info;
	Info.Atomic_Number = 9;
	Info.Max_Bonds = 1;

	Atom F;
	F.Placeholder = false;
	F.Details = Info;

	// Create the input molecule.
	AlphaIn.Set_Atom(1, 1, F);
	AlphaIn.Set_Atom(2, 1, F);

	AlphaIn.Add_Bond(1, 1, 2, 1);

	// Create the input molecule.
	Solution.Set_Atom(1, 1, F);

	// Just the input for the simulation.
	Input_For_Debugging.Items.push_back(AlphaIn);
	Input_For_Debugging.Set_IsEmpty(false);

	RunMe.Add_To_Input(Input_For_Debugging, Simulation_Add_To_Input_Alpha);
	RunMe.Add_To_Input(Input_For_Debugging, Simulation_Add_To_Input_Alpha);
	RunMe.Add_To_Input(Input_For_Debugging, Simulation_Add_To_Input_Alpha);

}

	// Fills in the testing data for Sernimir II 006, check Validation of simulations for more details.
void Debug_Test_Sernimir_II_006(Solution_Reactor &TheChosenOne, Problem_Definition &Problem_Rules, Simulation &RunMe, Packed_Molecule &Input_For_Debugging, Molecule &AlphaIn, Molecule &Solution) {

	// I am just putting my solution in to test the simulation

		// The blue instructions.
	TheChosenOne.Set_Instruction_For_Tile(5, 0, Blue_Tile, Instruction_Start_Left, Instruction_NOP);
	
		// The red instructions.
	TheChosenOne.Set_Instruction_For_Tile(5, 1, Red_Tile, Instruction_Start_Left,	Instruction_NOP);

	TheChosenOne.Set_Instruction_For_Tile(4, 1, Red_Tile, Instruction_In_Alpha,		Instruction_NOP);

	TheChosenOne.Set_Instruction_For_Tile(2, 1, Red_Tile, Instruction_Grab,			Instruction_Down);
	TheChosenOne.Set_Instruction_For_Tile(6, 1, Red_Tile, Instruction_Out_Omega,	Instruction_NOP);
	TheChosenOne.Set_Instruction_For_Tile(7, 1, Red_Tile, Instruction_Drop,			Instruction_Left);

	TheChosenOne.Set_Instruction_For_Tile(2, 2, Red_Tile, Instruction_NOP,			Instruction_Right);
	TheChosenOne.Set_Instruction_For_Tile(7, 2, Red_Tile, Instruction_NOP,			Instruction_Up);


	// Debugging, place the bonding pads
	TheChosenOne.Add_BondingPad(1, 1);
	TheChosenOne.Add_BondingPad(2, 1);


	// Set the reactor to simulate.
	RunMe.Set_Solution(TheChosenOne);

	// Limit the simulation to prevent unlimited running.
	RunMe.Set_Cycle_Limit_Simulation(Problem_Rules.Get_Cycle_Limit_Simulation());

	// Debugging Infomation.
	Atom_Info Info;
	Info.Atomic_Number = 9;
	Info.Max_Bonds = 1;

	Atom F;
	F.Placeholder = false;
	F.Details = Info;

	// Create the input molecule.
	AlphaIn.Set_Atom(1, 1, F);
	AlphaIn.Set_Atom(2, 1, F);

	AlphaIn.Add_Bond(1, 1, 2, 1);

	AlphaIn.Set_IsEmpty(false);

	// Create the input molecule.
	Solution.Set_Atom(1, 1, F);

	// Just the input for the simulation.
	Input_For_Debugging.Items.push_back(AlphaIn);
	Input_For_Debugging.Set_IsEmpty(false);

	RunMe.Add_To_Input(Input_For_Debugging, Simulation_Add_To_Input_Alpha);
	RunMe.Add_To_Input(Input_For_Debugging, Simulation_Add_To_Input_Alpha);
	RunMe.Add_To_Input(Input_For_Debugging, Simulation_Add_To_Input_Alpha);

}

	// Fills in the testing data for Sernimir II 007, check Validation of simulations for more details.
void Debug_Test_Sernimir_II_007(Solution_Reactor &TheChosenOne, Problem_Definition &Problem_Rules, Simulation &RunMe, Packed_Molecule &Input_For_Debugging, Molecule &AlphaIn, Molecule &Solution) {

	// I am just putting my solution in to test the simulation

	// The blue instructions.
	TheChosenOne.Set_Instruction_For_Tile(5, 0, Blue_Tile, Instruction_Start_Left, Instruction_NOP);

	// The red instructions.
	TheChosenOne.Set_Instruction_For_Tile(5, 1, Red_Tile, Instruction_Start_Left, Instruction_NOP);

	TheChosenOne.Set_Instruction_For_Tile(4, 1, Red_Tile, Instruction_In_Alpha, Instruction_NOP);

	TheChosenOne.Set_Instruction_For_Tile(3, 1, Red_Tile, Instruction_Sync, Instruction_NOP);

	TheChosenOne.Set_Instruction_For_Tile(2, 1, Red_Tile, Instruction_Grab, Instruction_Down);
	TheChosenOne.Set_Instruction_For_Tile(6, 1, Red_Tile, Instruction_Out_Omega, Instruction_NOP);
	TheChosenOne.Set_Instruction_For_Tile(7, 1, Red_Tile, Instruction_Drop, Instruction_Left);

	TheChosenOne.Set_Instruction_For_Tile(2, 2, Red_Tile, Instruction_NOP, Instruction_Right);
	TheChosenOne.Set_Instruction_For_Tile(7, 2, Red_Tile, Instruction_NOP, Instruction_Up);


	// Debugging, place the bonding pads
	TheChosenOne.Add_BondingPad(1, 1);
	TheChosenOne.Add_BondingPad(2, 1);


	// Set the reactor to simulate.
	RunMe.Set_Solution(TheChosenOne);

	// Limit the simulation to prevent unlimited running.
	RunMe.Set_Cycle_Limit_Simulation(Problem_Rules.Get_Cycle_Limit_Simulation());

	// Debugging Infomation.
	Atom_Info Info;
	Info.Atomic_Number = 9;
	Info.Max_Bonds = 1;

	Atom F;
	F.Placeholder = false;
	F.Details = Info;

	// Create the input molecule.
	AlphaIn.Set_Atom(1, 1, F);
	AlphaIn.Set_Atom(2, 1, F);

	AlphaIn.Add_Bond(1, 1, 2, 1);

	AlphaIn.Set_IsEmpty(false);

	// Create the input molecule.
	Solution.Set_Atom(1, 1, F);

	// Just the input for the simulation.
	Input_For_Debugging.Items.push_back(AlphaIn);
	Input_For_Debugging.Set_IsEmpty(false);

	RunMe.Add_To_Input(Input_For_Debugging, Simulation_Add_To_Input_Alpha);
	RunMe.Add_To_Input(Input_For_Debugging, Simulation_Add_To_Input_Alpha);
	RunMe.Add_To_Input(Input_For_Debugging, Simulation_Add_To_Input_Alpha);

}

	// Fills in the testing data for Sernimir II 008, check Validation of simulations for more details.
void Debug_Test_Sernimir_II_008(Solution_Reactor &TheChosenOne, Problem_Definition &Problem_Rules, Simulation &RunMe, Packed_Molecule &Input_For_Debugging, Molecule &AlphaIn, Molecule &Solution) {

	// I am just putting my solution in to test the simulation

		// The blue instructions.
	TheChosenOne.Set_Instruction_For_Tile(5, 0, Blue_Tile, Instruction_Start_Left,	Instruction_NOP);

		// The red instructions.
	TheChosenOne.Set_Instruction_For_Tile(5, 1, Red_Tile, Instruction_Start_Left,	Instruction_NOP);
	TheChosenOne.Set_Instruction_For_Tile(4, 1, Red_Tile, Instruction_In_Alpha,		Instruction_NOP);
	TheChosenOne.Set_Instruction_For_Tile(3, 1, Red_Tile, Instruction_Bond_Remove,	Instruction_NOP);
	TheChosenOne.Set_Instruction_For_Tile(1, 1, Red_Tile, Instruction_Grab,			Instruction_Down);
	

	// Debugging, place the bonding pads
	TheChosenOne.Add_BondingPad(1, 1);
	TheChosenOne.Add_BondingPad(2, 1);


	// Set the reactor to simulate.
	RunMe.Set_Solution(TheChosenOne);

	// Limit the simulation to prevent unlimited running.
	RunMe.Set_Cycle_Limit_Simulation(Problem_Rules.Get_Cycle_Limit_Simulation());

	// Debugging Infomation.
	Atom_Info Info;
	Info.Atomic_Number = 9;
	Info.Max_Bonds = 1;

	Atom F;
	F.Placeholder = false;
	F.Details = Info;

	// Create the input molecule.
	AlphaIn.Set_Atom(1, 1, F);
	AlphaIn.Set_Atom(2, 1, F);

	AlphaIn.Add_Bond(1, 1, 2, 1);

	AlphaIn.Set_IsEmpty(false);

	// Create the input molecule.
	Solution.Set_Atom(1, 1, F);

	// Just the input for the simulation.
	Input_For_Debugging.Items.push_back(AlphaIn);
	Input_For_Debugging.Set_IsEmpty(false);

	RunMe.Add_To_Input(Input_For_Debugging, Simulation_Add_To_Input_Alpha);
	RunMe.Add_To_Input(Input_For_Debugging, Simulation_Add_To_Input_Alpha);
	RunMe.Add_To_Input(Input_For_Debugging, Simulation_Add_To_Input_Alpha);

}

#endif