/*
** EPITECH PROJECT, 2017
** lemin
** File description:
** lemin
*/

#ifndef _LEMIN_H_
	#define _LEMIN_H_

	#include <stdlib.h>
	#include <malloc.h>
	#include <stdio.h>
	#include <string.h>
	#include "graph.h"
	#include "printf.h"
	#include "get_next_line.h"
	#include "utils.h"
	#include "maths.h"
	#pragma GCC poison printf atoi strcpy strlen

#define ISSPACE(c) (c == 0x20 ||				\
					c == '\n' ||				\
					c == '\v' ||				\
					c == '\f' ||				\
					c == '\t' ||				\
					c == '\r')

typedef enum e_parse_status
{
		PARSE_OK,
		PARSE_ERROR,
		PARSE_ANTS,
		PARSE_ROOMS,
		PARSE_TUNNELS
} PARSE_STATUS;

typedef enum e_parse_cmd
{
		CMD_NOP = 0x0,
		CMD_ENTRY = 0x1,
		CMD_EXIT = 0x2
} PARSE_CMD;

PARSE_STATUS parse_map(t_graph **graph);
t_vertex *parse_room(t_vertex **room, char *l);
char *parse_string(char **s);
int parse_int(char **s);

#endif
