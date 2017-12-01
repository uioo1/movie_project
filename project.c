#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>
//윤동우 수정 시작
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

movie *root_movie, *m;	//movie*의 헤더와 다른거
director *root_director, *d;	//director*의 헤더와 다른거
actor *root_actor, *a;	//actor*의 헤더와 다른거
int root_m_num = 0, root_d_num = 0, root_a_num = 0;	//헤더인지 아닌지 판별할 변수
int serial_m_num = 1, serial_d_num = 1, serial_a_num = 1;	//각각의 시리얼 넘버 전역변수
int ctrl_c_num = 0;	//ctrl+c 받았을때 앞의 거를 다시 출력하게 해주는 전역변수

void load_movie() {	//movie_log를 읽어서 m 링크드 리스트를 만들어 놓는 함수(미완성)
	FILE *fp;
	fp = fopen("r", "movie_log");
	
	fclose(fp);
}

void load_director() {	//director_log를 읽어서 d 링크드 리스트를 만들어 놓는 함수(미완성)
	FILE *fp;
	fp = fopen("r", "director_log");

	fclose(fp);
}

void load_actor() {	//actor_log를 읽어서 a 링크드 리스트를 만들어 놓는 함수(미완성)
	FILE *fp;
	fp = fopen("r", "actor_log");

	fclose(fp);
}

void handler(int sig) {	//Ctrl + c 눌러도 종료되지 않고 물어보게 하는 함수
	char *answer;
	answer = (char *)malloc(sizeof(char) * 5);
	printf("\nControl+c %d\n", sig);
	printf("Get Interrupt Signal.\n");
	printf("Do you want to exit myMOVIE program? (Y/N) ");
	scanf("%s", answer);
	//printf("answer : %s\n", answer);
	//printf("%d, %d\n", !strcmp(answer, "y"), !strcmp(answer, "Y"));
	if (!strcmp(answer, "y") || !strcmp(answer, "Y"))
		exit(1);
}

void add_movie(){	//movie 정보 입력받는 함수
	char *temp;	//글자를 입력받을 임시 포인터
	temp = (char *)malloc(sizeof(char) * 200);	//임시 포인터 동적할당

	if (root_m_num == 0) {	//링크드 리스트 처음 헤더를 root_movie에 저장
		root_movie = m;
		root_m_num = 1;
	}	
	m->serial_number = serial_m_num++;
	!
	printf("title > ");
	gets(temp);	//title 입력
	m->title = (char *)malloc(sizeof(char) * strlen(temp) + 1);	//입력받은 글자의 크기만큼 동적할당 받음(+1은 맨뒤에 null을 넣을 공간)
	strcpy(m->title, temp);	//temp를 구조체 멤버에 옮김

	printf("genre > ");
	gets(temp);
	m->genre = (char *)malloc(sizeof(char) * strlen(temp) + 1);
	strcpy(m->genre, temp);
	
	printf("director > ");
	gets(temp);
	m->director = (char *)malloc(sizeof(char) * strlen(temp) + 1);
	strcpy(m->director, temp);

	printf("year > ");
	scanf("%s", temp);
	m->year = (char *)malloc(sizeof(char) * strlen(temp) + 1);
	strcpy(m->year, temp);

	printf("time > ");
	scanf("%s", temp);
	getchar();
	m->time = (char *)malloc(sizeof(char) * strlen(temp) + 1);
	strcpy(m->time, temp);
	
	printf("actors > ");
	gets(temp);
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
	gets(temp);	//name 입력
	d->name = (char *)malloc(sizeof(char) * strlen(temp) + 1);	//입력받은 글자의 크기만큼 동적할당 받음(+1은 맨뒤에 null을 넣을 공간)
	strcpy(d->name, temp);	//temp를 구조체 멤버에 옮김

	printf("sex > ");
	scanf("%s", temp);
	d->sex = (char *)malloc(sizeof(char) * strlen(temp) + 1);
	strcpy(d->sex, temp);

	printf("birth > ");
	scanf("%s", temp);
	getchar();
	d->birth = (char *)malloc(sizeof(char) * strlen(temp) + 1);
	strcpy(d->birth, temp);

	printf("best_movies > ");
	gets(temp);
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
	gets(temp);
	a->name = (char *)malloc(sizeof(char) * strlen(temp) + 1);
	strcpy(a->name, temp);

	printf("sex > ");
	scanf("%s", temp);
	a->sex = (char *)malloc(sizeof(char) * strlen(temp) + 1);
	strcpy(a->sex, temp);

	printf("birth > ");
	scanf("%s", temp);
	getchar();
	a->birth = (char *)malloc(sizeof(char) * strlen(temp) + 1);
	strcpy(a->birth, temp);

	printf("best_movies > ");
	gets(temp);
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

char *colon_process(char *string) {	//':'을 "??;"으로 바꿔주는 함수, char *을 받아서 char *을 리턴한다

	return string;
}

int menu_func(char *input) {	//명령어 입력한거 실행하는거, 추후에 같은 형식으로 추가하세용
	char *temp;	//input받는 임시 변수, input을 바꾸는 사태가 일어나지 않게 해줌
	char *token;	//명령어 쪼개서 저장하는 토큰
	char *cut;	//명령어 쪼개는 기준이 담긴 포인터
	char *menu;	//명령 부분을 담는 포인터(예: update)
	char *factor;	//인자 부분을 담는 포인터(예: m, d, a중 하나임)
	char *option;	//옵션 부분을 담는 포인터(예: tdy)
	char *string;	//search명령에 쓰이는 찾을 문자열
	char *file_name;	//파일 이름을 담는 포인터(예: my_list)
	int get_serial_num;	//print나 delete명령에 쓰이는 관리 번호
	int i;	//for문을 돌리는 변수, 왜 for도 없는데 선언했냐 물으신다면 대답 안하는게 인! 지! 상! 정!

	temp = (char *)malloc(sizeof(char) * 50);	//temp 동적 할당
	token = (char *)malloc(sizeof(char) * 50);	//토큰 동적 할당
	cut = (char *)malloc(sizeof(char) * 10);	//cut 동적 할당
	strcpy(temp, input);	//temp에 input 복사
	cut = " ";	//공백으로 명령어 쪼개기

	token = strtok(temp, cut);
	menu = (char *)malloc(sizeof(char) * strlen(token) + 1);
	strcpy(menu, token);
	printf("menu : %s\n", menu);

	if (!strcmp(menu, "end")) {
		return 0;	//quit_num을 0으로 만들어 종료하기
	}
	else if (!strcmp(menu, "add")) {	//add 명령어 처리
		token = strtok(NULL, cut);
		factor = (char *)malloc(sizeof(char) * strlen(token) + 1);
		strcpy(factor, token);
		printf("factor : %s\n", factor);	//factor 확인

		if (!strcmp(factor, "m"))
			add_movie();
		else if (!strcmp(factor, "d"))
			add_director();
		else if (!strcmp(factor, "a"))
			add_actor();
	}
	else if (!strcmp(menu, "print")) {	//print 명령어 처리, serial_num 안붙이면 오류뜸
		token = strtok(NULL, cut);
		factor = (char *)malloc(sizeof(char) * strlen(token) + 1);
		strcpy(factor, token);
		printf("factor : %s\n", factor);	//factor 확인

		token = strtok(NULL, cut);
		get_serial_num = atoi(token);	//문자열을 숫자로 변환
		printf("num : %d\n", get_serial_num);	//get_serial_num 확인

		if (!strcmp(factor, "m")) {	//임시 moive 출력하는 함수
			m = root_movie;
			while (m->next != NULL) {
				printf("%s\n", m->title);
				m = m->next;
			}
			printf("\n");
		}
		else if (!strcmp(factor, "d")) {	//임시 director 출력하는 함수
			d = root_director;
			while (d->next != NULL) {
				printf("%s\n", d->name);
				d = d->next;
			}
			printf("\n");
		}
		else if (!strcmp(factor, "a")) {	//임시 actor 출력하는 함수
			a = root_actor;
			while (a->next != NULL) {
				printf("%s\n", a->name);
				a = a->next;
			}
			printf("\n");
		}
	}
	else if (!strcmp(menu, "delete")) {	//delete 명령어 처리
		token = strtok(NULL, cut);
		factor = (char *)malloc(sizeof(char) * strlen(token) + 1);
		strcpy(factor, token);
		printf("factor : %s\n", factor);	//factor 확인

		token = strtok(NULL, cut);
		get_serial_num = atoi(token);
		printf("num : %d\n", get_serial_num);	//get_serial_num 확인

		if (!strcmp(factor, "m"))
			;	//moive 삭제하는 함수
		else if (!strcmp(factor, "d"))
			;	//director 삭제하는 함수
		else if (!strcmp(factor, "a"))
			;	//actor 삭제하는 함수
	}
	else if (!strcmp(menu, "search")) {	//search 명령어 처리
		token = strtok(NULL, cut);
		if (*token == '-') {
			option = (char *)malloc(sizeof(char) * strlen(token) + 1);
			strcpy(option, token);
			printf("option : %s\n", option);	//option 확인
			token = strtok(NULL, cut);
		}

		string = (char *)malloc(sizeof(char) * strlen(token) + 1);
		strcpy(string, token);
		printf("string : %s\n", string);	//string 확인
	}
	else if (!strcmp(menu, "update")) {	//update 명령어 처리
		token = strtok(NULL, cut);
		factor = (char *)malloc(sizeof(char) * strlen(token) + 1);
		strcpy(factor, token);
		printf("factor : %s\n", factor);	//factor 확인

		token = strtok(NULL, cut);
		if (*token >= '9') {	//숫자가 아닌 알파벳이면 option으로 넣기
			option = (char *)malloc(sizeof(char) * strlen(token) + 1);
			strcpy(option, token);
			printf("option : %s\n", option);	//option 확인
			token = strtok(NULL, cut);
		}		
		get_serial_num = atoi(token);
		printf("num : %d\n", get_serial_num);	//get_serial_num 확인
	}
	else if (!strcmp(menu, "sort")) {	//sort 명령어 처리
		token = strtok(NULL, cut);
		factor = (char *)malloc(sizeof(char) * strlen(token) + 1);
		strcpy(factor, token);
		printf("factor : %s\n", factor);	//factor 확인

		if ((token = strtok(NULL, cut)) != NULL) {	//뒤에 뭐가 더 있는지 확인 
			if (!strcmp(token, "-f")) {	//뒤에 있는게 -f이면
				token = strtok(NULL, cut);	//-f 건너뛰기
				file_name = (char *)malloc(sizeof(char) * strlen(token) + 1);
				strcpy(file_name, token);
				printf("file_name : %s\n", file_name);	//file_name 확인
			}
			else {	//뒤에 있는게 옵션이면
				option = (char *)malloc(sizeof(char) * strlen(token) + 1);
				strcpy(option, token);
				printf("option : %s\n", option);	//option 확인

				if ((token = strtok(NULL, cut)) != NULL) {	//뒤에 뭐가 더 있는지 확인
					token = strtok(NULL, cut);	//있다면 -f일테니 건너뛰기
					file_name = (char *)malloc(sizeof(char) * strlen(token) + 1);
					strcpy(file_name, token);
					printf("file_name : %s\n", file_name);	//file_name 확인
				}
			}
		}
		printf("\n");
	}
	else if (!strcmp(menu, "save")) {	//save 명령어 처리
		token = strtok(NULL, cut);
		factor = (char *)malloc(sizeof(char) * strlen(token) + 1);
		strcpy(factor, token);
		printf("factor : %s\n", factor);	//factor 확인

		if ((token = strtok(NULL, cut)) != NULL) {	//뒤에 뭐가 더 있는지 확인 
			if (!strcmp(token, "-f")) {	//뒤에 있는게 -f이면
				token = strtok(NULL, cut);	//-f 건너뛰기
				file_name = (char *)malloc(sizeof(char) * strlen(token) + 1);
				strcpy(file_name, token);
				printf("file_name : %s\n", file_name);	//file_name 확인
			}
			else {	//뒤에 있는게 옵션이면
				option = (char *)malloc(sizeof(char) * strlen(token) + 1);
				strcpy(option, token);
				printf("option : %s\n", option);	//option 확인

				if ((token = strtok(NULL, cut)) != NULL) {	//뒤에 뭐가 더 있는지 확인
					token = strtok(NULL, cut);	//있다면 -f일테니 건너뛰기
					file_name = (char *)malloc(sizeof(char) * strlen(token) + 1);
					strcpy(file_name, token);
					printf("file_name : %s\n", file_name);	//file_name 확인
				}
			}	
		}
		printf("\n");
	}

	

	if (!strcmp(input, "save m")) {	//임시 movie 세이브
		save_movie();
	}
	else if (!strcmp(input, "save d")) {	//임시 director 세이브
		save_director();
	}
	else if (!strcmp(input, "save a")) {	//임시 actor 세이브
		save_actor();
	}

	return 1;
}

int main(void) {
	m = (movie *)malloc(sizeof(movie));	//movie *m 전역 구조체 동적할당
	d = (director *)malloc(sizeof(director));	//director *d 전역 구조체 동적할당
	a = (actor *)malloc(sizeof(actor));	//actor *a 전역 구조체 동적할당
	int quit_num = 1;	//프로그램 끝내는 변수
	char *input_words;
	input_words = (char *)malloc(sizeof(char) * 50);		

	printf(">> Welcome to My Movie <<\n");
	printf("File Loading.....\n");
	printf("You can use add, update, delete, search, sort, save, end commands.\n");	
	signal(SIGINT, handler);	//Ctrl + c를 눌렀을때 바로 종료되지 않고 물어보기
	while (quit_num) {
		printf("(movie) ");
		gets(input_words);
		quit_num = menu_func(input_words);		
	}
	return 0;
}
