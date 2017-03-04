#include "asm.h"
#include "keyboard.h"
struct position
{
    int x[100];
    int y[100];
    int nom_x;
    int nom_y;
}position;

void snake(void)
{
    int score = 0;
    char score_str[6];

    struct position pos;
    pos.nom_x = Random(23) % 96;
    pos.nom_y = Random(pos.nom_x) % 64;
    pos.x[0] = (Random(pos.nom_y) + 3) % 96 ;
    pos.y[0] = Random(pos.x[0]) % 64 ;

    pos.x[1] = pos.x[0] - 1;
    pos.y[1] = pos.y[0] - 1;

    char last_key = 'd';
    char key_pressed = 'd';
    int collision = 0;

    while(!collision)
    {
        //Get input
        if(new_input)
        {
            new_input = 0;
            key_pressed = (lastPressed+counter)[0];
            if(key_pressed != 'a' || key_pressed != 's' || key_pressed != 'd' || key_pressed != 'w')
            {
                key_pressed = last_key;
            }
            
        }

        //Movement
        int new_head_x;
        int new_head_y;
        if(key_pressed = 'a')
        {
            new_head_x = pos.x[0] -1;
            for(int i = 0;pos.x[i] != 0; i++)
            {
                if(i != 0)
                {
                    pos.x[i+1] = pos.x[i];
                }
            }
        }

    
        //Test if food is eaten
        if(pos.x[0] == pos.nom_x && pos.y[0] == pos.nom_y)
        {
            pos.nom_x = Random(pos.nom_y);
            pos.nom_y = Random(pos.nom_x);
        }

         //Drawing stuff
         int i = 0;
         while(pos.x[i] != 0)
         {
            if(i == 0)
            {
                DrawCharacter('@',pos.x[i],pos.y[i]);
            }
            else
            {
                DrawCharacter('#',pos.x[i],pos.y[i]);
            }
            DrawCharacter('X',pos.nom_x,pos.nom_y);
            SignedString(score,score_str,10);           
            DrawStringz(score_str,0,0);
         }
        DrawCharacter('X',pos.nom_x,pos.nom_y);
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

        timerWait(1000000);
    }

}
