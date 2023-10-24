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
FITNESS_DATA listoffitnessdata[60];
char testdate[20];
char testtime[20];
char teststeps[20];

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
        //printf("%s", token);
        strcpy(date, token);
    }
    
    token = strtok(NULL, delimiter);
    if (token != NULL) 
    {
        //printf("%s", token);
        strcpy(time, token);
    }
    
    token = strtok(NULL, delimiter);
    if (token != NULL) 
    {  
        //printf("%s", token);
        strcpy(steps, token);
    }
    
    // Free the duplicated string
    free(inputCopy);

}

// Complete the main function
int main() 
{
    char *filename = "FitnessData_2023.csv";
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        perror("");
        return 1;
    }
    int buffer_size = 100;
    char line_buffer[buffer_size];

    int linecount = 0; //i added this
    char* test;
    

    while (fgets(line_buffer, buffer_size, file) != NULL)
    {
        tokeniseRecord(line_buffer, ",", testdate, testtime, teststeps);
        //listoffitnessdata[linecount].date = testdate;
        //listoffitnessdata[linecount].time = testtime;
        //listoffitnessdata[linecount].steps = int(teststeps);
        printf("%s", line_buffer);
        printf("%s/%s/%s",testdate, testtime, teststeps);


        linecount = linecount + 1; //needs slight fix
    }

    printf("Number of records in file %i\n", (linecount+1));

    fclose(file);
    return 0;


}
