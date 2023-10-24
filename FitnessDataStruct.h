#ifndef FITNESSDATASTRUCT_H
#define FITNESSDATASTRUCT_H
#include <stdlib.h>
#include <stdio.h>

// Define an appropriate struct
typedef struct {
	char date[11];
	char time[6];
	int steps;
} FITNESS_DATA;

#endif