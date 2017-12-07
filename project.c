#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>

typedef struct sorting { //char형 sort를 위한 임시구조체
	int serial_number;
	char *string;
} sorting;

typedef struct sorting_num{ //int형 sort를 위한 임시구조체
	int serial_number;
	int num;
} sorting_num;

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
int ctrl_c_num = 0;	//ctrl+c 받았을때 앞의 거를 다시 출력하게 해주는 전역변수(아직 사용안됨)

char *colon_proc(char *);	//콜론 처리 함수 선언
char *anti_colon_proc(char *);	//??;처리 함수 선언
char *itoa(int value, char *str, int radix);	//itoa함수의 헤더 선언
char *mystrcat(char *, char *);	//strcat의 성능이 향상된 mystrcat 함수 헤더 선언

char *mystrcat(char *dest, char *src) {
	while (*dest) dest++;
	while (*dest++ = *src++);
	return --dest;
}

void load_movie() {	//movie_log를 읽어서 m 링크드 리스트를 만들어 놓는 함수(미완성)
	char *token, *line, *menu;	//토큰과 한줄을 저장하는 것과 메뉴(add, delete, update)를 저장할 포인터
	char *title, *genre, *director, *year, *m_time, *actors;	//movie에 넣을 쪼개놓은 멤버들 저장할 포인터
	char *full_file_name, *cp_file_name, *nt_year, *nt_mon, *nt_mday, *nt_hour, *nt_min;	//시간들을 문자열로 변환해서 저장할 포인터와 다 합칠 부분
	int serial_num;
	char ch;
	movie *m_load, *m_temp;
	time_t t = time(NULL);	//타임 구조체 선언
	struct tm tm = *localtime(&t);
	m_load = (movie *)malloc(sizeof(movie));

	full_file_name = (char *)malloc(sizeof(char) * 25);
	cp_file_name = (char *)malloc(sizeof(char) * 15);
	nt_year = (char *)malloc(sizeof(char) * 5);
	nt_mon = (char *)malloc(sizeof(char) * 3);
	nt_mday = (char *)malloc(sizeof(char) * 3);
	nt_hour = (char *)malloc(sizeof(char) * 3);
	nt_min = (char *)malloc(sizeof(char) * 3);

	sprintf(nt_year, "%d", tm.tm_year + 1900);
	printf("year : %s\n", nt_year);
	strcpy(cp_file_name, nt_year);
	sprintf(nt_mon, "%d", tm.tm_mon + 1);
	printf("month : %s\n", nt_mon);
	sprintf(nt_mday, "%d", tm.tm_mday);
	printf("day : %s\n", nt_mday);
	sprintf(nt_hour, "%d", tm.tm_hour);
	printf("hour : %s\n", nt_hour);
	sprintf(nt_min, "%d", tm.tm_min);
	printf("minute : %s\n", nt_min);

	token = (char *)malloc(sizeof(char) * 50);
	line = (char *)malloc(sizeof(char) * 200);

	FILE *fp, *fp_copy;	//movie_log를 위한것과 movie_list를 시간붙여서 저장할 파일 포인터
	fp = fopen("movie_log", "r");
	if (fp == NULL)
		return;

	while (fgets(line, 200, fp) != NULL) {	//log파일을 줄이 없을 때까지 읽음
		*(line + strlen(line) - 1) = 0;	//마지막에 읽어온 \n을 없애줌
		printf("%s\n", line);

		token = strtok(line, ":");
		printf("token : %s\n", token);
		menu = (char *)malloc(sizeof(char) * strlen(token) + 1);
		strcpy(menu, token);

		token = strtok(NULL, ":");
		printf("serial_num : %s\n", token);
		serial_num = atoi(token);	//문자열인 token을 정수로 변환

		if(!strcmp(menu, "add"))
			serial_m_num = serial_num + 1;	//나중에 add m을 할 때 올바른 시리얼 넘버를 갖게함


		if (strcmp(menu, "delete")) {
			token = strtok(NULL, ":");
			token = anti_colon_proc(token);	//??;를 :로 바꿔줌
			printf("title : %s\n", token);
			title = (char *)malloc(sizeof(char) * strlen(token) + 1);
			strcpy(title, token);

			token = strtok(NULL, ":");
			token = anti_colon_proc(token);
			printf("genre : %s\n", token);
			genre = (char *)malloc(sizeof(char) * strlen(token) + 1);
			strcpy(genre, token);

			token = strtok(NULL, ":");
			token = anti_colon_proc(token);
			printf("director : %s\n", token);
			director = (char *)malloc(sizeof(char) * strlen(token) + 1);
			strcpy(director, token);

			token = strtok(NULL, ":");
			token = anti_colon_proc(token);
			printf("year : %s\n", token);
			year = (char *)malloc(sizeof(char) * strlen(token) + 1);
			strcpy(year, token);

			token = strtok(NULL, ":");
			token = anti_colon_proc(token);
			printf("time : %s\n", token);
			m_time = (char *)malloc(sizeof(char) * strlen(token) + 1);
			strcpy(m_time, token);

			token = strtok(NULL, ":");
			token = anti_colon_proc(token);
			if (*token == '=') {
				//printf("= is comparamised\n");
				*(token + strlen(token) - 1) = 0;	//마지막에 읽어온 폼 피드(form feed?)를 없애줌
			}
			*(token + strlen(token) - 1) = 0;
			printf("actors : %s\n", token);
			actors = (char *)malloc(sizeof(char) * strlen(token) + 1);
			strcpy(actors, token);
		}


		if (!strcmp(menu, "add")) {	//tag가 add이면 실행하는 것
			if (root_m_num == 0) {	//링크드 리스트의 처음 헤더를 저장
				root_movie = m_load;
				root_m_num = 1;
			}
			m_load->serial_number = serial_num;
			m_load->title = (char *)malloc(sizeof(char) * strlen(title) + 1);
			strcpy(m_load->title, title);
			m_load->genre = (char *)malloc(sizeof(char) * strlen(genre) + 1);
			strcpy(m_load->genre, genre);
			m_load->director = (char *)malloc(sizeof(char) * strlen(director) + 1);
			strcpy(m_load->director, director);
			m_load->year = (char *)malloc(sizeof(char) * strlen(year) + 1);
			strcpy(m_load->year, year);
			m_load->time = (char *)malloc(sizeof(char) * strlen(m_time) + 1);
			strcpy(m_load->time, m_time);
			m_load->actors = (char *)malloc(sizeof(char) * strlen(actors) + 1);
			strcpy(m_load->actors, actors);

			m_load->next = (movie *)malloc(sizeof(movie));	//m_load의 next포인터를 동적할당
			m_load = m_load->next;	//m_load을 현재 m_load의 next로 바꿈
			m_temp = m_load;	//링크드 리스트의 마지막을 m_temp에다가 저장
			m_load->next = NULL;	//지금의 m_load의 next를 null로 해줌
		}
		else if (!strcmp(menu, "update")) {	//tag가 update이면 실행하는 것
			m_load = root_movie;
			while (1) {
				if (m_load->serial_number == serial_num) {	//update하고자 하는 시리얼 넘버와 일치하면 실행
					if (strcmp(title, "="))
						strcpy(m_load->title, title);
					if (strcmp(genre, "="))
						strcpy(m_load->genre, genre);
					if (strcmp(director, "="))
						strcpy(m_load->director, director );
					if (strcmp(year, "="))
						strcpy(m_load->year, year);
					if (strcmp(m_time, "="))
						strcpy(m_load->time, m_time);
					if (strcmp(actors, "="))
						strcpy(m_load->actors, actors);

					break;
				}
				if (m_load->next == NULL)
					break;
				m_load = m_load->next;
			}
			m_load = m_temp;
		}
		else if (!strcmp(menu, "delete")) {	//tag가 delete이면 실행하는 것
			m_load = root_movie;
			while (1) {
				if (m_load->serial_number == serial_num) {	//delete하고자 하는 시리얼 넘버와 일치하면 실행
					m_load->title = NULL;
					m_load->genre = NULL;
					m_load->director = NULL;
					m_load->year = NULL;
					m_load->time = NULL;
					m_load->actors = NULL;

					break;
				}
				m_load = m_load->next;
			}
			if (m_load->next == NULL)
				break;
			m_load = m_temp;
		}
		printf("\n");
	}
	m = m_load;

	strcat(cp_file_name, nt_mon);	//movie_list파일을 새로 저장할 때 확장자를 날짜로 하게 하는 부분
	if (atoi(nt_mday) < 10) {
		mystrcat(cp_file_name, "0");
		mystrcat(cp_file_name, nt_mday);
	}
	else {
		mystrcat(cp_file_name, nt_mday);
	}

	if (atoi(nt_hour) < 10) {
		mystrcat(cp_file_name, "0");
		mystrcat(cp_file_name, nt_hour);
	}
	else {
		mystrcat(cp_file_name, nt_hour);
	}

	if (atoi(nt_min) < 10) {
		mystrcat(cp_file_name, "0");
		mystrcat(cp_file_name, nt_min);
	}
	else {
		mystrcat(cp_file_name, nt_min);
	}
	printf("cp_file_name : %s\n", cp_file_name);
	strcpy(full_file_name, "movie_list.");
	mystrcat(full_file_name, cp_file_name);
	printf("full_file_name : %s\n", full_file_name);

	fp_copy = fopen(full_file_name, "wt");
	rewind(fp);	//movie_list의 맨 앞으로 파일 포인터를 옮김
	while ((ch = fgetc(fp)) != EOF)
		fputc(ch, fp_copy);

	fclose(fp);
	fclose(fp_copy);
	printf("\n");
}

void load_director() {	//director_log를 읽어서 d 링크드 리스트를 만들어 놓는 함수
	char *token, *line, *menu;	//토큰과 한줄을 저장하는 것과 메뉴(add, delete, update)를 저장할 포인터
	char *name, *sex, *birth, *best_movies;	//director에 넣을 쪼개놓은 멤버들 저장할 포인터
	char *full_file_name, *cp_file_name, *nt_year, *nt_mon, *nt_mday, *nt_hour, *nt_min;	//시간들을 문자열로 변환해서 저장할 포인터와 다 합칠 부분
	int serial_num;
	char ch;
	director *d_load, *d_temp;
	time_t t = time(NULL);	//타임 구조체 선언
	struct tm tm = *localtime(&t);
	d_load = (director *)malloc(sizeof(director));

	full_file_name = (char *)malloc(sizeof(char) * 25);
	cp_file_name = (char *)malloc(sizeof(char) * 15);
	nt_year = (char *)malloc(sizeof(char) * 5);
	nt_mon = (char *)malloc(sizeof(char) * 3);
	nt_mday = (char *)malloc(sizeof(char) * 3);
	nt_hour = (char *)malloc(sizeof(char) * 3);
	nt_min = (char *)malloc(sizeof(char) * 3);

	sprintf(nt_year, "%d", tm.tm_year + 1900);
	//printf("year : %s\n", nt_year);
	strcpy(cp_file_name, nt_year);
	sprintf(nt_mon, "%d", tm.tm_mon + 1);
	//printf("month : %s\n", nt_mon);
	sprintf(nt_mday, "%d", tm.tm_mday);
	//printf("day : %s\n", nt_mday);
	sprintf(nt_hour, "%d", tm.tm_hour);
	//printf("hour : %s\n", nt_hour);
	sprintf(nt_min, "%d", tm.tm_min);
	//printf("minute : %s\n", nt_min);

	token = (char *)malloc(sizeof(char) * 50);
	line = (char *)malloc(sizeof(char) * 200);

	FILE *fp, *fp_copy;	//director_log를 위한것과 director_list를 시간붙여서 저장할 파일 포인터
	fp = fopen("director_log", "r");
	if (fp == NULL)
		return;

	while (fgets(line, 200, fp) != NULL) {	//log파일을 줄이 없을 때까지 읽음
		*(line + strlen(line) - 1) = 0;	//마지막에 읽어온 \n을 없애줌
		//printf("%s\n", line);

		token = strtok(line, ":");
		//printf("token : %s\n", token);
		menu = (char *)malloc(sizeof(char) * strlen(token) + 1);
		strcpy(menu, token);

		token = strtok(NULL, ":");
		//printf("serial_num : %s\n", token);
		serial_num = atoi(token);	//문자열인 token을 정수로 변환

		if (!strcmp(menu, "add"))
			serial_d_num = serial_num + 1;	//나중에 add d를 할 때 올바른 시리얼 넘버를 갖게함


		if (strcmp(menu, "delete")) {
			token = strtok(NULL, ":");
			token = anti_colon_proc(token);	//??;를 :로 바꿔줌
			//printf("name : %s\n", token);
			name = (char *)malloc(sizeof(char) * strlen(token) + 1);
			strcpy(name, token);

			token = strtok(NULL, ":");
			token = anti_colon_proc(token);
			//printf("sex : %s\n", token);
			sex = (char *)malloc(sizeof(char) * strlen(token) + 1);
			strcpy(sex, token);

			token = strtok(NULL, ":");
			token = anti_colon_proc(token);
			//printf("birth : %s\n", token);
			birth = (char *)malloc(sizeof(char) * strlen(token) + 1);
			strcpy(birth, token);

			token = strtok(NULL, ":");
			token = anti_colon_proc(token);
			if (*token == '=') {
				//printf("= is comparamised\n");
				*(token + strlen(token) - 1) = 0;	//마지막에 읽어온 폼 피드(form feed?)를 없애줌
			}
			//printf("best_movies : %s\n", token);
			best_movies = (char *)malloc(sizeof(char) * strlen(token) + 1);
			strcpy(best_movies, token);
		}


		if (!strcmp(menu, "add")) {	//tag가 add이면 실행하는 것
			if (root_d_num == 0) {	//링크드 리스트의 처음 헤더를 저장
				root_director = d_load;
				root_d_num = 1;
			}
			d_load->serial_number = serial_num;
			d_load->name = (char *)malloc(sizeof(char) * strlen(name) + 1);
			strcpy(d_load->name, name);
			d_load->sex = (char *)malloc(sizeof(char) * strlen(sex) + 1);
			strcpy(d_load->sex, sex);
			d_load->birth = (char *)malloc(sizeof(char) * strlen(birth) + 1);
			strcpy(d_load->birth, birth);
			d_load->best_movies = (char *)malloc(sizeof(char) * strlen(best_movies) + 1);
			strcpy(d_load->best_movies, best_movies);

			d_load->next = (director *)malloc(sizeof(director));	//d_load의 next포인터를 동적할당
			d_load = d_load->next;	//d_load을 현재 d_load의 next로 바꿈
			d_temp = d_load;	//링크드 리스트의 마지막을 d_temp에다가 저장
			d_load->next = NULL;	//지금의 d_load의 next를 null로 해줌
		}
		else if (!strcmp(menu, "update")) {	//tag가 update이면 실행하는 것
			d_load = root_director;
			while (1) {
				if (d_load->serial_number == serial_num) {	//update하고자 하는 시리얼 넘버와 일치하면 실행
					if (strcmp(name, "="))
						strcpy(d_load->name, name);
					if (strcmp(sex, "="))
						strcpy(d_load->sex, sex);
					if (strcmp(birth, "="))
						strcpy(d_load->birth, birth);
					if (strcmp(best_movies, "="))
						strcpy(d_load->best_movies, best_movies);

					break;
				}
				if (d_load->next == NULL)
					break;
				d_load = d_load->next;
			}
			d_load = d_temp;
		}
		else if (!strcmp(menu, "delete")) {	//tag가 delete이면 실행하는 것
			d_load = root_director;
			while (1) {
				if (d_load->serial_number == serial_num) {	//delete하고자 하는 시리얼 넘버와 일치하면 실행
					d_load->name = NULL;
					d_load->sex = NULL;
					d_load->birth = NULL;
					d_load->best_movies = NULL;

					break;
				}
				d_load = d_load->next;
			}
			if (d_load->next == NULL)
				break;
			d_load = d_temp;
		}
		printf("\n");
	}
	d = d_load;

	strcat(cp_file_name, nt_mon);	//movie_list파일을 새로 저장할 때 확장자를 날짜로 하게 하는 부분
	if (atoi(nt_mday) < 10) {
		mystrcat(cp_file_name, "0");
		mystrcat(cp_file_name, nt_mday);
	}
	else {
		mystrcat(cp_file_name, nt_mday);
	}

	if (atoi(nt_hour) < 10) {
		mystrcat(cp_file_name, "0");
		mystrcat(cp_file_name, nt_hour);
	}
	else {
		mystrcat(cp_file_name, nt_hour);
	}

	if (atoi(nt_min) < 10) {
		mystrcat(cp_file_name, "0");
		mystrcat(cp_file_name, nt_min);
	}
	else {
		mystrcat(cp_file_name, nt_min);
	}
	//printf("cp_file_name : %s\n", cp_file_name);
	strcpy(full_file_name, "director_list.");
	mystrcat(full_file_name, cp_file_name);
	//printf("full_file_name : %s\n", full_file_name);

	fp_copy = fopen(full_file_name, "wt");
	rewind(fp);	//movie_list의 맨 앞으로 파일 포인터를 옮김
	while ((ch = fgetc(fp)) != EOF)
		fputc(ch, fp_copy);

	fclose(fp);
	fclose(fp_copy);
	printf("\n");
}

void load_actor() {	//actor_log를 읽어서 a 링크드 리스트를 만들어 놓는 함수
	char *token, *line, *menu;	//토큰과 한줄을 저장하는 것과 메뉴(add, delete, update)를 저장할 포인터
	char *name, *sex, *birth, *best_movies;	//actor에 넣을 쪼개놓은 멤버들 저장할 포인터
	char *full_file_name, *cp_file_name, *nt_year, *nt_mon, *nt_mday, *nt_hour, *nt_min;	//시간들을 문자열로 변환해서 저장할 포인터와 다 합칠 부분
	int serial_num;
	char ch;
	actor *a_load, *a_temp;
	time_t t = time(NULL);	//타임 구조체 선언
	struct tm tm = *localtime(&t);
	a_load = (actor *)malloc(sizeof(actor));

	full_file_name = (char *)malloc(sizeof(char) * 25);
	cp_file_name = (char *)malloc(sizeof(char) * 15);
	nt_year = (char *)malloc(sizeof(char) * 5);
	nt_mon = (char *)malloc(sizeof(char) * 3);
	nt_mday = (char *)malloc(sizeof(char) * 3);
	nt_hour = (char *)malloc(sizeof(char) * 3);
	nt_min = (char *)malloc(sizeof(char) * 3);

	sprintf(nt_year, "%d", tm.tm_year + 1900);
	//printf("year : %s\n", nt_year);
	strcpy(cp_file_name, nt_year);
	sprintf(nt_mon, "%d", tm.tm_mon + 1);
	//printf("month : %s\n", nt_mon);
	sprintf(nt_mday, "%d", tm.tm_mday);
	//printf("day : %s\n", nt_mday);
	sprintf(nt_hour, "%d", tm.tm_hour);
	//printf("hour : %s\n", nt_hour);
	sprintf(nt_min, "%d", tm.tm_min);
	//printf("minute : %s\n", nt_min);

	token = (char *)malloc(sizeof(char) * 50);
	line = (char *)malloc(sizeof(char) * 200);

	FILE *fp, *fp_copy;	//actor_log를 위한것과 actor_list를 시간붙여서 저장할 파일 포인터
	fp = fopen("actor_log", "r");
	if (fp == NULL)
		return;

	while (fgets(line, 200, fp) != NULL) {	//log파일을 줄이 없을 때까지 읽음
		*(line + strlen(line) - 1) = 0;	//마지막에 읽어온 \n을 없애줌
		//printf("%s\n", line);

		token = strtok(line, ":");
		//printf("token : %s\n", token);
		menu = (char *)malloc(sizeof(char) * strlen(token) + 1);
		strcpy(menu, token);

		token = strtok(NULL, ":");
		//printf("serial_num : %s\n", token);
		serial_num = atoi(token);	//문자열인 token을 정수로 변환

		if (!strcmp(menu, "add"))
			serial_d_num = serial_num + 1;	//나중에 add a를 할 때 올바른 시리얼 넘버를 갖게함


		if (strcmp(menu, "delete")) {
			token = strtok(NULL, ":");
			token = anti_colon_proc(token);	//??;를 :로 바꿔줌
			//printf("name : %s\n", token);
			name = (char *)malloc(sizeof(char) * strlen(token) + 1);
			strcpy(name, token);

			token = strtok(NULL, ":");
			token = anti_colon_proc(token);
			//printf("sex : %s\n", token);
			sex = (char *)malloc(sizeof(char) * strlen(token) + 1);
			strcpy(sex, token);

			token = strtok(NULL, ":");
			token = anti_colon_proc(token);
			//printf("birth : %s\n", token);
			birth = (char *)malloc(sizeof(char) * strlen(token) + 1);
			strcpy(birth, token);

			token = strtok(NULL, ":");
			token = anti_colon_proc(token);
			if (*token == '=') {
				//printf("= is comparamised\n");
				*(token + strlen(token) - 1) = 0;	//마지막에 읽어온 폼 피드(form feed?)를 없애줌
			}
			//printf("best_movies : %s\n", token);
			best_movies = (char *)malloc(sizeof(char) * strlen(token) + 1);
			strcpy(best_movies, token);
		}


		if (!strcmp(menu, "add")) {	//tag가 add이면 실행하는 것
			if (root_a_num == 0) {	//링크드 리스트의 처음 헤더를 저장
				root_actor = a_load;
				root_a_num = 1;
			}
			a_load->serial_number = serial_num;
			a_load->name = (char *)malloc(sizeof(char) * strlen(name) + 1);
			strcpy(a_load->name, name);
			a_load->sex = (char *)malloc(sizeof(char) * strlen(sex) + 1);
			strcpy(a_load->sex, sex);
			a_load->birth = (char *)malloc(sizeof(char) * strlen(birth) + 1);
			strcpy(a_load->birth, birth);
			a_load->best_movies = (char *)malloc(sizeof(char) * strlen(best_movies) + 1);
			strcpy(a_load->best_movies, best_movies);

			a_load->next = (actor *)malloc(sizeof(actor));	//a_load의 next포인터를 동적할당
			a_load = a_load->next;	//a_load을 현재 a_load의 next로 바꿈
			a_temp = a_load;	//링크드 리스트의 마지막을 a_temp에다가 저장
			a_load->next = NULL;	//지금의 a_load의 next를 null로 해줌
		}
		else if (!strcmp(menu, "update")) {	//tag가 update이면 실행하는 것
			a_load = root_actor;
			while (1) {
				if (a_load->serial_number == serial_num) {	//update하고자 하는 시리얼 넘버와 일치하면 실행
					if (strcmp(name, "="))
						strcpy(a_load->name, name);
					if (strcmp(sex, "="))
						strcpy(a_load->sex, sex);
					if (strcmp(birth, "="))
						strcpy(a_load->birth, birth);
					if (strcmp(best_movies, "="))
						strcpy(a_load->best_movies, best_movies);

					break;
				}
				if (a_load->next == NULL)
					break;
				a_load = a_load->next;
			}
			a_load = a_temp;
		}
		else if (!strcmp(menu, "delete")) {	//tag가 delete이면 실행하는 것
			a_load = root_actor;
			while (1) {
				if (a_load->serial_number == serial_num) {	//delete하고자 하는 시리얼 넘버와 일치하면 실행
					a_load->name = NULL;
					a_load->sex = NULL;
					a_load->birth = NULL;
					a_load->best_movies = NULL;

					break;
				}
				a_load = a_load->next;
			}
			if (a_load->next == NULL)
				break;
			a_load = a_temp;
		}
		printf("\n");
	}
	a = a_load;

	strcat(cp_file_name, nt_mon);	//movie_list파일을 새로 저장할 때 확장자를 날짜로 하게 하는 부분
	if (atoi(nt_mday) < 10) {
		mystrcat(cp_file_name, "0");
		mystrcat(cp_file_name, nt_mday);
	}
	else {
		mystrcat(cp_file_name, nt_mday);
	}

	if (atoi(nt_hour) < 10) {
		mystrcat(cp_file_name, "0");
		mystrcat(cp_file_name, nt_hour);
	}
	else {
		mystrcat(cp_file_name, nt_hour);
	}

	if (atoi(nt_min) < 10) {
		mystrcat(cp_file_name, "0");
		mystrcat(cp_file_name, nt_min);
	}
	else {
		mystrcat(cp_file_name, nt_min);
	}
	//printf("cp_file_name : %s\n", cp_file_name);
	strcpy(full_file_name, "actor_list.");
	mystrcat(full_file_name, cp_file_name);
	//printf("full_file_name : %s\n", full_file_name);

	fp_copy = fopen(full_file_name, "wt");
	rewind(fp);	//movie_list의 맨 앞으로 파일 포인터를 옮김
	while ((ch = fgetc(fp)) != EOF)
		fputc(ch, fp_copy);

	fclose(fp);
	fclose(fp_copy);
	printf("\n");
}

void handler(int sig) {	//Ctrl + c 눌러도 종료되지 않고 물어보게 하는 함수
	char *answer;
	answer = (char *)malloc(sizeof(char) * 5);
	printf("\nControl+c\n");
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
	FILE *fp;
	fp = fopen("movie_log", "at");

	temp = (char *)malloc(sizeof(char) * 200);	//임시 포인터 동적할당

	if (root_m_num == 0) {	//링크드 리스트 처음 헤더를 root_movie에 저장
		root_movie = m;
		root_m_num = 1;
	}
	m->serial_number = serial_m_num++;

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
	scanf("%[^\n]s", temp);
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

	fprintf(fp, "add:%d:%s:%s:%s:%s:%s:%s\n", m->serial_number, colon_proc(m->title), colon_proc(m->genre), colon_proc(m->director), colon_proc(m->year), colon_proc(m->time), colon_proc(m->actors));

	m->next = (movie *)malloc(sizeof(movie));	//m의 next포인터를 동적할당
	m = m->next;	//m을 현재 m의 next로 바꿈
	m->next = NULL;	//지금의 m의 next를 null로 해줌

	fclose(fp);
	printf("@@ Done\n\n");
}

void add_director() {	//director 정보 입력받는 함수
	char *temp;
	FILE *fp;
	temp = (char *)malloc(sizeof(char) * 200);
	fp = fopen("director_log", "at");

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

	fprintf(fp, "add:%d:%s:%s:%s:%s\n", d->serial_number, colon_proc(d->name), colon_proc(d->sex), colon_proc(d->birth), colon_proc(d->best_movies));

	d->next = (director *)malloc(sizeof(director));	//d의 next포인터를 동적할당
	d = d->next;	//d를 현재 d의 next로 바꿈
	d->next = NULL;	//지금의 d의 next를 null로 해줌

	fclose(fp);
	printf("@@ Done\n\n");
}

void add_actor() {	//actor의 정보를 입력받는 함수
	char *temp;
	FILE *fp;
	temp = (char *)malloc(sizeof(char) * 200);
	fp = fopen("actor_log", "at");

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

	fprintf(fp, "add:%d:%s:%s:%s:%s\n", a->serial_number, colon_proc(a->name), colon_proc(a->sex), colon_proc(a->birth), colon_proc(a->best_movies));

	a->next = (actor *)malloc(sizeof(actor));	//a의 next포인터를 동적할당
	a = a->next;	//a을 현재 a의 next로 바꿈
	a->next = NULL;	//지금의 a의 next를 null로 해줌

	fclose(fp);
	printf("@@ Done\n\n");
}

void save_director() {
	FILE *fp;
	fp = fopen("director_list", "wt");
	d = root_director;
	while (d->next != NULL) {
		if (d->name == NULL) {
			d = d->next;
			continue;
		}
		fprintf(fp, "%d:%s:%s:%s:%s\n", d->serial_number, colon_proc(d->name), colon_proc(d->sex), colon_proc(d->birth), colon_proc(d->best_movies));
		d = d->next;
	}
	fclose(fp);
	printf("@@ Done\n\n");
}

void save_movie() {
	printf("error1\n");
	FILE *fp;
	fp = fopen("movie_list", "wt");
	printf("error2\n");
	m = root_movie;
	printf("error3\n");
	while (m->next != NULL) {
		if (m->title == NULL) {
			m = m->next;
			continue;
		}
		fprintf(fp, "%d:%s:%s:%s:%s:%s:%s\n", m->serial_number, colon_proc(m->title), colon_proc(m->genre), colon_proc(m->director), colon_proc(m->year), colon_proc(m->time), colon_proc(m->actors));
		m = m->next;
	}
	printf("error5\n");
	fclose(fp);
	printf("@@ Done\n\n");
}

void save_actor() {
	FILE *fp;
	fp = fopen("actor_list", "wt");
	a = root_actor;
	while (a->next != NULL) {
		if (a->name == NULL) {
			a = a->next;
			continue;
		}
		fprintf(fp, "%d:%s:%s:%s:%s\n", a->serial_number, colon_proc(a->name), colon_proc(a->sex), colon_proc(a->birth), colon_proc(a->best_movies));
		a = a->next;
	}
	fclose(fp);
	printf("@@ Done\n\n");
}

char *colon_proc(char *s) {	//':'을 "??;"로 치환하는 함수
	char *result, *sr;	//result는 치환한 결과저장, sr은 계속해서 따져주면서 바뀌는 문자열
	char *colon, *newstr;	//콜론을 저장할 곳과 ??;를 저장할 곳
	colon = (char *)malloc(sizeof(char) * 2);	//콜론 동적 할당
	newstr = (char *)malloc(sizeof(char) * 4);	//??; 동적할당
	colon = ":";
	newstr = "??;";

	size_t i, count = 0;	//사이즈를 받을 변수 i 선언
	size_t colonlen = strlen(colon);
	size_t newlen = strlen(newstr);

	for (i = 0; s[i] != '\0';) {	//:를 ??;로 바꾸면서 필요할 메모리를 계산하는 반복문
		if (memcmp(&s[i], colon, colonlen) == 0) {
			count++;
			i += colonlen;
		}
		else i++;
	}

	result = (char *)malloc(i + 1 + count * (newlen - colonlen));	//필요한 메모리만큼 새로 동적할당

	sr = result;
	while (*s) {	//콜론을 ??;로 바꿔주는 반복문
		if (memcmp(s, colon, colonlen) == 0) {
			memcpy(sr, newstr, newlen);
			sr += newlen;
			s += colonlen;
		}
		else *sr++ = *s++;
	}
	*sr = '\0';	//마지막에 NULL 저장

	return result;
}

char *anti_colon_proc(char *s) {	//'??;'을 ":"로 치환하는 함수
	char *result, *sr;	//result는 치환한 결과저장, sr은 계속해서 따져주면서 바뀌는 문자열
	char *anti_colon, *newstr;	//??;을 저장할 곳과 콜론을 저장할 곳
	anti_colon = (char *)malloc(sizeof(char) * 2);	//"??;" 동적 할당
	newstr = (char *)malloc(sizeof(char) * 4);	//':' 동적할당
	anti_colon = "??;";
	newstr = ":";

	size_t i, count = 0;	//사이즈를 받을 변수 i 선언
	size_t anti_colonlen = strlen(anti_colon);
	size_t newlen = strlen(newstr);

	for (i = 0; s[i] != '\0';) {	//??;를 ':'로 바꾸면서 필요할 메모리를 계산하는 반복문
		if (memcmp(&s[i], anti_colon, anti_colonlen) == 0) {
			count++;
			i += anti_colonlen;
		}
		else i++;
	}

	result = (char *)malloc(i + 1 + count * (newlen - anti_colonlen));	//필요한 메모리만큼 새로 동적할당

	sr = result;
	while (*s) {	//??;을 콜론으로 바꿔주는 반복문
		if (memcmp(s, anti_colon, anti_colonlen) == 0) {
			memcpy(sr, newstr, newlen);
			sr += newlen;
			s += anti_colonlen;
		}
		else *sr++ = *s++;
	}
	*sr = '\0';	//마지막에 NULL 저장

	return result;
}


void print_m(int sn){ //movie print 함수
	movie *m_p;
	director *d_p;
	actor *a_p;
   m_p = root_movie;
   d_p = root_director;
   a_p = root_actor;
   while(m_p->serial_number != sn){ //입력한 serial_number가 없는 경우 메시지 출력
      if(m_p->next == NULL){
         printf("serial number is not found\n\n");
         return;
      }
      m_p = m_p->next;
   }
	if(m_p->title == NULL){ //delete된 레코드일 경우
	 	printf("*deleted record*\n\n", m_p->serial_number);
		return;
	}

  printf("%d, %s, %s\n", m_p->serial_number, m_p->title == NULL ? "-" : m_p->title, m_p->genre==NULL ? "-" : m_p->genre);
	if(root_d_num == 0){ //director에 아무것도 저장이 안 돼있는 상태에서의 오류를 피하기 위한 코드
		printf("(-)\n");
	}

	else{ //director 링크드 리스트를 읽어 해당하는 director가 있는지 검사
		while(1){
			if(d_p->next == NULL){
				break;
			}
			if(d_p->name == NULL){
				d_p = d_p->next;
				continue;
			}
			if(m_p->director == NULL){
				d_p = d_p->next;
				continue;
			}
			if(!strcmp(m_p->director, d_p->name)){ //해당하는 movie 레코드에서 출력하는 director가 director 레코드에 있을 경우
				break;
			}
   	   d_p = d_p->next;
   	}
		printf("D : %s(%s)\n", m_p->director==NULL? "-":m_p->director, d_p->next==NULL ? "-" : d_p->birth); //director가 레코드에 있을 경우엔 해당 레코드에서 읽어오고 없는 경우엔 "-" 출력.
	}
	char *a_name = NULL;
	char *string = NULL;

	int i = 1; //배우 수를 출력하기 위한 변수
	if(m_p->actors != NULL){
		a_name = (char *)malloc(sizeof(char)*strlen(m_p->actors)+1); //배우가 몇 명일지 정확히 알 수 없으므로 최대값 할당.
		string = (char *)malloc(sizeof(char)*strlen(m_p->actors)+1);
		strcpy(string, m_p->actors); //movie 레코드의 actors 통째로 복사
		a_name = strtok(string, ","); //하나하나 끊음

	if(root_a_num == 0){ //배우 레코드에 아무것도 저장되어있지 않을 경우 에러를 피하기 위한 코드
	//	printf("A%d : %s(-)\n", i++, a_name);
	}
	else{  //actors 링크드 리스트를 읽어 해당 actor가 있는지 검사
		while(1){
			if(a_p->next == NULL)
				break;
			if(a_p->name == NULL){
				a_p = a_p ->next;
				continue;
			}
			if(!strncmp(a_name, a_p->name, strlen(a_name)-1))
				break;
			a_p = a_p->next;
		}
		printf("A%d : %s(%s)", i++, a_name==NULL? "-":a_name, (a_p->next == NULL) ? "-" : a_p->birth); //찾은 경우엔 actor 레코드에서 정보를 읽어오고 없는 경우엔 "-" 출력
	}

		a_name = strtok(NULL, ",");
		while(1){ //두번째 actor부터의 반복문(strtok 함수의 두번째 실행부터 형식이 바뀌기 때문에 나누었음)
			if(a_name == NULL){
				printf("\n\n");
				return;
			}
			if(*a_name == ' '){ //배우 이름이 ', '로 입력되었을 경우 strtok로 끊으면 다음 배우의 이름은 첫글자가 공백이므로 공백을 없애주는 코드
				a_name = a_name+sizeof(char);
			}
			a_p = root_actor;
			while(1){
				if(a_p->next == NULL)
					break;
				if(a_p->name == NULL){
					a_p = a_p->next;
					continue;
				}
				if(!strncmp(a_name, a_p->name,strlen(a_name)-1))
					break;
				a_p = a_p->next;
			}
			printf("A%d : %s(%s)\n", i++, a_name, a_p->next == NULL ? "-" : a_p->birth);
			a_name = strtok(NULL, ",");
		}
	}
	else{
		printf("A%d : -(-)\n\n", i++);
		return;
	}



}
void print_d(int sn){ //director 레코드의 print 함수
	movie *m_p;
	director *d_p;
	actor *a_p;
   m_p = root_movie;
   d_p = root_director;
   a_p = root_actor;
   while(d_p->serial_number != sn){ //serial_number가 없을 경우의 에러메시지 출력
      if(root_d_num == 0 || d_p->next == NULL){
         printf("serial number is not found\n\n");
         return;
      }
      d_p = d_p->next;
   }
	 if(d_p->name == NULL){
		 printf("*deleted record*\n");
		 return;
	 }

	char *a_best_movie = (char *)malloc(sizeof(char)*strlen(d_p->best_movies)+1); //best_movies에서 한 작품씩 끊어 저장하기 위한 포인터
	char *string = (char *)malloc(sizeof(char)*strlen(d_p->best_movies)+1); //best_movies를 통째로 저장하기 위한 포인터

  printf("%d, %s, %s, %s\n", d_p->serial_number, d_p->name, d_p->sex, d_p->birth); //director의 정보 출력
	strcpy(string, d_p->best_movies);
	a_best_movie = strtok(string, ",");

	while(1){ //a_best_movie가 movie 레코드에 있는지 검사
		if(a_best_movie == NULL){//best movie가 입력되지 않았을 때
			printf("\n");
			return;
		}
		if(root_m_num == 0 || m_p->next == NULL){ //movie 레코드에 아무것도 입력되지 않아서 뜨는 에러를 피하기 위한 코드 + 못 찾았을 경우 break
			break;
		}
		if(m_p->title == NULL){
			m_p = m_p->next;
			continue;
		}
		if(!strncmp(a_best_movie, m_p->title, strlen(a_best_movie)-1)){ //찾으면 break로 빠져나옴
			break;
		}
		m_p = m_p->next;
	}
	printf("%s\n", a_best_movie);
	printf("\t%s\t, \t%s\t, \t%s\n", a_best_movie, m_p->next==NULL ? "-" : m_p->year, m_p->next==NULL ? "-" : m_p->time);
	a_best_movie = strtok(NULL, ",");
	while(1){		//두번째 best_movies부터의 반복문
		if(a_best_movie == NULL){
			printf("\n");
			return;
		}
		if(*a_best_movie == ' ')
			a_best_movie = a_best_movie+sizeof(char);
		m_p = root_movie;
		while(1){
				if(m_p->next == NULL)
					break;
				if(m_p->title == NULL){
					m_p=m_p->next;
					continue;
				}
				if(!strncmp(a_best_movie, m_p->title, strlen(a_best_movie)-1))
					break;
				m_p = m_p->next;
		}
		printf("%s, %s, %s\n", a_best_movie, m_p->next==NULL? "-" : m_p->year, m_p->next==NULL? "-" : m_p->time);
		a_best_movie = strtok(NULL, ",");
	}

	printf("\n");


}


void print_a(int sn){
	movie *m_p;
	director *d_p;
	actor *a_p;
   m_p = root_movie;
   d_p = root_director;
   a_p = root_actor;
   while(a_p->serial_number != sn){
      if(a_p->next == NULL){
         printf("serial number is not found\n\n");
         return;
      }
      a_p = a_p->next;
   }
	 if(a_p->name==NULL){
		 printf("*deleted record*\n");
		 return;
	 }
	char *a_best_movie = (char *)malloc(sizeof(char)*strlen(a_p->best_movies)+1);
	char *string = (char *)malloc(sizeof(char)*strlen(a_p->best_movies)+1);

  printf("%d, %s, %s, %s\n", a_p->serial_number, a_p->name, a_p->sex, a_p->birth);

	strcpy(string, a_p->best_movies);
	a_best_movie = strtok(string, ",");
	while(1){
		if(a_best_movie == NULL){
			printf("\n"); //best movie가 아예 입력되지 않았을 때
			return;
		}
		if(m_p->next==NULL){ //best movie가 목록에 없을 때
			break;
		}
		if(m_p->title == NULL){
			m_p = m_p->next;
			continue;
		}
		if(!strncmp(a_best_movie, m_p->title, strlen(a_best_movie)-1))
			break;
		m_p = m_p->next;
	}
	printf("%s, %s, %s\n", a_best_movie, m_p->next == NULL ? "-" : m_p->year, m_p->next == NULL ? "-" : m_p->time);
	a_best_movie = strtok(NULL, ",");
	while(1){	//두번째 대표작부터의 반복문
		if(a_best_movie == NULL){
			printf("\n");
			return;
		}
		if(*a_best_movie == ' ')
			a_best_movie = a_best_movie+sizeof(char);
		m_p = root_movie;
		while(1){
				if(m_p->next == NULL){
					break;
				}
				if(m_p->title == NULL){
					m_p = m_p->next;
					continue;
				}
				if(!strncmp(a_best_movie, m_p->title, strlen(a_best_movie)-1))
					break;
				m_p = m_p->next;
			}
		printf("%s, %s, %s\n", a_best_movie, m_p->next==NULL ? "-" : m_p->year, m_p->next==NULL ? "-" : m_p->time);
		a_best_movie = strtok(NULL, ",");
	}

}
void print_m_file(int sn, char *fn){ //sort를 위한 file 출력 함수(print함수와 거의 같음)
	movie *m_p;
	director *d_p;
	actor *a_p;
   m_p = root_movie;
   d_p = root_director;
   a_p = root_actor;
	 FILE *ofp = fopen(fn, "a");
   while(m_p->serial_number != sn){
      if(m_p->next == NULL){
         printf("serial number is not found\n\n");
         return;
      }
      m_p = m_p->next;
   }
	 if(m_p->title==NULL){
		 printf("*deleted record*\n");
		 return;
	 }
  fprintf(ofp, "%d, %s, %s\n", m_p->serial_number, m_p->title == NULL ? "-" : m_p->title, m_p->genre == NULL? "-" : m_p->genre);
	if(root_d_num == 0){
		fprintf(ofp, "(-)\n");
	}
	else{
   	while(1){
			if(d_p->next == NULL){
					break;
			}
			if(d_p->name == NULL){
				d_p=d_p->next;
				continue;
			}
			if(!strcmp(m_p->director, d_p->name)){
				break;
			}
   	   d_p = d_p->next;
   	}
		fprintf(ofp, "D : %s(%s)\n", m_p->director == NULL? "-" : m_p->director, d_p->next==NULL ? "-" : d_p->birth);
	}

	char *a_name = (char *)malloc(sizeof(char)*strlen(m_p->actors)+1);
	char *string = (char *)malloc(sizeof(char)*strlen(m_p->actors)+1);

	strcpy(string, m_p->actors);
	a_name = strtok(string, ",");
	int i = 1;

	if(root_a_num == 0){
		fprintf(ofp, "A%d : %s(-)\n", i++, a_name);
	}
	else{
		while(1){
			if(a_p->next == NULL)
				break;
			if(a_p->name == NULL){
				a_p = a_p->next;
				continue;
			}
			if(!strncmp(a_name, a_p->name, strlen(a_name)-1))
				break;
			a_p = a_p->next;
		}
		fprintf(ofp, "A%d : %s(%s)\n", i++, a_name, a_p->next == NULL ? "-" : a_p->birth);
	}

	a_name = strtok(NULL, ",");
	while(1){ //두번째 actor부터의 반복문
		if(a_name == NULL){
			fprintf(ofp, "\n");
			fclose(ofp);
			return;
		}
		if(*a_name == ' '){
			a_name = a_name+sizeof(char);
		}
		a_p = root_actor;
		while(1){
			if(a_p->next == NULL)
				break;
			if(a_p->name == NULL){
				a_p = a_p->next;
				continue;
			}
			if(!strncmp(a_name, a_p->name, strlen(a_name)-1))
				break;
			a_p = a_p->next;
		}
		fprintf(ofp, "A%d : %s(%s)\n", i++, a_name, a_p->next == NULL ? "-" : a_p->birth);
		a_name = strtok(NULL, ",");
	}

}

void print_d_file(int sn, char *fn){
	movie *m_p;
	director *d_p;
	actor *a_p;
   m_p = root_movie;
   d_p = root_director;
   a_p = root_actor;
	 FILE *ofp = fopen(fn, "a");
   while(d_p->serial_number != sn){
      if(root_d_num == 0 || d_p->next == NULL){
         printf("serial number is not found\n\n");
         return;
      }
      d_p = d_p->next;
   }
	 if (d_p->name==NULL){
		 printf("*deleted record*\n");
		 return;
	 }

	char *a_best_movie = (char *)malloc(sizeof(char)*strlen(d_p->best_movies)+1);
	char *string = (char *)malloc(sizeof(char)*strlen(d_p->best_movies)+1);

  fprintf(ofp, "%d, %s, %s, %s\n", d_p->serial_number, d_p->name==NULL? "-" : d_p->name, d_p->sex==NULL? "-" : d_p->sex, d_p->birth==NULL?"-":d_p->birth);
	strcpy(string, d_p->best_movies);
	a_best_movie = strtok(string, ",");

	while(1){
		if(a_best_movie == NULL){//best movie가 입력되지 않았을 때
			fprintf(ofp, "\n");
			return;
		}
		if(root_m_num == 0 || m_p->next == NULL){
			break;
		}
		if(m_p->title ==NULL){
			m_p=m_p->next;
			continue;
		}
		if(!strncmp(a_best_movie, m_p->title, strlen(a_best_movie)-1)){
			break;
		}
		m_p = m_p->next;
	}
	fprintf(ofp, "%s, %s, %s\n", a_best_movie, m_p->next==NULL ? "-" : m_p->year, m_p->next==NULL ? "-" : m_p->time);
	a_best_movie = strtok(NULL, ",");
	while(1){		//두번째 대표작부터의 반복문
		if(a_best_movie == NULL){
			fprintf(ofp, "\n");
			fclose(ofp);
			return;
		}
		if(*a_best_movie == ' ')
			a_best_movie = a_best_movie+sizeof(char);
		m_p = root_movie;
		while(1){
				if(m_p->next == NULL)
					break;
				if(m_p->title == NULL){
					m_p=m_p->next;
					continue;
				}
				if(!strncmp(a_best_movie, m_p->title, strlen(a_best_movie)-1))
					break;
				m_p = m_p->next;
		}
		fprintf(ofp, "%s, %s, %s\n", a_best_movie, m_p->next==NULL? "-" : m_p->year, m_p->next==NULL? "-" : m_p->time);
		a_best_movie = strtok(NULL, ",");
	}
}

void print_a_file(int sn, char *fn){
	movie *m_p;
	director *d_p;
	actor *a_p;
   m_p = root_movie;
   d_p = root_director;
   a_p = root_actor;
	 FILE *ofp = fopen(fn, "a");
   while(a_p->serial_number != sn){
      if(a_p->next == NULL){
         printf("serial number is not found\n\n");
         return;
      }
      a_p = a_p->next;
   }
	 if(a_p->name == NULL){
		 printf("*deleted record*\n");
		 return;
	 }

	char *a_best_movie = (char *)malloc(sizeof(char)*strlen(a_p->best_movies)+1);
	char *string = (char *)malloc(sizeof(char)*strlen(a_p->best_movies)+1);

  fprintf(ofp, "%d, %s, %s, %s\n", a_p->serial_number, a_p->name==NULL? "-" : a_p->name, a_p->sex==NULL? "-" : a_p->sex, a_p->birth==NULL? "-" : a_p->birth);

	strcpy(string, a_p->best_movies);
	a_best_movie = strtok(string, ",");
	while(1){
		if(a_best_movie == NULL){
			fprintf(ofp, "\n"); //best movie가 아예 입력되지 않았을 때
			return;
		}
		if(m_p->next==NULL){ //best movie가 목록에 없을 때
			break;
		}
		if(m_p->title == NULL){
			m_p=m_p->next;
			continue;
		}
		if(!strncmp(a_best_movie, m_p->title, strlen(a_best_movie)-1))
			break;
		m_p = m_p->next;
	}
	fprintf(ofp, "%s, %s, %s\n", a_best_movie, m_p->next == NULL ? "-" : m_p->year, m_p->next == NULL ? "-" : m_p->time);
	a_best_movie = strtok(NULL, ",");
	while(1){	//두번째 대표작부터의 반복문
		if(a_best_movie == NULL){
			fprintf(ofp, "\n");
			fclose(ofp);
			return;
		}
		if(*a_best_movie == ' ')
			a_best_movie = a_best_movie+sizeof(char);
		m_p = root_movie;
		while(1){
				if(m_p->next == NULL){
					break;
				}
				if(m_p->title ==NULL){
					m_p=m_p->next;
					continue;
				}
				if(!strncmp(a_best_movie, m_p->title, strlen(a_best_movie)-1))
					break;
				m_p = m_p->next;
			}
		fprintf(ofp, "%s, %s, %s\n", a_best_movie, m_p->next==NULL ? "-" : m_p->year, m_p->next==NULL ? "-" : m_p->time);
		a_best_movie = strtok(NULL, ",");
	}

}

void sort(char *factor, char *option, char *file_name){//구조체 크기 64
	if(strcmp(file_name, "NULL")){//filename이 지정돼있을 때 기존 파일 지움
		FILE *fp = fopen(file_name, "w");
		fclose(fp);
	}

	if(!strcmp(factor, "m")){ // factor == m
		movie *m_p; //링크드리스트 포인터
		sorting *m_string; //movie의 구조체 멤버들을 넣기 위한 구조체
		sorting m_tmp; //정렬을 위한 tmp
		sorting_num *m_num; //movie의 구조체 멤버들을 넣기 위한 구조체
		sorting_num m_tmp_n; //int형 정렬을 위한 tmp
		m_p = root_movie; //시작지점으로 돌려놓음
		int total = 0; //총 레코드 개수를 세기 위한 변수
		while(1){
			if(m_p->next == NULL){
				break;
			}
			total++;
			m_p = m_p->next;
		}
		m_string = (sorting *)malloc(sizeof(sorting)*total); //레코드 수만큼 구조체 포인터에 메모리 할당


		if(!strcmp(option, "NULL") || !strcmp(option, "t")){ //option == NULL or t일 때 (출력 동일)
			m_p = root_movie;
			for(int i=0; i<total; i++){ //movie 레코드의 title을 모두 임시 구조체로 옮겨옴
				if(m_p->title == NULL){
					m_p=m_p->next;
					total--;
					i--;
					continue;
				}
				(*(m_string+i)).string = (char *)malloc(sizeof(char)*strlen(m_p->title)+1);
				strcpy((*(m_string+i)).string, m_p->title);
				(*(m_string+i)).serial_number = m_p->serial_number;
				m_p=m_p->next;

		}
			for(int i=total-1; i>0; i--){ //버블정렬
				for(int j=0; j<i; j++){
					if((strcmp((*(m_string+j)).string, (*(m_string+j+1)).string)) > 0){
						m_tmp = *(m_string+j);
						*(m_string+j) = *(m_string+j+1);
					*(m_string+j+1) = m_tmp;
					}
				}

			}

			if(!strcmp(file_name, "NULL")){ //화면 출력일 때
				for(int i=0; i<total; i++){
					print_m((*(m_string+i)).serial_number);
				}
			}
			else{		//filename 지정한 출력일 때
				for(int i=0; i<total; i++){
					print_m_file((*(m_string+i)).serial_number, file_name);
				}
			}
		}
		else if(!strcmp(option, "g")){ //factor == m, option == g
			m_p = root_movie;
			for(int i=0; i<total; i++){
				if(m_p->title == NULL){
					m_p=m_p->next;
					total--;
					i--;
					continue;
				}
				(*(m_string+i)).string = (char *)malloc(sizeof(char)*strlen(m_p->genre)+1);
				strcpy((*(m_string+i)).string, m_p->genre);
				(*(m_string+i)).serial_number = m_p->serial_number;
				m_p=m_p->next;
			}
			for(int i=total-1; i>0; i--){
				for(int j=0; j<i; j++){
					if((strcmp((*(m_string+j)).string, (*(m_string+j+1)).string)) > 0){
						m_tmp = *(m_string+j);
						*(m_string+j) = *(m_string+j+1);
						*(m_string+j+1) = m_tmp;
					}
				}
			}
			if(!strcmp(file_name, "NULL")){ //화면 출력일 때
				for(int i=0; i<total; i++){
					print_m((*(m_string+i)).serial_number);
				}
			}
			else{		//filename 지정한 출력일 때
				for(int i=0; i<total; i++){
					print_m_file((*(m_string+i)).serial_number, file_name);
				}
			}
		}
		else if(!strcmp(option, "d")){ //factor == m, option == d
			m_p = root_movie;
			for(int i=0; i<total; i++){
				if(m_p->title == NULL){
					m_p=m_p->next;
					total--;
					i--;
					continue;
				}
				(*(m_string+i)).string = (char *)malloc(sizeof(char)*strlen(m_p->director)+1);
				strcpy((*(m_string+i)).string, m_p->director);
				(*(m_string+i)).serial_number = m_p->serial_number;
				m_p=m_p->next;
			}
			for(int i=total-1; i>0; i--){
				for(int j=0; j<i; j++){
					if((strcmp((*(m_string+j)).string, (*(m_string+j+1)).string)) > 0){
						m_tmp = *(m_string+j);
						*(m_string+j) = *(m_string+j+1);
						*(m_string+j+1) = m_tmp;
					}
				}
			}
			if(!strcmp(file_name, "NULL")){ //화면 출력일 때
				for(int i=0; i<total; i++){
					print_m((*(m_string+i)).serial_number);
				}
			}
			else{		//filename 지정한 출력일 때
				for(int i=0; i<total; i++){
					print_m_file((*(m_string+i)).serial_number, file_name);
				}
			}
		}

		else if(!strcmp(option, "y")){ //option == y (연도는 int형으로 비교)
			m_p = root_movie;
			m_num = (sorting_num *)malloc(sizeof(sorting_num)*total);
			for(int i=0; i<total; i++){
				if(m_p->title == NULL){
					m_p=m_p->next;
					total--;
					i--;
					continue;
				}
				(*(m_num+i)).num = atoi(m_p->year);
				(*(m_num+i)).serial_number = m_p->serial_number;
				m_p=m_p->next;
			}
			for(int i=total-1; i>0; i--){
				for(int j=0; j<i; j++){
					if((*(m_num+j)).num > (*(m_num+j+1)).num){
						m_tmp_n = *(m_num+j);
						*(m_num+j) = *(m_num+j+1);
						*(m_num+j+1) = m_tmp_n;
					}
				}
			}
			if(!strcmp(file_name, "NULL")){ //화면 출력일 때
				for(int i=0; i<total; i++){
					print_m((*(m_num+i)).serial_number);
				}
			}
			else{		//filename 지정한 출력일 때
				for(int i=0; i<total; i++){
					print_m_file((*(m_num+i)).serial_number, file_name);
				}
			}
		}
		else if(!strcmp(option, "r")){ //option == t (시간은 int형으로 비교)
			m_p = root_movie;
			m_num = (sorting_num *)malloc(sizeof(sorting_num)*total);
			for(int i=0; i<total; i++){
				if(m_p->title == NULL){
					m_p=m_p->next;
					total--;
					i--;
					continue;
				}
				(*(m_num+i)).num = atoi(m_p->time);
				(*(m_num+i)).serial_number = m_p->serial_number;
				m_p=m_p->next;
			}

			for(int i=total-1; i>0; i--){
				for(int j=0; j<i; j++){
					if((*(m_num+j)).num > (*(m_num+j+1)).num){
						m_tmp_n = *(m_num+j);
						*(m_num+j) = *(m_num+j+1);
						*(m_num+j+1) = m_tmp_n;
					}
				}
			}
			if(!strcmp(file_name, "NULL")){ //화면 출력일 때
				for(int i=0; i<total; i++){
					print_m((*(m_num+i)).serial_number);
				}
			}
			else{		//filename 지정한 출력일 때
				for(int i=0; i<total; i++){
					print_m_file((*(m_num+i)).serial_number, file_name);
				}
			}
		}
		else if(!strcmp(option, "a")){ //factor == m, option == a //걍 첫번째 배우 이름으로 함.
			m_p = root_movie;
			char *token;
			char *st; //임시로 actors를 통째로 담을 포인터
			for(int i=0; i<total; i++){
				if(m_p->title == NULL){
					m_p=m_p->next;
					total--;
					i--;
					continue;
				}
				st = (char *)malloc(sizeof(char)+strlen(m_p->actors)+1);
				strcpy(st, m_p->actors);
				token = strtok(st, ","); //token으로 첫번째 배우만 잘라냄.
				(*(m_string+i)).string = (char *)malloc(sizeof(char)*strlen(token)+1);
				strcpy((*(m_string+i)).string, token); //첫번째 배우를 구조체에 넣음.
				(*(m_string+i)).serial_number = m_p->serial_number;
				m_p=m_p->next;
			}
			for(int i=total-1; i>0; i--){
				for(int j=0; j<i; j++){
					if((strcmp((*(m_string+j)).string, (*(m_string+j+1)).string)) > 0){
						m_tmp = *(m_string+j);
						*(m_string+j) = *(m_string+j+1);
						*(m_string+j+1) = m_tmp;
					}
				}
			}
			if(!strcmp(file_name, "NULL")){ //화면 출력일 때
				for(int i=0; i<total; i++){
					print_m((*(m_string+i)).serial_number);
				}
			}
			else{		//filename 지정한 출력일 때
				for(int i=0; i<total; i++){
					print_m_file((*(m_string+i)).serial_number, file_name);
				}
			}
		}
	}
	else if(!strcmp(factor, "d")){ // factor == d
		director *d_p; //director 링크드 리스트 포인터
		sorting *d_string; //director의 char*형, serial number 넣기 위한 구조체
		sorting d_tmp; //정렬을 위한 tmp
		sorting_num *d_num; //director의 int형, serial number 넣기 위한 구조체
		sorting_num d_tmp_n; //int형 정렬을 위한 tmp
		d_p = root_director;
		int total = 0;
		while(1){
			if(d_p->next == NULL){
				break;
			}
			total++;
			d_p = d_p->next;
		}
		d_string = (sorting *)malloc(sizeof(sorting)*total);

		if(!strcmp(option, "NULL") || !strcmp(option, "n")){ //option ==NULL or n
			d_p = root_director;
			for(int i=0; i<total; i++){
				if(d_p->name == NULL){
					d_p=d_p->next;
					total--;
					i--;
					continue;
				}
				(*(d_string+i)).string = (char *)malloc(sizeof(char)*strlen(d_p->name)+1);
				strcpy((*(d_string+i)).string, d_p->name);
				(*(d_string+i)).serial_number = d_p->serial_number;
				d_p=d_p->next;
			}
			for(int i=total-1; i>0; i--){
				for(int j=0; j<i; j++){
					if((strcmp((*(d_string+j)).string, (*(d_string+j+1)).string)) > 0){
						d_tmp = *(d_string+j);
						*(d_string+j) = *(d_string+j+1);
						*(d_string+j+1) = d_tmp;
					}
				}
			}
			if(!strcmp(file_name, "NULL")){ //화면 출력일 때
				for(int i=0; i<total; i++){
					print_d((*(d_string+i)).serial_number);
				}
			}
			else{		//filename 지정한 출력일 때
				for(int i=0; i<total; i++){
					print_d_file((*(d_string+i)).serial_number, file_name);
				}
			}
		}
		else if(!strcmp(option, "s")){ //option ==s
			d_p = root_director;
			for(int i=0; i<total; i++){
				if(d_p->name == NULL){
					d_p=d_p->next;
					total--;
					i--;
					continue;
				}
				(*(d_string+i)).string = (char *)malloc(sizeof(char)*strlen(d_p->sex)+1);
				strcpy((*(d_string+i)).string, d_p->sex);
				(*(d_string+i)).serial_number = d_p->serial_number;
				d_p=d_p->next;
			}
			for(int i=total-1; i>0; i--){
				for(int j=0; j<i; j++){
					if((strcmp((*(d_string+j)).string, (*(d_string+j+1)).string)) > 0){
						d_tmp = *(d_string+j);
						*(d_string+j) = *(d_string+j+1);
						*(d_string+j+1) = d_tmp;
					}
				}
			}
			if(!strcmp(file_name, "NULL")){ //화면 출력일 때
				for(int i=0; i<total; i++){
					print_d((*(d_string+i)).serial_number);
				}
			}
			else{		//filename 지정한 출력일 때
				for(int i=0; i<total; i++){
					print_d_file((*(d_string+i)).serial_number, file_name);
				}
			}
		}
		else if(!strcmp(option, "b")){ //option == b (생년월일은 int형으로 비교)//어린 순으로 정렬됨.
			d_p = root_director;
			d_num = (sorting_num *)malloc(sizeof(sorting_num)*total);
			for(int i=0; i<total; i++){
				if(d_p->name == NULL){
					d_p=d_p->next;
					total--;
					i--;
					continue;
				}
				(*(d_num+i)).num = atoi(d_p->birth);
				(*(d_num+i)).serial_number = d_p->serial_number;
				d_p=d_p->next;
			}
			for(int i=total-1; i>0; i--){
				for(int j=0; j<i; j++){
					if((*(d_num+j)).num > (*(d_num+j+1)).num){
						d_tmp_n = *(d_num+j);
						*(d_num+j) = *(d_num+j+1);
						*(d_num+j+1) = d_tmp_n;
					}
				}
			}
			if(!strcmp(file_name, "NULL")){ //화면 출력일 때
				for(int i=0; i<total; i++){
					print_d((*(d_num+i)).serial_number);
				}
			}
			else{		//filename 지정한 출력일 때
				for(int i=0; i<total; i++){
					print_d_file((*(d_num+i)).serial_number, file_name);
				}
			}
		}
		else if(!strcmp(option, "m")){ //option == m 첫번째 영화 제목으로 함.
			d_p = root_director;
			char *token;
			char *st; //임시로 best_movies를 통째로 담을 포인터
			for(int i=0; i<total; i++){
				if(d_p->name == NULL){
					d_p=d_p->next;
					total--;
					i--;
					continue;
				}
				st = (char *)malloc(sizeof(char)+strlen(d_p->best_movies)+1);
				strcpy(st, d_p->best_movies);
				token = strtok(st, ",");
				(*(d_string+i)).string = (char *)malloc(sizeof(char)*strlen(token)+1);
				strcpy((*(d_string+i)).string, token);
				(*(d_string+i)).serial_number = d_p->serial_number;
				d_p=d_p->next;
			}
			for(int i=total-1; i>0; i--){
				for(int j=0; j<i; j++){
					if((strcmp((*(d_string+j)).string, (*(d_string+j+1)).string)) > 0){
						d_tmp = *(d_string+j);
						*(d_string+j) = *(d_string+j+1);
						*(d_string+j+1) = d_tmp;
					}
				}
			}
			if(!strcmp(file_name, "NULL")){ //화면 출력일 때
				for(int i=0; i<total; i++){
					print_d((*(d_string+i)).serial_number);
				}
			}
			else{		//filename 지정한 출력일 때
				for(int i=0; i<total; i++){
					print_d_file((*(d_string+i)).serial_number, file_name);
				}
			}
		}
	}
	else if(!strcmp(factor, "a")){ // factor == a
		actor *a_p;
		sorting *a_string; //director의 char*형, serial number 넣기 위한 구조체
		sorting a_tmp; //정렬을 위한 tmp
		sorting_num *a_num; //director의 int형, serial number 넣기 위한 구조체
		sorting_num a_tmp_n; //int형 정렬을 위한 tmp
		a_p = root_actor;
		int total = 0;
		while(1){
			if(a_p->next == NULL){
				break;
			}
			total++;
			a_p = a_p->next;
		}
		a_string = (sorting *)malloc(sizeof(sorting)*total);

		if(!strcmp(option, "NULL") || !strcmp(option, "n")){ //option ==NULL or n
			a_p = root_actor;
			for(int i=0; i<total; i++){
				if(a_p->name == NULL){
					a_p=a_p->next;
					total--;
					i--;
					continue;
				}
				(*(a_string+i)).string = (char *)malloc(sizeof(char)*strlen(a_p->name)+1);
				strcpy((*(a_string+i)).string, a_p->name);
				(*(a_string+i)).serial_number = a_p->serial_number;
				a_p=a_p->next;
			}
			for(int i=total-1; i>0; i--){
				for(int j=0; j<i; j++){
					if((strcmp((*(a_string+j)).string, (*(a_string+j+1)).string)) > 0){
						a_tmp = *(a_string+j);
						*(a_string+j) = *(a_string+j+1);
						*(a_string+j+1) = a_tmp;
					}
				}
			}
			if(!strcmp(file_name, "NULL")){ //화면 출력일 때
				for(int i=0; i<total; i++){
					print_a((*(a_string+i)).serial_number);
				}
			}
			else{		//filename 지정한 출력일 때
				for(int i=0; i<total; i++){
					print_a_file((*(a_string+i)).serial_number, file_name);
				}
			}
		}
		if(!strcmp(option, "s")){ //option ==s
			a_p = root_actor;
			for(int i=0; i<total; i++){
				if(a_p->name == NULL){
					a_p=a_p->next;
					total--;
					i--;
					continue;
				}
				(*(a_string+i)).string = (char *)malloc(sizeof(char)*strlen(a_p->sex)+1);
				strcpy((*(a_string+i)).string, a_p->sex);
				(*(a_string+i)).serial_number = a_p->serial_number;
				a_p=a_p->next;
			}
			for(int i=total-1; i>0; i--){
				for(int j=0; j<i; j++){
					if((strcmp((*(a_string+j)).string, (*(a_string+j+1)).string)) > 0){
						a_tmp = *(a_string+j);
						*(a_string+j) = *(a_string+j+1);
						*(a_string+j+1) = a_tmp;
					}
				}
			}
			if(!strcmp(file_name, "NULL")){ //화면 출력일 때
				for(int i=0; i<total; i++){
					print_a((*(a_string+i)).serial_number);
				}
			}
			else{		//filename 지정한 출력일 때
				for(int i=0; i<total; i++){
					print_a_file((*(a_string+i)).serial_number, file_name);
				}
			}
		}
		else if(!strcmp(option, "b")){ //option == b (생년월일은 int형으로 비교)//어린 순으로 정렬됨.
			a_p = root_actor;
			a_num = (sorting_num *)malloc(sizeof(sorting_num)*total);
			for(int i=0; i<total; i++){
				if(a_p->name == NULL){
					a_p=a_p->next;
					total--;
					i--;
					continue;
				}
				(*(a_num+i)).num = atoi(a_p->birth);
				(*(a_num+i)).serial_number = a_p->serial_number;
				a_p=a_p->next;
			}
			for(int i=total-1; i>0; i--){
				for(int j=0; j<i; j++){
					if((*(a_num+j)).num > (*(a_num+j+1)).num){
						a_tmp_n = *(a_num+j);
						*(a_num+j) = *(a_num+j+1);
						*(a_num+j+1) = a_tmp_n;
					}
				}
			}
			if(!strcmp(file_name, "NULL")){ //화면 출력일 때
				for(int i=0; i<total; i++){
					print_a((*(a_num+i)).serial_number);
				}
			}
			else{		//filename 지정한 출력일 때
				for(int i=0; i<total; i++){
					print_a_file((*(a_num+i)).serial_number, file_name);
				}
			}
		}
		else if(!strcmp(option, "m")){ //option == m 첫번째 영화 제목으로 함.
			a_p = root_actor;
			char *token;
			char *st; //임시로 best_movies를 통째로 담을 포인터
			for(int i=0; i<total; i++){
				if(a_p->name == NULL){
					a_p=a_p->next;
					total--;
					i--;
					continue;
				}
				st = (char *)malloc(sizeof(char)+strlen(a_p->best_movies)+1);
				strcpy(st, a_p->best_movies);
				token = strtok(st, ",");
				(*(a_string+i)).string = (char *)malloc(sizeof(char)*strlen(token)+1);
				strcpy((*(a_string+i)).string, token);
				(*(a_string+i)).serial_number = a_p->serial_number;
				a_p=a_p->next;
			}
			for(int i=total-1; i>0; i--){
				for(int j=0; j<i; j++){
					if((strcmp((*(a_string+j)).string, (*(a_string+j+1)).string)) > 0){
						a_tmp = *(a_string+j);
						*(a_string+j) = *(a_string+j+1);
						*(a_string+j+1) = a_tmp;
					}
				}
			}
			if(!strcmp(file_name, "NULL")){ //화면 출력일 때
				for(int i=0; i<total; i++){
					print_a((*(a_string+i)).serial_number);
				}
			}
			else{		//filename 지정한 출력일 때
				for(int i=0; i<total; i++){
					print_a_file((*(a_string+i)).serial_number, file_name);
				}
			}
		}
	}

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
	if (token == NULL)	//아무것도 입력안하면 걍 넘기기
		return 1;
	menu = (char *)malloc(sizeof(char) * strlen(token) + 1);
	strcpy(menu, token);
	printf("menu : %s\n", menu);

	if (!strcmp(menu, "end")) {
		return 0;	//quit_num을 0으로 만들어 종료하기
	}
	else if (!strcmp(menu, "add")) {	//add 명령어 처리
		token = strtok(NULL, cut);
		if (token == NULL)	//인자를 입력안하면 걍 넘기기
			return 1;
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
	else if (!strcmp(menu, "print")) {  //print 명령어 처리, 목록에 없는 거 출력해야 할 때 오류남.
		token = strtok(NULL, cut);
		factor = (char *)malloc(sizeof(char) * strlen(token) + 1);
		strcpy(factor, token);
		printf("factor : %s\n", factor); //factor 확인

		token = strtok(NULL, cut);
		if(token == NULL){            //serial number 없을 때(나중에 지워야함)
			 if (!strcmp(factor, "m")) {
			if(root_m_num == 0){
				printf("no movie.\n\n");
				return 1;
			}
					m = root_movie;
					while (m->next != NULL) {
						printf("%d:%s:%s:%s:%s:%s:%s\n", m->serial_number, m->title, m->genre, m->director, m->year, m->time, m->actors);
						 m = m->next;
					}
					printf("\n");
			 }
			 else if (!strcmp(factor, "d")) {
			if(root_d_num == 0){
				printf("no director.\n\n");
				return 1;
			}
					d = root_director;
					while (d->next != NULL) {
						 printf("add:%d:%s:%s:%s:%s\n", d->serial_number, d->name, d->sex, d->birth, d->best_movies);
						 d = d->next;
					}
					printf("\n");
			 }
			 else if (!strcmp(factor, "a")) {
			if(root_a_num == 0){
				printf("no actor.\n\n");
				return 1;
			}
					a = root_actor;
					while (1) {
						if(a->next == NULL)
							break;
						 printf("%d:%s\n", a->serial_number, a->name);
						 a = a->next;
					}
					printf("\n");
			 }
		}
		else{ 				//serial number 있을 때
			 get_serial_num = atoi(token); //문자열을 숫자로 변환
			 printf("num : %d\n", get_serial_num);  //get_serial_num 확인
			 if(!strcmp(factor, "m")){
			if(root_m_num == 0){
				printf("no movie.\n\n");
				return 1;
			}
					print_m(get_serial_num);
		}
			 else if(!strcmp(factor, "d")){
			if(root_d_num == 0){
				printf("no director.\n\n");
				return 1;
			}
					print_d(get_serial_num);
		}
			 else if(!strcmp(factor, "a")){
			if(root_a_num == 0){
				printf("no actor.\n\n");
				return 1;
			}
					print_a(get_serial_num);
		}
		}

		}
	else if (!strcmp(menu, "delete")) {	//delete 명령어 처리
		token = strtok(NULL, cut);
		if (token == NULL)	//인자를 입력안하면 걍 넘기기
			return 1;
		factor = (char *)malloc(sizeof(char) * strlen(token) + 1);
		strcpy(factor, token);
		printf("factor : %s\n", factor);	//factor 확인

		token = strtok(NULL, cut);
		if (token == NULL)	//시리얼 넘버를 입력안하면 걍 넘기기
			return 1;
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
		if (token == NULL)	//인자를 입력안하면 걍 넘기기
			return 1;

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
		if (token == NULL)	//인자를 입력안하면 걍 넘기기
			return 1;
		factor = (char *)malloc(sizeof(char) * strlen(token) + 1);
		strcpy(factor, token);
		printf("factor : %s\n", factor);	//factor 확인

		token = strtok(NULL, cut);
		if (token == NULL)	//뒤에 더 없으면 걍 넘기기
			return 1;
		if (*token >= '9') {	//숫자가 아닌 알파벳이면 option으로 넣기
			option = (char *)malloc(sizeof(char) * strlen(token) + 1);
			strcpy(option, token);
			printf("option : %s\n", option);	//option 확인
			token = strtok(NULL, cut);
			if (token == NULL)	//시리얼 넘버 없으면 걍 넘기기
				return 1;
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
				sort(factor, "NULL", file_name);
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
					sort(factor, option, file_name);
				}
				else{//뒤에 아무것도 없다면
					sort(factor, option, "NULL");
				}
			}
		}
		else{ 			//factor 뒤에 아무것도 없음.
			sort(factor, "NULL", "NULL");
		}
		printf("\n");
	}
	else if (!strcmp(menu, "save")) {	//save 명령어 처리
		token = strtok(NULL, cut);
		if (token == NULL)	//인자를 입력안하면 걍 넘기기
			return 1;
		factor = (char *)malloc(sizeof(char) * strlen(token) + 1);
		strcpy(factor, token);
		printf("factor : %s\n", factor);	//factor 확인

		if ((token = strtok(NULL, cut)) != NULL) {	//뒤에 뭐가 더 있는지 확인
			if (!strcmp(token, "-f")) {	//뒤에 있는게 -f이면
				token = strtok(NULL, cut);	//-f 건너뛰기
				if (token == NULL)	//파일이름을 입력안하면 걍 넘기기
					return 1;
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
					if (token == NULL)	//파일 이름을 입력안하면 걍 넘기기
						return 1;
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
	load_movie();
	load_director();
	load_actor();
	printf("You can use add, update, delete, search, sort, save, end commands.\n");
	signal(SIGINT, handler);	//Ctrl + c를 눌렀을때 바로 종료되지 않고 물어보기

	while (quit_num) {
		printf("(movie) ");
		gets(input_words);
		quit_num = menu_func(input_words);
	}

	return 0;
}
