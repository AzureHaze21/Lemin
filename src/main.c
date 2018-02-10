/*
** EPITECH PROJECT, 2017
** lemin
** File description:
** lemin
*/

#include "lemin.h"
#include <stdlib.h>
#include <unistd.h>

static int die(const char *msg)
{
		my_printf("%s", msg);
		return (84);
}

static void lemin(t_graph *graph, t_path *path)
{
		register t_ant *ants = malloc(graph->agents * sizeof(t_ant));
		int n = graph->agents;
		int total = n;
		int first = 0;

		if (!ants)
				return ;
		for (int i = 0; i < graph->agents; i++)
				ants[i] = (t_ant){ i + 1, path };
		while (total > 0) {
				for (register int i = 0; i < n; i++) {
						if (ants[i].id && !ants[i].current->next->cnx->ant) {
								my_printf(first ? " P%d-%s" : "P%d-%s",
										  ants[i].id, ants[i].current->next->cnx->name);
								first = 1;
								ants[i].current->cnx->ant = 0;
								if (ants[i].current->next->cnx != graph->exit)
										ants[i].current->next->cnx->ant = ants[i].id;
								else {
										ants[i].id = 0;
										total--;
								}
								ants[i].current = ants[i].current->next;
						}
				}
				first = 0;
				my_printf("\n");
		}
		free(ants);
}

int main(int argc, __attribute__((unused))char **argv)
{
		t_graph *graph = create_graph();
		t_path *path = NULL;

		if (!graph)
				return (die("Failed to create graph.\n"));
		else if (argc > 1)
				return (die("USAGE:\t ./lem_in < map\n"));
		else if (parse_map(&graph) == PARSE_ERROR || !graph->entry) {
				destroy_graph(&graph);
				return (die("Invalid map.\n"));
		}
		set_shortest_dist(graph->entry, graph->entry);
		path = get_path(graph);
		if (!path)
				return (die("No path found\n"));
		my_printf("#moves\n");
		lemin(graph, path);
		destroy_graph(&graph);
		destroy_path(&path);
		return (0);
}
