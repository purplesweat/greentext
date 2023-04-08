#include <ncurses/ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define MAXSTREAKS  512
#define FRAME       20000
#define GREEN       1
#define MIN_SIZE    (maxY / 3)
#define MAX_SIZE    (maxY - 5)

typedef struct {
    int x;
    double y;
    int len;
    double speed;
} streak;

streak* new_streak(double y, int x, int len, double speed) {
    streak* tmp = (streak *) malloc(sizeof(streak));
    tmp->y = y;
    tmp->x = x;
    tmp->len = len;
    tmp->speed = speed;
    return tmp;
}

int rand_int(int min, int max) {
    return min + (rand() % (max-min));
}

double rand_double(double min, double max) {
    return min + (rand() * (max-min)) / RAND_MAX;
}

void put_streak(streak* s, int maxY) {
    if (s == NULL) return;
    if (s->y < maxY)
        mvprintw((int) s->y, s->x, "%c", (char) (rand_int(33, 127)));
    mvprintw((int) s->y - s->len, s->x, " ");
    mvprintw((int) s->y - s->len - 1, s->x, " ");
    (s->y) += (s->speed);
}

void init(int* maxY, int* maxX) {
    srand((unsigned) time(0));
    WINDOW* w = initscr();
    cbreak();
    nodelay(w, TRUE);
    noecho();
    curs_set(FALSE);
    getmaxyx(w, *maxY, *maxX);
    if (has_colors() == TRUE)
        start_color();
    use_default_colors();
    init_pair(GREEN, COLOR_GREEN, -1);
    attron(COLOR_PAIR(GREEN));
}

int main(int argc, char *argv[]) {
    int maxX, maxY;
    streak* streaks[MAXSTREAKS];
    int ct = 0;
    init(&maxY, &maxX);
    
    while (getch() == ERR) {
        for (int i = 0; i < ct; i++) {
            put_streak(streaks[i], maxY);
            if (streaks[i]->y - streaks[i]->len > maxY && ct > 0) {
                free(streaks[i]);
                streaks[i] = streaks[--ct];
            }
        }
        if (rand_double(0, 1) < 0.9)
            streaks[ct++] = new_streak(
                0,
                rand_int(0, maxX),
                rand_int(MIN_SIZE, MAX_SIZE),
                rand_double(0.5, 1.5)
            );
        refresh();
        usleep(FRAME);
    }

    attroff(COLOR_PAIR(GREEN));
    endwin();
    return 0;
}
