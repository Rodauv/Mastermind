Welcome to My Mastermind
Task
Create the mastermind game in C. The game shall check the user input and compare it with the "secret code". The input shall contain the numbers between 0-7, each number shall be distinct.

Solving the puzzle is through the hints given after the input:
Missed pieces - the number in in the code, but in a wrong place
Matches - the number is in the code and in the right place. 

To win the game within the given attempts, all the 4 numbers shall be in the right order.

The secred code and the number of rounds (difficulty) can be controled by the given arguments:
-t xx -> will indicate the number of rounds (xx: any number above 0)
-c "1234" -> will indicate the secret code if we wish to indicate a number ourself

LIMITATIONS:
printf(3) - ok
write(2) - ok
read(2)
rand() (/ srand())
time()
atoi()
Description
To solve the problem and the limitations, the following functions were Implemented in the code:
- Implemented my own strcmp to determine the argument flags
- Created a string copy function to get the inputs from the commandline assigned to the round and secret code variables (if given)
- Made a validation to check if the User Input code is NOT between 0 and 7 (ASCII) 48-55, with length of 4 and all inputs are disticts
- getting the user input via read() from standard input "0" -> reading the whole buffer in and validating the input to avoid overflow through the while function. The result is checked againts length, range of given characters and kept in the same round till valid input is given
Installation
there is a makefile created with gcc parameters to compile & validate the c file/code. Apply the commandline "make -f makefile".
Usage

Initiate my_mastermind with
./my_project -c "argument1" -t argument2
-c: it shall be a string with distinct numbers between 0-7 and length of 4, else random code is generated
-t: shall be a valid int >0, else 10 rounds will be defaulted