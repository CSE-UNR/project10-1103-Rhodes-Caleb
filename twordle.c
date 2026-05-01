// Author: Caleb Rhodes
// Date: 
// Purpose: Project 10

#include <stdio.h>
#include <stdbool.h>

#define INPUT_FILE "word.txt"
#define LETTER_CAP 5
#define MAX_GUESSES 6

int readFile(char solutionStr[]);
void makeLowercase(char str[]);
void promptUser(int tries, char userGuess[]);
int guessLen(char userGuess[]);
bool checkValidLen(char userGuess[]);
bool checkValidIn(char userGuess[]);
void checkGuess(int tries, char solutionStr[], char userGuess[], char guessesAndHints[][LETTER_CAP + 1], int used[]);
void giveHints(int tries, char solutionStr[], char userGuess[], char guessesAndHints[][LETTER_CAP + 1], int used[]);
void dispGuesses(bool win, int tries, char guessesAndHints[][LETTER_CAP + 1]);
bool checkWin(int tries, char guessesAndHints[][LETTER_CAP + 1]);

int main(){
	bool win = false;
	int tries = 0;
	char solutionStr[LETTER_CAP + 1], userGuess[LETTER_CAP + 2], guessesAndHints[MAX_GUESSES * 2][LETTER_CAP + 1];
	int used[LETTER_CAP] = {0, 0, 0, 0, 0};
	
	readFile(solutionStr);
	
	do{
	
	promptUser(tries, userGuess);
	checkGuess(tries, solutionStr, userGuess, guessesAndHints, used);
	giveHints(tries, solutionStr, userGuess, guessesAndHints, used);
	win = checkWin(tries, guessesAndHints);
	dispGuesses(win, tries, guessesAndHints);
	tries++;
	
	} while(tries < MAX_GUESSES && win != true);
	
	if(win && tries == 1){
		printf("================================\n");
		printf("		%s\n", guessesAndHints[0]);
		printf("	You won in %d guess\n", tries);
		printf("		GOATED!\n");
	}
	else if(win){
		printf("================================\n");
		printf("		%s\n", guessesAndHints[(tries - 1) * 2]);
		printf("	You won in %d guess\n", tries);
		printf("		Amazing!\n");
	}
	else{
		printf("================================\n");
		printf("\nYou lost, better luck next time!\n");
	}
	
	return 0;
}

int readFile(char solutionStr[]){
	FILE *inFile = fopen (INPUT_FILE, "r");
	
	if(inFile == NULL){
		printf("An error occured when attempting to open the %s file, goodbye!\n", INPUT_FILE);
		return 0;
	}
	
	fscanf(inFile, "%5s", solutionStr);
	fclose(inFile);
	makeLowercase(solutionStr);
	return 1;
}

void makeLowercase(char str[]){
	for(int i = 0; str[i] != '\0'; i++){
		if(str[i] >= 'A' && str[i] <= 'Z'){
			str[i] = str[i] + 32;
		}
	}
}


void promptUser(int tries, char userGuess[]){
	bool validLen = false;	
	bool validIn = false;
	
	if(tries < LETTER_CAP){
		printf("Guess %d! Enter your guess: ", tries + 1);
		scanf("%s", userGuess);
	}
	if(tries == LETTER_CAP){
		printf("\nFINAL GUESS: ");
		scanf("%s", userGuess);
	}

	validLen = checkValidLen(userGuess);
	validIn = checkValidIn(userGuess);
	
	while(!validLen){
		printf("Your guess must be 5 letters long.\n");
		printf("Please try again: ");
		scanf("%s", userGuess);
		validLen = checkValidLen(userGuess);
	}
	while(!validIn){
	printf("Your guess must contain only letters.\n");
		printf("Please try again: ");
		scanf("%s", userGuess);
		validIn = checkValidIn(userGuess);
	}
	makeLowercase(userGuess);
}

int guessLen(char userGuess[]){
	int length = 0;
	
	for(int i = 0; userGuess[i] != '\0'; i++){
		length++;
	}
	return length;
}

bool checkValidLen(char userGuess[]){
	bool validLen = true;
	int length = guessLen(userGuess);
	
	if(length != LETTER_CAP){
		validLen = false;
	}
	return validLen;
}

bool checkValidIn(char userGuess[]){
	bool validIn = true;
	
	for(int i = 0; userGuess[i] != '\0'; i++){
		if(!((userGuess[i] >= 'a' && userGuess[i] <= 'z') || (userGuess[i] >= 'A' && userGuess[i] <= 'Z'))){
			validIn = false;
		}
	}
	return validIn;
}

void checkGuess(int tries, char solutionStr[], char userGuess[], char guessesAndHints[][LETTER_CAP + 1], int used[]){
	int correctRow = tries * 2;
	
	for(int i = 0; i < LETTER_CAP; i++){
		if(solutionStr[i] == userGuess[i]){
			guessesAndHints[correctRow][i] = userGuess[i] - 32;
			used[i] = 1;
		}
		else{
			guessesAndHints[correctRow][i] = userGuess[i];
		}
	}
	guessesAndHints[correctRow][LETTER_CAP] = '\0';	
}

void giveHints(int tries, char solutionStr[], char userGuess[], char guessesAndHints[][LETTER_CAP + 1], int used[]){
	int correctRow = tries * 2;
	int hintRow = (tries * 2) + 1;
	
	for(int i = 0; i < LETTER_CAP; i++){
		guessesAndHints[hintRow][i] = ' ';
	}
	
	for(int i = 0; guessesAndHints[correctRow][i] != '\0'; i++){
		for(int j = 0; solutionStr[j] != '\0'; j++){
			if(guessesAndHints[correctRow][i] >= 'a' && guessesAndHints[correctRow][i] <= 'z' && guessesAndHints[correctRow][i] == solutionStr[j] && !used[j]){
				guessesAndHints[hintRow][i] = '^';
				used[j] = 1;
				break;
			}
		}
	}
	guessesAndHints[hintRow][LETTER_CAP] = '\0';
}

void dispGuesses(bool win, int tries, char guessesAndHints[][LETTER_CAP + 1]){
	if(win != true){
		printf("================================\n");
		
		for(int rowInd = 0; rowInd <= tries; rowInd++){
			printf("%s\n", guessesAndHints[rowInd * 2]);
			printf("%s\n", guessesAndHints[(rowInd * 2) + 1]);
		}
	}
}
			
	
bool checkWin(int tries, char guessesAndHints[][LETTER_CAP + 1]){
	bool won = true;
	int guessRow = tries * 2;
	
	for(int i = 0; i < LETTER_CAP; i++){
		if(guessesAndHints[guessRow][i] < 'A' || guessesAndHints[guessRow][i] > 'Z'){
			won = false;
		}
	}
	return won;
}
