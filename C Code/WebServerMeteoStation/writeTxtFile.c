#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h> // Include the header file for sleep()
	
int main() {
    
    FILE *file;
    char *filename = "./data.csv";
    int sensorReading = 0;

    // Attempt to delete the existing file
    if (remove(filename) != 0) {
	perror("Error deleting the file");
    }
    else {
	printf("File deleted successfully\n");
    }
        
    for(;;){
	sensorReading=rand()%10000;
	
        // Open the file in "a" mode (append content to existing file)
        file = fopen(filename, "a");
        
        if (file == NULL) {
            printf("Error opening file\n");
            exit(1);
        }
	else{
	    printf("File opened correctly\n");
	}

	
	fprintf(file, "Temperature,%d\n", sensorReading);
	printf("Temperature: %d\n", sensorReading);
	
        
        // Flush the output buffer to ensure the data is written to the file immediately
        fflush(file);
        printf("File flushed\n");

        // This is to prevent the loop from running too fast and overwhelming the system
        sleep(1);

        // Close the file
        fclose(file);
        printf("file closed\n");
        sleep(1);		//wait 1 sec

    }
    return 0;
}
  
    
  
