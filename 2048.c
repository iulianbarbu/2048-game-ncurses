#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <menu.h>
#include <time.h>
#include <math.h>
#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
#define COLOR_2 8
#define COLOR_4 9
#define COLOR_8 10
#define COLOR_16 11
#define COLOR_32 12
#define COLOR_64 13
#define COLOR_128 14
#define COLOR_256 15
#define COLOR_512 16
#define COLOR_1024 17
#define COLOR_2048 18
#define COLOR_DEF 20
#define COLOR_PAC 21
#define COLOR_WIN 22
#define COLOR_BACKGROUND 23
//------------------------------------------------------------
// FUNCTII PENTRU JOCUL PROPRIU ZIS





void afiseaza(WINDOW *win[],int game_state[][4],int i,int j, int directie)
{
    int x = game_state[i][j];
    if(x==2)
        wbkgd(win[afla_poz(i,j)],COLOR_PAIR(13));
    if(x==4)
        wbkgd(win[afla_poz(i,j)],COLOR_PAIR(3));
    if(x==8)
        wbkgd(win[afla_poz(i,j)],COLOR_PAIR(4));
    if(x==16)
        wbkgd(win[afla_poz(i,j)],COLOR_PAIR(5));
    if(x==32)
        wbkgd(win[afla_poz(i,j)],COLOR_PAIR(6));
    if(x==64)
        wbkgd(win[afla_poz(i,j)],COLOR_PAIR(7));
    if(x==128)
        wbkgd(win[afla_poz(i,j)],COLOR_PAIR(8));
    if(x==256)
        wbkgd(win[afla_poz(i,j)],COLOR_PAIR(9));
    if(x==512)
        wbkgd(win[afla_poz(i,j)],COLOR_PAIR(10));
    if(x==1024)
        wbkgd(win[afla_poz(i,j)],COLOR_PAIR(11));
    if(x==2048)
        wbkgd(win[afla_poz(i,j)],COLOR_PAIR(12));

    mvwprintw(win[afla_poz(i,j)],2,1,"      ");
    if(x==2048 || x==1024) mvwprintw(win[afla_poz(i,j)],2,3,"%d",game_state[i][j]);
    if(x==128 || x==256 || x==512) mvwprintw(win[afla_poz(i,j)],2,4,"%d",game_state[i][j]);
    if(x==16 || x==32 || x==64) mvwprintw(win[afla_poz(i,j)],2,4,"%d",game_state[i][j]);
    if(x==2 || x==4 || x==8) mvwprintw(win[afla_poz(i,j)],2,5,"%d",game_state[i][j]);
    wrefresh(win[afla_poz(i,j)]);

}


int afla_poz(int x,int y)
{
    if(x==0) return y;
    if(x==1) return y+4;
    if(x==2) return y+8;
    if(x==3) return y+12;
}


void random_populate1(int matrix[][4])
{
    int x1,x2,y1,y2;
    srand(time(NULL));
    x1=rand()%4;
    y1=rand()%4;
    x2=rand()%4;
    y2=rand()%4;

    while(x1==x2 && y1==y2)
    {
        x1=rand()%4;
        x2=rand()%4;
        y1=rand()%4;
        y2=rand()%4;
    }



    refresh();
    matrix[x1][y1]=((rand()%2)+1)*2;
    matrix[x2][y2]=((rand()%2)+1)*2;
}


void random_populate2(int matrix[][4],WINDOW *win[])
{

    int x,y;
    x=rand()%4;
    y=rand()%4;

    while(matrix[x][y]!=0)
    {
        x=rand()%4;
        y=rand()%4;
    }

    matrix[x][y]=((rand()%2)+1)*2;

    refresh();
    afiseaza(win,matrix,x,y,-1);
    wrefresh(win[afla_poz(x,y)]);

}

void zero_matrix(int matrix[][4])
{
    int i,j;
    for(i=0; i<4; i++)
        for(j=0; j<4; j++)
            matrix[i][j]=0;
}

int misca_te_asa_cum_imi_place_mie(WINDOW *win[], int mutare[][4], int game_state[][4],int directie,WINDOW *panou,int *score)
{
    int i,j;


    if(directie==-1)
    {


        for(j=1; j<4; j++)
            for(i=0; i<4; i++)
                if(game_state[i][j]!=0 && (game_state[i][j-1]==0 || game_state[i][j-1]==game_state[i][j]))
                {
                    if(game_state[i][j]==game_state[i][j-1] && mutare[i][j]==0 && mutare[i][j-1]==0)
                    {
                        mvwprintw(win[afla_poz(i,j)],2,1,"        ");

                        game_state[i][j-1]=2*game_state[i][j];
                        game_state[i][j]=0;

                        *score=(*score)+game_state[i][j-1];
                        mvwprintw(panou,2,2,"SCOR: %d",*score);
                        wrefresh(panou);

                        refresh();

                        mutare[i][j-1]=1;


                        afiseaza(win,game_state,i,j-1,-1);
                        wbkgd(win[afla_poz(i,j)],COLOR_PAIR(2));
                        wrefresh(win[afla_poz(i,j)]);
                        wrefresh(win[afla_poz(i,j-1)]);

                        if(game_state[i][j-1]==2048) return 2;
                        return 1;
                    }
                    if(mutare[i][j]==0 && mutare[i][j-1]==0)
                    {
                        mvwprintw(win[afla_poz(i,j)],2,1,"        ");

                        game_state[i][j-1]=game_state[i][j];
                        game_state[i][j]=0;

                        refresh();


                        afiseaza(win,game_state,i,j-1,-1);
                        wbkgd(win[afla_poz(i,j)],COLOR_PAIR(2));

                        wrefresh(win[afla_poz(i,j)]);
                        wrefresh(win[afla_poz(i,j-1)]);



                        return 1;
                    }



                }

    }

    if(directie==1)
        for(j=2; j>=0; j--)
            for(i=0; i<4; i++)
                if(game_state[i][j]!=0 && (game_state[i][j+1]==0 || game_state[i][j+1]==game_state[i][j]))
                {
                    if(game_state[i][j]==game_state[i][j+1] && mutare[i][j]==0 && mutare[i][j+1]==0)
                    {
                        mvwprintw(win[afla_poz(i,j)],2,1,"        ");

                        game_state[i][j+1]=2*game_state[i][j];
                        game_state[i][j]=0;


                        *score=(*score)+game_state[i][j+1];
                        mvwprintw(panou,2,2,"SCOR: %d",*score);
                        wrefresh(panou);


                        mutare[i][j+1]=1;

                        refresh();


                        afiseaza(win,game_state,i,j+1,1);
                        wbkgd(win[afla_poz(i,j)],COLOR_PAIR(2));
                        wrefresh(win[afla_poz(i,j)]);
                        wrefresh(win[afla_poz(i,j+1)]);

                        if(game_state[i][j+1]==2048) return 2;
                        return 1;
                    }
                    if(mutare[i][j]==0 && mutare[i][j+1]==0)
                    {
                        mvwprintw(win[afla_poz(i,j)],2,1,"        ");

                        game_state[i][j+1]=game_state[i][j];
                        game_state[i][j]=0;

                        refresh();


                        afiseaza(win,game_state,i,j+1,1);
                        wbkgd(win[afla_poz(i,j)],COLOR_PAIR(2));
                        wrefresh(win[afla_poz(i,j)]);
                        wrefresh(win[afla_poz(i,j+1)]);
                        return 1;
                    }


                }


    if(directie==2)
        for(i=1; i<4; i++)
            for(j=0; j<4; j++)
                if(game_state[i][j]!=0 && (game_state[i-1][j]==0 || game_state[i-1][j]==game_state[i][j]))
                {

                    if(game_state[i][j]==game_state[i-1][j] && mutare[i][j]==0 && mutare[i-1][j]==0)
                    {
                        mvwprintw(win[afla_poz(i,j)],2,1,"        ");

                        game_state[i-1][j]=2*game_state[i][j];
                        game_state[i][j]=0;


                        mutare[i-1][j]=1;


                        *score=(*score)+game_state[i-1][j];
                        mvwprintw(panou,2,2,"SCOR: %d",*score);
                        wrefresh(panou);



                        refresh();

                        afiseaza(win,game_state,i-1,j,2);
                        wbkgd(win[afla_poz(i,j)],COLOR_PAIR(2));
                        wrefresh(win[afla_poz(i,j)]);
                        wrefresh(win[afla_poz(i-1,j)]);

                        if(game_state[i-1][j]==2048) return 2;

                        return 1;
                    }
                    if(mutare[i][j]==0 && mutare[i-1][j]==0)
                    {
                        mvwprintw(win[afla_poz(i,j)],2,1,"        ");

                        game_state[i-1][j]=game_state[i][j];
                        game_state[i][j]=0;

                        refresh();

                        afiseaza(win,game_state,i-1,j,2);
                        wbkgd(win[afla_poz(i,j)],COLOR_PAIR(2));
                        wrefresh(win[afla_poz(i,j)]);
                        wrefresh(win[afla_poz(i-1,j)]);
                        return 1;
                    }


                }

    if(directie==-2)
        for(i=2; i>=0; i--)
            for(j=0; j<4; j++)
                if(game_state[i][j]!=0 && (game_state[i+1][j]==0 || game_state[i+1][j]==game_state[i][j]))
                {
                    if(game_state[i][j]==game_state[i+1][j] && mutare[i][j]==0 && mutare[i+1][j]==0)
                    {
                        mvwprintw(win[afla_poz(i,j)],2,1,"        ");


                        game_state[i+1][j]=2*game_state[i][j];
                        game_state[i][j]=0;

                        mutare[i+1][j]=1;


                        *score=(*score)+game_state[i+1][j];
                        mvwprintw(panou,2,2,"SCOR: %d",*score);
                        wrefresh(panou);



                        refresh();

                        afiseaza(win,game_state,i+1,j,-2);

                        wbkgd(win[afla_poz(i,j)],COLOR_PAIR(2));
                        wrefresh(win[afla_poz(i,j)]);
                        wrefresh(win[afla_poz(i+1,j)]);

                        if(game_state[i+1][j]==2048) return 2;

                        return 1;

                    }
                    if(mutare[i][j]==0 && mutare[i+1][j]==0)
                    {
                        mvwprintw(win[afla_poz(i,j)],2,1,"        ");

                        game_state[i+1][j]=game_state[i][j];
                        game_state[i][j]=0;


                        refresh();


                        afiseaza(win,game_state,i+1,j,-2);

                        wbkgd(win[afla_poz(i,j)],COLOR_PAIR(2));
                        wrefresh(win[afla_poz(i,j)]);
                        wrefresh(win[afla_poz(i+1,j)]);
                        return 1;

                    }


                }

    return 0;
}

int misca_te_fals(int a[][4],int mutare[][4],int directie)
{
    int i,j;
    if(directie==-1)
        for(j=1; j<4; j++)
            for(i=0; i<4; i++)
            {
                if(a[i][j]!=0 && (a[i][j-1]==0 || a[i][j-1]==a[i][j]))
                {
                    if(a[i][j]==a[i][j-1] && mutare[i][j]==0 && mutare[i][j-1]==0)
                    {
                        a[i][j-1]=2*a[i][j];
                        a[i][j]=0;

                        mutare[i][j-1]=1;

                        return 1;
                    }
                    if(mutare[i][j]==0 && mutare[i][j-1]==0)
                    {

                        a[i][j-1]=a[i][j];
                        a[i][j]=0;


                        return 0;
                    }
                }

            }

    if(directie==1)
        for(j=2; j>=0; j--)
            for(i=0; i<4; i++)
            {
                if(a[i][j]!=0 && (a[i][j+1]==0 || a[i][j+1]==a[i][j]))
                {
                    if(a[i][j]==a[i][j+1] && mutare[i][j]==0 && mutare[i][j+1]==0)
                    {
                        a[i][j+1]=2*a[i][j];
                        a[i][j]=0;

                        mutare[i][j+1]=1;

                        return 1;
                    }
                    if(mutare[i][j]==0 && mutare[i][j+1]==0)
                    {

                        a[i][j+1]=a[i][j];
                        a[i][j]=0;


                        return 0;
                    }
                }

            }
    if(directie==-2)
        for(i=2; i>=0; i--)
            for(j=0; j<4; j++)
                if(a[i][j]!=0 && (a[i+1][j]==0 || a[i+1][j]==a[i][j]))
                {
                    if(a[i][j]==a[i+1][j] && mutare[i][j]==0 && mutare[i+1][j]==0)
                    {


                        a[i+1][j]=2*a[i][j];
                        a[i][j]=0;

                        mutare[i+1][j]=1;

                        return 1;

                    }
                    if(mutare[i][j]==0 && mutare[i+1][j]==0)
                    {

                        a[i+1][j]=a[i][j];
                        a[i][j]=0;

                        return 0;

                    }


                }

    if(directie==2)
        for(i=1; i<4; i++)
            for(j=0; j<4; j++)
                if(a[i][j]!=0 && (a[i-1][j]==0 || a[i-1][j]==a[i][j]))
                {

                    if(a[i][j]==a[i-1][j] && mutare[i][j]==0 && mutare[i-1][j]==0)
                    {

                        a[i-1][j]=2*a[i][j];
                        a[i][j]=0;


                        mutare[i-1][j]=1;


                        return 1;
                    }
                    if(mutare[i][j]==0 && mutare[i-1][j]==0)
                    {
                        a[i-1][j]=a[i][j];
                        a[i][j]=0;

                        return 0;
                    }


                }

    return -1;
}
int MUTARE_ELIBERATOARE(int a[][4])
{

    int i,j,down=0,up=0,left=0,right=0,br=0,b[4][4],c[4][4],d[4][4],e[4][4],f[4][4];

    zero_matrix(f);

    for(i=0; i<4; i++)
        for(j=0; j<4; j++)
        {
            b[i][j]=a[i][j];
            c[i][j]=a[i][j];
            d[i][j]=a[i][j];
            e[i][j]=a[i][j];
        }

    while(br>=0)
    {
        br=misca_te_fals(b,f,-2);
        down+=br;
    }
    br=0;
    zero_matrix(f);
    while(br>=0)
    {
        br=misca_te_fals(c,f,2);
        up+=br;
    }
    br=0;
    zero_matrix(f);
    while(br>=0)
    {
        br=misca_te_fals(d,f,-1);
        left+=br;
    }
    br=0;
    zero_matrix(f);
    while(br>=0)
    {
        br=misca_te_fals(e,f,1);
        right+=br;
    }

    if(left>-1 && left>=right && left>=down && left>=right) return KEY_LEFT;
    if(right>-1 && right>=left && right>=down && right>=up) return KEY_RIGHT;
    if(up>-1 && up>=right && up>=down && up>=left) return KEY_UP;
    if(down>-1 && down>=right && down>=up && down>=left) return KEY_DOWN;
}


int see_state(int a[][4])
{
    int i,j,b=1;


    for(i=0; i<4; i++)
        for(j=0; j<4; j++)
        {
            if(a[i][j]==0) return 1;
            if((j+1<=3 &&  a[i][j+1]==a[i][j]) || (j-1>=0 && a[i][j-1]==a[i][j]) || (i+1<=3 && a[i+1][j]==a[i][j]) || (i-1>=0 && a[i-1][j]==a[i][j])) b=0;
        }
    if(b==1) return 0;
    return 1;
}

int create_game_instance(int arg)
{
INCEPUT:
    if(1)
    {
        WINDOW *win[16],*princwin,*underline[3],*messages,*panou_inf;
        int game_state[4][4],contor=0,mutare[4][4];
        int rows,cols,c=0,score=0;
        int i,j,p1=1,p2,br=1,cbr=0;

FISIERGOL:
        if(arg==0)
        {
            for(i=0; i<4; i++)
                for(j=0; j<4; j++)
                    game_state[i][j]=0;
            random_populate1(game_state);

        }

        if(arg==1)
        {
            FILE *fp;
            fp = fopen("saved_state","r");
            int i,j;
            for(i=0; i<4; i++)
                for(j=0; j<4; j++)
                    fscanf(fp,"%d",&game_state[i][j]);
            arg=0;

        }


        refresh();
        getmaxyx(stdscr,rows,cols);
        panou_inf = newwin(26,20,((rows-26)/2-5),((cols-50)/2)-25);
        princwin = newwin(26,50,((rows-26)/2)-5,(cols-50)/2);
        box(panou_inf,0,0);

        wbkgd(princwin,COLOR_PAIR(16));
        wrefresh(princwin);
        wrefresh(panou_inf);
        mvwprintw(panou_inf,2,2,"Scor: %d",score);
        wrefresh(panou_inf);
        for(i=0; i<16; i+=4,contor++)
        {
            p2=2;
            for(j=0; j<4; j++)
            {
                win[i+j]=newwin(5,10,((rows-26)/2)-5+p1,((cols-50)/2)+p2);
                wbkgd(win[i+j],COLOR_PAIR(2));
                if(game_state[contor][j])
                    afiseaza(win,game_state,contor,j,-1);
                p2=p2+12;
                wrefresh(win[i+j]);
            }
            p1=p1+6;

        }
	
		
        messages = newwin(1,50,((rows-26)/2)+22,((cols-50)/2));
	
        mvwprintw(messages,0,15,"For menu press (m)");

        wrefresh(messages);

        int copie_tasta=0,b=1,inv=0;
        time_t clk;
        struct tm *cur_time;

        time(&clk);
        cur_time = localtime(&clk);
        mvwprintw(panou_inf,3,2,"Data: %d-%d-%d",cur_time->tm_mday,1+cur_time->tm_mon,1900+cur_time->tm_year);
        mvwprintw(panou_inf,4,2,"Ora: %d:%d:%d",cur_time->tm_hour,cur_time->tm_min,cur_time->tm_sec);
        mvwprintw(panou_inf,6,2,"*USE ARROW KEYS  ");
        mvwprintw(panou_inf,7,2,"FOR MOVING CELLS.");
        mvwprintw(panou_inf,9,2,"*THE GAME WILL S-");
        mvwprintw(panou_inf,10,2,"-TOP WHEN YOU RE-");
        mvwprintw(panou_inf,11,2,"-ACH 2048.	  ");
        mvwprintw(panou_inf,13,2,"*YOU COULD SAVE  ");
        mvwprintw(panou_inf,14,2,"YOUR PROGRESS PR-");
        mvwprintw(panou_inf,15,2,"-ESSING (m) AND  ");
        mvwprintw(panou_inf,16,2,"CHOOSING QUIT AND");
        mvwprintw(panou_inf,17,2,"SAVE.");
        mvwprintw(panou_inf,19,2,"*AT EVERY 20 SEC ");
        mvwprintw(panou_inf,20,2,"THE GAME WILL CH-");
        mvwprintw(panou_inf,21,2,"OOSE A DIRECTION ");
        mvwprintw(panou_inf,22,2,"THAT FREES THE M-");
        mvwprintw(panou_inf,23,2,"AXIMUM NUMBER OF ");
        mvwprintw(panou_inf,24,2,"CELLS.");
        wrefresh(panou_inf);

        underline[0] = newwin(1,6,((rows-26)/2)+25,((cols-50)/2)+9);
        underline[1] = newwin(1,7,((rows-26)/2)+25,((cols-50)/2)+18);
        underline[2] = newwin(1,13,((rows-26)/2)+25,((cols-50)/2)+28);

PRINCIPAL:
        while(c!=3)
        {
            int cas=0; // ma fol. de ea atunci cand se face 2048

            time(&clk);
            cur_time = localtime(&clk);
            mvwprintw(panou_inf,3,2,"Data: %d-%d-%d",cur_time->tm_mday,1+cur_time->tm_mon,1900+cur_time->tm_year);
            mvwprintw(panou_inf,4,2,"Ora: %d:%d:%d   ",cur_time->tm_hour,cur_time->tm_min,cur_time->tm_sec);

            wrefresh(panou_inf);
            br = 1; // cu aceasta variabila retin daca s-a efectuat o miscare valida sau nu
            cbr = 0; // cu aceasta variabila numar de cat ori s-a facut miscari in tabela, pe directia data
            switch(c)
            {
            case KEY_LEFT:
                zero_matrix(mutare);
                while(br)
                {
                    cbr++;
                    br = misca_te_asa_cum_imi_place_mie(win,mutare,game_state,-1,panou_inf,&score);
                    if(br==2) cas=1;
                    if(cbr==1 && br==0) cbr=0;
                }
                if(cas==1) goto WINNERTAKESITALL;
                if(see_state(game_state)==0) goto LOSER;
                if(cbr) random_populate2(game_state,win);
                break;
            case KEY_RIGHT:
                zero_matrix(mutare);
                while(br)
                {
                    cbr++;
                    br = misca_te_asa_cum_imi_place_mie(win,mutare,game_state,1,panou_inf,&score);
                    if(br==2) cas=1;
                    if(cbr==1 && br==0) cbr=0;
                }
                if(cas==1) goto WINNERTAKESITALL;
                if(see_state(game_state)==0) goto LOSER;
                if(cbr) random_populate2(game_state,win);
                break;
            case KEY_UP:
                zero_matrix(mutare);
                while(br)
                {
                    cbr++;
                    br = misca_te_asa_cum_imi_place_mie(win,mutare,game_state,2,panou_inf,&score);
                    if(br==2) cas=1;
                    if(cbr==1 && br==0) cbr=0;
                }
                if(cas==1) goto WINNERTAKESITALL;
                if(see_state(game_state)==0) goto LOSER;
                if(cbr) random_populate2(game_state,win);
                break;
            case KEY_DOWN:
                zero_matrix(mutare);
                while(br)
                {
                    cbr++;
                    br = misca_te_asa_cum_imi_place_mie(win,mutare,game_state,-2,panou_inf,&score);
                    if(br==2) cas=1;
                    if(cbr==1 && br==0) cbr=0;
                }
                if(cas==1) goto WINNERTAKESITALL;
                if(see_state(game_state)==0) goto LOSER;
                if(cbr) random_populate2(game_state,win);
                break;
            }

            if(c==KEY_RESIZE)
            {
                contor=0;
                getmaxyx(stdscr,rows,cols);
                p1=1;

                wclear(stdscr);
                wclear(princwin);
                delwin(princwin);

                for(i=0; i<16; i++)
                {
                    wclear(win[i]);
                    delwin(win[i]);

                }

                for(i=0; i<3; i++)
                {
                    wclear(underline[i]);
                    delwin(underline[i]);
                }

                wclear(panou_inf);
                wclear(messages);
                delwin(messages);
                delwin(panou_inf);
                refresh();

                princwin = newwin(26,50,((rows-26)/2)-5,(cols-50)/2);
                panou_inf = newwin(26,20,((rows-26)/2)-5,((cols-50)/2)-25);
                box(panou_inf,0,0);
                wbkgd(princwin,COLOR_PAIR(16));
                wrefresh(princwin);
                mvwprintw(panou_inf,2,2,"Scor: %d",score);
                time(&clk);
                cur_time = localtime(&clk);
                mvwprintw(panou_inf,3,2,"Data: %d-%d-%d",cur_time->tm_mday,1+cur_time->tm_mon,1900+cur_time->tm_year);
                mvwprintw(panou_inf,4,2,"Ora: %d:%d:%d",cur_time->tm_hour,cur_time->tm_min,cur_time->tm_sec);
                mvwprintw(panou_inf,6,2,"*USE ARROW KEYS  ");
                mvwprintw(panou_inf,7,2,"FOR MOVING CELLS.");
                mvwprintw(panou_inf,9,2,"*THE GAME WILL S-");
                mvwprintw(panou_inf,10,2,"-TOP WHEN YOU RE-");
                mvwprintw(panou_inf,11,2,"-ACH 2048.	  ");
                mvwprintw(panou_inf,13,2,"*YOU COULD SAVE  ");
                mvwprintw(panou_inf,14,2,"YOUR PROGRESS PR-");
                mvwprintw(panou_inf,15,2,"-ESSING (m) AND  ");
                mvwprintw(panou_inf,16,2,"CHOOSING QUIT AND");
                mvwprintw(panou_inf,17,2,"SAVE.");
                mvwprintw(panou_inf,19,2,"*AT EVERY 20 SEC ");
                mvwprintw(panou_inf,20,2,"THE GAME WILL CH-");
                mvwprintw(panou_inf,21,2,"OOSE A DIRECTION ");
                mvwprintw(panou_inf,22,2,"THAT FREES THE M-");
                mvwprintw(panou_inf,23,2,"AXIMUM NUMBER OF ");
                mvwprintw(panou_inf,24,2,"CELLS.");
                wrefresh(panou_inf);

                for(i=0; i<16; i+=4,contor++)
                {
                    p2=2;
                    for(j=0; j<4; j++)
                    {

                        win[i+j]=newwin(5,10,((rows-26)/2)-5+p1,((cols-50)/2)+p2);
                        wbkgd(win[i+j],COLOR_PAIR(2));
                        if(game_state[contor][j])
                            afiseaza(win,game_state,contor,j,-1);
                        p2=p2+12;
                        wrefresh(win[i+j]);
                    }
                    p1=p1+6;

                }
		
		
	
                messages = newwin(1,50,((rows-26)/2)+22,((cols-50)/2));
		mvwprintw(messages,0,16,"For menu press (m)");
                wrefresh(messages);

                underline[0] = newwin(1,6,((rows-26)/2)+25,((cols-50)/2)+9);
                underline[1] = newwin(1,7,((rows-26)/2)+25,((cols-50)/2)+18);
                underline[2] = newwin(1,13,((rows-26)/2)+25,((cols-50)/2)+28);

                refresh();
            }

            // DESCHID MENIUL

            if(inv==0) c=-1;
            time_t start = time(0);
            timeout(1000);
            c=getch();
            double seconds_since_start = difftime(time(0),start);
            if(seconds_since_start>=1) inv++;
            else inv=0;
            refresh();
            if(inv==20)
            {
                inv=0;
                c=MUTARE_ELIBERATOARE(game_state);
                refresh();
                if(c==-1)
                {
                    zero_matrix(mutare);
                    while(br)
                    {
                        cbr++;
                        br = misca_te_asa_cum_imi_place_mie(win,mutare,game_state,-2,panou_inf,&score);
                        if(br==2) cas=1;
                        if(cbr==1 && br==0)
                        {
                            cbr=0;
                            c=-2;
                        }
                    }

                    if(cas==1) goto WINNERTAKESITALL;
                    if(see_state(game_state)==0) goto LOSER;
                    if(cbr)  random_populate2(game_state,win);
                    br=1;
                    cbr=0;
                    cas=0;
                    if(c==-2)
                    {
                        zero_matrix(mutare);
                        while(br)
                        {
                            cbr++;
                            br = misca_te_asa_cum_imi_place_mie(win,mutare,game_state,-1,panou_inf,&score);
                            if(br==2) cas=1;
                            if(cbr==1 && br==0)
                            {
                                cbr=0;
                                c=-3;
                            }
                        }
                        if(cas==1) goto WINNERTAKESITALL;
                        if(see_state(game_state)==0) goto LOSER;
                        if(cbr) random_populate2(game_state,win);
                        br=1;
                        cbr=0;
                        cas=0;
                    }
                    if(c==-3)
                    {
                        zero_matrix(mutare);
                        while(br)
                        {
                            cbr++;
                            br = misca_te_asa_cum_imi_place_mie(win,mutare,game_state,1,panou_inf,&score);
                            if(br==2) cas=1;
                            if(cbr==1 && br==0)
                            {
                                cbr=0;
                                c=-4;
                            }
                        }
                        if(cas==1) goto WINNERTAKESITALL;
                        if(see_state(game_state)==0) goto LOSER;
                        if(cbr) random_populate2(game_state,win);
                        br=1;
                        cbr=0;
                        cas=0;
                    }
                    if(c==-4)
                    {
                        zero_matrix(mutare);
                        while(br)
                        {
                            cbr++;
                            br = misca_te_asa_cum_imi_place_mie(win,mutare,game_state,2,panou_inf,&score);
                            if(br==2) cas=1;
                            if(cbr==1 && br==0) cbr=0;
                        }
                        if(cas==1) goto WINNERTAKESITALL;
                        if(see_state(game_state)==0) goto LOSER;
                        if(cbr) random_populate2(game_state,win);
                        br=1;
                        cbr=0;
                        cas=0;
                    }
                }
                goto PRINCIPAL;
            }
            if(c=='m')
            {
                wattron(underline[0],COLOR_PAIR(1));
                wprintw(underline[0],"      ");
                wattroff(underline[0],COLOR_PAIR(1));
                wrefresh(underline[0]);
                mvprintw(((rows-26)/2)+24,((cols-50)/2)+9,"Resume");
                mvprintw(((rows-26)/2)+24,((cols-50)/2)+18,"Restart");
                mvprintw(((rows-26)/2)+24,((cols-50)/2)+28,"Quit and Save");

                refresh();
                b=0;
            }
            int item_curent=0,x=0;

            // NAVIGAREA PRIN MENIU
            while(b==0)
            {
                wclear(messages);
                mvwprintw(messages,0,5,"For returning to game hit Resume button");
                wrefresh(messages);
                c=getch();
                if(c==KEY_LEFT || c==KEY_RIGHT || (c=='\n' && (copie_tasta==KEY_LEFT || copie_tasta==KEY_RIGHT || copie_tasta==0 || copie_tasta=='\n')))
                {


                    switch(c)
                    {
                    case KEY_LEFT:
                        x=item_curent;
                        if(item_curent>0) item_curent--;

                        if(item_curent==0 && x!=item_curent)
                        {
                            wattron(underline[0],COLOR_PAIR(1));
                            wprintw(underline[0],"      ");
                            wattroff(underline[0],COLOR_PAIR(1));
                            wclear(underline[item_curent+1]);
                            wrefresh(underline[0]);
                            wrefresh(underline[item_curent+1]);
                            refresh();
                        }
                        if(item_curent==1 && x==2)
                        {
                            wattron(underline[1],COLOR_PAIR(1));
                            wprintw(underline[1],"       ");
                            wattroff(underline[1],COLOR_PAIR(1));
                            wclear(underline[item_curent+1]);
                            wrefresh(underline[1]);
                            wrefresh(underline[item_curent+1]);
                            refresh();
                        }
                        break;
                    case KEY_RIGHT:
                        x=item_curent;
                        if(item_curent<2) item_curent++;
                        if(item_curent==1)
                        {
                            wattron(underline[1],COLOR_PAIR(1));
                            wprintw(underline[1],"       ");
                            wattroff(underline[1],COLOR_PAIR(1));
                            wclear(underline[item_curent-1]);
                            wrefresh(underline[1]);
                            wrefresh(underline[item_curent-1]);
                            refresh();
                        }
                        if(item_curent==2 && x!=item_curent)
                        {
                            wattron(underline[2],COLOR_PAIR(1));
                            wprintw(underline[2],"             ");
                            wattroff(underline[2],COLOR_PAIR(1));
                            wclear(underline[item_curent-1]);
                            wrefresh(underline[2]);
                            wrefresh(underline[item_curent-1]);
                            refresh();
                        }
                        break;
                    case '\n':
                        if(item_curent==2)
                        {
                            clear();
                            wclear(princwin);
                            delwin(princwin);
                            wclear(messages);
                            delwin(messages);
                            for(i=0; i<16; i++)
                            {
                                wclear(win[i]);
                                delwin(win[i]);
                            }
                            for(i=0; i<3; i++)
                            {
                                wclear(underline[i]);
                                delwin(underline[i]);
                            }
                            wclear(panou_inf);
                            delwin(panou_inf);
                            FILE *fp;
                            fp = fopen("saved_state","w");
                            for(i=0; i<4; i++)
                                for(j=0; j<4; j++)
                                    if(j!=3)
                                        fprintf(fp,"%d ",game_state[i][j]);
                                    else fprintf(fp,"%d\n",game_state[i][j]);
                            fclose(fp);
                            c=3;
                            b=1;
                        }
                        if(item_curent==1)
                        {
                            clear();
                            wclear(princwin);
                            delwin(princwin);
                            wclear(messages);
                            delwin(messages);
                            for(i=0; i<16; i++)
                            {
                                wclear(win[i]);
                                delwin(win[i]);
                            }
                            for(i=0; i<3; i++)
                            {
                                wclear(underline[i]);
                                delwin(underline[i]);
                            }
                            wclear(panou_inf);
                            delwin(panou_inf);
                            goto INCEPUT;
                        }
                        if(item_curent==0)
                        {
                            wclear(messages);
	                            mvwprintw(messages,0,15,"For menu press (m)");
                            wclear(underline[0]);
                            wclear(underline[1]);
                            wclear(underline[2]);
                            wrefresh(underline[0]);
                            wrefresh(underline[1]);
                            wrefresh(underline[2]);
                            wrefresh(messages);
                            mvprintw(((rows-26)/2)+24,((cols-50)/2)+9,"       ");
                            mvprintw(((rows-26)/2)+24,((cols-50)/2)+18,"       ");
                            mvprintw(((rows-26)/2)+24,((cols-50)/2)+28,"             ");
                            refresh();
                            b=1;
                        }
                        break;
                    }

                    copie_tasta=c;

                }
		
		// O functionalitate in plus pentru meniul din timpul jocului

                if(c=='m' || c==KEY_RESIZE)
                {

                    wclear(messages);
                    mvwprintw(messages,0,15,"For menu press (m)");
                    mvprintw(((rows-26)/2)+24,((cols-50)/2)+9,"      ");
                    mvprintw(((rows-26)/2)+24,((cols-50)/2)+18,"       ");
                    mvprintw(((rows-26)/2)+24,((cols-50)/2)+28,"             ");
                    wclear(underline[0]);
                    wclear(underline[1]);
                    wclear(underline[2]);
                    wrefresh(underline[0]);
                    wrefresh(underline[1]);
                    wrefresh(underline[2]);
                    wrefresh(messages);
                    refresh();
                    b=1;

                }

            }
            refresh();
            goto PRINCIPAL;

	// AFISAJUL IN CAZUL IN CARE SE PIERDE
LOSER:
            if(1)
            {
                WINDOW *winner[2];
                winner[0] = newwin(1,8,((rows-26)/2)+25,((cols-50)/2)+17);
                winner[1] = newwin(1,4,((rows-26)/2)+25,((cols-50)/2)+27);
                mvprintw(((rows-26)/2)+24,((cols-50)/2)+17,"New Game");
                mvprintw(((rows-26)/2)+24,((cols-50)/2)+27,"Quit");

                wclear(messages);
                mvwprintw(messages,0,15,"GAME OVER! SORRY! :-(");
                wrefresh(messages);

                wattron(winner[0],COLOR_PAIR(14));
                wprintw(winner[0],"        ");
                wattroff(winner[0],COLOR_PAIR(14));

                wrefresh(winner[0]);

                int ch=0,item_cur=1;
                while(ch!=3)
                {

                    ch = getch();

                    if(ch==KEY_RESIZE)
                    {
                        int i;
                        for(i=0; i<2; i++) delwin(winner[i]);
                        mvprintw(((rows-26)/2)+24,((cols-50)/2)+17,"        ");
                        mvprintw(((rows-26)/2)+24,((cols-50)/2)+27,"    ");
                        clear();
                        wclear(princwin);
                        delwin(princwin);
                        wclear(messages);
                        delwin(messages);
                        for(i=0; i<16; i++)
                        {
                            wclear(win[i]);
                            delwin(win[i]);
                        }
                        for(i=0; i<3; i++)
                        {
                            wclear(underline[i]);
                            delwin(underline[i]);
                        }
                        wclear(panou_inf);
                        delwin(panou_inf);


                        //--------------------
                        int contor=0,rows,cols,j,p2,p1;
                        //-------------------

                        getmaxyx(stdscr,rows,cols);

                        p1=1;
                        refresh();


                        princwin = newwin(26,50,((rows-26)/2)-5,(cols-50)/2);
                        panou_inf = newwin(26,20,((rows-26)/2)-5,((cols-50)/2)-25);
                        box(panou_inf,0,0);
                        wbkgd(princwin,COLOR_PAIR(16));
                        wrefresh(princwin);
                        mvwprintw(panou_inf,2,2,"Scor: %d",score);
                        time(&clk);
                        cur_time = localtime(&clk);
                        mvwprintw(panou_inf,3,2,"Data: %d-%d-%d",cur_time->tm_mday,1+cur_time->tm_mon,1900+cur_time->tm_year);
                        mvwprintw(panou_inf,4,2,"Ora: %d:%d:%d",cur_time->tm_hour,cur_time->tm_min,cur_time->tm_sec);
                        mvwprintw(panou_inf,6,2,"*USE ARROW KEYS  ");
                        mvwprintw(panou_inf,7,2,"FOR MOVING CELLS.");
                        mvwprintw(panou_inf,9,2,"*THE GAME WILL S-");
                        mvwprintw(panou_inf,10,2,"-TOP WHEN YOU RE-");
                        mvwprintw(panou_inf,11,2,"-ACH 2048.	  ");
                        mvwprintw(panou_inf,13,2,"*YOU COULD SAVE  ");
                        mvwprintw(panou_inf,14,2,"YOUR PROGRESS PR-");
                        mvwprintw(panou_inf,15,2,"-ESSING (m) AND  ");
                        mvwprintw(panou_inf,16,2,"CHOOSING QUIT AND");
                        mvwprintw(panou_inf,17,2,"SAVE.");
                        mvwprintw(panou_inf,19,2,"*AT EVERY 20 SEC ");
                        mvwprintw(panou_inf,20,2,"THE GAME WILL CH-");
                        mvwprintw(panou_inf,21,2,"OOSE A DIRECTION ");
                        mvwprintw(panou_inf,22,2,"THAT FREES THE M-");
                        mvwprintw(panou_inf,23,2,"AXIMUM NUMBER");
                        mvwprintw(panou_inf,24,2,"OF CELLS.");
                        wrefresh(panou_inf);

                        for(i=0; i<16; i+=4,contor++)
                        {
                            p2=2;
                            for(j=0; j<4; j++)
                            {

                                win[i+j]=newwin(5,10,((rows-26)/2)-5+p1,((cols-50)/2)+p2);
                                wbkgd(win[i+j],COLOR_PAIR(2));
                                if(game_state[contor][j])
                                    afiseaza(win,game_state,contor,j,-1);
                                p2=p2+12;
                                wrefresh(win[i+j]);
                            }
                            p1=p1+6;
                        }

                        underline[0] = newwin(1,6,((rows-26)/2)+25,((cols-50)/2)+9);
                        underline[1] = newwin(1,7,((rows-26)/2)+25,((cols-50)/2)+18);
                        underline[2] = newwin(1,13,((rows-26)/2)+25,((cols-50)/2)+28);
                        messages = newwin(1,50,((rows-26)/2)+22,((cols-50)/2));
                        winner[0] = newwin(1,8,((rows-26)/2)+25,((cols-50)/2)+17);
                        winner[1] = newwin(1,4,((rows-26)/2)+25,((cols-50)/2)+27);
                        mvprintw(((rows-26)/2)+24,((cols-50)/2)+17,"New Game");
                        mvprintw(((rows-26)/2)+24,((cols-50)/2)+27,"Quit");
                        wclear(messages);
                        mvwprintw(messages,0,15,"GAME OVER! SORRY! :-(");
                        wrefresh(messages);

                        wattron(winner[item_cur-1],COLOR_PAIR(14));
                        wprintw(winner[item_cur-1],"             ");
                        wattroff(winner[item_cur-1],COLOR_PAIR(14));
                        wrefresh(winner[item_cur-1]);

                        wrefresh(messages);



                        refresh();
                    }

                    if(ch==KEY_LEFT && item_cur==2)
                    {
                        wclear(winner[1]);
                        item_cur--;
                        wattron(winner[0],COLOR_PAIR(14));
                        wprintw(winner[0],"        ");
                        wattroff(winner[0],COLOR_PAIR(14));
                        wrefresh(winner[1]);
                        wrefresh(winner[0]);
                    }
                    if(ch==KEY_RIGHT && item_cur==1)
                    {
                        wclear(winner[0]);
                        item_cur++;
                        wattron(winner[1],COLOR_PAIR(14));
                        wprintw(winner[1],"            ");
                        wattroff(winner[1],COLOR_PAIR(14));
                        wrefresh(winner[1]);
                        wrefresh(winner[0]);
                        ch=0;
                    }

                    if(ch==KEY_RIGHT && item_cur==2)
                    {
                        wclear(winner[1]);
                        item_cur++;
                        wattron(winner[2],COLOR_PAIR(14));
                        wprintw(winner[2],"    ");
                        wattroff(winner[2],COLOR_PAIR(14));
                        wrefresh(winner[1]);
                        wrefresh(winner[2]);

                    }
                    if(ch=='\n' && item_cur==2)
                    {

                        int i;
                        for(i=0; i<2; i++) delwin(winner[i]);
                        mvprintw(((rows-26)/2)+24,((cols-50)/2)+17,"        ");
                        mvprintw(((rows-26)/2)+24,((cols-50)/2)+27,"    ");
                        clear();
                        wclear(princwin);
                        delwin(princwin);
                        wclear(messages);
                        delwin(messages);
                        for(i=0; i<16; i++)
                        {
                            wclear(win[i]);
                            delwin(win[i]);
                        }
                        for(i=0; i<3; i++)
                        {
                            wclear(underline[i]);
                            delwin(underline[i]);
                        }
                        wclear(panou_inf);
                        delwin(panou_inf);
                        return 1;

                    }
                    if(ch=='\n' && item_cur==1)
                    {
                        int i;
                        for(i=0; i<2; i++) delwin(winner[i]);
                        mvprintw(((rows-26)/2)+24,((cols-50)/2)+17,"        ");
                        mvprintw(((rows-26)/2)+24,((cols-50)/2)+27,"    ");
                        clear();
                        wclear(princwin);
                        delwin(princwin);
                        wclear(messages);
                        delwin(messages);
                        for(i=0; i<16; i++)
                        {
                            wclear(win[i]);
                            delwin(win[i]);
                        }
                        for(i=0; i<3; i++)
                        {
                            wclear(underline[i]);
                            delwin(underline[i]);
                        }
                        wclear(panou_inf);
                        delwin(panou_inf);
                        goto INCEPUT;
                    }

                }
            }

	// AFISASUL IN CAZUL IN CARE SE CASTIGA

WINNERTAKESITALL:
            if(1)
            {
                WINDOW *winner[2];
                winner[0] = newwin(1,8,((rows-26)/2)+25,((cols-50)/2)+17);
                winner[1] = newwin(1,4,((rows-26)/2)+25,((cols-50)/2)+27);
                mvprintw(((rows-26)/2)+24,((cols-50)/2)+17,"New Game");
                mvprintw(((rows-26)/2)+24,((cols-50)/2)+27,"Quit");

                wclear(messages);
                mvwprintw(messages,0,14,"CONGRATS! YOU WIN! :-)");
                wrefresh(messages);

                wattron(winner[0],COLOR_PAIR(14));
                wprintw(winner[0],"        ");
                wattroff(winner[0],COLOR_PAIR(14));

                wrefresh(winner[0]);

                int ch=0,item_cur=1;
                while(ch!=3)
                {

                    ch = getch();

                    if(ch==KEY_RESIZE)
                    {
                        int i;
                        for(i=0; i<2; i++) delwin(winner[i]);
                        mvprintw(((rows-26)/2)+24,((cols-50)/2)+17,"        ");
                        mvprintw(((rows-26)/2)+24,((cols-50)/2)+27,"    ");
                        clear();
                        wclear(princwin);
                        delwin(princwin);
                        wclear(messages);
                        delwin(messages);
                        for(i=0; i<16; i++)
                        {
                            wclear(win[i]);
                            delwin(win[i]);
                        }
                        for(i=0; i<3; i++)
                        {
                            wclear(underline[i]);
                            delwin(underline[i]);
                        }
                        wclear(panou_inf);
                        delwin(panou_inf);


                        //--------------------
                        int contor=0,rows,cols,j,p2,p1;
                        //-------------------

                        getmaxyx(stdscr,rows,cols);

                        p1=1;
                        refresh();


                        princwin = newwin(26,50,((rows-26)/2)-5,(cols-50)/2);
                        panou_inf = newwin(20,20,((rows-26)/2)-5,((cols-50)/2)-25);
                        box(panou_inf,0,0);
                        wbkgd(princwin,COLOR_PAIR(16));
                        wrefresh(princwin);
                        mvwprintw(panou_inf,2,2,"Scor: %d",score);
                        time(&clk);
                        cur_time = localtime(&clk);
                        mvwprintw(panou_inf,3,2,"Data: %d-%d-%d",cur_time->tm_mday,1+cur_time->tm_mon,1900+cur_time->tm_year);
                        mvwprintw(panou_inf,4,2,"Ora: %d:%d:%d",cur_time->tm_hour,cur_time->tm_min,cur_time->tm_sec);
                        mvwprintw(panou_inf,6,2,"*USE ARROW KEYS  ");
                        mvwprintw(panou_inf,7,2,"FOR MOVING CELLS.");
                        mvwprintw(panou_inf,9,2,"*THE GAME WILL S-");
                        mvwprintw(panou_inf,10,2,"-TOP WHEN YOU RE-");
                        mvwprintw(panou_inf,11,2,"-ACH 2048.	  ");
                        mvwprintw(panou_inf,13,2,"*YOU COULD SAVE  ");
                        mvwprintw(panou_inf,14,2,"YOUR PROGRESS PR-");
                        mvwprintw(panou_inf,15,2,"-ESSING (m) AND  ");
                        mvwprintw(panou_inf,16,2,"CHOOSING QUIT AND");
                        mvwprintw(panou_inf,17,2,"SAVE.");
                        mvwprintw(panou_inf,19,2,"*AT EVERY 20 SEC ");
                        mvwprintw(panou_inf,20,2,"THE GAME WILL CH-");
                        mvwprintw(panou_inf,21,2,"OOSE A DIRECTION ");
                        mvwprintw(panou_inf,22,2,"THAT FREES THE M-");
                        mvwprintw(panou_inf,23,2,"AXIMUM NUMBER");
                        mvwprintw(panou_inf,24,2,"OF CELLS.");

                        wrefresh(panou_inf);

                        for(i=0; i<16; i+=4,contor++)
                        {
                            p2=2;
                            for(j=0; j<4; j++)
                            {

                                win[i+j]=newwin(5,10,((rows-26)/2)-5+p1,((cols-50)/2)+p2);
                                wbkgd(win[i+j],COLOR_PAIR(2));
                                if(game_state[contor][j])
                                    afiseaza(win,game_state,contor,j,-1);
                                p2=p2+12;
                                wrefresh(win[i+j]);
                            }
                            p1=p1+6;
                        }

                        underline[0] = newwin(1,6,((rows-26)/2)+25,((cols-50)/2)+9);
                        underline[1] = newwin(1,7,((rows-26)/2)+25,((cols-50)/2)+18);
                        underline[2] = newwin(1,13,((rows-26)/2)+25,((cols-50)/2)+28);
                        messages = newwin(1,50,((rows-26)/2)+22,((cols-50)/2));
                        winner[0] = newwin(1,8,((rows-26)/2)+25,((cols-50)/2)+17);
                        winner[1] = newwin(1,4,((rows-26)/2)+25,((cols-50)/2)+27);
                        mvprintw(((rows-26)/2)+24,((cols-50)/2)+17,"New Game");
                        mvprintw(((rows-26)/2)+24,((cols-50)/2)+27,"Quit");
                        wclear(messages);
                        mvwprintw(messages,0,14,"CONGRATS! YOU WIN! :-)");
                        wrefresh(messages);

                        wattron(winner[item_cur-1],COLOR_PAIR(14));
                        wprintw(winner[item_cur-1],"             ");
                        wattroff(winner[item_cur-1],COLOR_PAIR(14));
                        wrefresh(winner[item_cur-1]);

                        wrefresh(messages);



                        refresh();

                    }

                    if(ch==KEY_LEFT && item_cur==2)
                    {
                        wclear(winner[1]);
                        item_cur--;
                        wattron(winner[0],COLOR_PAIR(14));
                        wprintw(winner[0],"        ");
                        wattroff(winner[0],COLOR_PAIR(14));
                        wrefresh(winner[1]);
                        wrefresh(winner[0]);
                    }
                    if(ch==KEY_RIGHT && item_cur==1)
                    {
                        wclear(winner[0]);
                        item_cur++;
                        wattron(winner[1],COLOR_PAIR(14));
                        wprintw(winner[1],"            ");
                        wattroff(winner[1],COLOR_PAIR(14));
                        wrefresh(winner[1]);
                        wrefresh(winner[0]);
                        ch=0;
                    }
                    if(ch=='\n' && item_cur==2)
                    {

                        int i;
                        for(i=0; i<2; i++) delwin(winner[i]);
                        mvprintw(((rows-26)/2)+24,((cols-50)/2)+14,"        ");
                        mvprintw(((rows-26)/2)+24,((cols-50)/2)+24,"    ");
                        clear();
                        wclear(princwin);
                        delwin(princwin);
                        wclear(messages);
                        delwin(messages);
                        for(i=0; i<16; i++)
                        {
                            wclear(win[i]);
                            delwin(win[i]);
                        }
                        for(i=0; i<3; i++)
                        {
                            wclear(underline[i]);
                            delwin(underline[i]);
                        }
                        wclear(panou_inf);
                        delwin(panou_inf);
                        return 1;

                    }
                    if(ch=='\n' && item_cur==1)
                    {
                        int i;
                        for(i=0; i<2; i++) delwin(winner[i]);
                        mvprintw(((rows-26)/2)+24,((cols-50)/2)+14,"        ");
                        mvprintw(((rows-26)/2)+24,((cols-50)/2)+24,"    ");
                        clear();
                        wclear(princwin);
                        delwin(princwin);
                        wclear(messages);
                        delwin(messages);
                        for(i=0; i<16; i++)
                        {
                            wclear(win[i]);
                            delwin(win[i]);
                        }
                        for(i=0; i<3; i++)
                        {
                            wclear(underline[i]);
                            delwin(underline[i]);
                            wclear(winner[i]);
                            delwin(winner[i]);
                        }
                        wclear(panou_inf);
                        delwin(panou_inf);
                        goto INCEPUT;
                    }

                }
            }
        }
    }

    return 1;


}



// END END END END END
// -----------------------------------------------------------


int main()
{

	// CATEVA COMENZI TRIMISE IN PREALABIL
    system("resize -s 40 120 > /dev/null");
    system("touch saved_state");
    system("touch prior");

    int i,j;
    initscr();


	// INITIALIZAREA CULORILOR PE CARE LE VOI FOLOSI CAND VOI CREA INSTANTA DE JOC
    start_color();
    use_default_colors();

    init_pair(1,COLOR_BLACK,COLOR_GREEN);
    init_color(COLOR_DEF,700,750,710);
    init_pair(2,COLOR_BLACK,COLOR_DEF);
    init_color(COLOR_4,910,560,350);
    init_pair(3,COLOR_BLACK,COLOR_4);
    init_color(COLOR_8,930,570,130);
    init_pair(4,COLOR_BLACK,COLOR_8);
    init_color(COLOR_16,980,930,360);
    init_pair(5,COLOR_BLACK,COLOR_16);
    init_color(COLOR_32,980,910,710);
    init_pair(6,COLOR_BLACK,COLOR_32);
    init_color(COLOR_64,880,940,750);
    init_pair(7,COLOR_BLACK,COLOR_64);
    init_color(COLOR_128,0,420,310);
    init_pair(8,COLOR_BLACK,COLOR_128);
    init_color(COLOR_256,710,650,260);
    init_pair(9,COLOR_BLACK,COLOR_256);
    init_color(COLOR_512,750,580,890);
    init_pair(10,COLOR_BLACK,COLOR_512);
    init_color(COLOR_1024,800,400,600);
    init_pair(11,COLOR_BLACK,COLOR_1024);
    init_color(COLOR_2048,1000,650,790);
    init_pair(12,COLOR_BLACK,COLOR_2048);
    init_color(COLOR_2,570,600,590);
    init_pair(13,COLOR_BLACK,COLOR_2);
    init_color(COLOR_WIN,1000,440,370);
    init_pair(14,COLOR_BLACK,COLOR_WIN);
    init_color(COLOR_PAC,240,170,120);
    init_pair(16,COLOR_BLACK,COLOR_PAC);
    init_color(COLOR_BACKGROUND,150,210,160);
    init_pair(17,COLOR_RED,COLOR_BACKGROUND);

    refresh();

    noecho();

    curs_set(0);


	// CREAREA MENIULUI JOCULUI
    char *choices[] =
    {
        "New Game",
        "Resume Game",
        "Exit",
    };

    ITEM **my_items;

    MENU *my_menu;

    WINDOW *my_menu_win;

    int n_choices,prior=0;

    ITEM *cur_item;

    cbreak();

    keypad(stdscr, TRUE);

    n_choices = ARRAY_SIZE(choices);

    printw("%d",n_choices);
    refresh();

    my_items = (ITEM **)calloc(n_choices + 1, sizeof(ITEM *));

    for(i = 0; i < n_choices; ++i)
        my_items[i] = new_item(choices[i],"");

    my_items[n_choices] = (ITEM *)NULL;

    my_menu = new_menu((ITEM **)my_items);


    FILE *fp;
    fp = fopen("title.txt","r");

    int new_rows,new_cols,rows=0,cols=0,lines=0,copie_tasta=0,item_curent=1;

    getmaxyx(stdscr,new_rows,new_cols);

    if(new_rows!=rows && new_cols!=cols)
    {
        rows=new_rows;
        cols=new_cols;
        wresize(stdscr,rows,cols);
        wclear(stdscr);
        refresh();
    }

    char aux[1000];

	// CITESC DIN FISIERUL title.txt ACEL 2048 ASCII ART
    while(fgets(aux,999,fp)!=NULL)
    {
        lines++;

        mvprintw(lines+(rows/6),(cols-strlen(aux))/2,"%s",aux);

        refresh();
    }

    fclose(fp);


    int width_menu_win=strlen(choices[1])+10,height_menu_win=10;

    my_menu_win = newwin(height_menu_win,width_menu_win,lines+3+(rows/6),(cols-width_menu_win+5)/2);

    keypad(my_menu_win,TRUE);

    set_menu_win(my_menu,my_menu_win);
	 
    set_menu_sub(my_menu, derwin(my_menu_win, 5,15,1,1));
	
    refresh();

    set_menu_mark(my_menu, "*");

    post_menu(my_menu);

    wrefresh(my_menu_win);

    int c=0,b=1,t=0;


    while(c!=3)
    {

        FILE *wp;
        wp=fopen("prior","r");
        fscanf(wp,"%d",&prior);
        fclose(wp);
		
		// DE SE VA REDIMENSIONA INTRA IN ACEST WHILE
        while((c == KEY_RESIZE && b==1) || t==1) // t-ul are a face cu iesirea din instanta de joc, care va returna 1;
        {
            int new_rows,new_cols,lines=0;

            getmaxyx(stdscr,new_rows,new_cols);

            if(t!=1)
            {
                wclear(my_menu_win);

                delwin(my_menu_win);

                unpost_menu(my_menu);

                free_menu(my_menu);

                for(i=0; i<=n_choices; i++)
                    free_item(my_items[i]);

            }
            my_items = (ITEM **)calloc(n_choices + 1, sizeof(ITEM *));

            for(i = 0; i < n_choices; ++i)
                my_items[i] = new_item(choices[i],"");

            my_items[n_choices] = (ITEM *)NULL;

            my_menu = new_menu((ITEM **)my_items);

            FILE *fp;
            fp = fopen("title.txt","r");

            if(new_rows!=rows ||  new_cols!=cols)
            {
                rows=new_rows;
                cols=new_cols;
                wresize(stdscr,rows,cols);
                wclear(stdscr);
                refresh();
            }

            char aux[1000];

            while(fgets(aux,999,fp)!=NULL)
            {
                lines++;

                mvprintw(lines+(rows/6),(cols-strlen(aux))/2,"%s",aux);

                refresh();
            }

            fclose(fp);

            int width_menu_win=strlen(choices[1])+10,height_menu_win=10;

            my_menu_win = newwin(height_menu_win,width_menu_win,lines+3+(rows/6),(cols-width_menu_win+5)/2);

            keypad(my_menu_win,TRUE);

            set_menu_win(my_menu,my_menu_win);

            set_menu_sub(my_menu, derwin(my_menu_win, 5,15,1,1));

            refresh();

            set_menu_mark(my_menu, "*");

            post_menu(my_menu);

            wrefresh(my_menu_win);
            if(t==1) t=0;
            else c=getch();
        }
	
		// NAVIGAREA PRIN MENIU

        while(c==KEY_UP || c==KEY_DOWN ||  (c=='\n' && (copie_tasta==KEY_UP || copie_tasta==KEY_DOWN || copie_tasta==0 || copie_tasta=='\n')))
        {
            switch(c)
            {
            case KEY_DOWN:
                menu_driver(my_menu, REQ_DOWN_ITEM);
                if(item_curent<3) item_curent++;
                break;
            case KEY_UP:
                menu_driver(my_menu, REQ_UP_ITEM);
                if(item_curent>1) item_curent--;
                break;
            case '\n':
                if(item_curent==1)
                {
			// acest prior are a face cu butonul "Resume Game", care este functionabil abia dupa prima intrare in "New Game"
                    FILE *fp;
                    fp = fopen("prior","w");
                    fprintf(fp,"1");
                    fclose(fp);

                    wclear(stdscr);
                    wclear(my_menu_win);
                    delwin(my_menu_win);
                    unpost_menu(my_menu);
                    free_menu(my_menu);
                    for(i=0; i < n_choices; ++i)
                        free_item(my_items[i]);
                    move(0,0);
                    refresh();
                    t=create_game_instance(0);
                    b=0;
                    break;
                }
                if(item_curent==2 && prior==1)
                {
                    wclear(stdscr);
                    wclear(my_menu_win);
                    delwin(my_menu_win);
                    unpost_menu(my_menu);
                    free_menu(my_menu);
                    for(i=0; i < n_choices; ++i)
                        free_item(my_items[i]);
                    move(0,0);
                    refresh();
                    t=create_game_instance(1);
                    item_curent=1;
                    b=0;
                    break;
                }
                if(item_curent==3)
                {

                    wclear(stdscr);
                    wclear(my_menu_win);
                    delwin(my_menu_win);
                    unpost_menu(my_menu);
                    free_menu(my_menu);
                    for(i=0; i < n_choices; ++i)
                        free_item(my_items[i]);
                    refresh();
                    wrefresh(my_menu_win);
                    endwin();
                    exit(1);
                    break;
                }

            }

            if(t==0) wrefresh(my_menu_win); // daca t este 0 abia atunci sa reinprospateze fereastra meniului, caci 
					    // nu s-a iesit din instanta de joc, deci nu trebuie restartat meniul, 
					    // facand highlight pe prima optiune , adica "New Game"
            copie_tasta=c;
            if(t==1) c='d'; // o atribuire care nu afecteaza cu nimic rularea programului;
            else  c=getch();
        }

        if(t==0) c=getch(); // sa nu se citeasca daca abia s-a iesit dintr-o instanta de joc (implicit inseamna ca t sa fie 1)
    }

    endwin();

    return 0;

}

