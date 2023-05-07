#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "streak.h"

#define MAXSTREAKS  512
#define FRAME       20000
#define GREEN       1
#define MIN_SIZE    (maxY / 3)
#define MAX_SIZE    (maxY - 5)

WINDOW *w;
int maxX;
int maxY;

streak* streaks[MAXSTREAKS];
int streak_ptr;

int rand_int(int min, int max) {
    return min + (rand() % (max-min));
}

double rand_double(double min, double max) {
    return min + (rand() * (max-min)) / RAND_MAX;
}

streak* new_streak(double y, int x, int len, double speed) {
    streak* tmp = (streak *) malloc(sizeof(streak));
    tmp->y = y;
    tmp->x = x;
    tmp->len = len;
    tmp->speed = speed;
    return tmp;
}

void put_streak(streak* s) {
    if (s == NULL) return;
    if (s->y < maxY)
        mvprintw((int) s->y, s->x, "%c", (char) (rand_int(33, 126)));
    else
        mvprintw(maxY, s->x, " ");
    mvprintw((int) s->y - s->len, s->x, " ");
    mvprintw((int) s->y - s->len - 1, s->x, " ");
    (s->y) += (s->speed);
}

void init() {
    srand((unsigned) time(0));
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
    streak_ptr = 0;
}

void draw_streaks() {
    for (int i = 0; i < streak_ptr; i++) {
        put_streak(streaks[i]);
        if (streaks[i]->y - streaks[i]->len > maxY && streak_ptr > 0) {
            mvprintw(maxY-1, streaks[i]->x, " ");
            free(streaks[i]);
            streaks[i] = streaks[--streak_ptr];
        }
    }
}

void add_new_random_streak() {
    streaks[streak_ptr++] = new_streak(
        0,
        rand_int(0, maxX),
        rand_int(MIN_SIZE, MAX_SIZE),
        rand_double(0.75, 1.25)
    );
}

int main(int argc, char *argv[]) {
    init();
    
    while (getch() == ERR) {
        draw_streaks();
        if (rand_double(0, 1) < 0.9)
            add_new_random_streak();
        refresh();
        usleep(FRAME);
    }

    attroff(COLOR_PAIR(GREEN));
    endwin();
    return 0;
}
