#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <linux/kernel.h>
#include <sys/sysinfo.h>
#include <libgen.h>
#include <signal.h>
#include <sys/wait.h>

int loop = 1;
#define MAX_LINE 80 /* The maximum length of a command */

int count = 0;
//Program will randomly select fortune commands and list them
const char* x[] = {
        "limerick", "fortunes2", "linuxcookie",
        "freebsd-tips", "osfortune", "startrek",
        "zippy", "debian-hints"
};
const size_t FORTUNES = sizeof(x)/sizeof(*x) - 1;

void green() {
    printf("\033[0;32m"); //033 is known as an escape sequence and is used to control the console's cursor and text color, among other things.
}

void purple() {
    printf("\033[0;35m");
}

void cyan() {
    printf("\033[0;36m");
}

void reset() {
    printf("\033[0m");//Resets the text to default color
}

int main(void) {

    system("clear");

    char input[1024];

    while (loop) {

        prompt();

        fgets(input, 1024, stdin);

        router(input);
    }

    return 0;
}

void prompt() {

    char * username;
    char hostname[HOST_NAME_MAX + 1];//Generally limited to 255 bytes.

    username = getlogin();

    gethostname(hostname, HOST_NAME_MAX + 1);

    char cwd[PATH_MAX];// The maximum permitted size of file paths(4096 bytes)

    green();
    printf("%s", hostname);

    purple();
    printf("@");

    cyan();
    printf("%s", username);

    reset();

    printf(":~$ ");

}
//Function used for routing user input, this is one of the main functions, since it deals with system calls, inputs and outputs.
void shell_router(char input[1024]) {

    char function [10] = "";
    int fun_counter = 0;

    // Function to take input
    for (int i = 0; i < strlen(input); i++) {
        if (input[i] != ' ' || (int) input[i] == 0) {
            function [fun_counter] = input[i];
            fun_counter++;
        } else {
            break;
        }
    }

    // removes the '\n' char
    function [strcspn(function, "\n")] = 0;
    //if statements which calls the function to its input
    if (strcmp(function, "copy") == 0) {
        copy(input);
    } else if (strcmp(function, "history") == 0) {
        get_history();
    } else if (strcmp(function, "free") == 0) {
        free_malloc();
    } else if (strcmp(function, "fortune") == 0) {
        fortune();
    } else if(strcmp(function, "custom") == 0){
		  for (int i = 0; i < 150; i++){ 
		    system("sleep 0.01"); // airplane movement
		    system("clear"); // clears the screen before each instance of airplane appears
		    customCommand(i); // the airplane moves 150 spaces
		  }
		  system("clear");
	  } else if ((int)function [0] != 0) {
        printf("%s: command not found\n", function);
    }

}
// cp functionality
void copy(char input[]) {
    FILE * fp1, * fp2;
    char source[50];
    char destination[50];
// cp function first takes the file and scans the file with corresponding source and destination
    printf("Enter source file name:");
    scanf("%49s", source);
    printf("Enter destination file name:");
    scanf("%49s", destination);
    //opens the file with corresponding source and destination and copies the content from source to destination adn saves
    fp1 = fopen(source, "r");
    fp2 = fopen(destination, "w");
    if (!fp1 || !fp2) {
        printf("error");
    }
    char c;
    while ((c = fgetc(fp1)) != EOF) { // fgetc returns the character read as an int or returns EOF to indicate an error or end of file.
        fputc(c, fp2);
    }
    fclose(fp1);
    fclose(fp2);
}


#define BUFFER_SIZE 50
#define buffer "\n\Shell Command History:\n"
char history[10][BUFFER_SIZE]; //history array to store history commands

//history functionality that displays history 
void displayHistory() {

    printf("Shell command history:\n");

    int i;
    int j = 0;
    int histCount = count;
    //Function to print out history
    for (i = 0; i < 10; i++) {
        printf("%d.  ", histCount);
        while (history[i][j] != '\n' && history[i][j] != '\0') {
            printf("%c", history[i][j]);
            j++;
        }
        printf("\n");
        j = 0;
        histCount--;
        if (histCount == 0)
            break;
    }
    printf("\n");
}
//Fuction to get the command from shell, tokenize it and set the args parameter
int formatCommand(char inputBuffer[], char * args[], int * flag) {

    int length;// # of chars in command line
    int i;// loop index for inputBuffer
    int start;// index of beginning of next command
    int ct = 0;// index of where to place the next parameter into args[]

    length = read(STDIN_FILENO, inputBuffer, MAX_LINE);

    start = -1;
    if (length == 0)
        exit(0); //end of command
    if (length < 0) {
        printf("Command not read\n");
        exit(-1); //end of command
    }
    //examine each character
    for (i = 0; i < length; i++) {
        switch (inputBuffer[i]) {
            case ' ':
            case '\t':// to seperate arguments
                if (start != -1) {
                    args[ct] = & inputBuffer[start];
                    ct++;
                }
                inputBuffer[i] = '\0';// add a null char at the end
                start = -1;
                break;

            case '\n'://final char 
                if (start != -1) {
                    args[ct] = & inputBuffer[start];
                    ct++;
                }
                inputBuffer[i] = '\0';
                args[ct] = NULL; // no more args
                break;

            default:
                if (start == -1)
                    start = i;
                if (inputBuffer[i] == '&') {
                    * flag = 1;//this flag is the differentiate whether the child process is invoked in background
                    inputBuffer[i] = '\0';
                }
        }
    }

    args[ct] = NULL;//if the input line was > 80

    if (strcmp(args[0], "history") == 0) {
        if (count > 0) {

            displayHistory();
        } else {
            printf("\nNo Commands in the history\n");
        }
        return -1;
    } else if (args[0][0] - '!' == 0) {
        int x = args[0][1] - '0';
        int z = args[0][2] - '0';

        if (x > count) {//second letter check
            printf("\nNo Such Command in the history\n");
            strcpy(inputBuffer, "Wrong command");
        } else if (z != -48) {//third letter check
            printf("\nNo Such Command in the history. Enter <=!9 (buffer size is 10 along with current command)\n");
            strcpy(inputBuffer, "Wrong command");
        } else {

            if (x == -15) {//Checking for '!!',ascii value of '!' is 33
                strcpy(inputBuffer, history[0]);// this will be your 10 th(last) command
            } else if (x == 0) {
                printf("Enter proper command");
                strcpy(inputBuffer, "Wrong command");
            } else if (x >= 1) {//Checking for '!n', n >=1
                strcpy(inputBuffer, history[count - x]);

            }

        }
    }
    for (i = 9; i > 0; i--)//Moving the history elements one step higher
        strcpy(history[i], history[i - 1]);

    strcpy(history[0], inputBuffer);//Updating the history array with input buffer
    count++;
    if (count > 10) {
        count = 10;
    }
}

//get history with forking the process 
void get_history() {
    char inputBuffer[MAX_LINE];/* buffer to hold the input command */
    int flag;// equals 1 if a command is followed by "&"
    char * args[MAX_LINE / 2 + 1];/* max arguments */
    int should_run = 1;

    pid_t pid, tpid;
    int i;

    while (should_run) {//infinite loop for shell prompt
        flag = 0;//flag =0 by default
        printf("history>");
        fflush(stdout);
        //If statements that chechk whether the process is child or parent
        if (-1 != formatCommand(inputBuffer, args, & flag)) {// get next command  
            pid = fork();

            if (pid < 0) {//if pid is less than 0, forking fails

                printf("Fork failed.\n");
                exit(1);
            } else if (pid == 0) {

                if (execvp(args[0], args) == -1) {//execvp function is most commonly used to overlay a process image that has been created by a call to the fork function.

                    printf("Error executing command\n");
                }

            } 
            // if flag == 0, the parent will wait,
        	// otherwise returns to the formatCommand() function.
            else {
                i++;
                if (flag == 0) {
                    i++;
                    wait(NULL);
                }
            }
        }
    }
}

//free functionality
void free_malloc() { //The malloc function will request a block of memory from the heap
    int * ptr, * ptr1;
    int n, i;

    n = 5;
    printf("Enter number of elements: %d\n", n);
    ptr = (int * ) malloc(n * sizeof(int));
    ptr1 = (int * ) calloc(n, sizeof(int));

    if (ptr == NULL || ptr1 == NULL) {
        printf("Memory not allocated.\n");
        exit(0);
    } else {

        printf("Memory successfully allocated using malloc.\n");//malloc() takes a single argument (the amount of memory to allocate in bytes)

        free(ptr);
        printf("Malloc Memory successfully freed.\n");//Malloc Memory cleaned

        printf("\nMemory successfully allocated using calloc.\n");//calloc() needs two arguments (the number of variables to allocate in memory, and the size in bytes of a single variable).

        free(ptr1);
        printf("Calloc Memory successfully freed.\n");//Calloc Mmeory cleaned
    }
}
// Function that returns a random number ex.inputs 10, but returns 7
int random(int Size) {
    int k;
    k = 0;
    srand((unsigned) time(NULL));//Set the random number seed according to the system time float x = rand() * x/RAND_MAX;
    k = rand() % Size;
    return k;
}
//fortune functionality
void fortune() {
    execlp("/usr/games/fortune", x[random(FORTUNES)], "-l", NULL, NULL);//Print a random fortune from an array.
}

void printline(char *line, int number){
        for(int i = 0; i < number; i++){
                printf(" "); // prints an empty space based on the value of number (space)
        }
        printf("%s\n", line); // prints a "line" of the airplane
}
// int spaces determines how far the airplane moves
	void customCommand(int spaces){ 
	purple();
  
     char *line1 =                           |
     char *line2 =                           |
     char *Line3 =                     --====|====--

     char *line4 =                       .-"""""-.
     char *line5 =                     .'_________'.
     char *line6 =                    /_/_|__|__|_\_\
     char *line7 =                   ;'-._       _.-';
  char *line8 = ,--------------------|    `-. .-'    |--------------------,
  char *line9 =  ``""--..__    ___   ;       '       ;   ___    __..--""``
    char *line10 =         `"-// \\.._\             /_..// \\-"`
     char *line11 =            \\_//    '._       _.'    \\_//
  char *line12 =                `"`        ``---``        `"`

	// prints all four segments of the helicopter using printline() 
	printline(line1, spaces);
	printline(line2, spaces);
	printline(line3, spaces);
    printline(line4, spaces);
    printline(line5, spaces);
    printline(line6, spaces);
    printline(line7, spaces);
    printline(line8, spaces);
    printline(line9, spaces);
    printline(line10, spaces);
    printline(line11, spaces);
    printline(line12, spaces);
	reset();

}
//Fork Bomb is a program that harms a system by making it run out of memory. 
void forkbomb()
{
    char ch;
    printf("Do You really wanna do this? (y/n): ");//Ask user yes or no
    scanf("%c", &ch);
//If yes execute bomb
    if(ch=='y' || ch=='Y'){
        printf("Well,that escalated quickly\n");
        while(1){
           fork();   
        } 

    }
//If not thank the user:)
    else if(ch=='n' || ch=='N'){

        printf("Grateful AF\n ");
    
    }
    else{
		printf("This didn't age well\n");
	}
}