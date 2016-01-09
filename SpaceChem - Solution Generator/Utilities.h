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
