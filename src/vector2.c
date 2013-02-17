#include <math.h>

#include "vector2.h"

vector2_t vector2_add(vector2_t lhs, vector2_t rhs)
{
    vector2_t result;

    result.x = lhs.x + rhs.x;
    result.y = lhs.y + rhs.y;
    return result;
}

vector2_t vector2_mul(vector2_t lhs, float rhs)
{
    vector2_t result;

    result.x = lhs.x * rhs;
    result.y = lhs.y * rhs;
    return result;
}

float vector2_dot(vector2_t lhs, vector2_t rhs)
{
    float result = 0.0f;

    result = lhs.x * rhs.x;
    result += lhs.y * rhs.y;
    return result;
}

float vector2_length(vector2_t v)
{
    return sqrtf(v.x * v.x + v.y * v.y);
}

vector2_t vector2_normalize(vector2_t v)
{
    vector2_t result;
    float length;
    
    length = vector2_length(v);
    if (length) {
        result = vector2_mul(v, 1.0f / length); 
    } else {
        result.x = 0.0f;
        result.y = 0.0f;
    }
    return result;
}

inline vector2_t vector2_reverse(vector2_t v)
{
    return vector2_mul(v, -1.0f);
}
