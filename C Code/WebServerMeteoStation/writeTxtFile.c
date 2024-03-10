#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h> // Include the header file for sleep()
	
int main() {
    
    FILE *file;
    char *filename = "./data.txt";
    int sensorReading = 0;

    for(;;){
	sensorReading=rand()%10000;
	
	// Attempt to delete the existing file
	if (remove(filename) != 0) {
		perror("Error deleting the file");
	}
	else {
		printf("File deleted successfully\n");
	}
        
        // Open the file in "w" mode (override file content)
        file = fopen(filename, "w");
        
        if (file == NULL) {
            printf("Error opening file\n");
            exit(1);
        }
	else{
	    printf("File opened correctly\n");
	}

		
	
	fprintf(file, "Sensor Value: %d\n", sensorReading);
	printf("Sensor Value: %d\n", sensorReading);
	
        
        // Flush the output buffer to ensure the data is written to the file immediately
        fflush(file);
        printf("File flushed\n");

        // This is to prevent the loop from running too fast and overwhelming the system
        // You can adjust this value based on your requirement
        sleep(1);

        // Close the file
        fclose(file);
        printf("file closed\n");
        sleep(1);		//wait 1 sec

    }
    return 0;
}
  
    
  
