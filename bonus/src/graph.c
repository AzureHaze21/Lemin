/*
** EPITECH PROJECT, 2017
** lemin
** File description:
** lemin
*/

#include "graph.h"
#include "printf.h"
#include "utils.h"
#include "maths.h"

void reset_paths(t_graph *g)
{
		t_vertex *it = g ? g->vertices : NULL;

		while (it)
		{
				it->visited = 0;
				it = it->next;
		}
}

void set_shortest_dist(t_vertex *v, t_vertex *start)
{
		register t_edge *it = v ? v->edges : NULL;
		int dist = 0;

		v->visited = 1;
		while (it) {
				if (it->cnx != start) {
						dist = get_dist(v, it->cnx) + v->dist;
						if (!it->cnx->dist || dist < it->cnx->dist) {
								it->cnx->dist = dist;
								it->cnx->from = v;
						}
				}
				it = it->next;
		}
		it = v ? v->edges : NULL;
		while (it) {
				if (!it->cnx->visited)
						set_shortest_dist(it->cnx, start);
				it = it->next;
		}
}

static inline void __attribute__((always_inline))
stack(t_path **path, t_vertex *v)
{
		t_path *p = malloc(sizeof(t_path));

		if (!p || !path)
				return ;
		p->cnx = v;
		p->next = *path;
		*path = p;
}

t_path *get_path(const t_graph *g)
{
		t_vertex *it = g ? g->exit : NULL;
		t_path *path = NULL;

		while (it != g->entry) {
				if (!it)
						return (NULL);
				stack(&path, it);
				it = it->from;
		}
		stack(&path, g->entry);
		return (path);
}

int can_reach_rec(t_vertex *from,
				  t_vertex *to)
{
		register t_edge *it = from ? from->edges : NULL;

		if (from->visited == 1 || !from)
				return (0);
		from->visited = 1;
		if (from == to)
				return (1);
		while (it)
		{
				if (!it->cnx->ant)
				{
						if (can_reach_rec(it->cnx, to))
								return (1);
				}
				it = it->next;
		}
		return (0);
}

int can_reach(t_graph *g,
			  t_vertex *src,
			  t_vertex *dst)
{
		t_vertex *it = g ? g->vertices : NULL;
		t_vertex *from = NULL;

		reset_paths(g);
		while (it)
		{
				if (it == src)
						from = src;
				it = it->next;
		}
		if (!from)
				return (0);
		return (can_reach_rec(from, dst));
}

t_graph *create_graph(void)
{
		t_graph *p = malloc(sizeof(t_graph));

		if (!p)
				return NULL;
		*p = (t_graph){ 0, NULL, NULL, NULL };
		return (p);
}

t_vertex *add_vertex(t_vertex **room,
					 char *name,
					 int x,
					 int y)
{
		t_vertex *p = malloc(sizeof(t_vertex));
		t_vertex *it = *room;

		if (!p)
				return (NULL);
		*p = (t_vertex){ name, x, y, 0, 0, 0, NULL, NULL, NULL };
		if (!it) {
				*room = p;
				return (p);
		}
		while (it->next)
				it = it->next;
		it->next = p;
		return (p);
}

t_vertex *get_vertex(t_vertex *v, const char *name)
{
		t_vertex *p = v;

		while (p)
		{
				if (!my_strcmp(p->name, name))
						return (p);
				p = p->next;
		}
		return (NULL);
}

t_edge *add_edge(t_vertex **v, const char *src, const char *dst)
{
		t_edge *e = malloc(sizeof(t_edge));
		t_edge *it = NULL;
		t_vertex *p1 = get_vertex(*v, src);
		t_vertex *p2 = get_vertex(*v, dst);

		if (!e || !p1 || !p2)
				return (NULL);
		e->cnx = p2;
		e->next = NULL;
		if (!(p1->edges))
				p1->edges = e;
		else {
				it = p1->edges;
				while (it && it->next)
						it = it->next;
				it->next = e;
		}
		return (e);
}

void destroy_edges(t_edge **edges)
{
		t_edge *p = *edges;

		while (p)
		{
				p = (*edges)->next;
				free(*edges);
				*edges = p;
		}
}

void destroy_graph(t_graph **g)
{
		t_vertex *p = (*g)->vertices;
		t_vertex *tmp = NULL;

		while (p)
		{
				tmp = p->next;
				free(p->name);
				destroy_edges(&p->edges);
				free(p);
				p = tmp;
		}
		free(*g);
}

void destroy_path(t_path **p)
{
		t_path *it = *p;

		while (it)
		{
				it = (*p)->next;
				free(*p);
				(*p) = it;
		}
}
