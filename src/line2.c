#include <math.h>

#include "line2.h"

vector2_t line2_normal(line2_t *line)
{
    vector2_t line_vector;
    vector2_t normal;

    line_vector = vector2_add(line->end, vector2_reverse(line->begin));
    normal.x = line_vector.y;
    normal.y = line_vector.x;
    if (normal.x > 0) {
        if (normal.y > 0) {
            normal.x = -normal.x;
        } else {
            normal.y = -normal.y;
        }
    } else {
        if (normal.y > 0) {
            normal.y = -normal.y;
        } else {
            normal.x = -normal.x;
        }
    }
    return normal;
}

int line2_equation(line2_t *line, float *a, float *b, float *c)
{
    float tmp;

    if (!(a && b && c)) {
        return -1;
    }
    tmp = (line->end.x - line->begin.x);
    if (tmp != 0) {
        *a = -(line->end.y - line->begin.y) / tmp;
        *b = 1;
        *c = -line->begin.y - *a * line->begin.x;
    } else {
        *a = 1;
        *b = 0;
        *c = -line->begin.x;
    }
    return 0;
}

float line2_distance(line2_t *line, vector2_t point)
{
    float a, b, c, d;
    
    line2_equation(line, &a, &b, &c);
    d = fabs(a*point.x + b*point.y + c) / sqrtf(a*a + b*b);
    return d;
}
