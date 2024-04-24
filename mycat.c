// Libraries declaration
#include <stdio.h> 			// Standard buffered input/output
#include <sys/types.h> 		// Data types
#include <sys/stat.h>		// Define structure of returned data
#include <fcntl.h>			// File control options: fcntl(), open()
#include <unistd.h> 		// Standard symbolic constants and types

// Buffer size definition
#define BUFFER_SIZE 1024 // Set number of bytes to be used only by our program


int main(int argc, char *argv[]){
	// argv[0] = program, argv[1] = file. If arc<2, not enogh arguments
	if(argc < 2){
		printf("Not enough arguments\n");
		return -1; // Returning -1 indicating an error occurred. Stops program
	}

	// Open the file, read only
	int file = open(argv[1], O_RDONLY);

	// Check error
	if (file < 1){
		printf("The selected file does not exist\n");
		return -1; // Returning -1 indicating an error occurred
	}

	// Variable for saving the read file
	char saved[BUFFER_SIZE];
	int readFile = read(file, saved, BUFFER_SIZE); // Read file

	// While exists something to be read
    while (readFile >0){
		write(STDOUT_FILENO, saved, readFile); // Write the content of the buffer, standard output
		readFile = read(file, saved, BUFFER_SIZE); // Memory position renewed so it goes through file
	}

	close(file); // Close file previously correctly read
	return 0; // Returning 0 indicating no error was encountered in the program
}
