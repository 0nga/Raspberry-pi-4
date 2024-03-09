
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <bcm2835.h>

/*
int main() {
    FILE *htmlFile;

    for(;;){
        
    // Open the HTML file in write mode
    htmlFile = fopen("index.html", "w");

    // Check if file was opened successfully
    if (htmlFile == NULL) {
        printf("Unable to create file.\n");
        return 1;
    }

    // Write HTML content into the file
    fprintf(htmlFile, "<!DOCTYPE html>\n");
    fprintf(htmlFile, "<html>\n");
    fprintf(htmlFile, "<head>\n");
    fprintf(htmlFile, "<title>Meteo Station</title>\n");
    fprintf(htmlFile, "</head>\n");
    fprintf(htmlFile, "<body>\n");
    
        int temperature = rand()%10;
        int humidity = rand()%10;
        int lux = rand()%10;
 

        // Print variable values into the HTML
        fprintf(htmlFile, "<h1>Variable Values</h1>\n");
        fprintf(htmlFile, "<p>Temperature: %d C</p>\n", temperature);
        fprintf(htmlFile, "<p>Humidity: %d</p>\n", humidity);
        fprintf(htmlFile, "<p>Lux: %d</p>\n", lux);

        // Close the HTML file
        fprintf(htmlFile, "</body>\n");
        fprintf(htmlFile, "</html>\n");
        fclose(htmlFile);
        bcm2835_delay(1000); //1 second delay
    }

    printf("HTML file generated successfully.\n");

    return 0;
}*/



#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h> // Include the header file for sleep()


int main() {
    
    FILE *file;
    char *filename = "./data.txt";
    
    // Attempt to delete the existing file
    if (remove(filename) != 0) {
        perror("Error deleting the file");
    } else {
        printf("File deleted successfully\n");
    }

    while (1) {
        
        // Open the file in "w" mode 
        file = fopen(filename, "w");
        if (file == NULL) {
            fprintf(stderr, "Error opening file.\n");
            exit(1);
        }

        // Continuously write to the file
    
        int temperature = rand()%10;

        // Write formatted time to the file
        fprintf(file, "Temperature: %d C", temperature);

        // Flush the output buffer to ensure the data is written to the file immediately
        fflush(file);

        // Sleep for 1 second (optional)
        // This is to prevent the loop from running too fast and overwhelming the system
        // You can adjust this value based on your requirement
        sleep(2);
    

        // Close the file
        fclose(file);
    }
    return 0;
}

