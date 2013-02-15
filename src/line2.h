#ifndef LINE2_H
#define LINE2_H

#include "vector2.h"

typedef struct line2 {
    vector2_t begin;
    vector2_t end;
}line2_t;
#define line2_s sizeof(line2_t)

vector2_t line2_normal(line2_t *line);
int line2_equation(line2_t *line, float *a, float *b, float *c);
float line2_distance(line2_t *line, vector2_t point);

#endif
