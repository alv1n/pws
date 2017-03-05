#include "asm.h"
#include "keyboard.h"
#include "sleep.h"
#include "scan.h"
#include "print.h"

struct position
{
    int x[100];
    int y[100];
    int nom_x;
    int nom_y;
}position;

void snake(void)
{
    PrintClear();
    int score = 0;
    char score_str[6];

    struct position pos;
    pos.nom_x = 100;
    pos.nom_y = 200;
    
    for(int i=0;i<100;i++)
    {
        pos.x[i] = 0;
        pos.y[i] = 0;
    }
    pos.x[0] = 5;
    pos.y[0] = 5;
    pos.x[1] = 4;
    pos.y[1] = 5;

    char last_key = 'd';
    char key_pressed = 'd';
    int collision = 0;

    while(!collision)
    {
        //Get input
        if(new_input)
        {
            new_input = 0;
            key_pressed = GetChar();
            if(key_pressed != 'a' && key_pressed != 's' && key_pressed != 'd' && key_pressed != 'w')
            {
                key_pressed = last_key;
            }
            
        }

        //Movement
        int i;
        for(i = 0;pos.x[i+1] != 0; i++)
        {
            if(i != 0)
            {
                pos.x[i+1] = pos.x[i];
                pos.y[i+1] = pos.y[i];
            }
        }
        pos.x[i] = 0;
        pos.y[i] = 0;
        switch(key_pressed)
        {
            case 'a':
            case 'A':
                pos.x[0] -= 1;
                break;
            case 'd':
            case 'D':
                pos.x[0] += 1;
                break;
            case 's':
            case 'S':
                pos.y[0] -= 1;
                break;
            case 'w':
            case 'W':
                pos.y[0] += 1;
                break;
            default:
                break;
        }


    
        //Test if food is eaten
        if(pos.x[0] == pos.nom_x && pos.y[0] == pos.nom_y)
        {
            pos.nom_x = Random(pos.nom_y);
            pos.nom_y = Random(pos.nom_x);
        }

         //Drawing stuff
         for(int j = 0; pos.x[j] != 0; j++)
         {
            if(j == 0)
            {
                DrawCharacter('@',8*pos.x[j],8*pos.y[j]);
            }
            else
            {
                DrawCharacter('#',8*pos.x[j],16*pos.y[j]);
            }
         }
        DrawCharacter('X',8*pos.nom_x,16*pos.nom_y);
        SignedString(score,score_str,10);           
        DrawStringz(score_str,0,0);

        //Test Collision
        if(pos.x[0] < 1 || pos.x[0] > 96 || pos.y[0] < 1 || pos.y[0] > 64)
        {
            return;
        }

        for(i = 1;pos.x[i] != 0; i++)
        {
            if(pos.x[0] == pos.x[i] && pos.y[0] == pos.x[i])
            {
                return;
            }
        }

        Sleep(1000000);
    }

}

