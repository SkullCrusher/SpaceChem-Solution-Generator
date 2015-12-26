// A simulation of a reactor.

#ifndef Simulation_Header
#define Simulation_Header

	// Required for definitions and global class.
#include "Definitions.h"

#include "Waldo.h"
#include "Solution.h"
#include "Atom.h"


class Simulation{
	
		// The cap on cycles.
	unsigned long Cycle_Limit_Simulation;

		// How many cycles have been simulated,
	unsigned long Cycles;

		// The solution to be simulated.
	Solution_Reactor Solution;

		// The red and blue waldo which are the controlling parts of the simulation.
	Waldo Red_Waldo;
	Waldo Blue_Waldo;

	/* 
				The in and out containers for molecules.
		It is a buffer that the controller for the simulation has to handle.
		We know that only two Molecule can be pulled in and pushed out on each cycle.

		Note: The reason why it is not one is if the molecules happen to be different
		they might not collide so it requires a double buffer.
	*/
	Molecule In_Alpha[2];
	Molecule Out_Omega[2];
	
	Molecule In_Beta[2];
	Molecule Out_Phi[2];

	
		// Default constructor.
	public: Simulation(){
		Cycle_Limit_Simulation = 0;
		Cycles = 0;
	}

		// Default destructor.
	public: ~Simulation(){}

		// Finds the starting instruction in the solution for the waldo.
	private: short FindStart(bool RedorBlue, Waldo &argument){

		for (int w = 0; w < 10; w++){
			for (int h = 0; h < 8; h++){				
				Tile Result = Solution.GetTile(w, h, RedorBlue);
					
					// If the tile is a starting point, set it.
				if (Result.Instruction_1 == Instruction_Start_Left  || 
					Result.Instruction_1 == Instruction_Start_Right ||
					Result.Instruction_1 == Instruction_Start_Up	||
					Result.Instruction_1 == Instruction_Start_Down){

					short Direction = -1;

					if (Result.Instruction_1 == Instruction_Start_Left){Direction = Instruction_Left;}
					if (Result.Instruction_1 == Instruction_Start_Right){Direction = Instruction_Right;}
					if (Result.Instruction_1 == Instruction_Start_Up){Direction = Instruction_Up;}
					if (Result.Instruction_1 == Instruction_Start_Down){Direction = Instruction_Down;}

					argument.SetX(w);
					argument.SetY(h);
					argument.SetActive(true);
					argument.Set_Direction(Direction);

					return Simulation_Continue;
				}							
			}
		}		

		return Simulation_Continue;
	}

		// Generates the requirements to start the simulation.
	private: int GenerateDefaults(){
			// Find the starting point and direction of the waldos.
		
		int RedStart_R = FindStart(Red_Tile, Red_Waldo);
		int BlueStart_R = FindStart(Blue_Tile, Blue_Waldo);

		return Simulation_Continue;
	}

		// Moves the waldo based off the direction inside it.
	private: void MoveWaldo(Waldo &argument){
		
		if (argument.GetDirection() == Waldo_Direction_Left){
				// Check if the waldo is at the edge, if so do nothing.
			if (argument.GetX() > 0){
				argument.SetX(argument.GetX() - 1);
			}
		}

		if (argument.GetDirection() == Waldo_Direction_Right){
				// Check if the waldo is at the edge, if so do nothing.
			if (argument.GetX() < 9){
				argument.SetX(argument.GetX() + 1);
			}
		}

		if (argument.GetDirection() == Waldo_Direction_Up){
				// Check if the waldo is at the edge, if so do nothing.
			if (argument.GetY() > 0){
				argument.SetY(argument.GetY() - 1);
			}
		}

		if (argument.GetDirection() == Waldo_Direction_Down){
				// Check if the waldo is at the edge, if so do nothing.
			if (argument.GetY() < 7){
				argument.SetY(argument.GetY() + 1);
			}
		}

	}

		// Checks the entire Reactor to see if there is a collision 
			 // (Note to self, you might be able to reduce the processing time here by only checking the change)
/*TODO*/private: short CheckForCollision(){

		//#define Collision_No_Collision			0
		//#define Collision_Yes_Collision			1

		return Collision_No_Collision;
	}

		// Runs the instruction that is provided in Instruction_1 and used Instruction_2 for direction.
	private: short Execute_Instruction(Waldo &argument, bool RedorBlue){
		
			// Pull the instructions for that tile.
		Tile Instruction = Solution.GetTile(argument.GetX(), argument.GetY(), RedorBlue);
		// Attempt to run the instruction in Instruction_1.

		// Change the direction to the instruction in Instruction_2.


		


		return Execution_NoError;
	}

	/*
			 
		#define Solution_Unprocessed			1	// The solution has not been processed in a simulation
		#define Solution_Invalid_Collision		2	// The solution is invalid because it has a collision
		#define Solution_Invalid_NoStart		3	// The solution is invalid because there is not start (requires 1)
		#define Solution_Out_Of_Cycles			4	// The solution went past the cycle cap.
		#define Solution_Accepted				5	// The solution is a valid solution.

	*/

	private: int Simulate_Cycle(){

			// The steps of the simulation:

			// Check if there is a red track we need to simulate
		if (Red_Waldo.GetActive()){

				// 1. Move Red Waldo.
			MoveWaldo(Red_Waldo);

				// 2. Check for collision (only if holding molecule).
			if (Red_Waldo.GetGrabbing_Molecule()){
				int Result = CheckForCollision();

					// If there is a collision, halt.
				if (Result == Collision_Yes_Collision){

						// Set the information on the simulation.
					Solution.Set_Status(Solution_Invalid_Collision);
					Solution.Set_HasBeenSimulated(true);

					return Simulation_Collision;
				}
			}

				// 3. Execute Red Waldo instruction_1.
				// 4. Set new direction if there instruction_2.
			int Result = Execute_Instruction(Red_Waldo, Red_Tile);

			// 5. Check for collision (only if there was an instruction that could cause).	

		}
		

			

			// 6. Move Blue Waldo.

			// 7. Check for collision (only if holding molecule)	

			// 8. Execute Blue Waldo instruction_1.
			// 9. Set new direction if there instruction_2.

			// 10. Check for collision (only if there was an instruction that could cause).	
		

		return Simulation_Continue;
	}

		// Process the simulation.
	public: int Tick(){
	
			// Halt the simulation if the cycles have reached the cap.
		if (Cycles >= Cycle_Limit_Simulation){
			return Simulation_OutOfCycles;
		}

			// If this is the first tick run the requirements to fill in the waldo.
		if (Cycles == 0){
			int Result = GenerateDefaults();

				// If there was an error.
			if (Result == Simulation_InvalidSimulation){
				return Simulation_InvalidSimulation;
			}
		}

			// Simulate a single cycle.
		int Result = Simulate_Cycle();
				
		Cycles++;

		return Result; // Normally Simulation_Continue
	}

		// Accept a new solution.
	public: void Set_Solution(Solution_Reactor argument) {
		Solution = argument;
	}

	public: void Set_Cycle_Limit_Simulation(int argument){
		Cycle_Limit_Simulation = argument;
	}

};


#endif