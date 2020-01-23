#include<stdio.h>
#include<stdlib.h>

const int MAX_DATA_STACK_HEIGHT = 23;
const int MAX_CODE_LENGTH = 500;
const int MAX_LEXI_LEVELS = 3;

typedef struct command
{
    int op;
    int l;
    int m;
} command;

command** fillCommandStack(char* filename)
{
    FILE* inputFile;
    int op, l, m, i = 0;

    if (filename == NULL)
        return NULL;

    inputFile = fopen(filename, "r");

    if (inputFile == NULL)
        return NULL;

    command** commandsArray = calloc(MAX_CODE_LENGTH, sizeof(command*));

    while (fscanf(inputFile, "%d %d %d", &op, &l, &m) != EOF)
    {
        commandsArray[i] = malloc(sizeof(command*));
        commandsArray[i]->op = op;
        commandsArray[i]->l = l;
        commandsArray[i]->m = m;
        i++;
    }

    return commandsArray;
}

void printCommands(command** commandsArray)
{
    int i;

    for(i = 0; i < MAX_CODE_LENGTH; i++)
        if (commandsArray[i] == NULL)
            break;
        else printf("%p --> %d %d %d\n", commandsArray[i], commandsArray[i]->op, commandsArray[i]->l, commandsArray[i]->m);

    return;
}


void printStack(int* data_stack)
{
	int i = 0;

	for (i = MAX_DATA_STACK_HEIGHT; i >= 0; i--)
	{
		printf("%d", data_stack[i]);
	}
}

// Adds the literal M to the top of the stack 
void LIT(int m, int* bp, int* gp, int* sp, int* data_stack)
{
	if (bp == 0)
	{
		gp = gp - 1;
		data_stack[*gp] = m;
	}
	else
	{
		sp = sp - 1;
		data_stack[*sp] = m;
	}
}

// Performs the OPR OP code
void OPR(int m, int* bp, int* sp, int* pc, int* data_stack)
{
	// Switch cases based off the arithmatic modifier
	switch(m)
	{
		// RET
		case 0:
			*sp = *bp + 1;
			*bp = data_stack[*sp - 3];
			*pc = data_stack[*sp - 4];
			break;
		// NEG
		case 1:
			data_stack[*sp] = data_stack[*sp] * -1;
			break;
		// ADD
		case 2:
			*sp -= 1;
			data_stack[*sp] += data_stack[*sp + 1];
			break;
		// SUB
		case 3:
			*sp -= 1;
			data_stack[*sp] -= data_stack[*sp + 1];
			break;
		// MUL
		case 4:
			*sp -= 1;
			data_stack[*sp] *= data_stack[*sp + 1];
			break;
		// DIV
		case 5:
			*sp -= 1;
			data_stack[*sp] /= data_stack[*sp + 1];
			break;
		// ODD
		case 6:
			if (data_stack[*sp] % 2 == 1)
			{
				data_stack[*sp] = 1;
			}
			else
			{
				data_stack[*sp] = 0;
			}
			break;
		// MOD
		case 7:
			*sp -= 1;
			data_stack[*sp] %= data_stack[*sp + 1];
			break;
		// EQL
		case 8:
			*sp -= 1;
			if (data_stack[*sp] == data_stack[*sp - 1])
			{
				data_stack[*sp] = 1;
			}
			else
			{
				data_stack[*sp] = 0;
			}
			break;
		// NEQ
		case 9:
			*sp -= 1;
			if (data_stack[*sp] != data_stack[*sp - 1])
			{
				data_stack[*sp] = 1;
			}
			else
			{
				data_stack[*sp] = 0;
			}
			break;
		// LSS
		case 10:
			*sp -= 1;
			if (data_stack[*sp] < data_stack[*sp - 1])
			{
				data_stack[*sp] = 1;
			}
			else
			{
				data_stack[*sp] = 0;
			}
			break;
		// LEQ
		case 11:
			*sp -= 1;
			if (data_stack[*sp] <= data_stack[*sp - 1])
			{
				data_stack[*sp] = 1;
			}
			else
			{
				data_stack[*sp] = 0;
			}
			break;
		// GTR
		case 12:
			*sp -= 1;
			if (data_stack[*sp] > data_stack[*sp - 1])
			{
				data_stack[*sp] = 1;
			}
			else
			{
				data_stack[*sp] = 0;
			}
			break;
		// GEQ
		case 13:
			*sp -= 1;
			if (data_stack[*sp] >= data_stack[*sp - 1])
			{
				data_stack[*sp] = 1;
			}
			else
			{
				data_stack[*sp] = 0;
			}
			break;
	}

	/* Logical operations are set to 1 if true, 0 otherwise */
}

void LOD(int l, int m, int* bp, int* gp, int* sp, int* data_stack)
{
	
}

void STO(int l, int m, int* bp, int* gp, int* sp, int* data_stack)
{

}

void CAL(int l, int m, int* bp, int* gp, int* sp, int* data_stack)
{

}

void INC(int m, int* bp, int* gp, int* sp)
{

}

void JMP(int m, int* pc)
{

}

void SIO(int m, int* sp, int* HALT, int* data_stack)
{
	int i = 0;

	switch(m)
	{
		case 1: /* Print the stack */
			printf("%d", data_stack[*sp]);
			*sp += 1;
			break;
		case 2: /* Read in the stack */
			break;
		case 3: /* HALT */
			*HALT = 1;
			break;
	}
}

int main() /*READ IN VALUES FROM SOME FILE*/
{
	/* Initialze our values */
	int sp = MAX_DATA_STACK_HEIGHT;
	int bp = 0, pc = 0, ir = 0, gp = -1, i = 0, HALT = 0;
	int* data_stack = malloc(sizeof(int*) * MAX_DATA_STACK_HEIGHT); /* Is max data stack height the correct size for this?*/

	for (i = MAX_DATA_STACK_HEIGHT; i >= 0; i--)
	{
		data_stack[i] = 2; // Initialize to !0 for testing purposes
	}

	while (HALT == 0)
	{

		LIT(3, &bp, &gp, &sp, data_stack);
		//LIT(4, &bp, &gp, &sp, data_stack);
		OPR(2, &bp ,&sp, &pc, data_stack);
		printStack(data_stack);
		SIO(3, &sp, &HALT, data_stack);
	}
	/*End initialization*/
}
