#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 512



void handle_escape(const char o[], char n[]); /*old, new */
void read_char(char s[]);
void handle_range(char s[]);
void del(const char s[]);
void translate(const char set1[], const char set2[]);
void expand(const char set1[], char set2[]);
void truncate(char set1[], const char set2[]);
int  detect_range(const char set[]);
int  check_argc(int arg);
int  handle_flag(char *arg);

int main(int argc, char *argv[]) {

	char input1[MAXSIZE];
	char input2[MAXSIZE];
	char *set1;
	char *set2;
	char *set3;

	if(check_argc(argc) == 3 && handle_flag(argv[1]) == -1) {
		set1 = argv[1];
		set2 = argv[2];
		handle_escape(set1, input1);
		handle_escape(set2, input2);
		if(detect_range(input1) == 1)
			handle_range(input1);
		if(detect_range(input2) == 1) 
			handle_range(input2);
		expand(input1, input2);
		translate(input1, input2);
	}
	else if(check_argc(argc) == 3 && handle_flag(argv[1]) == 0) {
		set1 = argv[2];
		handle_escape(set1, input1);
		if(detect_range(input1) == 1)
			handle_range(input1);	
		del(input1);	

	}
	else if((check_argc(argc) == 4) && (handle_flag(argv[1]) == 1)) {
		set1 = argv[2];
		set2 = argv[3];
		handle_escape(set1, input1);
		handle_escape(set2, input2);
		if(detect_range(input1) == 1)
			handle_range(input1);
		if(detect_range(input2) == 1) 
			handle_range(input2);
		truncate(input1, input2);
		translate(input1, input2);
	}
	return 0;

}

/*Checks how many arguments are passed in, errors if it is more than 4*/
int check_argc(int arg) {
	if (arg > 4 || arg < 2) {
		fprintf(stderr, "Error: Usage tr <argument> <argument> <argument>");
		exit(1);
	}
	if(arg == 3)
		return 3;
	else if ( arg == 4)
		return 4;
	else
		return 2;
}

int handle_flag(char *arg) {
	char str1[] = "-t";
	char str2[] = "-d";
	if (strcmp(arg, str1) == 0) {
		return 1;
	}
	else if (strcmp(arg, str2) == 0) 
		return 0;
	return -1;
}

void read_char(char s[]) {
	int i;
	int a = sizeof(s);
	for (i = 0; i < a; i++) {
		/*if (s[i] == '\')*/
	}

}

void translate(const char set1[], const char set2[]) {
	int c;
	int i;
	int pos = -1;
	while ((c = getchar()) != EOF) {
		for (i = 0; set1[i] != '\0' && set2[i] != '\0'; i++) {
			if(c == set1[i]) {
				pos = i;
			}
		}
		if (pos != -1) {
			putchar(set2[pos]);
			pos = -1;
		}
		else 
			putchar(c);

	}

}

void del(const char s[]) {
	int c;
	int i;
	int bool_print = 1;
	while ((c = getchar()) != EOF) {
		for (i = 0; s[i] != '\0'; i++) {
			if (c == s[i]) 
				bool_print = 0;
		}
		if (bool_print == 0) {
			bool_print = 1;
		}
		else 
			putchar(c);
	}
}

void handle_escape(const char o[], char n[]) {
	size_t i;
	size_t x = 0;
	for (i = 0; o[i] != '\0'; i++, x++) {
		if(o[i] != '\\'){
			n[x] = o[i];
		}
		else {
			i++; 
			switch(o[i]) {
				case '\\':
					n[x] = '\\';
					break;
				case 'a':
					n[x] = '\a';
					break;
				case 'b':
					n[x] = '\b';
					break;
				case 'f':
					n[x] = '\f';
					break;
				case 'n':
					n[x] = '\n';
					break;
				case 'r' : 
					n[x] = '\r';
					break;
				case 't':
					n[x] = '\t';
					break;
				case 'v': 
					n[x] = '\v';
					break;
				case '\'': 
					n[x] = "\'";
					break;
				case '\"': 
					n[x] = '\"';
					break;
				default: fprintf(stderr, "Invalid escape character used");
			}
		}
		
	}
	n[i] = '\0';

}

void handle_range(char n[]) {
	char temp[MAXSIZE];
	size_t i;
	int x;
	int z = 0;
	for (i = 0; i < strlen(n); i++) {
		if (n[i] == '-' && i != 0 && n[i+1] != '-') {
			for (x = n[i-1]; x <= n[i+1]; x++, z++) {
				temp[z] = x;
			}
		}
	
	}
	strncpy(n,temp, (size_t) z);
}

void expand(const char set1[], char set2[]) {
	size_t i, x;
	char temp;
	if (strlen(set1) > strlen(set2)) {
		temp = set2[strlen(set2) - 1];
		for (i = strlen(set2); i < strlen(set1); i++) {
			set2[i] = temp;
		}
		set2[i+1] = '\0';

	}

}

void truncate(char set1[], const char set2[]) {
	if (strlen(set1) > strlen(set2)) {
		set1[strlen(set2)] = '\0';
	}
}

int detect_range(const char set[]) {
	size_t i;
	for (i = 0; set[i] != '\0'; i++) {
		if (set[i] == '-' && set[i+1] != '\0')
			return 1;
	}
	return 0;

}

