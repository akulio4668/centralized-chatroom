#include <curses.h>
#include <stdlib.h>
#include <string.h>

#define ITERMAX 10000

WINDOW *full_win;

int main(int argc, char **argv) {
    // long iter;
    // int maxlines, maxcols;

    // char buff[1000];
    // int buffpos = 0;

    // char *chathist[1000];
    // int histpos = 0;

    initscr();
    cbreak();
    noecho();
    
    clear();

    full_win = newwin(5, 5, 100, 100);

    // maxlines = LINES - 1;
    // maxcols = COLS - 1;

    // while (1) {
    //     for (iter = 0; iter <= maxcols; iter++) {
    //         mvaddch(maxlines - 1, iter, '=');
    //     }

    //     move(maxlines, maxcols);

    //     char c = getch();
    //     if (c == 127) {
    //         if (buffpos > 0)
    //             buff[--buffpos] = 0;
    //     } else if (c == '\n') {
    //         if (buff[0] != 0) {
    //             buff[buffpos] = 0;
    //             chathist[histpos++] = strdup(buff);
    //             for (int i = 0; i < 1000; ++i) {
    //                 buff[i] = 0;
    //             }
    //             buffpos = 0;
    //         }
    //     } else {
    //         buff[buffpos++] = c;
    //     }

    //     clear();

    //     for (int i = histpos - 1; i >= 0; i--) {
    //         mvaddstr(maxlines - 1 - histpos + i, maxcols - strlen(chathist[i]) + 1, chathist[i]);
    //     }

    //     if ((maxcols - buffpos + 1) >= 0) {
    //         mvaddstr(maxlines, maxcols - buffpos + 1, buff);
    //     } else {
    //         mvaddstr(maxlines, 0, buff - (maxcols - buffpos + 1));
    //     }
    // }

    refresh();

    wrefresh(full_win);
    wgetch(full_win);

    getch();
    delwin(full_win);

    endwin();

    exit(0);
}