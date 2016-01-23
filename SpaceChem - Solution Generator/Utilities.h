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

/*
	Utilities.h - Used to store functions called directly by main.
*/



	// To be done after.
void PrintUsage() {
	printf("--\n");
	printf("--\n");
}

// A structure to hold all the information provided by Command Line.
struct CommandLine{

	// What operation should be done.
	int Operation = Command_Line_OP_NOP;

	// For the error code.
	int Status_Code = Command_Line_NoError;

	// The path to the definition problem. 
	std::string In_FilePath = "";

	// The path to dump the results to.
	std::string Out_FilePath = "";

	// Flags and values - These override the problem defined in the file.

	// The results of the simulation should be output to a file.
	bool Flag_ShouldDumpToFile = false;

	// The results of the simulation should be output to console.
	bool Flag_ShouldDumpToConsole = false;

	// Should the information that displays at the start be disabled. 
	// This is to be able to dump the console without having to remove a header.
	bool Flag_ShouldDisableStartInfo = false;

	// Should the debugging infomation be output to console.
	bool Flag_ShouldDisplayDebugging = false;

	// Should the program use the cache file to keep a buffer of the current work that has been done.
	/*Future maybe*/bool Flag_ShouldProtectFromPowerloss = false;

	// Should for large pools the data be dumped to the hard drive unless in use.
	/*Future maybe*/bool Flag_ShouldCache = false;


};


// Take the commandline arguments and decide what to
CommandLine ParseCommandLine(int argc, char *argv[]){

	CommandLine Result;

	for (int i = 1; i < argc; i++){
		// Operations:
		// -OP_Test  : Simulates the testing data to check the validation of the current version.
		if (strcmp(argv[i], "-OP_Test") == 0){
			Result.Operation = Command_Line_OP_TEST;
			continue;
		}
		// -OP_SAF   : Loads a problem definition from a file and simulates it until a solution is found.
		if (strcmp(argv[i], "-OP_SAF") == 0){
			Result.Operation = Command_Line_OP_SAF;
			continue;
		}
		// -OP_CS	 : Load a solution and simulate it and give the result if it is valid.
		if (strcmp(argv[i], "-OP_CS") == 0){
			Result.Operation = Command_Line_OP_CS;
			continue;
		}

		// -h or --help  : provide the usage for the user.
		if (strcmp(argv[i], "-h") == 0){
			// Print the usage and exit.
			PrintUsage();

			Result.Operation = Command_Line_OP_NOP;
			return Result;
		}

		// -f <filepath> : the input file.
		if (strcmp(argv[i], "-f") == 0){

			// The file command has to be followed by a path.
			if ((i + 1) < argc){

				// Set the filepath and increase i;
				Result.In_FilePath = argv[i + 1];

				i++;

				continue;
			}
			else{
				// Return with the error code.
				Result.Status_Code = Command_Line_Missing_Path;

				return Result;
			}
		}
		// -r <filepath> : the output file.
		if (strcmp(argv[i], "-r") == 0){

			// The file command has to be followed by a path.
			if ((i + 1) < argc){

				// Set the filepath and increase i;
				Result.Out_FilePath = argv[i + 1];

				i++;

				continue;
			}
			else{
				// Return with the error code.
				Result.Status_Code = Command_Line_Missing_Path;

				return Result;
			}
		}

		// -c : Output result to console.
		if (strcmp(argv[i], "-c") == 0){
			Result.Flag_ShouldDumpToConsole = true;
			continue;
		}

		// -d or --debugging : enable debugging infomation.
		if (strcmp(argv[i], "-d") == 0 || strcmp(argv[i], "--debugging") == 0){
			Result.Flag_ShouldDisplayDebugging = true;
			continue;
		}
	}

	return Result;
}


void PrintStartInfomation(){
	printf("SpaceChem Solution Generator - written by David Harkins.\n");
}

	// Load file by full path and return a pointer to a char *str or null.
char *LoadFileByName(std::string argument) {

	std::streampos size;
	char * memblock;

	std::ifstream file(argument.c_str(), std::ios::in | std::ios::binary | std::ios::ate);
	if (file.is_open()) {

		size = file.tellg();
		memblock = new char[(unsigned int)size];
		file.seekg(0, std::ios::beg);
		file.read(memblock, size);
		file.close();

	}
	else { return NULL; }

	return memblock;
}
