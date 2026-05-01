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
bool checkValid(char userGuess[]);
void checkGuess(int tries, char solutionStr[], char userGuess[], char guessesAndHints[][LETTER_CAP + 1]);
void giveHints(int tries, char solutionStr[], char userGuess[], char guessesAndHints[][LETTER_CAP + 1]);
void dispGuesses(bool win, int tries, char guessesAndHints[][LETTER_CAP + 1]);
bool checkWin(int tries, char guessesAndHints[][LETTER_CAP + 1]);

int main(){
	bool win = false;
	int tries = 0;
	char solutionStr[LETTER_CAP + 1], userGuess[LETTER_CAP + 2], guessesAndHints[MAX_GUESSES * 2][LETTER_CAP + 1];
	
	readFile(solutionStr);
	
	do{
	
	promptUser(tries, userGuess);
	checkGuess(tries, solutionStr, userGuess, guessesAndHints);
	giveHints(tries, solutionStr, userGuess, guessesAndHints);
	win = checkWin(tries, guessesAndHints);
	dispGuesses(win, tries, guessesAndHints);
	//win = checkWin(tries, guessesAndHints);
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
	bool validGuess = false;	
	
	if(tries < LETTER_CAP){
		printf("Guess %d! Enter your guess: ", tries + 1);
		scanf("%s", userGuess);
	}
	if(tries == LETTER_CAP){
		printf("\nFINAL GUESS: ");
		scanf("%s", userGuess);
	}
	validGuess = checkValid(userGuess);
	
	while(!validGuess){
		printf("Your guess must be 5 letters long.\n");
		printf("Please try again: ");
		scanf("%s", userGuess);
		validGuess = checkValid(userGuess);
	}
	makeLowercase(userGuess);
}

int guessLen(char userGuess[]){
	int length = 0;
	
	for(int i = 0; userGuess[i] != '\0'; i++){
		if ((userGuess[i] >= 'a' && userGuess[i] <= 'z') || (userGuess[i] >= 'A' && userGuess[i] <= 'Z')){
			length++;
	}
	}
	return length;
}

bool checkValid(char userGuess[]){
	int length = guessLen(userGuess);
	
	if(length != LETTER_CAP){
		return false;
	}
	return true;
}
void checkGuess(int tries, char solutionStr[], char userGuess[], char guessesAndHints[][LETTER_CAP + 1]){
	int correctRow = tries * 2;
	
	for(int i = 0; i < LETTER_CAP; i++){
		if(solutionStr[i] == userGuess[i]){
			guessesAndHints[correctRow][i] = userGuess[i] - 32;
		}
		else{
			guessesAndHints[correctRow][i] = userGuess[i];
		}
	}
	guessesAndHints[correctRow][LETTER_CAP] = '\0';	
}

void giveHints(int tries, char solutionStr[], char userGuess[], char guessesAndHints[][LETTER_CAP + 1]){
	int correctRow = tries * 2;
	int hintRow = (tries * 2) + 1;
	
	for(int i = 0; i < LETTER_CAP; i++){
		guessesAndHints[hintRow][i] = ' ';
	}
	
	for(int i = 0; guessesAndHints[correctRow][i] != '\0'; i++){
		for(int j = 0; solutionStr[j] != '\0'; j++){
			if(guessesAndHints[correctRow][i] >= 'a' && guessesAndHints[correctRow][i] <= 'z' && guessesAndHints[correctRow][i] == solutionStr[j]){
				guessesAndHints[hintRow][i] = '^';
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
