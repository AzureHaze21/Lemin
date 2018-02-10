/*
** EPITECH PROJECT, 2017
** lemin
** File description:
** maths
*/

#ifndef _MATHS_H_
	#define _MATHS_H_

	#include "graph.h"

	#define ABS(n) (n < 0 ? -n : n)

float my_sqrt(float f);
float my_pow(float f, int n);
int get_dist(const t_vertex *v1, const t_vertex *v2);

#endif
