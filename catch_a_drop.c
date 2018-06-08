#include <pthread.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
int key = 0;
int sx = 27;
int sy = 18;
int ky;
int kx = 56;
static void *stakandvig(void *none)
{
	while(key != 'q') {
		key = getch();
		switch(key) {
			case KEY_LEFT:
				if(sx>2) sx=sx-2;
				break;
			case KEY_RIGHT:
				if (sx<53) sx=sx+2;
				break;
			default:
				break;
		}
	}
	return NULL;
}
void ramka(int n)
{
	for(n=0;n<60;n++)
	{
		mvprintw(5,COLS/2-30+n,"@");
		mvprintw(20,COLS/2-30+n,"@");
	}
	for(n=5;n<21;n++)
	{
		mvprintw(n,COLS/2+29,"@");
		mvprintw(n,COLS/2-30,"@");
	}
	for (n=5;n<8;n++) mvprintw(n,COLS/2-38,"@");
	for (n=0;n<8;n++)
	{
		mvprintw(5,COLS/2-38+n,"@");
		mvprintw(7,COLS/2-38+n,"@");
	}
}
int main()
{
	int i=0;
	int n;
	if ( NULL == ( initscr()) ) {
		fprintf(stderr,"Ncurses' launch has error\n");
		return -1;
	}
	raw();
	noecho();
	keypad(stdscr, TRUE);
	curs_set(0);
	pthread_t stak;
	pthread_create(&stak, NULL, stakandvig, NULL);
	while(key != 'q') {
		srand(time(NULL));
		kx= rand()% 56 + 2 ;
		for(ky=6;ky<18;ky++)
		{
			refresh();
			clear();
			ramka(n);
			mvprintw(6,COLS/2-34,"%d",i);
			mvaddstr(ky,COLS/2-30+kx,"##");
			mvaddstr(sy,COLS/2-30+sx,"|    |");
			mvaddstr(sy+1,COLS/2-30+sx,"======");
			napms(125);
			if (key=='q') break;
		}
		if((kx>sx)&&((kx+1)<(sx+5))) i+=10;
		else i-=10;
		if(i<(-49)) break;
	}
	pthread_cancel(stak);
	clear();
	if (i>(-41)) mvprintw(LINES/2,COLS/2-5,"POINTS: %d",(i+10));
	else mvprintw(LINES/2,COLS/2-5,"GAME OVER!");
	refresh();
	napms(1000);
	endwin();
	return 0;
}
