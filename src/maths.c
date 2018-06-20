/*
** EPITECH PROJECT, 2017
** lemin
** File description:
** math
*/

#include "maths.h"
#include "printf.h"

float my_sqrt(float n)
{
	int i = 0x5f3759df - ((*(int*)&n) >> 1);
	float y = *(float*)&i;
	y *= (1.5f - 0.5f * n * y * y);
	y *= (1.5f - 0.5f * n * y * y);
	y *= (1.5f - 0.5f * n * y * y);
	return ((float)(y * n));
}

float my_pow(float f, int n)
{
	if (n == 0) return 1;
	if (n == 1) return f;
	double sign = (f < 0 && n % 2) ? -1.f : 1.f;
	double m = f;
	while (n-- > 1) f *= m;
	return (f*sign);
}

int get_dist(const t_vertex *v1, const t_vertex *v2)
{
	float x2 = my_pow(v2->x - v1->x, 2);
	float y2 = my_pow(v2->y - v1->y, 2);
	float n = my_sqrt(x2 + y2);
	int i = (int)n;
	int dist = (n - (float)i) > 0.49f ? i + 1 : i;
	return (dist);
}
