//SE 185: Final Project Template//
/////////////////////////
/* 
Team xx (please insert your team number instead of xx)
Team member 1 "Drake Rippey" | "25%"
Team member 2 "Alex Shepard" | "25%"
Team member 3 "Sam Packard" | "25%"
Team member 4 "Elmin Didic" | "25%"
*/


////////////////////
#include<stdio.h>//
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<ctype.h>

#define X_SIZE 40
#define Y_SIZE 20

//////////////////////
//Struct Definition//
////////////////////


/////////////////////////////////////
//User Defined Functions Prototype//
//List prototypes here and define//
//them below the main function////
/////////////////////////////////

void generateWord(int j, char word[15]);
int numWords(int minLetters);
void WordAdder();
void addWordToBoard(char list[Y_SIZE][15], int offsets[Y_SIZE], int minLetters);
void printBoard(char list[Y_SIZE][15], int offsets[Y_SIZE]);

int main(){

  
	srand((int)time(0));
	char newWord[15];
	int wordLength, startTime_Game, endTime_Game, startTime_Entry, endTime_Entry;
	int wordsDisplayed = 0, gameTotalTime, entryTotalTime;
  char input[20];
  int endgame = 0;
	
  char textFile[20] = "wordList.txt";

	// opening statement
	printf("Hello, this is a typing game. You will need to type the words as they appear\n");
	printf("Would you like to [p]lay or add a [w]ord?\n");
	printf("You currently have %d words that can be used. (p/w)\n", numWords(0));
	scanf("%s", input);
	
	//checks the users start key
	while (strcmp(input, "p") != 0) {
		WordAdder();
		printf("There are now %d words. Would you like to play or add another word? (p/w)\n", numWords(0));
		scanf("%s", input);
	}
	
	//ask for minimum word length;
	printf("What would you like your minimum word length to be?");
	scanf("%d", &wordLength);
	

  //Setting up the board
	int offsets[Y_SIZE + 1];
	char words[Y_SIZE + 1][15];
	
	for (int i = 0; i < Y_SIZE; i++) {
		offsets[i] = 0;
		strcpy(words[i], "");
	}
	
  //starts timer for whole game
	startTime_Game = time(0);

  //makes sure the game starts with a word on the board
	addWordToBoard(words, offsets, wordLength);

  //Game loop
	while(strcmp(input, "FORCE_EXIT") != 0 && endgame == 0) {
		// this section will generate new words based on how long it took the user to enter the previous word
		// also as the game progresses will display words at a faster rate
		if (wordsDisplayed < 15) {
			for (int i = 0; i < entryTotalTime; i = i + 3) {
        if (strcmp(words[Y_SIZE - 1], "") != 0) endgame = 1;
				addWordToBoard(words, offsets, wordLength);
				++wordsDisplayed;
			}
		} else if (wordsDisplayed < 30) {
			for (int i = 0; i < entryTotalTime; i = i + 2) {
        if (strcmp(words[Y_SIZE - 1], "") != 0) endgame = 1;
				addWordToBoard(words, offsets, wordLength);
				++wordsDisplayed;
			}
		} else {
			for (int i = 0; i < entryTotalTime; ++i) {
        if (strcmp(words[Y_SIZE - 1], "") != 0) endgame = 1;
				addWordToBoard(words, offsets, wordLength);
				++wordsDisplayed;
			}
		}
    // Make the arrays one item longer, don't display it but have it be the "you lost" row...? if it ever fills up then you're done

    if (endgame == 1) break;
		printBoard(words, offsets);
		
		startTime_Entry = time(0);    // starts timer for user entry
		scanf("%s", input);
		endTime_Entry = time(0);      // ends timer for user entry
		entryTotalTime = endTime_Entry - startTime_Entry;



    //Checks if the user input matches any existing words on the board
    //"Deletes" word if typed correctly
    for (int i = Y_SIZE - 1; i >= 0; i--) {
			if (strcmp(input, words[i]) == 0) {
				strcpy(words[i], "");
				break; //Ensures the farthest down instance of the word is deleted if the word appears multiple times
			}
		}
    
   

	}

  //ends timer for whole game
	endTime_Game = time(0);
	gameTotalTime = endTime_Game - startTime_Game;
	
	//displays how long the game took
	printf("This game took you %d minutes and %d seconds", (gameTotalTime / 60), gameTotalTime - ((gameTotalTime / 60)*60));
	
	return 0;
}

///////////////////////////////////////
//User Defined Functions' Definition//
/////////////////////////////////////

void addWordToBoard(char list[Y_SIZE][15], int offsets[Y_SIZE], int minLetters) {
	// Shift everything down one line first to open the top line for a new word
	for (int i = Y_SIZE - 1; i > 0; i--) {
		strcpy(list[i], list[i - 1]);
		offsets[i] = offsets[i - 1];

    
	}

  // Creates new word and adds it to the board
	char wordToAdd[15];
	generateWord((rand() % numWords(0)), wordToAdd);
	
  //makes sure the word is above the minimum amount of letters
  if (strlen(wordToAdd) < minLetters) {
		generateWord((rand() % numWords(0)), wordToAdd);
	}

	strcpy(list[0], wordToAdd);
	offsets[0] = rand() % (X_SIZE - strlen(list[0]) + 1);
}

void printBoard(char list[Y_SIZE][15], int offsets[Y_SIZE]) {
  system("clear");
	for (int i = 0; i < Y_SIZE; i++) {
		// Creates a temporary string for an entire line of the board
		char line[X_SIZE + 2] = "|";
		int length = strlen(list[i]);
		
		// Adds spaces up until the words "x" position
		for (int j = 0; j < offsets[i]; j++) strcat(line, " ");
    // Adds the word
		strcat(line, list[i]);
		// Fills in spaces after until X_SIZE is reached
		for (int j = offsets[i] + length; j < X_SIZE; j++) strcat(line, " ");
		// Closes off the line, then prints
		strcat(line, "|");

		printf("%s\n", line);
	}
}

void generateWord(int j, char word[15]) {
	FILE* wordList = NULL;
	
	
	wordList = fopen("wordList.txt", "r");
	if (wordList == NULL) {
		printf("Could not open file wordList.txt");
	}
	
	for (int i = 0; i <= j; ++i) {
		fscanf(wordList, "%s", word);
	}
	fclose(wordList);
	
}

int numWords(int minLetters) {
	FILE* wordList = NULL;
	char word[15];
	int numWords = 0;
	
	wordList = fopen("wordList.txt", "r");
	if (wordList == NULL) {
		printf("Could not open file wordList.txt");
	}
	
	while (!feof(wordList)) {
		fscanf(wordList, "%s", word);
		if (strlen(word) >= minLetters) {
			++numWords;
    }
	}
	fclose(wordList);
	
	return numWords;
}

void WordAdder() 
{
     //User input char Array
    char userInput[100];
    
    //Creating a file pointer called "fPointer"
    FILE * fPointer;
    //Creating if not made it will make a file
    fPointer = fopen("wordList.txt", "a");
    
    //Asking the user to enter a word and setting it to "userInput"
    printf("Enter in a word to add\n");
    scanf("%s", userInput);
    
    //Adding Text to a line in the file and addinga new line
    fprintf(fPointer, "%s\n", userInput);
   
   
    
    //Closing File Pointer 
    fclose(fPointer);
}