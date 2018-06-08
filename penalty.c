#include <pthread.h>
#include <ncurses.h>
#include <stdio.h>
#include <ctype.h>

int key = 0; //enter variable
int stop = 0; //variable to stop
int a = 18; //coordinate of a ball like X
int b = 21; // coordinate of a ball like Y
int o = 0; //variable for moving ball up
int x = 2; //x-coordinate of moving keeper
int y = 4; //y-coordinate of moving keeper
int optscreen();
int fullpicture(int,int);
int lasttitle();

static void *Ballmove(void *none) {
	while(stop == 0) {
		key = tolower(getch());
		switch(key) {
			case KEY_UP:
				for(o;o<19;o++) {
					b--;
					napms(80);
				}
				stop = 1;
				break;
			case KEY_LEFT:
				if(a>2) a -= 2;
				break;
			case KEY_RIGHT:
				if (a<34) a += 2;
				break;
			case 'q':
				stop = 2;
			default:
			break;
		}
	}
	return NULL;
}

int main() {
	int n; //number of keeper movings left and right
	int i; //use to draw
	if ( NULL == ( initscr()) ) {
		fprintf(stderr,"Ncurses' launch has error\n");
		return -1;
	}
	if ((COLS < 60 || LINES < 30)) {
		endwin();
		fprintf(stderr,"Screen not normal \n");
		return -1;
	}
	optscreen();
	pthread_t ball; //thread descriptor
	pthread_create(&ball, NULL, Ballmove, NULL); //thread creation
	while(stop == 0) fullpicture(i,n);
	pthread_cancel(ball); //synchronize thread to main
	lasttitle(); //func of last title(win,lose,quit)
	endwin(); //close ncurses
	return 0;
}

int drawwalls(int i) {
	for (i=0;i<38;i++) {
		mvaddch(1,((COLS/2)-19+i),'*');
		mvaddch(2,((COLS/2)-19+i),'*');
	}
	for (i=3;i<5;i++) {
		mvprintw(i,(COLS/2-19),"**");
		mvprintw(i,(COLS/2+17),"**");
	}
}
int drawballkeeper() {
	mvaddstr(b,(COLS/2-19+a),"00");
	mvaddstr(b+1,(COLS/2-19+a),"OO");
	mvaddstr(y,(COLS/2-19+x),"HHHHHHHHHHHH");
	mvaddstr(y+1,(COLS/2-19+x),"HHHHHHHHHHHH");
}
int fullpicture(int i,int n) {
	for(n=0;n<22;n++) {
		refresh();
		clear();
		drawwalls(i);
		drawballkeeper();
		napms(100);
		if (stop==0) x++;
		else break;
	}
	for(n=0;n<23;n++) {
		refresh();
		clear();
		drawwalls(i);
		drawballkeeper();
	napms(100);
	if (stop==0) x--;
		else break;
	}
	x++;
}
int optscreen() {
	raw(); //full control of keypad(ctr+c does't break)
	noecho(); //input symbols are not seen
	keypad(stdscr, TRUE); //connect buttons Key_up and others
	curs_set(0); //delete cursor
	start_color(); //start to use colors
	init_pair(1,COLOR_YELLOW,COLOR_BLACK); //make colors for foreground and background
	attron(COLOR_PAIR(1)); //on colors
}
int lasttitle() {
	clear();
	if (stop == 1) {
		if (( (a+1) >= x) & ( a <= (x+11) )) {
			mvaddstr(LINES/2,COLS/2-5,"You LOST !");
			refresh();
		}
		else {
			mvaddstr(LINES/2,COLS/2-9,"You scored a GOAL!");
			refresh();
		}
	}
	else {
		mvaddstr(LINES/2,COLS/2-12,"You got out of the game.");
		refresh();
	}
	napms(1000);
}
