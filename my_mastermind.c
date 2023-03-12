/*
PRINTS:
1. Will you find the secret code? (write)
2. ---\nRound 0 (printf)
3. Well placed pieces: 0\nMisplaced pieces: 1 (printf)
4. Wrong input! (write)
5. Congratz! You did it! (printf)
LIMITATIONS:
printf(3) - ok
write(2) - ok
read(2)
rand() (/ srand())
time()
atoi()
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#define len 4
#define randrange(N) rand() / (RAND_MAX/(N) + 1)
#define MAX 7
static int vektor[10];
int candidates[MAX];
const char alphabet[] = "01234567";

int my_strcmp(char* param_1, char* param_2)
/*Implemented my own strcmp to determine the argument flags*/
{
   int i = 0;
   while(param_1[i] != '\0' && param_2[i] != '\0') {
       if (param_1[i] < param_2[i]) {
           return 1;
       }
       if (param_1[i] > param_2[i]) {
           return 1;
       }
       i++;
   }
   return 0;
}

/*String copy function to get the inputs from the commandline assigned to the round and secret code variables (if given)*/
void string_copy(char* dest, const char* source){
    while (*source != '\0')
    {
        *dest = *source;
        dest++;
        source++;
    }
    *dest = '\0';
}

int stringLength(char *str){
    int length=0;
    while(*str){
        str++;
        length++;
    }
    return length;
}

/*check if the code is NOT between 0 and 7 (ASCII) 48-55*/
int checkCode(char* code){
    for(int i = 0 ; i<len;i++){
        if ((char)(code[i]) < 48 || (char)(code[i]) > 55){
            return 0;
        }
    }
    return 1;
}

int dupl(char* str){
    int count = stringLength(str);

    for(int i = 0; i < count; i++){
        for(int j = i + 1; j < count; j++){
            if(str[i] == str[j]){
                return 0;
            }
        }
    }
    return 1;
}

/*getting the user input via read() from standard input "0" -> reading the whole buffer in and validating the input to avoid overflow through the while function
The result is checked againts length, range of given characters and kept in the same round till valid input is given*/
char* read_input(){
    int flag = 0;
    int ch;
    char* userinput = malloc(sizeof(char) * BUFSIZ);
    while(flag != 1){
        ch = read(0,userinput,BUFSIZ);
        if(ch == 5 && dupl(userinput) == 1){
            flag = 1;
        }
        if(flag == 1){
            flag = checkCode(userinput);
        }
        if(flag == 0){
            printf("Wrong input!\n");
        }
    }
    userinput[ch] = '\0';
    return userinput;
}



/*if there is no argument given by "-c", there is a random code generated. The code is defined in an array and distinct numbers are generated to define the index of the array*/
char* autocode(){
    char *rstr = malloc((len + 1) * sizeof(char));
    int i;
    for (i=0; i<MAX; i++){
        candidates[i] = i;
    }

    for (i = 0; i < MAX-1; i++) {
        int c = randrange(MAX-i);
        int t = candidates[i];
        candidates[i] = candidates[i+c];
        candidates[i+c] = t;
    }

    for (i=0; i<len; i++)
        vektor[i] = candidates[i] + 1;

    for (i=0; i<len; i++)
        rstr[i] = alphabet[vektor[i]];

    rstr[len] = '\0';
    return rstr;
}

/*Main function runs the loop for the rounds:
    1. check if the number of rounds is given by an argument
    1b. if no -t => default it to 10
    1c. if no -c => use random code
    2. run the for loop for the numner of -t
    3. match, win and miss are standard string compares based on index level match or generic match. If index level match is true for all => win*/
int main(int ac, char** av){
    char* argnum;
    int run;
    char* scode;
    char* userInput;
    int runval = 0;
    int scodeval = 0;
    if(ac > 0){
        for(int i = 1; i < ac; i++){
            if(my_strcmp(av[i], "-c") == 0){
                scode = malloc(sizeof(char)*5);
                if(checkCode(av[i+1]) == 1 && stringLength(av[i+1]) == 4 && dupl(av[i+1]) == 1){
                    string_copy(scode, av[i+1]);
                    scodeval = 1;
                }
            }
            else if(my_strcmp(av[i], "-t") == 0){
                for(int j = 0; j < stringLength(av[i+1]); j++){
                    if((char)(av[i+1][j]) > 48 && (char)(av[i+1][j]) < 55){
                        argnum = malloc(sizeof(char)*stringLength(av[i+1]));
                        string_copy(argnum, av[i+1]);
                        runval = 1;
                    }
                }  
            }
        }
    }
    run = atoi(argnum);
    if(runval == 0){
        run = 10;
    }
    if(scodeval == 0){
            srand(time(NULL));
            scode = autocode();
        }
    userInput = malloc(sizeof(char) * len+1);
    write(1,"Will you find the secret code?\n",32);
    for(int round = 0; round < run; round++){
        printf("---\nRound: %d\n",round);
        userInput = read_input();
        int miss = 0;
        int match = 0;
        for(int i = 0; i < len; i++){
            if(scode[i] == userInput[i]){
                match += 1;
            }
        }
        if(match == 4){
                write(1,"Congrats, you win!\n",20);
                break;
            }     
        for(int i = 0; scode[i]; i++){
            for(int j = 0; userInput[j]; j++){
                if(scode[i] == userInput[j] && scode[i] != userInput[i]){
                    miss += 1;
                }
            }
        }
        printf("Well placed pieces: %d\nMisplaced pieces: %d\n",match,miss);
    }
}