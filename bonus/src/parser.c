/*
** EPITECH PROJECT, 2017
** lemin
** File description:
** parser
*/

#include "lemin.h"
#include "graph.h"
#include "printf.h"

int parse_int(char **s)
{
		char *p = NULL;

		while (*(*s) && ISSPACE(*(*s)))
				(*s)++;
		p = *s;
		if (!(*p))
				return (-1);
		while (*(*s) && !ISSPACE(*(*s)))
		{
				if (!(*(*s) >= '0' && *(*s) <= '9'))
						return (-1);
				(*s)++;
		}
		*(*s)++ = 0;
		return (my_atoi(p));
}

int parse_comment(char *s)
{
		while (*s && ISSPACE(*s))
				s++;
		if (!(*s))
				return (0);
		if (*s && *s == '#' &&
			my_strcmp(s, "##start") &&
			my_strcmp(s, "##end"))
				return (0);
		return (-1);
}

PARSE_CMD parse_cmd(char *s)
{
		while (*s && ISSPACE(*s))
				s++;
		if (*s && *s == '#' && *(s + 1) == '#')
		{
				if (!strcmp(s, "##start"))
				{
						my_printf("##start\n");
						return (CMD_ENTRY);
				}
				if (!strcmp(s, "##end"))
				{
						my_printf("##end\n");
						return (CMD_EXIT);
				}
		}
		return (CMD_NOP);
}

char *parse_string(char **s)
{
		char *p = *s;
		size_t len = 0;

		if (!(*s))
				return (NULL);
		while (*(*s) && ISSPACE(*(*s)))
				(*s)++;
		p = *s;
		while (*(*s) && !ISSPACE(*(*s)))
		{
				++len;
				(*s)++;
		}
		*(*s)++ = 0;
		if (!len)
				return (NULL);
		return (my_strdup(p));
}

t_vertex *parse_room(t_vertex **room, char *s)
{
		t_vertex *p = NULL;
		char *name = NULL;
		int x = -1;
		int y = -1;

		name = parse_string(&s);
		x = parse_int(&s);
		y = parse_int(&s);
		if (x == -1 || y == -1 || name == NULL)
				return (NULL);
		p = add_vertex(room, name, x, y);
		if (!p)
				return (NULL);
		my_printf("%s %d %d\n", p->name, p->x, p->y);
		return (p);
}

t_edge *parse_tunnel(t_vertex **vertices, char **s)
{
		char *p1 = NULL;
		char *p2 = NULL;

		while (*(*s) && ISSPACE(*(*s)))
				(*s)++;
		p1 = *s;
		while (*(*s) && *(*s) != '-')
				(*s)++;
		*(*s)++ = 0;
		p2 = *s;
		while (*(*s) && *(*s) != '-')
				(*s)++;
		*(*s) = 0;
		if (!add_edge(vertices, p1, p2))
				return (NULL);
		my_printf("%s-%s\n", p1, p2);
		return (add_edge(vertices, p2, p1));
}

int is_tunnel(const char *s)
{
		int i = 0;
		int link = 0;

		while (s[i] && ISSPACE(s[i]))
				i++;
		while (s[i] && !ISSPACE(s[i]))
		{
				link = s[i] == '-' ? i : link;
				i++;
		}
		return (link > 0 && link < i);
}

PARSE_STATUS parse_map(t_graph **g)
{
		char *l = NULL;
		char *p = NULL;
		PARSE_STATUS st = PARSE_ANTS;
		PARSE_CMD cmd = CMD_NOP;

		while ((l = get_next_line(0)) && (p = l)) {
				if (st == PARSE_ROOMS && is_tunnel(l)) {
						my_printf("#tunnels\n");
						st = PARSE_TUNNELS;
				}
				if (!parse_comment(l))
						(void)l;
				else if (cmd == CMD_ENTRY &&
						 ((*g)->entry = parse_room(&(*g)->vertices, l)))
				{
						(*g)->entry->ant = (*g)->agents;
						cmd = CMD_NOP;
				}
				else if (cmd == CMD_EXIT &&
						 ((*g)->exit = parse_room(&(*g)->vertices, l)))
						cmd = CMD_NOP;
				else if (st == PARSE_ROOMS &&
						 (cmd = parse_cmd(l)) > 0)
						(void)l;
				else if ((st == PARSE_ANTS) &&
						 ((*g)->agents = parse_int(&l)) != -1) {
						my_printf("#number_of_ants\n%d\n#rooms\n",
								  (*g)->agents);
						st = PARSE_ROOMS;
				}
				else if (st == PARSE_ROOMS &&
						 (parse_room(&(*g)->vertices, l)))
						(void)l;
				else if (st == PARSE_TUNNELS &&
						 (parse_tunnel(&(*g)->vertices, &l)))
						(void)l;
				else
						return (PARSE_ERROR);
				free(p);
		}
		return (PARSE_OK);
}
