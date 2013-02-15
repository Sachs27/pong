#ifndef VECTOR2_H
#define VECTOR2_H

typedef struct vector2 {
    float x;
    float y;
}vector2_t;
#define vector2_s sizeof(vector2_t)

vector2_t vector2_normalize(vector2_t v);
float vector2_length(vector2_t v);
vector2_t vector2_add(vector2_t lhs, vector2_t rhs);
vector2_t vector2_mul(vector2_t lhs, float rhs);
float vector2_dot(vector2_t lhs, vector2_t rhs);
vector2_t vector2_reverse(vector2_t v);

#endif
