#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct movie {
	int serial_number;
	char *title;
	char *genre;
	char *director;
	char *year;
	char *time;
	char *actors;
	struct movie *next;
}movie;

typedef struct director {
	int serial_number;
	char *name;
	char *sex;
	char *birth;
	char *best_movies;
	struct director *next;
}director;

typedef struct actor {
	int serial_number;
	char *name;
	char *sex;
	char *birth;
	char *best_movies;
	struct actor *next;
}actor;

void add_movie(movie *m){
	movie *temp_mp;
	char *temp;
	m = (movie *)malloc(sizeof(movie));	
	temp = (char *)malloc(sizeof(char) * 200);
	printf("title > ");
	scanf("%s", temp);
	m->title = (char *)malloc(sizeof(char) * strlen(temp));
	strcpy(m->title, temp);

	m = m->next;
}

int main(void) {
	movie *m;
	actor *a;
	director *d;

	char *input_words;
	input_words = (char *)malloc(sizeof(char) * 20);
	printf(">> Welcome to My Movie <<\n");
	printf("File Loading.....\n");
	printf("You can use add, update, delete, search, sort, save, end commands.\n");
	while (1) {
		printf("(movie) ");
		scanf("%s", input_words);
		add_movie(m);
	}
	return 0;
}