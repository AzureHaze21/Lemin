#include "lemin.h"
#include <SDL2/SDL.h>

#define WINDOW_X 1024
#define WINDOW_Y 768

static float scaleX = 1.0f;
static float scaleY = 1.0f;

static void draw_end_nodes(SDL_Renderer *renderer, t_graph *g)
{
		SDL_Rect rect1 = { g->entry->x - 2, g->entry->y - 2, 4, 4 };
		SDL_Rect rect2 = { g->exit->x - 2, g->exit->y - 2, 4, 4 };
		SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
		SDL_RenderDrawRect(renderer, &rect1);
		SDL_RenderFillRect(renderer, &rect1);
		SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
		SDL_RenderDrawRect(renderer, &rect2);
		SDL_RenderFillRect(renderer, &rect2);
}

static void draw_tunnels(t_vertex *v, SDL_Renderer *renderer)
{
		register t_edge *it = v ? v->edges : NULL;
		SDL_Rect rect;
		
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 10);
		while (v)
		{
				rect = (SDL_Rect){ v->x - 1, v->y - 1, 2, 2 };
				SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
				SDL_RenderDrawRect(renderer, &rect);
				SDL_RenderFillRect(renderer, &rect);
				it = v->edges;
				while (it) {
						SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
						SDL_RenderDrawLine(renderer,
										   v->x, v->y,
										   it->cnx->x, it->cnx->y);
						it = it->next;
				}
				v = v->next;
		}
}

static void draw_path(t_path *p, SDL_Renderer *renderer)
{
		t_path *it = p;

		SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
		while (it->next)
		{
				SDL_RenderDrawLine(renderer,
								   it->cnx->x, it->cnx->y,
								   it->next->cnx->x, it->next->cnx->y);
				it = it->next;
		}
}

int main(int __attribute__((__unused__))argc,
		 char __attribute__((__unused__))*argv[])
{
		t_graph *g = create_graph();
		t_path *p = NULL;

		parse_map(&g);
		if (!g->entry)
				return (84);
		set_shortest_dist(g->entry, g->entry);
		p = get_path(g);
		if (!p)
				return (84);
		if (SDL_Init(SDL_INIT_VIDEO) == 0) {
				SDL_Window* window = NULL;
				SDL_Renderer* renderer = NULL;
				if (SDL_CreateWindowAndRenderer(WINDOW_X, WINDOW_Y, 0, &window, &renderer) == 0) {
						SDL_bool done = SDL_FALSE;
						while (!done) {
								SDL_Event event;
								SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
								SDL_RenderClear(renderer);
								draw_tunnels(g->vertices, renderer);
								draw_path(p, renderer);
								draw_end_nodes(renderer, g);
								SDL_RenderPresent(renderer);
								while (SDL_PollEvent(&event)) {
										if (event.type == SDL_QUIT)
												done = SDL_TRUE;
										if (event.type == SDL_KEYDOWN)
										{
												if (event.key.keysym.sym == SDLK_DOWN && scaleX > 0)
												{
														scaleX -= 0.05f;
														scaleY -= 0.05f;
														SDL_RenderSetScale(renderer, scaleX, scaleY);
												}
												if (event.key.keysym.sym == SDLK_UP)
												{
														scaleX += 0.05f;
														scaleY += 0.05f;
														SDL_RenderSetScale(renderer, scaleX, scaleY);
												}
										}
										
								}
						}
				}				
				if (renderer)
						SDL_DestroyRenderer(renderer);
				if (window)
						SDL_DestroyWindow(window);
		}
		destroy_graph(&g);
		destroy_path(&p);
		SDL_Quit();
		return 0;
}
