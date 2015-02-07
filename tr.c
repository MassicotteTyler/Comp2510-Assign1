#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSIZE 512


/*Author: Tyler Massicotte A00855150 Set D
* Email: MassicotteTyler@gmail.com
* This program is a simplified version of the unix command, 
* which is translate. The program translates characters from the 
* first set the equivalent character in the second set. 
* Ex a1.exe abc xyz
*/
void handle_escape(const char o[], char n[]); /*old, new */
void handle_range(char s[]);
void del(const char s[]);
void translate(const char set1[], const char set2[]);
void expand(const char set1[], char set2[]);
void truncate(char set1[], const char set2[]);
int  detect_range(const char set[]);
int  check_argc(int arg);
int  handle_flag(char *arg);

/*
* Main Function: Starting point of the program, takes in command
* line arguments. Number of arguments is represented as argc.
* The commands themselves are represented in char pointers as argv.
* The multiple if statements process what conditions the user as 
* passed in through the command line and handles them accordingly.
*/
int main(int argc, char *argv[]) {

	char input1[MAXSIZE]; /*Char array to store the string from argv*/
	char input2[MAXSIZE];
	char *set1;
	char *set2;

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
/*Takes in an argv and detects if it is -t or -d.
* Returns 1 if -t, 0 if -d and -1 if neither.
*/
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

/*Takes in 2 sets of strings. Gets characters via stdin and compares
* the character to the characters in set1, if there is a match it 
* replaces the character with the character in the equivalent position
* in set2
*/
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

/*
* Takes in a char array s[]. Gets characters from stdin and compares
* them with the chars in s. If there is a match the char is not printed
* and the next iteration of the loop is started.
*/
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

/*Takes in two char arrays, o(ld) and n(ew). The array o is looped through
* and looks for a '\' character. If found it checks the next character and
* compares them to acceptable cases in the switch. If an acceptable case
* is found it replaces the '\' character with the appropriate escape char
* e.g. 'a\t' becomes 'a    '
*/
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
					n[x] = '\'';
					break;
				case '\"': 
					n[x] = '\"';
					break;
				default: fprintf(stderr, "Invalid escape character used");
			}
		}
		
	}
	n[x] = '\0';

}

/*Detects if there is a - character. If a - character is detected it
* gets the value of the value of the character before it and after. It
* then writes to a new array all the values from the first character to
* the last inclusively. Then the new array is copied to the old one.
*/
void handle_range(char n[]) {
	char temp[MAXSIZE];
	size_t i;
	int x;
	int z = 0;
	for (i = 0; i < strlen(n); i++) {
		if (n[i] == '-' && i != 0 && n[i+1] != '-') {
			if (n[i-1] > n[i+1]) {
				fprintf(stderr, "Error, first char of range exceeds second");
				exit(1);
			}
			for (x = n[i-1]; x <= n[i+1]; x++, z++) {
				temp[z] = x;
			}
		}
	
	}
	strncpy(n,temp, (size_t) z);
}

/*
*
*
*/
void expand(const char set1[], char set2[]) {
	size_t i;
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

