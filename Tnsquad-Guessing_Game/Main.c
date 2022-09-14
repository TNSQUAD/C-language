#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

#define MAX_WORDS 10
#define MAX_WORD_LENGTH 80
#define MAX_ATTEMPTS 5

int ChooseCategory();
char* PickWordFromSelectedCategory(char table[MAX_WORDS][MAX_WORD_LENGTH]);
void InitializeRandomlySelectedWord(char selectedWord[], char hiddenWord[]);
int EvaluateGuess(char playerGuess, char selectedWord[], char hiddenWord[]);

void main()
{
	int SelectedCategoryIndex = -1;
	int WrongGuessesByPlayer = 0;
	char LetterGuessedByPlayer;

	char AfricanCountries[MAX_WORDS][MAX_WORD_LENGTH] = {"MOROCCO", "ALGERIA", "MAURITIUS", "MOZAMBIQUE", "NIGERIA",
													   "ZIMBABWE", "SOMALIA", "CHAD", "SEYCHELLES", "DJIBOUTI"};

	char ProgrammingLanguages[MAX_WORDS][MAX_WORD_LENGTH] = {"JAVASCRIPT", "PHP", "RUBY", "PYTHON",
													 "HASKELL", "SWIFT", "POWERSHELL", "TYPESCRIPT",
													 "JAVA", "MODULA"};

	char Animals[MAX_WORDS][MAX_WORD_LENGTH] = {"TIGER", "LION", "CHEETAH", "LEOPARD", "ELEPHANT", "BEAR",
												"DEER", "RHINOCEROS", "ZEBRA", "CROCODILE"};

	char SelectedCategoryWords[MAX_WORDS][MAX_WORD_LENGTH] = {""};

	char* RandomlySelectedWord;
	char HiddenWord[MAX_WORD_LENGTH];

	do
	{
		SelectedCategoryIndex = ChooseCategory();
	} while (SelectedCategoryIndex == -1);

	switch (SelectedCategoryIndex)
	{
	case 1:
		memcpy(SelectedCategoryWords, AfricanCountries, sizeof(AfricanCountries));
		printf("You have selected African Countries. Cool, let's play!!\n");
		break;
	case 2:
		memcpy(SelectedCategoryWords, ProgrammingLanguages, sizeof(ProgrammingLanguages));
		printf("You have selected Programming Languages. Cool, let's play!!\n");
		break;
	case 3:
		memcpy(SelectedCategoryWords, Animals, sizeof(Animals));
		printf("You have selected Animals. Cool, let's play!!\n");
		break;
	default:
		break;
	}

	RandomlySelectedWord = PickWordFromSelectedCategory(SelectedCategoryWords);
	InitializeRandomlySelectedWord(RandomlySelectedWord, HiddenWord);

	// Main Game Loop
	while (WrongGuessesByPlayer < MAX_ATTEMPTS)
	{
		printf("\n\n%s", HiddenWord);
		printf("\nGuess a letter for the hidden word : ");

		scanf("%c", &LetterGuessedByPlayer);
		getc(stdin);
		LetterGuessedByPlayer = toupper(LetterGuessedByPlayer);
		fflush(stdin);

		if (EvaluateGuess(LetterGuessedByPlayer, RandomlySelectedWord, HiddenWord) == 0)
		{
			printf("\nNope! %c isn't a part of the hidden word. Please try again! ", LetterGuessedByPlayer);
			WrongGuessesByPlayer++;
		}
		else
		{
			printf("\nVoila! You guessed the letter right! Great job!\n");
		}

		// Notify the player about the progress of the game so far...
		printf("You have %d ", MAX_ATTEMPTS - WrongGuessesByPlayer);
		printf("attempts left!\n");

		if (strcmp(RandomlySelectedWord, HiddenWord) == 0)
		{
			printf("Congratulations! You got the word right!\n");
			printf("The hidden word was : %s!\n", RandomlySelectedWord);
			break;
		}
	}

	if (WrongGuessesByPlayer == MAX_ATTEMPTS)
	{
		printf("\nToo bad! You have been hanged!\n");
		printf("The hidden word was : %s!\n", RandomlySelectedWord);
	}

	_getch();
}

int ChooseCategory()
{
	printf("Welcome to TNSQUAD Guessing words game written in Classic C!\n\n");
	printf("Select a category of words to play with : \n");
	printf("Press '1' to select African Countries.\n");
	printf("Press '2' to select Programming Languages.\n");
	printf("Press '3' to select Animals.\n");

	int userInput;
	scanf("%d", &userInput);
	getc(stdin);
	fflush(stdin);

	if (userInput > 0 && userInput < 4)
	{
		return userInput;
	}
	else
	{
		printf("\nINVALID INPUT. Please try again!\n\n");
		return -1;
	}
}

char* PickWordFromSelectedCategory(char table[MAX_WORDS][MAX_WORD_LENGTH])
{
	srand(time(NULL));
	int wordToChooseIndex = rand() % MAX_WORDS;
	//wordToChooseIndex = 0; // HACK : REMOVE LATER
	return (char *)table[wordToChooseIndex];
}

void InitializeRandomlySelectedWord(char selectedWord[], char hiddenWord[])
{
	int index;
	int wordLength = strlen(selectedWord);

	if (wordLength > 3)
	{
		for (index = 0; index < wordLength; index++)
		{
			hiddenWord[index] = '-';
		}

		hiddenWord[index] = '\0';
	}
}

int EvaluateGuess(char playerGuess, char selectedWord[], char hiddenWord[])
{
	int index;
	int outcome = 0;

	for (index = 0; selectedWord[index] != '\0'; index++)
	{
		// check whether the word has already been guessed.
		if (playerGuess == hiddenWord[index])
		{
			return 0;
		}

		// check whether the player's guess matches any character within the randomly selected word.
		if (playerGuess == selectedWord[index])
		{
			hiddenWord[index] = playerGuess;
			outcome++;
		}
	}

	return outcome;
}

