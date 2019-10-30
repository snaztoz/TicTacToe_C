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
//
//

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Player
{
    char name[30];
    int winStatus;
    char SIGN; // could be O or X
} player;

enum Boolean {false, true};

enum GameConditions 
{
    /* exit conditions */
    NOT_EXIT,
    EXIT,

    /* winning conditions */
    NOT_WINNER = 0,
    WINNER,

    /* game flow */
    KEEP_PLAY = 0,
    GAMEOVER,
    CANT_MOVE,
    ILLEGAL,
};

// manually create an input function,
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

void clrstdin(void)
{
    while(getchar() != '\n') 0;
}

/*======================= SOME MECHANISMS =========================*/

int isLegal(char choosenOption)
{
    char possibleOption[12] = {
        'e', 'E', '0', 
        '1', '2', '3', 
        '4', '5', '6', 
        '7', '8', '9'
    };

    for(int i = 0; i < 12; i++)
        if(choosenOption == possibleOption[i]) 
            return true;

    printf("There is no such option.\n");
    getch();
    return false;
}

void printTable(char table[3][3])
{
    printf("\n\n");

    int m = 0;  // THE FIRST INDEX OF THE TABLE
    int n;      //  ~  SECOND INDEX OF THE TABLE

    for(int i = 1; i <= 5; i++)
    {
        /* even lines */
        if(i % 2 == 0) {
            for(int j = 0; j < 17; j++)
            { 
                (j == 5 || j == 11)? printf(" ") : printf("-");
            }
        } 

        /* odd lines */
        else {
            n = 0;
            for(int k = 0; k < 17; k++)
            {
                if(k == 2 || k == 8 || k == 14) { 
                    printf("%c",table[m][n]);
                    n++; 
                }
                else if(k == 5 || k == 11) 
                    printf("|");
                else
                    printf(" ");
            }
            m++; // increment first index only after printing odd lines
        }
        printf("\n"); // breakline
    }
    printf("\n"); // give more space
}

void clearTable(char table[3][3])
{
    for(int m = 0; m < 3; m++)
        for(int n = 0; n < 3; n++)
            table[m][n] = ' ';
}

int isStillCanMove(char table[3][3])
{
    for(int m = 0; m < 3; m++)
    {
        for(int n = 0; n < 3; n++)
        {
            if(table[m][n] == ' ')
                return true;
        }
    }

    return false;
}

int restartGame()
{
    printf("Enter E/e to exit, or other keys to play again: ");
    int x = getSingleChar();

    if (x == 'E' || x == 'e')
        return false;
    else
        return true;
}


/*======================= DISPLAY PAGES =========================*/
void showOption()
{
    puts("====================================");
    puts("    Welcome to Tic-Tac-Toe Game!    ");
    puts("====================================");
    puts("1. Play with two players");
    puts("2. Play vs Computer (Currently N/A)");
    puts("3. Show statistics");
    puts("4. Exit");
    printf("\nYour choice: ");
}

void showHelpScreen()
{
    system("cls");
    char table[3][3] = {
        {'1', '2', '3'},
        {'4', '5', '6'},
        {'7', '8', '9'},
    };

    printTable(table);
    
    printf("To choose a block in the table, \n");
    printf("press the corresponding number to the position like the table above.\n");
    printf("You can't choose any blocks that already choosen either by player 1 or player 2.\n\n\n");

    printf("Press ANY key to continue...\n");
    getch();
}


/*======================= GAME FLOW =======================*/

void initPlayers(const char* gametype, player players[2])
{
    if(gametype == "multiplayer")
    {
        /* inputting users name */
        printf("\n");
        for(int i = 0; i < 2; i++) 
        {
            printf("\nPlease enter player %d name (it can't contain any spaces): ", i + 1);
            scanf("%s", players[i].name);
            players[i].winStatus = NOT_WINNER;
            if(i == 0) 
                clrstdin();
        }
        printf("\n\n\n(Press ANY key to continue)\n");
        getch();
        
        /* choose signs each player will use */
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
        else {  // if user input illegal signs 
            system("cls");
            printf("\n\nThere is no such sign...\n");
            printf("%s, which signs are you going to use?(O/X) ", players[0].name);
            goto ask_sign_again; 
        }
        
        /* retell the used signs */
        system("cls");
        printf("\n\n");
        printf("Okay,\n\n");
        printf("%s will use the %c signs\n", players[0].name, players[0].SIGN);
        printf("%s will use the %c sign\n", players[1].name, players[1].SIGN);
        printf("\n(Press ANY key if you are ready to play)\n");
        getch();
    }

    /* not yet created */
    else
    {
        printf("This is vs computer");
    }
}

int isGameover(char table[3][3])
{
    if(table[0][0] != ' ')
    {
        if( (table[0][0] == table[0][1] && table[0][0] == table[0][2]) ||
            (table[0][0] == table[1][0] && table[0][0] == table[2][0]) )
            return true;
    }
    if(table[1][1] != ' ')
    {
        if( (table[1][1] == table[1][0] && table[1][1] == table[1][2]) ||
            (table[1][1] == table[0][1] && table[1][1] == table[2][1]) ||
            (table[1][1] == table[0][0] && table[1][1] == table[2][2]) ||
            (table[1][1] == table[0][2] && table[1][1] == table[2][0]) )
            return true;
    }
    if(table[2][2] != ' ')
    {
        if( (table[2][2] == table[2][0] && table[2][2] == table[2][1]) ||
            (table[2][2] == table[0][2] && table[2][2] == table[1][2]) )
            return true;
    }
    
    return false;
}

int processChoosenOption(char table[3][3], char choice, player players)
{
    int choice_int = (choice - '0') - 1;
    int firstIndex = choice_int / 3;
    int secondIndex = choice_int % 3;

    /* the block isn't choosen yet */
    if(table[firstIndex][secondIndex] == ' ') {

        /* fill the table with user's sign */
        table[firstIndex][secondIndex] = players.SIGN;

        /* check some conditions */
        if(isGameover(table)) { 
            players.winStatus = WINNER;
            return GAMEOVER; 
        }
        if(!isStillCanMove(table))
            return CANT_MOVE;
    } 

    /* the block is already choose */
    else {
        printf("You can't choose that block!\n");
        return ILLEGAL;
    }

    return KEEP_PLAY;
}

int startMultiplayer(char table[3][3])
{
    system("cls"); // clean the screen

    // create and init players
    player players[2];
    initPlayers("multiplayer", players);

    // GAMEPLAY
    int currentPlayer;
    int condition = 0;
    char choosenOption;

    for(int i = 0; ; i++)
    {
        re_choice:
        currentPlayer = i % 2;

        /* displaying the texts */
        system("cls");
        printTable(table);
        printf("%s, it's your turn.\n", players[currentPlayer].name);
        printf("Enter 1-9 to mark the block in the table, or 0 for help, or e/E to exit\n");
        printf("Choose your answer: ");
        choosenOption = getSingleChar();

        /* filtering the choosen option */
        if(!isLegal(choosenOption))
            goto re_choice;

        /* If the choosen option passed the filtering loop */
        if (choosenOption != '0' && choosenOption != 'e' && choosenOption != 'E')
        {
            condition = processChoosenOption(table, choosenOption, 
                                            players[currentPlayer]);

            /* If the game is over */
            if(condition == GAMEOVER){ 
                system("cls");
                printTable(table);
                printf("\nCongratulation %s! You win the round!\n", 
                    players[currentPlayer].name);
                return NOT_EXIT;
            }
            /* If there is no possible move left */
            else if(condition == CANT_MOVE) {
                system("cls");
                printTable(table);
                printf("\nThere is no possible move left...\n");
                return NOT_EXIT;
            }
            /* if the selected block is already choosen */
            else if(condition == ILLEGAL) {
                getch();
                goto re_choice;
            }
        }

        else if (choosenOption == '0'){
            showHelpScreen();
            /* Why not just let go?
             * Because the loop will make this player
             * skip his/her turn if he/she choose the option
             * to look at help screen.
             * So that goto is used to prevent the loop counter
             * increments.
             */
            goto re_choice;
        } 

        else // EXIT THE GAME
            return EXIT;         
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
    int optionToExecute, exit;
    char table[3][3] = {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '},
    };
    
    show_option:
    system("cls");
    showOption();

    /* Make sure the user enter proper input */
    optionToExecute = getSingleChar() - '0';

    /* run the option */
    switch(optionToExecute)
    {
        case 1:
            if(startMultiplayer(table) == NOT_EXIT)
                if(restartGame()) {
                    clearTable(table);
                    goto show_option;
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
        default:
            printf("There is no such option...\n");
            getch();
            goto show_option;
    }

    printf("\nExit\n");
    return 0;
}
