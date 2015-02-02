#include <stdio.h>
#include <stdlib.h>


int check_argc(int arg) {
	if(arg > 4) {
		printf("Too many arguments");
		return -1;
	}
	return 0;
}

void parse_argv(char *argv) {

}

void handle_escape(char s[]) {

}

void read_char(char s[]) {

}

void handle_range(char s[]) {

}

void del(char s[]) {

}

void translate(const char s[]. const char t[]) {

}


int main(int argc, char **argv) {

	printf("%d %s\n", argc, "Number of arguments");
	printf("%s %s\n", argv[1], argv[2]);
	read_argc(argc);
	return 0;

}