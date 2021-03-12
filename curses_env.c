#include <curses.h>
#include <stdlib.h>

#define ITERMAX 10000

int main(int argc, char **argv) {
    long iter;
    int maxlines, maxcols;

    char buff[1000];
    int pos = 0;

    initscr();
    cbreak();
    noecho();
    
    clear();

    maxlines = LINES - 1;
    maxcols = COLS - 1;

    while (1) {
        for (iter = 0; iter <= maxcols; iter++) {
            mvaddch(maxlines - 1, iter, '=');
        }

        move(maxlines, maxcols);

        char c = getch();
        if (c == 127) {
            if (pos > 0)
                buff[--pos] = 0;
        } else {
            buff[pos++] = c;
        }

        clear();

        mvaddstr(maxlines, maxcols - pos + 1, buff);

        
    }

    refresh();

    getch();
    endwin();

    exit(0);
}