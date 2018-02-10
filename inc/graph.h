/*
** EPITECH PROJECT, 2017
** lemin
** File description:
** lemin
*/

#ifndef _GRAPH_H_
	#define _GRAPH_H_
	#include <unistd.h>
	#include <stdlib.h>

typedef struct s_vertex t_vertex;
typedef struct s_edge t_edge;
typedef struct s_edge t_path;
typedef struct s_graph t_graph;
typedef struct s_ant t_ant;

struct s_vertex
{
		char *name;
		int x;
		int y;
		int ant;
		int dist;
		int visited;
		t_edge *edges;
		t_vertex *from;
		t_vertex *next;
};

struct s_edge
{
		t_vertex *cnx;
		t_edge *next;
};

struct s_graph
{
		int agents;
		t_vertex *entry;
		t_vertex *exit;
		t_vertex *vertices;
};

struct s_ant
{
		int id;
		t_path *current;
};

t_graph *create_graph(void)  __attribute_warn_unused_result__;
void destroy_path(t_path **p);
void destroy_graph(t_graph **g);
void print_graph(const t_graph *g);
t_vertex *get_vertex(t_vertex *v, const char *name);
void reset_paths(t_graph *g);
int can_reach(t_graph *g, t_vertex *src, t_vertex *dst);
int can_reach_rec(t_vertex *from, t_vertex *to);
t_path *get_path(const t_graph *g);
void set_shortest_dist(t_vertex *v, t_vertex *start);
t_vertex *add_vertex(t_vertex **v, char *name, int x, int y);
t_edge *add_edge(t_vertex **vertices,
				 const char *src,
				 const char *dst);

#endif
