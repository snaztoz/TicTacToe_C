//
//  A Simple Tic-Tac-Toe Game, 
//  created by: Hafidh M.S.
//
//  This source code is opened to everyone, free to use
//  to everyone, and everything in this program are free
//  to be tweaked
//
//
// ====================================================
//                      NOTES
// ====================================================
//
// TODO:
// 1. CREATE VsCom GAMEPLAY
// 2. 
// 3. 
// 4. 
//
// CURRENT PROBLEMS:
// 1. NO PROBLEMS FOUND SO FAR
// 2. 
//
// FURTHER CHECKING:
// 1. THE getSingleChar FUNCTION
// 2.
//

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Player
{
    char name[21];
    int winStatus;
    char SIGN; // could be O or X
} player;

// I manually create an input function,
// maybe it works almost the same way as
// getchar function does
char getSingleChar()
{
    char line[200];
    
    fgets(line, 200, stdin);
    if(line[1] == '\n'){
        return line[0];
    } else {
        return '\0';
    }
}

/*======================= Greeting menu starts here =========================*/

void showOption()
{
    puts("====================================");
    puts("    Welcome to Tic-Tac-Toe Game!    ");
    puts("====================================");
    puts("1. Play with two players");
    puts("2. Play vs Computer (Currently N/A)");
    puts("3. Show statistics");
    puts("4. Exit");
}

int takeChoice()
{
    int availableOption[] = {1, 2, 3, 4};

    int optionChoosed;
    printf("\nYour choice: ");
    scanf("%d", &optionChoosed);

    for(int i = 0; i < 4; i++)
    {
        if(optionChoosed == availableOption[i]) {return optionChoosed;}
    }

    return 0;
}

/*======================= Game mechanisms starts here =======================*/

void printTables(char table[3][3])
{
    printf("\n\n");

    int m = 0; // THIS IS THE FIRST INDEX OF THE TABLE

    for(int i = 0; i < 5; i++)
    {
        if(i % 2 == 1) { // EVEN LINES GOES HERE
            for(int j = 0; j < 17; j++)
            { 
                if(j == 5 || j == 11)
                    printf(" ");
                else
                    printf("-");
            }
        } 

        else {   //ODD LINES GOES HERE
        
            int n = 0; // THE SECOND INDEX OF THE TABLE
            for(int k = 0; k < 17; k++)
            {
                if(k == 2 || k == 8 || k == 14) { 
                    printf("%c",table[m][n]);
                    n++; 
                }
                else if((k == 5) || (k == 11)) 
                    printf("|");
                else
                    printf(" ");
            }
            m++; // INCREMENT EVERYTIME AFTER PRINTING ODD LINES
        }
        printf("\n"); // BREAKLINE
    }
    printf("\n"); // MORE SPACE
}

void clearTables(char table[3][3])
{
    for(int m = 0; m < 3; m++)
    {
        for(int n = 0; n < 3; n++)
        {
            table[m][n] = ' ';
        }
    }
}

void initializePlayers(const char* gametype, player players[2])
{
    if(gametype == "multiplayer")
    {
        // NAME INPUT SCREEN
        printf("\n\n");
        for(int i = 0; i < 2; i++) 
        {
            printf("Please enter player %d name: ", i + 1);
            scanf("%s", players[i].name);
            players[i].winStatus = 0;
        }
        printf("\n\n\n(Press ANY key to continue)\n");
        getch();
        

        // CHOOSING SIGN SCREEN
        system("cls");
        printf("\n\n");
        printf("%s, which signs are you going to use?(O/X) ", players[0].name);
        getSingleChar(); // don't know what this line actually does
                         // and don't know why I actually need this
        ask_sign_again:
        players[0].SIGN = getSingleChar();
        if(players[0].SIGN == 'O' || players[0].SIGN == 'o') { 
            players[0].SIGN = 'O';
            players[1].SIGN = 'X'; 
        } 
        else if(players[0].SIGN == 'X' || players[0].SIGN == 'x') { 
            players[0].SIGN = 'X';
            players[1].SIGN = 'O'; 
        }
        else { 
            system("cls");
            printf("\n\nThere is no such sign...\n");
            printf("%s, which signs are you going to use?(O/X) ", players[0].name);
            goto ask_sign_again; 
        }
        

        // TELLING USER'S SIGN SCREEN
        system("cls");
        printf("\n\n");
        printf("Okay,\n\n");
        printf("%s will use the %c signs\n", players[0].name, players[0].SIGN);
        printf("%s will use the %c sign\n", players[1].name, players[1].SIGN);
        printf("\n(Press ANY key if you are ready to play)\n");
        getch();
    }


    else
    {
        printf("This is vs computer");
    }
}

void showHelpScreen()
{
    system("cls");
    char table[3][3] = {
        {'1', '2', '3'},
        {'4', '5', '6'},
        {'7', '8', '9'},
    };

    printTables(table);
    
    printf("To choose a block in the table, \n");
    printf("press the corresponding number to the position like the table above.\n");
    printf("You can't choose any blocks that already choosen either by player 1 or player 2.\n\n\n");

    printf("Press ANY key to continue...\n");
    getch();
}

int isStillCanMove(char table[3][3])
{
    int stillCanMove = 0;

    for(int m = 0; m < 3; m++)
    {
        for(int n = 0; n < 3; n++)
        {
            if(table[m][n] == ' '){
                stillCanMove = 1;
                return stillCanMove;
            }
        }
    }

    return stillCanMove;
}

int checkIsGameover(char table[3][3])
{
    if(table[0][0] != ' ')
    {
        if(table[0][0] == table[0][1] && table[0][0] == table[0][2])
            return 1;
        else if(table[0][0] == table[1][0] && table[0][0] == table[2][0]) 
            return 1;
    }
    if(table[1][1] != ' ')
    {
        if(table[1][1] == table[1][0] && table[1][1] == table[1][2])
            return 1;
        else if(table[1][1] == table[0][1] && table[1][1] == table[2][1])
            return 1;
        else if(table[1][1] == table[0][0] && table[1][1] == table[2][2]) 
            return 1;
        else if(table[1][1] == table[0][2] && table[1][1] == table[2][0])
            return 1;
    }
    if(table[2][2] != ' ')
    {
        if(table[2][2] == table[2][0] && table[2][2] == table[2][1])
            return 1;
        else if(table[2][2] == table[0][2] && table[2][2] == table[1][2]) 
            return 1;
    }
    
    return 0;
}

int processChoosenOption(char table[3][3], char choice, player players)
{
    int choice_int = choice - '0';
    choice_int = choice_int - 1;
    int firstIndex = choice_int / 3;
    int secondIndex = choice_int % 3;

    /* the block isn't choosen yet */
    if(table[firstIndex][secondIndex] == ' ') {

        table[firstIndex][secondIndex] = players.SIGN;
        if(checkIsGameover(table)) { 
            players.winStatus = 1;
            return 1; 
        }
        if(!isStillCanMove(table)) {
            return 2;
        }
    } 
    /* the block is already choose */
    else {
        printf("You can't choose that block!\n");
        return 3;
    }

    return 0;
}

int askForRestartGame()
{
    int x;
    printf("Enter E/e to exit, or other keys to play again: ");

    x = getSingleChar();
    if(x == 'E' || x == 'e') 
        return 0; 
    else 
        return 1;
}

int startMultiplayer(char table[3][3])
{
    system("cls"); //CLEAN THE SCREEN

    // CREATE and INITIALIZE PLAYERS section
    player players[2];
    initializePlayers("multiplayer", players);

    // GAMEPLAY
    int currentPlayer;
    char choosenOption;
    char possibleOption[12] = {'e', 'E', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    int condition = 0;
    for(int i = 0; ; i++)
    {
        re_choice:
        currentPlayer = i % 2;
        system("cls");

        printTables(table);
        printf("%s, it's your turn.\n", players[currentPlayer].name);
        printf("Enter 1-9 to mark the block in the table, or 0 for help, or e/E to exit\n");
        printf("Choose your answer: ");
        choosenOption = getSingleChar();

        // FILTERING THE CHOOSEN OPTION
        for(int i = 0; i <= 12; i++)
        {
            if(i == 12) {
                printf("There is no such option.\n");
                getch();
                goto re_choice;
            }
            if(choosenOption == possibleOption[i]) { break; }
        }

        /* If the choosen option passed the filtering loop */
        if (choosenOption != '0' && choosenOption != 'e' && choosenOption != 'E'){

            condition = processChoosenOption(table, choosenOption, 
                                            players[currentPlayer]);

            /* If the game is over */
            if(condition == 1){ 
                system("cls");
                printTables(table);
                printf("\nCongratulation %s! You win the round!\n", 
                    players[currentPlayer].name);
                return 0;
            }

            /* If there is no possible move left */
            else if(condition == 2){
                system("cls");
                printTables(table);
                printf("\nThere is no possible move left...\n");
                return 0;
            }

            /* if the selected block is already choosen */
            else if(condition == 3) {
                getch();
                goto re_choice;
            }
        }

        else if (choosenOption == '0'){
            showHelpScreen();
            /* Why not just let go?
             * Because the loop will make this player
             * skip his/her turn if he/she the option
             * to look at help screen.
             * So I use goto to prevent the loop counter
             * increments.
             */
            goto re_choice;
        } 

        else // EXIT THE GAME
            return 1;         
    }
}

void startVsComputer()
{
    printf("\nvs Computer is currently not available...\n");
}

void showStatistics()
{
    printf("\nStatistics is currently not available...\n");
}


int main()
{
    int optionToExecute;
    char table[3][3] = {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '},
    };
    
    show_option:
    system("cls");
    showOption();
    // Make sure the user enter proper input
    optionToExecute = takeChoice();
    while(!optionToExecute)
    {
        printf("There is no such option\n");
        optionToExecute = takeChoice();
    }

    int exit;
    switch(optionToExecute)
    {
        case 1:
            exit = startMultiplayer(table);
            if(!exit) { 
                if(askForRestartGame()) {
                    goto show_option;
                } 
            }
            break;
        case 2:
            startVsComputer();
            printf("\nPress ANY key to continue...\n");
            getch();
            goto show_option;
            break;
        case 3:
            showStatistics();
            printf("\nPress ANY key to continue...\n");
            getch();
            goto show_option;
            break;
        case 4:
            break;
    }

    printf("Exit\n");
    return 0;
}