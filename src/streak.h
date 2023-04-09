typedef struct {
    int x;
    double y;
    int len;
    double speed;
} streak;

streak* new_streak(double y, int x, int len, double speed);
void put_streak(streak* s);
