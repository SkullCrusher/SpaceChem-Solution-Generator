
#ifndef Simulation_Controller_Header
#define Simulation_Controller_Header

#include <vector>

	// Required for definitions and global class.
#include "Definitions.h"
#include "Problem_Definiton.h"
#include "Solution.h"

	// Core parts of the program.
#include "Simulation.h"
#include "Generation.h"

	// Debugging, Senimir II
#include "Debugging_Sernimir_II_Testing.h"


class Simulation_Controller{

	Problem_Definition Problem_Rules;

		// Default constructor
	public: Simulation_Controller(){

	}
		// Default destructor
	public: ~Simulation_Controller(){

	}

		// Used for the prototype to handle bulk input.
	public: std::vector<Solution_Reactor> Input;


	private: int Debug_Prototype_Simulate_Reactor(int Index) {
		
			// Debugging I am just putting my solution in to test the simulation
		Solution_Reactor TheChosenOne;
			
		Simulation RunMe;

			// Debugging, Create the input molecule.
		Molecule AlphaIn;
		
			// Debugging, Create the input molecule.
		Molecule Solution;

			// Just the input for the simulation.
		Packed_Molecule Input_For_Debugging;

			// Test problem.
		Debug_Test_Sernimir_II_001(TheChosenOne, Problem_Rules, RunMe, Input_For_Debugging, AlphaIn, Solution);
	

		

		int Total_Correct_Output = 0;

			// Process the simulation.
		int Results = Simulation_Continue;
		while (Results == Simulation_Continue) {

				// Keep adding the input to the simulation to make sure it's full.
			RunMe.Add_To_Input(Input_For_Debugging, Simulation_Add_To_Input_Alpha);
			RunMe.Add_To_Input(Input_For_Debugging, Simulation_Add_To_Input_Alpha);

				// Simulate the simulation
			Results = RunMe.Tick();

				// Pull from the output.
			Packed_Molecule Temp = RunMe.Remove_From_Output();

				// Process the output.
			if (!Temp.IsEmpty) {
					// We check if the result molecule is the same as the solution. (note they don't have to apperent on the same position of the grid.)
				if (Temp.Items[0] == Solution) {
					Total_Correct_Output++;
				}else {
					RunMe.Set_Simulation_Status(Simulation_Invalid_Output);
					RunMe.Set_Is_Simulated(true);
				}
			}

				// We accept it and return.
			if (Total_Correct_Output == 10) {
				RunMe.Set_Simulation_Status(Simulation_Complete);
				RunMe.Set_Is_Simulated(true);

					// testing to see the size.
				Input.push_back(RunMe.GetSolution());

				return Simulation_Complete;
			}
		}
		
		RunMe.Set_Simulation_Status(Results);
		RunMe.Set_Is_Simulated(true);

		return Results;
	}

		// Run the program.
	public: int Tick(){
		
			// In the future the simulation controller will handle multiple reactors but for the prototype it just handles one.

		/*
		for (unsigned int i = 0; i < Input.size(); i++) {
			Debug_Prototype_Simulate_Reactor(i);
		}
		*/
		for (unsigned int i = 0; i < 1000; i++) {
			Debug_Prototype_Simulate_Reactor(0);
		}

		return 0;
	}


		//Basic Utilities
	public: void Set_Problem_Definition(Problem_Definition argument){ Problem_Rules = argument; }
	

};


#endif