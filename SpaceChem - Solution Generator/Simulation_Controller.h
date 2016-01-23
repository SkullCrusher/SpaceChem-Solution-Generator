/*
	SpaceChem Solution Generator - Solves problems using the genetic algorithm.
					Copyright(C) 2016 by David Harkins.

	This program is free software : you can redistribute it and / or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation version 3 of the License.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

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
#include "Sernimir_II_Testing.h"


class Simulation_Controller{

	Problem_Definition Problem_Rules;

		// Default constructor
	public: Simulation_Controller(){}

		// Default destructor
	public: ~Simulation_Controller(){}

			//argument, Problem_Rules, RunMe, InputForAlpha, AlphaIn, InputForBeta, BetaIn, Expected_Out_Omega, Expected_Out_Phi
			/*
	private: void Preprocess_Single_Reactor(Solution_Reactor &argument,
											Problem_Definition &Problem_Rules, 
											Simulation &RunMe, 
											Packed_Molecule &InputForAlpha, 
											Molecule &AlphaIn, 
											Packed_Molecule &BetaIn,
											Molecule &Expected_Out_Omega,
											Molecule &Solution) {

		// Set the reactor to simulate.
		RunMe.Set_Solution(argument);

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
		InputForAlpha.Items.push_back(AlphaIn);
		InputForAlpha.Set_IsEmpty(false);

		RunMe.Add_To_Input(Input_For_Debugging, Simulation_Add_To_Input_Alpha);
		RunMe.Add_To_Input(Input_For_Debugging, Simulation_Add_To_Input_Alpha);
		RunMe.Add_To_Input(Input_For_Debugging, Simulation_Add_To_Input_Alpha);

	}
	*/

		// Made for the prototype and is only used when a single reactor is in question and not a set of reactors.
	public: int Simulate_Single_Reactor(Solution_Reactor &argument,
													Simulation RunMe,				 
													Packed_Molecule InputForAlpha,
													Packed_Molecule InputForBeta,
													Packed_Molecule Expected_Out_Omega,
													Packed_Molecule Expected_Out_Phi){

		// Set the reactor to simulate.
		RunMe.Set_Solution(argument);

		// Limit the simulation to prevent unlimited running.
		RunMe.Set_Cycle_Limit_Simulation(Problem_Rules.Get_Cycle_Limit_Simulation());	

			// Fill in the input for both alpha and beta.
		for (unsigned int i = 0; i < 3; i++){ RunMe.Add_To_Input(InputForAlpha, Simulation_Add_To_Input_Alpha); }
		for (unsigned int i = 0; i < 3; i++){ RunMe.Add_To_Input(InputForAlpha, Simulation_Add_To_Input_Beta); }
			
		int Total_Correct_Output = 0;

			// Process the simulation.
		int Results = Simulation_Continue;
		while (Results == Simulation_Continue) {

				// Keep adding the input to the simulation to make sure it's full.
			RunMe.Add_To_Input(InputForAlpha, Simulation_Add_To_Input_Alpha);
			RunMe.Add_To_Input(InputForAlpha, Simulation_Add_To_Input_Alpha);

				// Simulate the simulation
			Results = RunMe.Tick();

				// Pull from the output.
			Packed_Molecule Temp = RunMe.Remove_From_Output();

				// Process the output.
			if (!Temp.IsEmpty) {
					// We check if the result molecule is the same as the solution. (note they don't have to apperent on the same position of the grid.)
				if (Temp.Items.size() >= 1) {
					if (Temp.Items[0] == Expected_Out_Omega) {
						Total_Correct_Output++;
					}else{
						RunMe.Set_Simulation_Status(Simulation_Invalid_Output);
						RunMe.Set_Is_Simulated(true);
						RunMe.Increment_Cycle_Count(); // Because the validation is outside of the simulation it needs to increase one cycle.
						break;
					}
				}else {
					RunMe.Set_Simulation_Status(Simulation_Invalid_Output);
					RunMe.Set_Is_Simulated(true);
					break;
				}
			}

				// We accept it and return.
			if (Total_Correct_Output == 10) {
				RunMe.Set_Simulation_Status(Simulation_Complete);
				RunMe.Set_Is_Simulated(true);

					// Pull the solution data from the simulation.
				argument = RunMe.GetSolution();

				return Simulation_Complete;
			}
		}

		RunMe.Set_Simulation_Status(Results);
		RunMe.Set_Is_Simulated(true);

			// Pull the solution data from the simulation.
		argument = RunMe.GetSolution();

		return Results;
	}

   
			 /*
		// Calls the simulation of a single reactor, this is used for the prototype.
	private: int Prototype_Simulate_Reactor(Solution_Reactor &argument) {
		
			// Debugging I am just putting my solution in to test the simulation
	//	Solution_Reactor TheChosenOne; // Provided by outside source.
			
		Simulation RunMe;

			// Debugging, Create the input molecule.
		Molecule AlphaIn;
		
			// Debugging, Create the input molecule.
		Molecule Solution;

			// Debugging, Just the input for the prototype simulation.
		Packed_Molecule Input_For_Debugging;

			//A debugging Test problem.
		//Debug_Test_Sernimir_II_006(TheChosenOne, Problem_Rules, RunMe, Input_For_Debugging, AlphaIn, Solution);
		//TheChosenOne = argument;

		Debug_Prototype_Fill_In_Reactor(argument, Problem_Rules, RunMe, Input_For_Debugging, AlphaIn, Solution);

		

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
				if (Temp.Items.size() >= 1) {
					if (Temp.Items[0] == Solution) {
						Total_Correct_Output++;
					}else{
						RunMe.Set_Simulation_Status(Simulation_Invalid_Output);
						RunMe.Set_Is_Simulated(true);
						RunMe.Increment_Cycle_Count(); // Because the validation is outside of the simulation it needs to increase one cycle.
						break;
					}
				}else {
					RunMe.Set_Simulation_Status(Simulation_Invalid_Output);
					RunMe.Set_Is_Simulated(true);
					break;
				}
			}

				// We accept it and return.
			if (Total_Correct_Output == 10) {
				RunMe.Set_Simulation_Status(Simulation_Complete);
				RunMe.Set_Is_Simulated(true);

					// Pull the solution data from the simulation.
				argument = RunMe.GetSolution();

				return Simulation_Complete;
			}
		}
		
		RunMe.Set_Simulation_Status(Results);
		RunMe.Set_Is_Simulated(true);

			// Pull the solution data from the simulation.
		argument = RunMe.GetSolution();

		return Results;
	}
	*/
		// Run the program.
	public: int Tick(std::vector<Solution_Reactor> &Solution_Pool){
		
			// In the future the simulation controller will handle multiple reactors but for the prototype it just handles one.
		for (unsigned int i = 0; i < Solution_Pool.size(); i++) {

				// If the solution has not been simulated, simulate it.
			if (!Solution_Pool[i].Get_HasBeenSimulated()) {
			//	Prototype_Simulate_Reactor(Solution_Pool[i]);
			}
		}		

		return 0;
	}

		//Basic Utilities
	public: void Set_Problem_Definition(Problem_Definition argument){ Problem_Rules = argument; }
	
};


#endif