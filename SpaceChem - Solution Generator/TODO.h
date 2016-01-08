/*
	Bugs to fix:
		- (kinda fixed, I patched it to just force one output) The output should be single molecules not packed. 
					It turns out it costs a cycle to output a single molecule and they don't all go as one.		
		- (Fixed) If both waldos are grabbing the same molecule, don't double move and check if they are not going the same direction.

		- (Fixed) Block output for molecules that are held by waldos.
		- (Fixed) Start does not count towards the symbol count.
		
	Required new features
		- Validation of the output to ensure it's matching the requirements.
	
	Notes:
		- Check to make sure any function that pulls from the active_molecule pool checks to make sure if the molecule is empty or not.
		- Add bond, does it handle atoms with no bond already?
		- Note, this needs to check waldos to make sure they are not holding the atom. If they are Fix thier index. 
		Also there might be a chance where two waldos grab the same molecule and split it? That case should be looked into.

	Future updates after prototype:
		- Create a output idle if it is full.
		- Add bond does not take two molecules and connect them.
		- Change the validation of a molecule to hanlde any shape and just require a type of connection.
			(Rules from the game\Output - Different shapes.png)


		//		IDEAS
		//	Experiment ID:
		//		- Web server for experiments.
		//			:with json that sotres all possible
		//
		//
		//


*/