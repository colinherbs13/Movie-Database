#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
/*Author: Colin Herbert
  Date Created: 11/12/19
  Description of Program: Create a program that asks the number of movies to read in, then allocates memory and reads data from text files, and executes different actions based on a menu input.
	inputs: number of movies, quit/continue, menu input
	outputs: movie title, rating, duration, year, and genre; interactive menu, sorted list of movies
*/
typedef struct movie_s {
	char title[100];
	double rating; //rating from 1-10
	int duration; //in minutes
	int year;
	char genre[50];
}movies;

void swap(movies* x, movies* y) {
	movies temp;
	temp = *x;
	*x = *y;
	*y = temp;
}

void selection(movies x[], int size) {
	int i, j; int max;
	for (i = 0; i < size; i++) {
		max = i;
		for (j = i; j < size; j++) {
			if (x[j].rating > x[max].rating) {
				max = j;
			}
		}
		swap(&x[i], &x[max]);
	}
}

void printMovie(movies* ptr) {
	printf("%s\t\t%.2lf\t%d\t%d\t%s \n", ptr->title, ptr->rating, ptr->duration, ptr->year, ptr->genre);
}

void searchStartLetter(int size, movies* ptr) {
	char input;
	int i, count = 0;
	movies *outpList = (movies*)malloc(size * sizeof(movies));
	printf("\n");
	printf("Enter the first character of movie titles: ");
	scanf(" %c", &input);
	for (i = 0; i < size; i++) {
		if ((ptr[i].title[0] == input)) {
			outpList[count] = ptr[i];
			count++;	
		}
	}
	selection(outpList, size);
	for (i = 0; i < count; i++) {
		printf("%s(%d) %.2lf\n", outpList[i].title, outpList[i].year, outpList[i].rating);
	}
	if (count == 0) {
		printf("No movies in the database starting with %c\n", input);
	}
}

void searchKeyword(int size, movies* ptr) {
	char keyword[100];
	int i, count = 0;
	movies *outpList = (movies*)malloc(size * sizeof(movies));
	printf("\n");
	printf("Enter the keyword: ");
	scanf("%s", keyword);
	for (i = 0; i < size; i++) { //scans every character in the string and looks for spaces
		if (strstr(ptr[i].title, keyword) != NULL) {
			outpList[count] = ptr[i];
			count++;
		}
	}
	selection(outpList, size);
	for (i = 0; i < count; i++) {
		printf("%s(%d) %.2lf\n", outpList[i].title, outpList[i].year, outpList[i].rating);
	}
	if (count == 0) {
		printf("No movies in the database with %s\n", keyword);
	}
}

void aboveRating(int size, movies* ptr) {
	double inpRating;
	int i, count = 0;
	movies* outpList = (movies*)malloc(size * sizeof(movies));
	printf("\n");
	printf("Enter rating ");
	scanf("%lf", &inpRating);
	for (i = 0; i < size; i++) {
		if (inpRating <= ptr[i].rating) {
			outpList[count] = ptr[i];
			count++;
		}
	}
	selection(outpList, size);
	for (i = 0; i < count; i++) {
		printf("%s(%d) %.2lf\n", outpList[i].title, outpList[i].year, outpList[i].rating);
	}
	if (count == 0) {
		printf("No movies in the database with rating higher than %.2lf\n", inpRating);
	}
}

void searchYear(int size, movies* ptr) {
	int inpYear;
	int i, count = 0;
	movies* outpList = (movies*)malloc(size * sizeof(movies));
	printf("\n");
	printf("Enter Year ");
	scanf("%d", &inpYear);
	for (i = 0; i < size; i++) {
		if (inpYear == ptr[i].year) {
			outpList[count] = ptr[i];
			count++;
		}
	}
	selection(outpList, size);
	for (i = 0; i < count; i++) {
		printf("%s(%d) %.2lf\n", outpList[i].title, outpList[i].year, outpList[i].rating);
	}
	if (count == 0) {
		printf("No movies in the database with year %d\n", inpYear);
	}
}

void belowDuration(int size, movies* ptr) {
	int inpDuration;
	int i, count = 0;
	movies* outpList = (movies*)malloc(size * sizeof(movies));
	printf("\n");
	printf("Enter duration (in mins): ");
	scanf("%d", &inpDuration);
	for (i = 0; i < size; i++) {
		if (inpDuration >= ptr[i].duration) {
			outpList[count] = ptr[i];
			count++;
		}
	}
	selection(outpList, size);
	for (i = 0; i < count; i++) {
		printf("%s(%d) %.2lf duration %d\n", outpList[i].title, outpList[i].year, outpList[i].rating, outpList[i].duration);
	}
	if (count == 0) {
		printf("No movies in the database with duration lower than %d\n", inpDuration);
	}
}

void searchGenre(int size, movies* ptr) {
	char inpGenre[50];
	int i, count = 0;
	movies* outpList = (movies*)malloc(size * sizeof(movies));
	printf("\n");
	printf("Enter genre (Action, Adventure, Comedy, Crime, Documentary, Drama, Horror, Musical, Mystery, Thriller): ");
	scanf("%s", inpGenre);
	for (i = 0; i < size; i++) {
		if (strcmp(inpGenre, ptr[i].genre) == 0) {
			outpList[count] = ptr[i];
			count++;
		}
	}
	selection(outpList, size);
	for (i = 0; i < count; i++) {
		printf("%s(%d) %.2lf\n", outpList[i].title, outpList[i].year, outpList[i].rating);
	}
	if (count == 0) {
		printf("No movies in the database with %s\n", inpGenre);
	}
}
int main(void) {
	FILE* inp = fopen("movies.txt", "r");
	movies* ptr = NULL;
	int numMovies, i, menuInput = 7;
	char quit = 'N';

	printf("Enter number of movies you want to use from the database: ");
	scanf("%d", &numMovies);
	ptr = (movies*)malloc(numMovies * sizeof(movies));

	for (i = 0; i < numMovies; i++) {
		fgets(ptr[i].title, 50, inp);
		if (ptr[i].title[strlen(ptr[i].title) - 1] == '\n') {
			ptr[i].title[strlen(ptr[i].title) - 1] = '\0';
		}
		fscanf(inp, "%lf %d %d %s ", &ptr[i].rating, &ptr[i].duration, &ptr[i].year, ptr[i].genre);
		printMovie(&ptr[i]);
	}
	printf("\n");
	while ((quit != 'Q') && (quit != 'q')) {
		menuInput = 7;
		printf("\nlist movie(s)\n");
		printf("1: starting with alphabet, 2: with keyword, 3: by rating\n");
		printf("4: by year, 5: by duration (mins), 6: by genre\n\n");
		while ((menuInput < 1) || (menuInput > 6)) {
			printf("Choose 1-6 from the above options: ");
			scanf("%d", &menuInput);
			switch (menuInput) {
			case 1:
				searchStartLetter(numMovies, ptr);
				break;
			case 2:
				searchKeyword(numMovies, ptr);
				break;
			case 3:
				aboveRating(numMovies, ptr);
				break;
			case 4:
				searchYear(numMovies, ptr);
				break;
			case 5:
				belowDuration(numMovies, ptr);
				break;
			case 6:
				searchGenre(numMovies, ptr);
				break;
			default:
				printf("option not found\n");
			}
		}
		printf("Contine (q/Q to quit)? ");
		scanf(" %c", &quit);
	}
	fclose(inp);
	return(0);
}
	