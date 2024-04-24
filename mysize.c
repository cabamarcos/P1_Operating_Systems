// Libraries declaration
#include <stdio.h>          // Standard buffered input/output
#include <sys/types.h>      // Data types
#include <sys/stat.h>       // Define structure of returned data
#include <fcntl.h>          // File control options: fcntl(), open()
#include <dirent.h> 	    // Format of directory entries
#include <unistd.h>         // Standard symbolic constants and types


int main(int argc, char *argv[]){
    // Variable declaration
    char folder[PATH_MAX];
    int fileOpn;
    int startPointer;
    int endPointer;
    int fileSize;

    getcwd(folder, -1);	// Pathname of the current directory
    DIR *folderDir; //  Open directory and return DIR pointer to the beginning
    struct dirent *file; // Creation of dirent structure

    // Getting the pathname
    folderDir = opendir(folder);
    if (folderDir == NULL){ // IF error
        printf("Error when opening folder\n");
        return -1; // Returning -1 indicating an error occurred
    }

    // Pointer to the previously created dirent structure representing directory entry
    file = readdir(folderDir);
    // While files exist in folder
    while (file != NULL){
        if ((file -> d_type) == DT_REG){ // If regular file
            // Open file
            fileOpn = open((file -> d_name), O_RDONLY);

            // Check error
            if (fileOpn < 0){
                printf("Error when opening file\n");
                return -1; // Returning -1 indicating an error occurred. Stops program
            }

            // Get file size (using 2 pointers)
            startPointer = lseek(fileOpn, 0, SEEK_SET); // Position of pointer at offset (0)
            endPointer = lseek(fileOpn, 0, SEEK_END); // Position of pointer at file size + offset (0)
            fileSize = (endPointer - startPointer); // Subtracting start pointer and end pointer = file length

            // Print file file name and size
            printf("%s    %i\n", file -> d_name, fileSize); // notice: \t is not constant, so we add '    '

            // Close file
            fileOpn = close(fileOpn);

            // Check error
            if (fileOpn < 0){
                printf("Error when closing file\n");
                return -1; // Returning -1 indicating an error occurred. Stop program
            }

        }
        
        file = readdir(folderDir); // Select next directory entry (file) and repeat process
    }

    return 0; // Returning 0 indicating no error was encountered in the program
}