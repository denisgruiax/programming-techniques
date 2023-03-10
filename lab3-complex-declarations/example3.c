#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct
{
    double x, y;
} Point;

double dist(const Point *point);
int compareDistance(const void *elem1, const void *elem2);

int main(int argc, char *argv[])
{
    Point points[5] = {{1, 3}, {7, 5}, {0, 0}, {-2, 4}, {1, 1}};
    qsort(points, 5, sizeof(Point), compareDistance);

    for (unsigned i = 0; i < 5; i++)
        printf("%g %g\n", (points + i)->x, (points + i)->y);

    return 0;
}

double dist(const Point *point)
{
    return sqrt((point->x * point->x) + (point->y * point->y));
}

int compareDistance(const void *elem1, const void *elem2)
{
    const Point *p1 = (const Point *)elem1;
    const Point *p2 = (const Point *)elem2;

    double d1 = dist(p1);
    double d2 = dist(p2);

    if (d1 < d2)
        return -1;
    if (d1 > d2)
        return 1;
    return 0;
}