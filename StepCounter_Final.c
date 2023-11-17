#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FitnessDataStruct.h"

// Struct moved to header file

// Define any additional variables here
// Global variables for filename and FITNESS_DATA array
FITNESS_DATA listoffitnessdata[500]; //given up to 500 records
char line[buffer_size];
char filename[buffer_size];

//create temp variables to then move into the typedef array
char tempdate[11]; //using typedef
char temptime[6]; //using typedef
char tempsteps[4]; //should not pass 9999 steps

// This is your helper function. Do not change it in any way.
// Inputs: character array representing a row; the delimiter character
// Ouputs: date character array; time character array; steps character array
void tokeniseRecord(const char *input, const char *delimiter,
                    char *date, char *time, char *steps) {
    // Create a copy of the input string as strtok modifies the string
    char *inputCopy = strdup(input);
    
    // Tokenize the copied string
    char *token = strtok(inputCopy, delimiter);
    if (token != NULL) {        strcpy(date, token);
    }
    
    token = strtok(NULL, delimiter);
    if (token != NULL) {
        strcpy(time, token);
    }
    
    token = strtok(NULL, delimiter);
    if (token != NULL) {
        strcpy(steps, token);
    }
    
    // Free the duplicated string
    free(inputCopy);

                    }




// Complete the main function
int main() 
{
    // array of daily readings
    //reading daily_readings[100];

    char choice;
    int counter = 0;
    float mean = 0;

    while (1)
    {
        printf("A: Specify filename to be imported\n"); 
        printf("B: Display the total number of records in the file\n"); 
        printf("C: Find the date and time of the timeslot with the fewest steps\n");  
        printf("D: Find the data and time of the timeslot with the largest number of steps\n");   
        printf("E: Find the mean step count of all the records in the file\n");       
        printf("F: Find the longest continuous period where the step count is above 500 steps\n"); 
        printf("Q: Quit Program\n"); 

        // get the next character typed in and store in the 'choice'
        choice = getchar();

        // this gets rid of the newline character which the user will enter
        // as otherwise this will stay in the stdin and be read next time
        while (getchar() != '\n');


        // switch statement to control the menu.
        switch (choice)
        {
        // this allows for either capital or lower case
        case 'A':
        case 'a':
            // get filename from the user
            printf("Please enter the name of the data file: ");

            // these lines read in a line from the stdin (where the user types)
            // and then takes the actual string out of it
            // this removes any spaces or newlines.
            fgets(line, buffer_size, stdin);
            sscanf(line, " %s ", filename);

            FILE *input = fopen(filename, "r");
            if (!input)
            {
                printf("Error: File could not be opened\n");
                return 1;
            }
            break;

        case 'B':
        case 'b':
            counter = 0;
            while (fgets(line, buffer_size, input))
            {
                counter++;
            }
            printf("Total Records: %d\n", counter);
            fclose(input);
            break;

        case 'C':
        case 'c':
            counter = 0;
            FITNESS_DATA lowest_steps = {"2000-01-01", "00:00", 9999};
            while (fgets(line, buffer_size, input))
            {
                tokeniseRecord(line, ",", tempdate, temptime, tempsteps); //use the tokeniseRecord to 
                //copy all the temporary data from the cycle to the array of fitness_data
                strcpy(listoffitnessdata[counter].date ,tempdate);
                strcpy(listoffitnessdata[counter].time, temptime);
                listoffitnessdata[counter].steps = atoi(tempsteps); //had to use atoi to convert the str to int
                if (listoffitnessdata[counter].steps < lowest_steps.steps)
                {
                    lowest_steps = listoffitnessdata[counter];
                }
                
                counter++;
            }
            printf("%s/%s/%d\n", lowest_steps.date,lowest_steps.time,lowest_steps.steps);
            fclose(input);
            break;

        case 'D':
        case 'd':
            counter = 0;
            FITNESS_DATA highest_steps = {"2000-01-01", "00:00", -1};
            while (fgets(line, buffer_size, input))
            {
                tokeniseRecord(line, ",", tempdate, temptime, tempsteps); //use the tokeniseRecord to 
                //copy all the temporary data from the cycle to the array of fitness_data
                strcpy(listoffitnessdata[counter].date ,tempdate);
                strcpy(listoffitnessdata[counter].time, temptime);
                listoffitnessdata[counter].steps = atoi(tempsteps); //had to use atoi to convert the str to int
                if (listoffitnessdata[counter].steps > highest_steps.steps)
                {
                    highest_steps = listoffitnessdata[counter];
                }
                
                counter++;
            }
            printf("%s/%s/%d\n", highest_steps.date,highest_steps.time,highest_steps.steps);
            fclose(input);
            break;

        case 'E':
        case 'e':
            counter = 0;
            int total_steps = 0;
            int mean_steps = 0;
            while (fgets(line, buffer_size, input))
            {   
                tokeniseRecord(line, ",", tempdate, temptime, tempsteps);                
                total_steps += atoi(tempsteps); //had to use atoi to convert the str to int
                counter++;
            }
            mean_steps = total_steps / counter;
            printf("%d\n", mean_steps);
            fclose(input);       
            break;

        case 'F':
        case 'f':
            return 0;
            break;

        case 'Q': //quit function
        case 'q':
            return 0;
            break;

        // if they type anything else:
        default:
            printf("Invalid choice\n");
            break;    
        }
    }
}









