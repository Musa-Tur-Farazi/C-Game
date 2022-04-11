/*
    MUSA TUR FARAZI
    STUDENT ID : 2005038

    MD. AS-AID RAHMAN
    STUDENT ID : 2005039

    CSE'20 (LAB GROUP: A2)


*/
# include "iGraphics.h"
# include<conio.h>

int layer, selected, level_option, layer_indication;
int score_easy,score_medium,score_hard;
int ob1_num,ob2_num,plane_serial,missile_num;
int screen_x,screen_y;
int sd,life;
int max_score_easy =0,max_score_medium =0,max_score_hard =0;


char score_txt_1[15];
char score_txt_2[15];
char score_txt_3[15];
char score_txt_easy[15];
char score_txt_medium[15];
char score_txt_hard[15];
char life_text[15];

void draw_helicopter(int,int);
void speed();
void show_wall();
void show_moving_planes();
void show_missile();
void show_pillar_down();
void show_pillar_up();
void make_pillar_down();
void make_pillar_up();
void down_helicopter();
void make_moving_planes();
void make_wall();
void missile_shoot();

void level_display();
void draw_menu();



void collision_level_easy();
void collision_level_medium();
void collision_level_hard();

void score_count(int);
void score_show();
void score_present();
void store_score();

void sound_menu();
void sound_gameplay();

void help();
void reset();
int maximum(int a, int b);
int digit_display(int x,int y,int n);

FILE *fp;

typedef struct
{

    float x;
    float y;
    float width;
    float length;
    float velocity;
    int heli_life;
} heli;

heli helicopter;

typedef struct
{

    float x;
    float y;
    int width;
    int length;
    float velocity;
    int existance;

} obs;

obs pillar_down[30],pillar_up[30],wall[30],moving_planes[30];


typedef struct
{
    float x;
    float y;
    float velocity;
    float power;
} Missile;

Missile missile[40];


void iDraw()
{

    iClear();
    if(layer == 0)
    {
        reset();           ///menu
        sound_gameplay();
        sound_menu();
        draw_menu();
    }

    else if(layer == 1)
    {

        sound_menu();
        sound_gameplay();
        iSetColor(0,255,0);
        iShowBMP(0,50,"level_easy.bmp");
        draw_helicopter(helicopter.x,helicopter.y);
        show_pillar_down();
        show_pillar_up();
        collision_level_easy();
        score_show();
        speed();

    }

    else if(layer == 2)  ///level option display
    {
        sound_menu();
        sound_gameplay();
        level_display();

    }

    else if(layer == 3)  ///level_medium
    {
        sound_menu();
        sound_gameplay();
        iSetColor(0,255,0);
        iShowBMP(0,50,"level_medium.bmp");
        draw_helicopter(helicopter.x,helicopter.y);
        show_pillar_down();
        show_pillar_up();
        show_wall();
        collision_level_easy();
        collision_level_medium();
        score_show();
        speed();
    }
    else if(layer ==4)  ///score showing layer
    {
        sound_menu();
        sound_gameplay();
        score_count(layer_indication);

    }

    else if(layer ==5)  ///level_hard
    {
        sound_menu();
        sound_gameplay();
        iSetColor(0,255,0);
        iShowBMP(0,50,"level_hard.bmp");
        draw_helicopter(helicopter.x,helicopter.y);
        show_moving_planes();
        show_missile();
        collision_level_hard();
        score_show();
    }
    else if(layer == 6)
    {
        sound_menu();
        sound_gameplay();
        iShowBMP(0,60,"scorepage1.bmp");
        score_present();
    }
    else if(layer == 7)
    {
        sound_menu();
        sound_gameplay();
        help();
    }

}


void iMouseMove(int mx, int my)
{
    //Not Used
}

void iMouse(int button, int state, int mx, int my)
{

    if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        //Not used
    }
}

void iKeyboard(unsigned char key)
{
    if(key == 'q')
    {
        exit(0);
    }

    if(key == 'm') sd=1;
    if(key == 'c') sd=0;
    if(layer == 1 || layer == 3 || layer == 5)
    {
        if(key == 'd')
        {
            if (helicopter.x + helicopter.width / 2 <= screen_x) (helicopter.x)+= (helicopter.velocity*.6); ///
        }
        if(key == 'a')
        {
            if (helicopter.x - helicopter.width / 2>= 0) (helicopter.x)-= (helicopter.velocity*.6); ///
        }
        if(key == 'w')
        {
            if (helicopter.y - helicopter.length / 2<= screen_y-helicopter.length) (helicopter.y)+= (helicopter.velocity*.6); ///
        }
        if(key == 's')
        {
            if (helicopter.y + helicopter.length / 2>= 0) (helicopter.y)-= (helicopter.velocity*.6);
        }

    }

    if(layer == 0)
    {

        if(key == '\r')
        {
            mciSendString("play click.mp3",NULL,0,NULL);
            if(selected == 1)
            {
                layer = 1;
            }
            if(selected == 2)
            {
                layer = 2;
            }
            if(selected == 3)
            {
                layer = 6;
            }
            if(selected == 4)
            {
                layer = 7;
            }
            if(selected == 5)
            {
                exit(0);
            }
        }

    }
    else if(layer == 2)
    {

        if(key=='\b') layer = 0;

        else if(key == '\r')
        {
            mciSendString("play click.mp3",NULL,0,NULL);
            if(level_option == 1) layer = 1;
            if(level_option == 2) layer = 3;
            if(level_option == 3) layer = 5;
        }
        if(key == '\b')
        {
            mciSendString("play click.mp3",NULL,0,NULL);
            layer = 0;
        }
    }
    else if( layer == 4)
    {

        if(key=='\r')
        {
            mciSendString("play click.mp3",NULL,0,NULL);
            layer = 0;
        }
    }
    else if(layer == 1 || layer == 3 || layer == 5 || layer == 7)
    {

        if(key=='\b')
        {
            mciSendString("play click.mp3",NULL,0,NULL);
            layer = 0;
        }
    }
    else if(layer == 6)
    {

        if(key == '\b')
        {
            mciSendString("play click.mp3",NULL,0,NULL);
            layer = 0;
        }
    }

}

void iSpecialKeyboard(unsigned char key)
{

    if(key == GLUT_KEY_END)
    {
        exit(0);
    }
    if (layer == 0)
    {
        if (selected == 1 && key == GLUT_KEY_DOWN)
        {
            mciSendString("play optionchange.mp3",NULL,0,NULL);
            selected = 2;
        }
        else if (selected == 2 && key == GLUT_KEY_DOWN)
        {
            mciSendString("play optionchange.mp3",NULL,0,NULL);
            selected = 3;
        }
        else if (selected == 2 && key == GLUT_KEY_UP)
        {
            mciSendString("play optionchange.mp3",NULL,0,NULL);
            selected = 1;
        }
        else if (selected == 3 && key == GLUT_KEY_UP)
        {
            mciSendString("play optionchange.mp3",NULL,0,NULL);
            selected = 2;
        }
        else if (selected == 3 && key == GLUT_KEY_DOWN)
        {
            mciSendString("play optionchange.mp3",NULL,0,NULL);
            selected = 4;
        }
        else if (selected == 4 && key == GLUT_KEY_UP)
        {
            mciSendString("play optionchange.mp3",NULL,0,NULL);
            selected = 3;
        }
        else if (selected == 4 && key == GLUT_KEY_DOWN )
        {
            mciSendString("play optionchange.mp3",NULL,0,NULL);
            selected = 5;
        }
        else if (selected == 5 && key == GLUT_KEY_UP)
        {
            mciSendString("play optionchange.mp3",NULL,0,NULL);
            selected = 4;
        }
    }

    if(layer == 1 || layer == 3 || layer == 5)
    {
        if(key == GLUT_KEY_RIGHT)
        {
            if (helicopter.x + helicopter.width / 2 <= screen_x) (helicopter.x)+= (helicopter.velocity*.6); ///
        }
        if(key == GLUT_KEY_LEFT)
        {
            if (helicopter.x - helicopter.width / 2>= 0) (helicopter.x)-= (helicopter.velocity*.6); ///
        }
        if(key == GLUT_KEY_UP)
        {
            if (helicopter.y - helicopter.length / 2<= screen_y-helicopter.length) (helicopter.y)+= (helicopter.velocity*.6); ///
        }
        if(key == GLUT_KEY_DOWN)
        {
            if (helicopter.y + helicopter.length / 2>= 0) (helicopter.y)-= (helicopter.velocity*.6);
        }

    }

    if(layer == 2)
    {
        if (level_option == 1 && key == GLUT_KEY_DOWN)
        {
            mciSendString("play optionchange.mp3",NULL,0,NULL);
            level_option = 2;
        }
        else if (level_option == 2 && key == GLUT_KEY_DOWN)
        {
            mciSendString("play optionchange.mp3",NULL,0,NULL);
            level_option = 3;
        }
        else if (level_option == 2 && key == GLUT_KEY_UP)
        {
            mciSendString("play optionchange.mp3",NULL,0,NULL);
            level_option = 1;
        }
        else if (level_option == 3 && key == GLUT_KEY_UP)
        {
            mciSendString("play optionchange.mp3",NULL,0,NULL);
            level_option = 2;
        }
        else if (level_option == 3 && key == GLUT_KEY_DOWN)
        {
            mciSendString("play optionchange.mp3",NULL,0,NULL);
            level_option = 4;
        }
        else if (level_option == 4 && key == GLUT_KEY_UP)
        {
            mciSendString("play optionchange.mp3",NULL,0,NULL);
            level_option = 3;
        }
    }


}

void draw_helicopter(int x, int y)
{

    iSetColor(70,70,70);
    iFilledEllipse(x+20+32+25,y+15+7-3,50,7,100);///shadow
    iSetColor(220,220,220);
    iFilledEllipse(x+20+32+30,y+15+7,50,7,100); ///top fan

    iSetColor(70,70,70);
    iFilledRectangle(x+19,y+1.5,170-138,3);///body and rear connector shadow
    iSetColor(70,70,70);
    iFilledRectangle(x+19,y-6.5,170-138,3);///body and rear connector shadow

    iSetColor(70,70,70);
    iFilledEllipse(x+10-2.5,y-3,10,10,100);
    iSetColor(220,220,220);
    iFilledEllipse(x+10,y,10,10,100); ///small fan

    iSetColor(230,200,25);
    iFilledRectangle(x+20,y+2,170-138,3); ///body and rear connector(upper)

    iSetColor(230,200,25);
    iFilledRectangle(x+20,y-5,170-138,3); ///body and rear connector(lower)

    iSetColor(70,70,70);
    iFilledRectangle(x+10+32+11,y-29.5,50,3);///shadow
    iSetColor(70,70,70);
    iFilledRectangle(x+20+32+13,y-26,3,7);///shadow
    iSetColor(70,70,70);
    iFilledRectangle(x+20+32+15+26,y-26,3,7);///shadow

    iSetColor(230,200,25);
    iFilledRectangle(x+10+32+13,y-27,50,3); ///lower rect

    iSetColor(230,200,25);
    iFilledRectangle(x+20+32+15,y-25,3,7); ///lower rect-body connector(rear)

    iSetColor(230,200,25);
    iFilledRectangle(x+20+32+15+28,y-25,3,7); ///lower rect-body connector(front)

    iSetColor(70,70,70);
    iFilledEllipse(x+20+32+30-3,y-3,30,20,100);
    iSetColor(0,255,127);
    iFilledEllipse(x+20+32+30,y,30,20,100); ///body

}

void down_helicopter()
{
    helicopter.y-=8;
}



void draw_pillar_down(int x,int y)
{
    iSetColor(85,107,47);
    iFilledRectangle(x,0,40,y);
    iSetColor(154,205,50);
    iFilledRectangle(x+30,0,10,y);
    iSetColor(107,142,35);
    iFilledRectangle(x+15,0,15,y);
    iSetColor(10,10,10);
    iRectangle(x-1,y-10,42,10);
    iRectangle(x-1,0,42,y-10);
}
void draw_pillar_up(int x,int y)
{
    iSetColor(85,107,47);
    iFilledRectangle(x,y,40,600);
    iSetColor(154,205,50);
    iFilledRectangle(x+30,y,10,600);
    iSetColor(107,142,35);
    iFilledRectangle(x+15,y,15,600);
    iSetColor(10,10,10);
    iRectangle(x-1,y,42,10);
    iRectangle(x-1,y+10,42,600);
}

void show_pillar_down()
{
    int i;
    for(i=0; i<30; i++)
    {
        if(pillar_down[i].existance)
        {
            draw_pillar_down(pillar_down[i].x,pillar_down[i].y);
            pillar_down[i].x-=pillar_down[i].velocity;
        }

    }
}

void show_pillar_up()
{
    int i;
    for(i=0; i<30; i++)
    {
        if(pillar_up[i].existance)
        {
            draw_pillar_up(pillar_up[i].x,pillar_up[i].y);
            pillar_up[i].x-=pillar_up[i].velocity;

        }
    }
}


void make_pillar_down()
{
    srand(time(0));
    if (layer == 1 )
    {
        pillar_down[ob1_num].existance = 1;
        pillar_down[ob1_num].x = (rand() % 100) + screen_x ;
        pillar_down[ob1_num].y = (rand() % 300)+rand()%100 + 50;


        ob1_num++;

        if (ob1_num >= 30) ob1_num = 0;
    }
    if (layer == 3 )
    {
        pillar_down[ob1_num].existance = 1;
        pillar_down[ob1_num].x = (rand() % 200) + screen_x ;
        pillar_down[ob1_num].y = (rand() % 300)+100;

        ob1_num++;

        if (ob1_num >= 30) ob1_num = 0;
    }
}

void make_pillar_up()
{
    srand(time(0));
    if (layer == 1 )
    {
        pillar_up[ob2_num].existance = 1;
        pillar_up[ob2_num].x = (rand() % 100) + screen_x;
        pillar_up[ob2_num].y = (rand() % 300)+ 300;

        ob2_num++;

        if (ob2_num >= 30) ob2_num = 0;
    }
    else
    {
        pillar_up[ob2_num].existance = 1;
        pillar_up[ob2_num].x = (rand() % 200) + screen_x;
        pillar_up[ob2_num].y = (rand() % 300)+700;

        ob2_num++;

        if (ob2_num >= 30) ob2_num = 0;
    }
}

void draw_wall(int x,int y)
{
    iShowBMP(x,y,"brick2.bmp");
}

void show_wall()
{

    for(int i=0; i<30; i++)
    {
        if(wall[i].existance)
        {
            draw_wall(wall[i].x,wall[i].y);
            wall[i].x-=wall[i].velocity*1.7;
        }
    }
}

void make_wall()
{
    if (layer == 3 || layer ==5)
    {
        wall[ob2_num].existance = 1;
        wall[ob2_num].x = (rand() % 100) + screen_x;
        wall[ob2_num].y = (rand()% 650) +40;
        ob2_num++;
        if (ob2_num >= 30) ob2_num = 0;
    }
}

void draw_moving_planes(int x,int y)
{
    double w = 10,l=20;

    double xa[] = {y+100, y + l+100, y+100 };
    double ya[] = {x - w/2-300, x-300, x + w/2-300};

    double xa1[] = {x-20, x-5, x+4, x+10};
    double ya1[] = {y+ l + 20, y+l+22, y+ l + 20 + 40, y+ l + 20 + 40};

    double xa2[] = {x-20, x-5, x+4, x+10};
    double ya2[] = {y+l+10, y+l+8, y+ l+10- 40, y+ l+10- 40};

    int body = 20;
    int min_axis = 7.5;
    int max_axis = 15;

    iSetColor(255,69,0);
    iFilledPolygon(xa1, ya1, 4);///up wing
    iFilledPolygon(xa2, ya2, 4);///down wing

    iSetColor(0,255,0);
    iFilledRectangle(x-38.2+65, y+l+10-5, 4, 20);///back part

    iSetColor(200, 50, 20);
    iFilledRectangle(x-38, y+l+12, 65, 6); /// body
    iSetColor(0,0,240);
    iFilledRectangle(x-25, y+l+12+1.5, 15, 3);///window
    iSetColor(220,50,20);
    iFilledRectangle(x-25, y+l+18, 25, 4);
    iFilledRectangle(x-25, y+l+8, 25, 4);

    iSetColor(255, 255, 255);
    iFilledEllipse(x-39, y + l + 15, min_axis-2, max_axis-4);///fan

}


void show_moving_planes()
{

    for(int i=0; i<30; i++)
    {
        if(moving_planes[i].existance)
        {
            draw_moving_planes(moving_planes[i].x,moving_planes[i].y);
            moving_planes[i].x-=(moving_planes[i].velocity+3.5);
        }
    }

}


void make_moving_planes()
{
    if (layer == 5)
    {
        moving_planes[plane_serial].existance = 1;
        moving_planes[plane_serial].x = (rand() % 500) + screen_x;
        moving_planes[plane_serial].y = (rand()% 600) +40;
        plane_serial++;
        if (plane_serial >= 30) plane_serial = 0;
    }
}



void show_missile(void)
{

    iSetColor(245,240,245);
    for (int i = 0; i < 40; i++)
    {
        if (missile[i].power)
        {
            iFilledCircle(missile[i].x, missile[i].y, 5, 100);
            missile[i].x -= (moving_planes[i].velocity+8);
        }
    }
}

void missile_shoot(void)
{
    float missile_gap;
    int i;
    missile_gap = 150/(score_hard);
    if (i >= missile_gap)
    {
        if(layer == 5)
        {
            if(moving_planes[plane_serial].existance)
            {
                missile[missile_num].power = 1;
                missile[missile_num].y = moving_planes[plane_serial].y+34; //
                missile[missile_num].x = moving_planes[plane_serial].x -moving_planes[plane_serial].width;
                missile_num++;
            }
            if(missile_num >=40)
            {
                missile_num = 0;
            }
            if(plane_serial >= 30)
            {
                plane_serial = 0;
            }
            plane_serial++;
        }
        i = 0;
    }
    else i++;
}

void sound_menu()
{

    mciSendString("open menusfx.mp3 repeat",NULL, 0, NULL);
    if(sd == 0 && (layer == 0 || layer == 2 || layer ==4 || layer ==6 || layer ==7))
    {
             mciSendString("play menusfx.mp3 repeat",NULL, 0, NULL);
    }
    else if(sd == 1 || !((layer == 0 || layer == 2 || layer ==4 || layer ==6 || layer ==7)))
    {
        mciSendString("pause menusfx.mp3",NULL, 0, NULL);
    }
}

void sound_gameplay()
{
    mciSendString("open game_play.mp3",NULL,0,NULL);
    if(sd == 0 && (layer == 1 || layer == 3 || layer ==5))
    {
        mciSendString("play game_play.mp3 repeat",NULL, 0, NULL);
    }
    else if(sd == 1 || !(layer == 1 || layer == 3 || layer ==5))
    {
        mciSendString("pause game_play.mp3",NULL,0,NULL);
    }
}


void collision_level_easy(void)
{
    for (int i = 0; i < 30; i++)
    {
        if ((((helicopter.x - pillar_down[i].x) <= 4) && (pillar_down[i].x - helicopter.x) <= 120  && (( helicopter.y - pillar_down[i].y) <=22) && pillar_down[i].existance == 1)||helicopter.y <0)
        {

            pillar_down[i].existance = 0;
            pillar_down[i].x = -200;
            helicopter.heli_life -- ;
            life--;
            mciSendString("play singlecollide.mp3",NULL,0,NULL);
            if(helicopter.heli_life == 0)
            {
                mciSendString("play collison_sfx1.wav",NULL,0,NULL);
                layer = 4;
                break;
            }
        }
        else if((((helicopter.x - pillar_up[i].x) <= 4) && (pillar_up[i].x - helicopter.x) <= 120 && ((pillar_up[i].y - helicopter.y) <= 22) && pillar_up[i].existance == 1) || helicopter.y <0)
        {
            pillar_up[i].existance = 0;
            pillar_up[i].x = -200;
            helicopter.heli_life -- ;
            life--;
            mciSendString("play singlecollide.mp3",NULL,0,NULL);
            if(helicopter.heli_life == 0)
            {
                mciSendString("play collison_sfx1.wav",NULL,0,NULL);
                layer = 4;
                break;
            }
        }
    }
    layer_indication = 1;
}

void collision_level_medium()
{
    for(int i = 0; i<30; i++)
    {
        if(((((helicopter.x - wall[i].x)) <= 50) && (wall[i].x- helicopter.x <= 120) && (helicopter.y - wall[i].y) <= 150 && (wall[i].y - helicopter.y) <=25 && wall[i].existance == 1) || helicopter.y<0)
        {
            wall[i].existance = 0;
            wall[i].x-=200;
            helicopter.heli_life -- ;
            life--;
            mciSendString("play singlecollide.mp3",NULL,0,NULL);
            if(helicopter.heli_life == 0)
            {
                mciSendString("play collison_sfx1.wav",NULL,0,NULL);
                layer = 4;
                break;
            }
        }
    }
    layer_indication = 3;
}

void collision_level_hard()
{
    for (int i = 0 ; i < 40; i++)
    {
        if((((helicopter.x - missile[i].x) <= 5) && (missile[i].x - helicopter.x) <= 140  && (( helicopter.y - missile[i].y) <=30) && ((missile[i].y - helicopter.y) <= 22) && missile[i].power == 1) ||(helicopter.y <0))
        {
            missile[i].power = 0;
            helicopter.heli_life -- ;
            life--;
            mciSendString("play singlecollide.mp3",NULL,0,NULL);
            if(helicopter.heli_life == 0)
            {
                mciSendString("play collison_sfx1.wav",NULL,0,NULL);
                layer = 4;
                break;
            }
        }

        else if((((helicopter.x - moving_planes[i].x) <= 50) && (moving_planes[i].x - helicopter.x) <= 140  && (( helicopter.y - moving_planes[i].y) <= 50) && ((moving_planes[i].y - helicopter.y) <= 50)&& moving_planes[i].existance == 1) || helicopter.y <0)
        {
            moving_planes[i].existance = 0;
            moving_planes[i].x = -200;
            helicopter.heli_life -- ;
            life--;
            mciSendString("play singlecollide.mp3",NULL,0,NULL);
            if(helicopter.heli_life == 0)
            {
                mciSendString("play collison_sfx1.wav",NULL,0,NULL);
                layer = 4;
                break;
            }
        }

        layer_indication = 5;
    }

}
int maximum(int a, int b)
{
    return (a >= b) ? a:b;
}
void speed()
{
    for(int i=0; i<30; i++)
    {
        pillar_down[i].velocity +=0.005;
        pillar_up[i].velocity+=0.005;
        wall[i].velocity+=0.001;
    }
}

void score_show()
{
    iSetColor(255,255,255);
    fp = fopen("Highscore.txt","r");

    fscanf(fp,"%d\n",&max_score_easy);
    fscanf(fp,"%d\n",&max_score_medium);
    fscanf(fp,"%d\n",&max_score_hard);

    iText(screen_x-200,750,"SCORE : ",GLUT_BITMAP_HELVETICA_18);
    if(layer == 1)
    {
        iText(screen_x-50,750,itoa((score_easy+=1)/25,score_txt_easy,10),GLUT_BITMAP_HELVETICA_18);
        iText(screen_x-200,700,"HIGHSCORE : ",GLUT_BITMAP_HELVETICA_18);
        iText(screen_x-50,700,itoa(max_score_easy,score_txt_1,10),GLUT_BITMAP_HELVETICA_18);
        iText(screen_x-200,650,"LIFE : ",GLUT_BITMAP_HELVETICA_18);
        iText(screen_x-50,650,itoa(life,life_text,10),GLUT_BITMAP_HELVETICA_18);
    }
    else if(layer == 3)
    {
        iText(screen_x-50,750,itoa((score_medium+=1)/25,score_txt_medium,10),GLUT_BITMAP_HELVETICA_18);
        iText(screen_x-200,700,"HIGHSCORE : ",GLUT_BITMAP_HELVETICA_18);
        iText(screen_x-50,700,itoa(max_score_medium,score_txt_2,10),GLUT_BITMAP_HELVETICA_18);
        iText(screen_x-200,650,"LIFE : ",GLUT_BITMAP_HELVETICA_18);
        iText(screen_x-50,650,itoa(life,life_text,10),GLUT_BITMAP_HELVETICA_18);
    }
    else if(layer == 5)
    {
        iText(screen_x-50,750,itoa((score_hard+=1)/25,score_txt_hard,10),GLUT_BITMAP_HELVETICA_18);
        iText(screen_x-200,700,"HIGHSCORE : ",GLUT_BITMAP_HELVETICA_18);
        iText(screen_x-50,700,itoa(max_score_hard,score_txt_3,10),GLUT_BITMAP_HELVETICA_18);
        iText(screen_x-200,650,"LIFE : ",GLUT_BITMAP_HELVETICA_18);
        iText(screen_x-50,650,itoa(life,life_text,10),GLUT_BITMAP_HELVETICA_18);
    }

    if(layer == 4)
    {
        score_easy = 0;
        score_medium = 0;
        score_hard = 0;
    }
    fclose(fp);
}

void score_count(int layer)
{
    int titleX = screen_x / 2-200 ;
    int titleY = screen_y - 390;
    int option_length = 300;
    int option_width = 50;
    int option_x = titleX + 30;
    int option_y = titleY - 100;


    iShowBMP(0,0,"score_present.bmp");//

    iShowBMP(option_x+10,option_y+20,"gameover.bmp");
    iShowBMP(option_x+10,option_y+20-90,"score.bmp");
    iSetColor(240,240,200);

    iSetColor(66, 57, 128);

    if(layer == 1)
        iText(option_x + 187, option_y + 20 - 54,score_txt_easy, GLUT_BITMAP_TIMES_ROMAN_24);

    if(layer == 3)
        iText(option_x + 187, option_y + 20 - 54,score_txt_medium, GLUT_BITMAP_TIMES_ROMAN_24);

    if(layer == 5)
        iText(option_x + 187, option_y + 20 - 54,score_txt_hard, GLUT_BITMAP_TIMES_ROMAN_24);

    fp = fopen("Highscore.txt","w");

    fscanf(fp,"%d\n",&max_score_easy);
    fscanf(fp,"%d\n",&max_score_medium);
    fscanf(fp,"%d\n",&max_score_hard);

    max_score_easy = maximum(max_score_easy,atoi(score_txt_easy));
    fprintf(fp,"%d\n",max_score_easy);
    max_score_medium = maximum(max_score_medium,atoi(score_txt_medium));
    fprintf(fp,"%d\n",max_score_medium);
    max_score_hard = maximum(max_score_hard,atoi(score_txt_hard));
    fprintf(fp,"%d\n",max_score_hard);

    fclose(fp);

    iShowBMP2(option_x-150, option_y + 20 - 280,"pls2.bmp",0);
}

int digit_display(int x,int y,int n)
{
    if(n == 0) iShowBMP2(x,y,"0.bmp",0);
    if(n == 1) iShowBMP2(x,y,"1.bmp",0);
    if(n == 2) iShowBMP2(x,y,"2.bmp",0);
    if(n == 3) iShowBMP2(x,y,"3.bmp",0);
    if(n == 4) iShowBMP2(x,y,"4.bmp",0);
    if(n == 5) iShowBMP2(x,y,"5.bmp",0);
    if(n == 6) iShowBMP2(x,y,"6.bmp",0);
    if(n == 7) iShowBMP2(x,y,"7.bmp",0);
    if(n == 8) iShowBMP2(x,y,"8.bmp",0);
    if(n == 9) iShowBMP2(x,y,"9.bmp",0);
}
void score_present()
{
    iSetColor(255,255,255);

    int x =0;
    fp = fopen("Highscore.txt","r");

    fscanf(fp,"%d\n",&max_score_easy);
    fscanf(fp,"%d\n",&max_score_medium);
    fscanf(fp,"%d\n",&max_score_hard);

    while(max_score_easy != 0)
    {
        int d = max_score_easy %10;
        digit_display(600-x,470,d);
        max_score_easy /= 10;
        x += 38;
    }
    x =0;
    while(max_score_medium != 0)
    {
        int d = max_score_medium %10;
        digit_display(600-x,365,d);
        max_score_medium /= 10;
        x +=38;
    }
    x=0;
    while(max_score_hard != 0)
    {
        int d = max_score_hard %10;
        digit_display(600-x,279,d);
        max_score_hard /= 10;
        x +=38;
    }


    fclose(fp);

    if(sd == 0) iShowBMP2(2,10,"unmute.bmp",0);
    else if(sd == 1) iShowBMP2(2,10,"mute.bmp",0);

    iSetColor(255, 255, 255);
    iText(1000,100,"<<", GLUT_BITMAP_TIMES_ROMAN_24);
    iText(1030,100,"BACK", GLUT_BITMAP_TIMES_ROMAN_24);

}

void draw_menu()
{

    int titleX = screen_x / 2 + 160;
    int titleY = screen_y - 180;
    int option_length = 200;
    int option_width = 50;
    int option_x = titleX + 30;
    int option_y = titleY - 100;


    iSetColor(255,215,0);

    iShowBMP(0,0,"main_menu.bmp");
    iSetColor(255, 50,0);//
    iSetColor(255, 255, 255);
    if(selected == 1)
    {
        iFilledRectangle(option_x, option_y, option_length, option_width);
        iSetColor(0, 0, 0);
        iText(option_x + 55, option_y + 20, "NEW GAME", GLUT_BITMAP_9_BY_15);
    }
    else
    {
        iSetColor(255, 255, 255);
        iRectangle(option_x, option_y, option_length, option_width);
        iText(option_x + 55, option_y + 20, "NEW GAME", GLUT_BITMAP_9_BY_15);
    }
    if(selected == 2)
    {
        iFilledRectangle(option_x, option_y - 75, option_length, option_width);
        iSetColor(0, 0, 0);
        iText(option_x + 52.5, option_y + 20 - 75, "LEVEL", GLUT_BITMAP_9_BY_15);
    }
    else
    {
        iSetColor(255, 255, 255);
        iRectangle(option_x, option_y - 75, option_length, option_width);
        iText(option_x + 52.5, option_y + 20 - 75, "LEVEL", GLUT_BITMAP_9_BY_15);
    }
    if(selected == 3)
    {
        iFilledRectangle(option_x, option_y - 150, option_length, option_width);
        iSetColor(0, 0, 0);
        iText(option_x + 50, option_y + 20 - 150, "SCORE", GLUT_BITMAP_9_BY_15);
    }
    else
    {
        iSetColor(255, 255, 255);
        iRectangle(option_x, option_y - 150, option_length, option_width);
        iText(option_x + 50, option_y + 20 - 150, "SCORE", GLUT_BITMAP_9_BY_15);
    }
    if(selected == 4)
    {
        iFilledRectangle(option_x, option_y - 225, option_length, option_width);
        iSetColor(0, 0, 0);
        iText(option_x + 47.5, option_y + 20 - 225, "HELP", GLUT_BITMAP_9_BY_15);
    }
    else
    {
        iSetColor(255, 255, 255);
        iRectangle(option_x, option_y - 225, option_length, option_width);
        iText(option_x + 47.5, option_y + 20 - 225, "HELP", GLUT_BITMAP_9_BY_15);
    }

    if(selected == 5)
    {
        iFilledRectangle(option_x, option_y - 300, option_length, option_width);
        iSetColor(0, 0, 0);
        iText(option_x + 45, option_y + 20 - 300, "EXIT GAME", GLUT_BITMAP_9_BY_15);
    }
    else
    {
        iSetColor(255, 255, 255);
        iRectangle(option_x, option_y - 300, option_length, option_width);
        iText(option_x + 45, option_y + 20 - 300, "EXIT GAME", GLUT_BITMAP_9_BY_15);
    }

    if(sd == 0) iShowBMP2(10,50,"unmute.bmp",0);
    else iShowBMP2(10,50,"mute.bmp",0);
}

void level_display()
{
    iSetColor(255, 255, 255);
    int titleX = screen_x / 2 + 170;
    int titleY = screen_y - 170;
    int option_length = 200;
    int option_width = 50;
    int option_x = titleX + 30;
    int option_y = titleY - 100;

    iShowBMP(0,0,"main_menu.bmp"); //
    if(level_option == 1)
    {
        iFilledRectangle(option_x, option_y, option_length, option_width);
        iSetColor(0, 0, 0);
        iText(option_x + 55, option_y + 20, "EASY", GLUT_BITMAP_9_BY_15);
    }
    else
    {
        iSetColor(255, 255, 255);
        iRectangle(option_x, option_y, option_length, option_width);
        iText(option_x + 55, option_y + 20, "EASY", GLUT_BITMAP_9_BY_15);
    }
    if(level_option == 2)
    {
        iFilledRectangle(option_x, option_y - 75, option_length, option_width);
        iSetColor(0, 0, 0);
        iText(option_x + 52.5, option_y + 20 - 75, "MEDIUM", GLUT_BITMAP_9_BY_15);
    }
    else
    {
        iSetColor(255, 255, 255);
        iRectangle(option_x, option_y - 75, option_length, option_width);
        iText(option_x+52.5, option_y + 20 - 75, "MEDIUM", GLUT_BITMAP_9_BY_15);
    }

    if(level_option == 3)
    {
        iFilledRectangle(option_x, option_y - 150, option_length, option_width);
        iSetColor(0, 0, 0);
        iText(option_x + 50, option_y + 20 - 150, "HARD", GLUT_BITMAP_9_BY_15);
    }
    else
    {
        iSetColor(255, 255, 255);
        iRectangle(option_x, option_y - 150, option_length, option_width);
        iText(option_x + 50, option_y + 20 - 150, "HARD", GLUT_BITMAP_9_BY_15);
    }

    if(sd == 1) iShowBMP2(2,10,"unmute.bmp",0);
    else iShowBMP2(2,10,"mute.bmp",0);

    iSetColor(255, 255, 255);
    iText(1000,100,"<<", GLUT_BITMAP_TIMES_ROMAN_24);
    iText(1030,100,"BACK", GLUT_BITMAP_TIMES_ROMAN_24);
}

void help()
{
    iShowBMP(0,0,"help.bmp");
    iSetColor(255, 255, 255);
    iText(1000,100,"<<", GLUT_BITMAP_TIMES_ROMAN_24);
    iText(1030,100,"BACK", GLUT_BITMAP_TIMES_ROMAN_24);
}


void reset()
{

    helicopter.x = 20;
    helicopter.y = 500;
    helicopter.width = 145;
    helicopter.length = 70;
    helicopter.velocity = 30;
    helicopter.heli_life = 3;
    life = 3;
    for(int i=0; i<30; i++)
    {
        pillar_down[i].x = 100;
        pillar_down[i].y = 100;

        pillar_down[i].width = 80;
        pillar_down[i].length = 60;
        pillar_down[i].velocity = 3 ;
        pillar_down[i].existance = 0;

        pillar_up[i].x = 100;
        pillar_up[i].y = 100;


        pillar_up[i].width = 80;
        pillar_up[i].length = 60;
        pillar_up[i].velocity = 3 ;
        pillar_up[i].existance = 0;

        wall[i].x = 100;
        wall[i].y = 100;

        wall[i].width = 80;
        wall[i].length = 60;
        wall[i].velocity = 1.7 ;
        wall[i].existance = 0;


        moving_planes[i].x = 100;
        moving_planes[i].y = 100;

        moving_planes[i].velocity = 2 ;
        moving_planes[i].existance = 0;
    }

    for(int i =0; i<40; i++)
    {
        missile[i].x;
        missile[i].y;
        missile[i].velocity = 2;
        missile[i].power = 0;
    }
    score_easy = 0;
    score_medium = 0;
    score_hard = 0;


}

int main()
{
    srand(time(0));
    layer = 0;
    selected = 1;
    sd = 0;
    score_easy = 0;
    score_medium = 0;
    score_hard = 0;

    level_option = 1;
    ob1_num = 0;
    ob2_num = 0;
    missile_num = 0;
    plane_serial = 0;

    iSetTimer(1500,make_pillar_down);
    iSetTimer(40,down_helicopter);
    iSetTimer(1500,make_pillar_up);
    iSetTimer(1200,make_wall);
    iSetTimer(2000,make_moving_planes);
    iSetTimer(10,missile_shoot);
    iSetTimer(3000,score_show);

    screen_x=1200;
    screen_y=800;
    iInitialize(screen_x, screen_y, "Chopper Survival Quest");

    return 0;
}
