#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include "streak.h"
#include "util.h"

#define MAXSTREAKS  128
#define FRAME       20000
#define GREEN       1

WINDOW *w;
int maxX;
int maxY;

streak* streaks[MAXSTREAKS];

void init() {
    randomize();
    w = initscr();
    cbreak();
    nodelay(w, TRUE);
    noecho();
    curs_set(FALSE);
    getmaxyx(w, maxY, maxX);
    if (has_colors() == TRUE)
        start_color();
    use_default_colors();
    init_pair(GREEN, COLOR_GREEN, -1);
    attron(COLOR_PAIR(GREEN));
    streaks_init(maxY, maxX);
}

int main(int argc, char *argv[]) {
    init();
    
    while (getch() == ERR) {
        draw_streaks(streaks, maxY);
        if (rand_int(0, 10) < 5)
            add_new_random_streak(streaks, maxX);
        refresh();
        usleep(FRAME);
    }

    attroff(COLOR_PAIR(GREEN));
    endwin();
    return 0;
}
