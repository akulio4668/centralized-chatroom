#include <curses.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    long iter;
    int yi, xi;
    int y[3], x[3];
    int index;
    int maxlines, maxcols;

    initscr();
    cbreak();
    noecho();
    
    clear();

    maxlines = LINES - 1;
    maxcols = COLS - 1;

    y[0] = 0;
    x[0] = 0;

    y[1] = maxlines;
    x[1] = maxcols / 2;

    y[2] = 0;
    x[2] = maxcols;

    mvaddch(y[0], x[0], '0');
    mvaddch(y[1], x[1], '1');
    mvaddch(y[2], x[2], '2');

    yi = maxlines / 2;
    xi = maxcols / 2;

    mvaddch(yi, xi, '.');

    mvaddstr(maxlines, 0, "Press any key to quit");

    refresh();

    getch();
    endwin();

    exit(0);
}