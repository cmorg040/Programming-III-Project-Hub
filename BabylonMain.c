/*=============================================================================
 |   Source code:  babylonMain.c
 |        Author:  Carrel Morgan
 |    Student ID:  3759826
 |    Assignment:  Program #2
 |
 |            Course:  COP 4338
 |           Section:  U05
 |        Instructor:  William Feild
 |        Due Date:  02/12/2019, at the beginning of class
 |
 |	I hereby certify that this collective work is my own
 |	and none of it is the work of any other person or entity.
 |	______________________________________ [Signature]
 |
 |        Language:  C
 |  Compile/Run:  Unzip all files.
 |				- type: gcc -o Babel BabylonMain.c -lm
 |				- type: ./Babel
 |
 |  +-----------------------------------------------------------------------------
 |
 |  Description:  Finds all the perfect numbers within a given interval.
 |				  It then lists those perfect numbers and their factors.
 |				  Finally, the program computes the square root of each
 |				  perfect number using the Babylonian method.
 |
 |
 |
 |
 |        Input:  User inputs the precision to which the square root will be calculated.
 |
 |
 |
 |       Output:  The program should output a list of perfect numbers, their factors,
 |				  and their square root.
 |
 |     Process:
 |				1. Accept and validate user input.
 |				2. Check each number in the given range for perfection.
 |				3. Compute factors of each perfect number and print them.
 |				4. Compute Babylonian Square root of each function and print.
 |
 |
 |
 |
 |
 |
 |   Required Features Not Included:
 |                All features should be included.
 |
 |
 |
 |
 |
 |
 |   Known Bugs:  Program loses accuracy at 15th digit of precision.
 |				  Estimation values converge after about 10 iterations,
 |				  making further precision impossible. Can't find a solution.
 |  *===========================================================================*/

#include <stdio.h>	//for standard input output like scanf and printf.
#include <stdlib.h> //for standard C library functions.
#include <stdbool.h>//for testing perfect nums with booleans.
#include <math.h>	//included for testing Babylonian roots against actual sqrt value.

int getValidInput();
void computeAndPrintData(int userPrecision);
bool isPerfect(int potentialPerfect);
void printFactorsAndSum(int perfectNum);
long double convertPrecision(int userInput);
void computeAndPrintBabel(long double perfNum, int userPrecision);
void printErrorMessage(int errorCode);

#define INPUT_MIN 1
#define INPUT_MAX 15

#define PERFECT_RANGE_MIN 0
#define PERFECT_RANGE_MAX 10000

#define VALIDATION_FAILURE 01
#define PROGRAM_SUCCESS 11

#define EXPONENTIATION_CONSTANT 10

int main(void)
{
	int userPrecision = 0;
	userPrecision = getValidInput();

	if (userPrecision == VALIDATION_FAILURE)
		{
			printErrorMessage(VALIDATION_FAILURE);
			return VALIDATION_FAILURE;
		}
	else
		{
			printf("Input successfully validated. User input: %d\n",
					userPrecision);
		}

	computeAndPrintData(userPrecision);
	return PROGRAM_SUCCESS;
}

/*---------------------------- getValidInput ---------------------
 |  Function: getValidInput
 |
 |  Purpose:  Takes and validates user input.
 |
 |  @param  none
 |
 |  @return  returns valid user input as an integer.
 *----------------------------------------------------------*/
//FIXME: Try using getline() for input and validate with atoi for better validation)
int getValidInput()
{
	int input = 0;

	printf("Please input an integer between %d-%d: ", INPUT_MIN, INPUT_MAX);

	if (scanf("%d", &input) != 1)
		{
			return VALIDATION_FAILURE;
		}
	if (INPUT_MIN > input || INPUT_MAX < input)
		{
			return VALIDATION_FAILURE;
		}
	else
		{
			return input;
		}

}

/*---------------------------- printPerfects ---------------------
 |  Function: printPerfects
 |
 |  Purpose:  Prints perfect numbers in given range.
 |
 |  @param  userPrecision: Integer input received from user.
 |
 |  @return  none
 *----------------------------------------------------------*/
void computeAndPrintData(int userPrecision)
{
	int potentialPerfect = 0;

	for (potentialPerfect = 1; potentialPerfect <= PERFECT_RANGE_MAX;
			potentialPerfect++)
		{
			if (isPerfect(potentialPerfect))
				{
					printFactorsAndSum(potentialPerfect);
					computeAndPrintBabel(potentialPerfect, userPrecision);
				}
		}
}

/*---------------------------- isPerfect ---------------------
 |  Function: isPerfect
 |
 |  Purpose:  Checks if an integer is a perfect number.
 |
 |  @param  input: A number to be checked for perfection.
 |
 |  @return  returns true if inputis perfect, false otherwise.
 *----------------------------------------------------------*/
bool isPerfect(int potentialPerfect)
{
	int factorSum = 0;
	int potentialFactor = 0;

	for (potentialFactor = 1; potentialFactor <= (potentialPerfect / 2);
			potentialFactor++)
		{
			if (0 == (potentialPerfect % potentialFactor))
				{
					factorSum += potentialFactor;
				}
		}

	if (factorSum == potentialPerfect)
		{
			return true;
		}
	return false;
}

/*---------------------------- printFactorsAndSum ---------------------
 |  Function: printFactorsAndSum
 |
 |  Purpose:  Calculates factors of input and prints them, along with the input.
 |
 |  @param  perfectNum: The perfect number to be factored.
 |
 |  @return  none
 *----------------------------------------------------------*/
void printFactorsAndSum(int perfectNum)
{
	//Print the perfect number(the sum) and it's first factor(which is always 1)
	printf("\n%d = 1", perfectNum);

	int potentialFactor = 0;

	//Initializing at 2 because 1 is already printed as a factor.
	for (potentialFactor = 2; potentialFactor <= (perfectNum / 2);
			potentialFactor++)
		{
			if (0 == (perfectNum % potentialFactor))
				{
					printf(" + %d", potentialFactor);
				}
		}
}

/*---------------------------- convertPrecision ---------------------
 |  Function: convertPrecision
 |
 |  Purpose:  converts user input to decimal precision.
 |
 |  @param  userInput the users integer input for precision.
 |
 |  @return  decimalPrecision: The precision converted to a decimal value.
 *----------------------------------------------------------*/
long double convertPrecision(int userInput)
{
	long double decimalPrecision = 1.0; //Initialize to 1 to avoid div by 0
	int divCounter = 0;

	for (divCounter = 0; divCounter < userInput; divCounter++)
		{
			decimalPrecision = (decimalPrecision / EXPONENTIATION_CONSTANT);
		}

	return decimalPrecision;
}

/*---------------------------- computeBabel ---------------------
 |  Function: computeBabel
 |
 |  Purpose:  computes the square root of the input via the Babylonian method.
 |
 |	Formula: Sqrt(number) = Estimate[n+1] = 1/2(Estimate[n] + Number / Estimate)
 |
 |	Source: https://en.wikipedia.org/wiki/Methods_of_computing_square_roots#Babylonian_method
 |
 |  @param  long double perfectNum
 |			int userPrecision
 |
 |  @return  none
 *----------------------------------------------------------*/
void computeAndPrintBabel(long double perfNum, int userPrecision)
{
	int iterationCounter = 0;
	long double estimate = perfNum / 2.0; //Initial guess is set to half of the input.
	long double nextEstimate = 1.0;
	long double difference = estimate - nextEstimate;
	long double errorMargin = convertPrecision(userPrecision);

	while (difference > errorMargin)
		{
			nextEstimate = (estimate + perfNum / estimate) / (long double) 2.0;
			difference = estimate - nextEstimate;
			estimate = nextEstimate;
			iterationCounter++;

		}

	//print results
	printf("\nBabylonian Root:    %.*Lf\n", userPrecision, estimate);
	printf("Actual square root: %.*Lf\n", userPrecision, sqrtl(perfNum));
	printf("Iterations to compute: %d\n\n", iterationCounter);
}

/*---------------------------- printErrorMessage ---------------------
 |  Function: printErrorMessage
 |
 |  Purpose: Prints an appropriate error message based on the input error code.
 |
 |  @param  errorCode: The failure code returned by a function upon failure.
 |
 |  @return  none
 *----------------------------------------------------------*/

void printErrorMessage(int errorCode)
{
	if (errorCode == VALIDATION_FAILURE)
		{
			printf("Invalid input. Please input an integer between: %d - %d\n",
			INPUT_MIN, INPUT_MAX);
		}

	printf("Terminating Program.\n");
}
