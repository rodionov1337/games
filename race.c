#include <stdio.h>
#include <ncurses.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>

int key = 0; //переменная ввода
int x = 4; // координата моей машины
int y = 19;

int words(int s) //фунцкия для вывода текста на экран
{
	clear();
	if (key == 'q') mvprintw(LINES/2,COLS/2-2,"Quit! Your record: %d",s);
	else mvprintw(LINES/2,COLS/2-7,"You are loser! Your record: %d",s);
	refresh();
	napms(2000);
}

int graphic (int y1, int x1, int n, int s, int zhizni)
   {

	for(y1=1;y1<19;y1++)
                {
                        refresh();
                        clear();
			mvprintw(8,10,"Your record: %d",s);
			mvprintw(10,10,"Your lives : %d",zhizni);
                        mvaddstr(0,COLS/2-11,"XXXXXXXXXXXXXXXXXXXXXX");
                        for (n=1;n<20;n++)
                        {
                                mvaddstr(n,COLS/2-11,"XX");
                                mvaddstr(n,COLS/2+9,"XX");
                                mvaddstr(n,COLS/2-1,"||");
                        }
                        mvaddstr(y1,COLS/2+x1-11,"-WW-");
                        mvaddstr(y,COLS/2+x-11,"-MM-");
                        napms(50);
                        if (key == 'q') break;//выход из игры в любое время
                }
}
static void *mycar (void *none) // функция управления
{
	while (key!='q')
	{
		key = getch();
		switch(key)
		{
			case KEY_LEFT:
				x=4;
				break;
			case KEY_RIGHT:
				x=14;
				break;
			default:
				break;
		}
	}
	return NULL;
}
int main()
{
	int x1=4;
	int y1=1;// координата встречной машины
	int n;
	int s=0;
	int live=1;
	int check=0;
	if ( NULL == ( initscr()) )
	{
		fprintf(stderr,"Ncurses init error\n");
		return -1;
	}
	raw();
	noecho();
	curs_set(0);
	keypad(stdscr,TRUE);
	pthread_t move;
	pthread_create(&move, NULL, mycar, NULL);
	while (key!='q')
	{
		srand(time(NULL));
		x1 = rand()%2 ? 4 : 14;
		graphic(y1,x1,n,s,live);
		if(x==x1) live--;
		else
		{
			s++;
			check++;
		}
		if(check==10)
		{
		live++;
		check=0;
		}
		if(live<1) break;
	}
//	pthread_cancel(move);
	words(s);
	endwin();
	return 0;
}
