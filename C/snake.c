#include "asm.h"

struct position
{
    int pos_x[100];
    int pos_y[100];
    int nom_x;
    int nom_y;
}position;

void snake(void)
{
    int score = 0;
    char score_str[6];

    struct position pos;
    pos.nom_x = Random(0x23) % 96;
    pos.nom_y = Random(pos.nom_x) % 64;

    pos.pos_x[0] = (Random(pos.nom_y) + 3) % 96 ;
    pos.pos_y[0] = Random(pos.pos_x) % 64 ;

    pos.pos_x[1] = pos.pos_x[0] - 1;
    pos.pos_y[1] = pos.pos_y[0] - 1;

    char last_key = 'd';
    char key_pressed = 'd';
        
    int collision = 0;
    while(!collision)
    {
        //Test if food is eaten
        if(pos.pos_x[0] == pos.nom_x && pos.pos_y[0] == pos.nom_y)
        {
            pos.nom_x = Random(pos.nom_y);
            pos.nom_y = Random(pos.nom_x);
}
         //Get Key_pressed

         //Drawing stuff
         int i = 0;
         while(pos.pos_x[i] != 0)
         {
            if(i == 0)
            {
                DrawCharacter('@',pos.pos_x[i],pos.pos_y[i]);
            }
            else
            {
                DrawCharacter('#',pos.pos_x[i],pos.pos_y[i]);
            }
            DrawCharacter('X',pos.nom_x,pos.nom_y);
            SignedString(score,score_str,10);           
            DrawStringz(score_str,0,0);
         }
        DrawCharacter('X',pos.nom_x,pos.nom_y);
        SignedString(score,score_str,10);           
        DrawStringz(score_str,0,0);

        //Test Collision
        if(pos.pos_x[0] < 1 || pos.pos_x[0] > 96 || pos.pos_y[0] < 1 || pos.pos_y[0] > 64)
        {
            return;
        }

        for(i = 1;pos.pos_x[i] != 0; i++)
        {
            if(pos.pos_x[0] == pos.pos_x[i] && pos.pos_y[0] == pos.pos_x[i])
            {
                return;
            }
        }
    }

}
