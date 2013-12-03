/*math_for_kids*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>
#include <windows.h>
#include <sys/types.h>
#include <unistd.h>


#define NUM_OF_QUESTIONS 10

#define VERSION "0.2"
#define RETRIES_PER_QUESTION    3
#define MAX_NUMBER 10
#define FAIL    0
#define SUCCESS    1
#define BUFLEN 100
#define SMILEY ":-)"
#define SADLEY ":-("

#define T_250  250
#define T_500  500
#define T_750  750
#define T_1000 1000


#define DO  262
#define RE  294
#define MI  330
#define FA  349
#define SOL 392
#define LA  440
#define SI  494

char rcv_str[BUFLEN + 1];
int total_success_cntr = 0;

void play_error_sound()
{
    Beep(SOL , T_250);
    Beep(FA , T_250);
    Beep(MI , T_250);
    Beep(RE , T_250);
    Beep(DO , T_250);
}



void play_success_sound_short()
{
    Beep(FA , T_250);
    Beep(SI , T_250);
    Beep(SI , T_250);
    Beep(SI , T_250);
    Beep(SOL , T_250);
    Beep(LA , T_250);
    Beep(LA , T_250);
    Beep(SOL , T_1000);
}

void play_success_sound_short_orig()
{
    Beep(DO , T_250);
    Beep(RE , T_250);
    Beep(MI , T_250);
    Beep(FA , T_250);
    Beep(SOL , T_250);
    Beep(LA , T_250);
    //Beep(SI , 500);
}
void play_finish_sound()
{
    Beep(SI , T_500);
    Beep(DO , T_500);
    Beep(RE , T_500);
    Beep(MI , T_500);
    Beep(FA , T_500);
}

/****************/
int read_input()
{
    memset (rcv_str , 0 , BUFLEN + 1);
    printf("-->");
    scanf("%s", rcv_str);
    return atoi(rcv_str);
}

/****************/
int single_question (int a , int b)
{
    int num_of_retries = 0;
    int result = FAIL;


    printf("%d + %d = ?\n" , a , b);
    for (num_of_retries=0 ; num_of_retries < RETRIES_PER_QUESTION ; num_of_retries++)
    {
        int answer = read_input();
        if (answer < 0 || answer > (MAX_NUMBER * 2))
        {
            printf("\tNumber out of range(%d)...\n",answer);
            play_error_sound();
        }
        else if (answer == (a + b))
        {
            printf("%s Good answer!!!(%d)...\n",SMILEY,answer);
            play_success_sound_short();
            result = SUCCESS;
            break;
        }
        else
        {
            printf("\tWrong answer, try again (%d)...\n",answer);
            play_error_sound();
        }
    }
    return result;
}

/****************/
void delay(unsigned int mseconds)
{
    clock_t goal = mseconds + clock();
    while (goal > clock());
}


/****************/
int main()
{
    int questions_cntr = 0;
    int a , b , i;

    while (questions_cntr < NUM_OF_QUESTIONS)
    {
        questions_cntr++;
        printf("\n%d) ",questions_cntr);
        srand(time(NULL));
        a = (rand() % MAX_NUMBER) + 1;
        b = ((a * a + questions_cntr) % MAX_NUMBER) + 1;

        if (single_question(a , b) == SUCCESS)
        {
            total_success_cntr++;
        }
    }

    printf("\nFinished, your success ratio = %d/%d \n",total_success_cntr , questions_cntr);
    for (i = 0 ; i < questions_cntr ; i++)
    {
        if ( i < total_success_cntr)
        {
            printf("--%s ",SMILEY );
        }
        else
        {
            printf("--%s ",SADLEY );
        }

        delay(500);
    }
    play_finish_sound();
    getchar();

    return 0;
}
