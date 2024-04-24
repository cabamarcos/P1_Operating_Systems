// Libraries declaration
#include <stdio.h>			// Standard buffered input/output
#include <unistd.h>			// Standard symbolic constants and types
#include <sys/types.h>		// Data types
#include <dirent.h>			// Format of directory entries
#include <string.h>			// String operations


int main(int argc, char *argv[]){
	// MAX_PATH represents  maximum size that can have the path of the current directory.
    char directory[PATH_MAX]; // Max size the path of the directory can be is PATH_MAX

	if(argc < 2){
		getcwd(directory, -1); // If no directory is received, the current one will be used
	}
	
	// The argument is copied into the variable being used to store the directory
	else{
		strcpy(directory, argv[1]); 
	}

	// The memory direction of the directory is stored
	DIR* direction = opendir(directory);

	// Check if the direction is null, this will happen if the directory cannot be opened
	if (direction == NULL){
		printf("The directory does not exist.\n");
		return -1; // Returning -1 indicating an error occurred. Stops program
	}

	// Creation of dirent structure and pointer to it, representing directory entry
	struct dirent *directoryPointer = readdir(direction);
	
	// In the while loop the values found will be printed
	// Once the directory pointer is NULL the loop will stop, as nothing is left to be read in the directory
	while (directoryPointer != NULL){
		printf("%s\n", directoryPointer -> d_name);
		directoryPointer = readdir(direction); // Memory position renewed so it goes through all dir*
	}
    
	closedir(direction); // Directory is closed after the program ends
	return 0; // Returning 0 indicating no error was encountered in the program
}
