#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>

typedef struct movie {//asdf 
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

movie *root_movie, *m;	//movie*의 헤더와 다른거
director *root_director, *d;	//director*의 헤더와 다른거
actor *root_actor, *a;	//actor*의 헤더와 다른거
int root_m_num = 0, root_d_num = 0, root_a_num = 0;	//헤더인지 아닌지 판별할 변수
int serial_m_num = 1, serial_d_num = 1, serial_a_num = 1;	//각각의 시리얼 넘버 전역변수

void add_movie(){	//movie 정보 입력받는 함수
	char *temp;	//글자를 입력받을 임시 포인터
	temp = (char *)malloc(sizeof(char) * 200);	//임시 포인터 동적할당

	if (root_m_num == 0) {	//링크드 리스트 처음 헤더를 root_movie에 저장
		root_movie = m;
		root_m_num = 1;
	}	
	m->serial_number = serial_m_num++;

	printf("title > ");
	scanf("%s", temp);	//title 입력
	m->title = (char *)malloc(sizeof(char) * strlen(temp) + 1);	//입력받은 글자의 크기만큼 동적할당 받음(+1은 맨뒤에 null을 넣을 공간)
	strcpy(m->title, temp);	//temp를 구조체 멤버에 옮김

	printf("genre > ");
	scanf("%s", temp);
	m->genre = (char *)malloc(sizeof(char) * strlen(temp) + 1);
	strcpy(m->genre, temp);
	
	printf("director > ");
	scanf("%s", temp);
	m->director = (char *)malloc(sizeof(char) * strlen(temp) + 1);
	strcpy(m->director, temp);

	printf("year > ");
	scanf("%s", temp);
	m->year = (char *)malloc(sizeof(char) * strlen(temp) + 1);
	strcpy(m->year, temp);

	printf("time > ");
	scanf("%s", temp);
	m->time = (char *)malloc(sizeof(char) * strlen(temp) + 1);
	strcpy(m->time, temp);
	
	printf("actors > ");
	scanf("%s", temp);
	getchar();
	m->actors = (char *)malloc(sizeof(char) * strlen(temp) + 1);
	strcpy(m->actors, temp);
	
	m->next = (movie *)malloc(sizeof(movie));	//m의 next포인터를 동적할당
	m = m->next;	//m을 현재 m의 next로 바꿈
	m->next = NULL;	//지금의 m의 next를 null로 해줌

	printf("@@ Done\n\n");
}

void add_director() {	//director 정보 입력받는 함수
	char *temp;
	temp = (char *)malloc(sizeof(char) * 200);

	if (root_d_num == 0) {	//링크드 리스트 처음 헤더를 root_director에 저장
		root_director = d;
		root_d_num = 1;
	}
	d->serial_number = serial_d_num++;

	printf("name > ");
	scanf("%s", temp);	//name 입력
	d->name = (char *)malloc(sizeof(char) * strlen(temp) + 1);	//입력받은 글자의 크기만큼 동적할당 받음(+1은 맨뒤에 null을 넣을 공간)
	strcpy(d->name, temp);	//temp를 구조체 멤버에 옮김

	printf("sex > ");
	scanf("%s", temp);
	d->sex = (char *)malloc(sizeof(char) * strlen(temp) + 1);
	strcpy(d->sex, temp);

	printf("birth > ");
	scanf("%s", temp);
	d->birth = (char *)malloc(sizeof(char) * strlen(temp) + 1);
	strcpy(d->birth, temp);

	printf("best_movies > ");
	scanf("%s", temp);
	getchar();
	d->best_movies = (char *)malloc(sizeof(char) * strlen(temp) + 1);
	strcpy(d->best_movies, temp);

	d->next = (director *)malloc(sizeof(director));	//d의 next포인터를 동적할당
	d = d->next;	//d를 현재 d의 next로 바꿈
	d->next = NULL;	//지금의 d의 next를 null로 해줌

	printf("@@ Done\n\n");
}

void add_actor() {	//actor의 정보를 입력받는 함수
	char *temp;
	temp = (char *)malloc(sizeof(char) * 200);

	if (root_a_num == 0) {	//링크드 리스트 처음 헤더를 root_actor에 저장
		root_actor = a;
		root_a_num = 1;
	}
	a->serial_number = serial_a_num++;

	printf("name > ");
	scanf("%s", temp);
	a->name = (char *)malloc(sizeof(char) * strlen(temp) + 1);
	strcpy(a->name, temp);

	printf("sex > ");
	scanf("%s", temp);
	a->sex = (char *)malloc(sizeof(char) * strlen(temp) + 1);
	strcpy(a->sex, temp);

	printf("birth > ");
	scanf("%s", temp);
	a->birth = (char *)malloc(sizeof(char) * strlen(temp) + 1);
	strcpy(a->birth, temp);

	printf("best_movies > ");
	scanf("%s", temp);
	getchar();
	a->best_movies = (char *)malloc(sizeof(char) * strlen(temp) + 1);
	strcpy(a->best_movies, temp);

	a->next = (actor *)malloc(sizeof(actor));	//a의 next포인터를 동적할당
	a = a->next;	//a을 현재 a의 next로 바꿈
	a->next = NULL;	//지금의 a의 next를 null로 해줌

	printf("@@ Done\n\n");
}

void save_director() {
	FILE *fp;
	fp = fopen("director_list", "w");
	d = root_director;
	while (d->next != NULL) {		
		fprintf(fp, "%d:%s:%s:%s:%s\n", d->serial_number, d->name, d->sex, d->birth, d->best_movies);
		d = d->next;
	}
	fclose(fp);
	printf("@@ Done\n\n");
}

void save_movie() {
	FILE *fp;
	fp = fopen("movie_list", "w");
	m = root_movie;
	while (m->next != NULL) {
		fprintf(fp, "%d:%s:%s:%s:%s:%s\n", m->serial_number, m->title, m->genre, m->director, m->year, m->time);
		m = m->next;
	}
	fclose(fp);
	printf("@@ Done\n\n");
}

void save_actor() {
	FILE *fp;
	fp = fopen("actor_list", "w");
	a = root_actor;
	while (a->next != NULL) {
		fprintf(fp, "%d:%s:%s:%s:%s\n", a->serial_number, a->name, a->sex, a->birth, a->best_movies);
		a = a->next;
	}
	fclose(fp);
	printf("@@ Done\n\n");
}

void menu_func(char *input) {	//명령어 입력한거 실행하는거, 추후에 같은 형식으로 추가하세용
	/*char *token;	//명령어 쪼개서 저장하는 토큰
	char *cut;	//명령어 쪼개는 기준이 담긴 포인터
	char *menu;	//명령 부분을 담는 포인터(예: update)
	char *factor;	//인자 부분을 담는 포인터(예: m, d, a)
	char *option;	//옵션 부분을 담는 포인터(예: 
	int i;	//for문을 돌리는 변수, 왜 for문안에 선언안했냐 물으신다면 대답 안하는게 인! 지! 상! 정!
	token = (char *)malloc(sizeof(char) * 20);	//토큰 동적 할당
	cut = (char *)malloc(sizeof(char) * 10);	//cut 동적 할당
	cut = " ";

	token = strtok(input, cut);

	for (i = 0l i < 2; i++) {
		if (token == NULL)
			break;
		else if (i == 0) {
			 = (char *)malloc(sizeof(char) * strlen(temp) + 1);
			strcpy(a->name, temp);
		}
		printf("토큰 : %s\n", token);
		token = strtok(NULL, cut);
	}*/


	if (!strcmp(input, "add m"))
		add_movie();
	else if (!strcmp(input, "add d"))
		add_director();
	else if (!strcmp(input, "add a"))
		add_actor();
	else if (!strcmp(input, "add md")) {
		add_movie();
		add_director();
	}
	else if (!strcmp(input, "add dm")) {
		add_director();
		add_movie();
	}
	else if (!strcmp(input, "add ma")) {
		add_movie();
		add_actor();
	}
	else if (!strcmp(input, "add am")) {
		add_actor();
		add_movie();
	}
	else if (!strcmp(input, "add da")) {
		add_director();
		add_actor();
	}
	else if (!strcmp(input, "add ad")) {
		add_actor();
		add_director();
	}
	else if (!strcmp(input, "add mda")) {
		add_movie();
		add_director();
		add_actor();
	}
	else if (!strcmp(input, "add mad")) {
		add_movie();
		add_actor();
		add_director();
	}
	else if (!strcmp(input, "add amd")) {
		add_actor();
		add_movie();
		add_director();
	}
	else if (!strcmp(input, "add adm")) {
		add_actor();
		add_director();
		add_movie();
	}
	else if (!strcmp(input, "add dma")) {
		add_director();
		add_movie();
		add_actor();
	}
	else if (!strcmp(input, "add dam")) {
		add_director();
		add_actor();
		add_movie();
	}
	else if (!strcmp(input, "print m")) {
		m = root_movie;
		while(m->next != NULL) {
			printf("%s\n", m->title);
			m = m->next;
		}
	}
	else if (!strcmp(input, "print d")) {
		d = root_director;
		while (d->next != NULL) {
			printf("%s\n", d->name);
			d = d->next;
		}
	}
	else if (!strcmp(input, "print a")) {
		a = root_actor;
		while (a->next != NULL) {
			printf("%s\n", a->name);
			a = a->next;
		}
	}
	else if (!strcmp(input, "save m")) {
		save_movie();
	}
	else if (!strcmp(input, "save d")) {
		save_director();
	}
	else if (!strcmp(input, "save a")) {
		save_actor();
	}
}

int main(void) {
	m = (movie *)malloc(sizeof(movie));	//movie *m 전역 구조체 동적할당
	d = (director *)malloc(sizeof(director));	//director *d 전역 구조체 동적할당
	a = (actor *)malloc(sizeof(actor));	//actor *a 전역 구조체 동적할당

	char *input_words;
	input_words = (char *)malloc(sizeof(char) * 20);
	printf(">> Welcome to My Movie <<\n");
	printf("File Loading.....\n");
	printf("You can use add, update, delete, search, sort, save, end commands.\n");

	while (1) {
		printf("(movie) ");
		gets(input_words);
		menu_func(input_words);
	}
	return 0;
}
