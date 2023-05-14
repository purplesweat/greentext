typedef struct {
    int x;
    double y;
    int len;
    double speed;
} streak;

streak* new_streak(double y, int x, int len, double speed);
void put_streak(streak* s, int maxY);
void draw_streaks(streak* streaks[], int maxY);
void add_new_random_streak(streak* streaks[], int maxX);
void streaks_init(int maxY, int maxX);
