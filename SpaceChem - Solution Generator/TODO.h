/*
	Bugs to fix:
		- The output should be single molecules not packed, it turns out it costs a cycle to output a single molecule and they don't all go as one.
			: The output needs to stall if it can't output. Also figure out which is output first.
		- Start does not count towards the symbol count.

	Required new features
		- Validation of the output to ensure it's matching the requirements.
	
	Notes:
		- Check to make sure any function that pulls from the active_molecule pool checks to make sure if it is empty or not.
		- Add bond, does it handle atoms with no bond already?
		- Note, this needs to check waldos to make sure they are not holding the atom. If they are Fix thier index. 
		Also there might be a chance where two waldos grab the same molecule and split it? That case should be looked into.

	Future updates:
		- Create a output idle if it is full.

*/