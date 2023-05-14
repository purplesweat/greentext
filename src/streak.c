#include <ncurses.h>
#include <stdlib.h>
#include "util.h"
#include "streak.h"

int streak_ptr;
int min_size, max_size;

streak* new_streak(double y, int x, int len, double speed) {
    streak* tmp = (streak *) malloc(sizeof(streak));
    tmp->y = y;
    tmp->x = x;
    tmp->len = len;
    tmp->speed = speed;
    return tmp;
}

void put_streak(streak* s, int maxY) {
    if (s == NULL) return;
    if (s->y < maxY)
        mvaddch((int) s->y, s->x, (char) (rand_int(33, 126)));
    else
        mvaddch(maxY, s->x, ' ');
    mvaddch((int) s->y - s->len, s->x, ' ');
    mvaddch((int) s->y - s->len - 1, s->x, ' ');
    s->y += s->speed;
}

void draw_streaks(streak* streaks[], int maxY) {
    for (int i = 0; i < streak_ptr; i++) {
        put_streak(streaks[i], maxY);
        if (streaks[i]->y - streaks[i]->len > maxY && streak_ptr > 0) {
            mvprintw(maxY-1, streaks[i]->x, " ");
            free(streaks[i]);
            streaks[i] = streaks[--streak_ptr];
        }
    }
}

void add_new_random_streak(streak* streaks[], int maxX) {
    streaks[streak_ptr++] = new_streak(
        0,
        rand_int(0, maxX),
        rand_int(min_size, max_size),
        rand_double(0.5, 1)
    );
}

void streaks_init(int maxY, int maxX) {
    streak_ptr = 0;
    min_size = maxY / 3;
    max_size = maxY - 10;
}
