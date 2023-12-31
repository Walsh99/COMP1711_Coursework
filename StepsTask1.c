#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define an appropriate struct
typedef struct {
	char date[11];
	char time[6];
	int steps;
} FITNESS_DATA;

// Define any additional variables here

//create an array of type FITNESS_DATA to store the records
FITNESS_DATA listoffitnessdata[500]; //given up to 500 records

//create temp variables to then move into the typedef array
char tempdate[11]; //using typedef
char temptime[6]; //using typedef
char tempsteps[4]; //should not pass 9999 steps

int linecount = 0; //to count number of lines/records in the csv  


// This is your helper function. Do not change it in any way.
// Inputs: character array representing a row; the delimiter character
// Ouputs: date character array; time character array; steps character array
void tokeniseRecord(const char *input, const char *delimiter,
                    char *date, char *time, char *steps) {
    // Create a copy of the input string as strtok modifies the string
    char *inputCopy = strdup(input);
    
    // Tokenize the copied string
    char *token = strtok(inputCopy, delimiter);
    if (token != NULL) 
    {
        strcpy(date, token);
    }
    
    token = strtok(NULL, delimiter);
    if (token != NULL) 
    {
        strcpy(time, token);
    }
    
    token = strtok(NULL, delimiter);
    if (token != NULL) 
    {  
        strcpy(steps, token);
    }
    
    // Free the duplicated string
    free(inputCopy);

}

// Complete the main function
int main() 
{
    //Open file
    char *filename = "FitnessData_2023.csv";
    FILE *file = fopen(filename, "r"); //to read
    if (file == NULL)
    {
        perror("");
        return 1;
    }
    int buffer_size = 500; //allow up to 500 lines
    char line_buffer[buffer_size];

    while (fgets(line_buffer, buffer_size, file) != NULL) //loop through the csv record by record
    {
        tokeniseRecord(line_buffer, ",", tempdate, temptime, tempsteps); //use the tokeniseRecord to 
        //copy all the temporary data from the cycle to the array of fitness_data
        strcpy(listoffitnessdata[linecount].date ,tempdate);
        strcpy(listoffitnessdata[linecount].time, temptime);
        listoffitnessdata[linecount].steps = atoi(tempsteps); //had to use atoi to convert the str to int
        
        linecount = linecount + 1; 
    }

    printf("Number of records in file: %i\n", (linecount)); //output number of records
    
    for (int i = 0; i < 3; i++) //get the first 3 records using the typedef array
    {
        printf("%s/%s/%d\n",listoffitnessdata[i].date, listoffitnessdata[i].time, listoffitnessdata[i].steps);
    }    

    fclose(file); //close the file
    return 0;
}
