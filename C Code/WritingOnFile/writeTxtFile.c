
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <bcm2835.h>

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
}


/*
 * #include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    FILE *file_pointer;
	int randValue = rand()%10;
    // Open file in write mode
    file_pointer = fopen("data.txt", "w");

    // Check if file opened successfully
    if (file_pointer == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    // Write content to the file
    fprintf(file_pointer, "%d", randValue);

    // Close the file
    fclose(file_pointer);

    printf("Content written to file successfully!\n");

    return 0;
}*/
