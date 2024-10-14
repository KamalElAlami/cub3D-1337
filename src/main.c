/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kael-ala <kael-ala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 02:37:09 by kael-ala          #+#    #+#             */
/*   Updated: 2024/10/14 07:59:37 by kael-ala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

#define MOVE_SPEED 0.05
#define ROTATE_SPEED 0.05

void render_player(t_graphics *graphic, t_player *player)
{
    const int PLAYER_SIZE = 8;

    int player_x = (int)(player->posx * 32);
    int player_y = (int)(player->posy * 32);

    uint32_t player_color = 0xFF0000FF;
    for (int y = -PLAYER_SIZE/2; y < PLAYER_SIZE/2; y++)
    {
        for (int x = -PLAYER_SIZE/2; x < PLAYER_SIZE/2; x++)
        {
            if (x*x + y*y <= (PLAYER_SIZE/2)*(PLAYER_SIZE/2))
            {
                mlx_put_pixel(graphic->img, player_x + x, player_y + y, player_color);
            }
        }
    }
}

void draw_player(void *ptr)
{
    t_player *p = ptr;
    render_player(p->graph, p);
}

void key_hook(void *player)
{
    t_player *p = player;

    if (mlx_is_key_down(p->graph->mlx, MLX_KEY_W))
        p->posy += p->posy * MOVE_SPEED;
    if (mlx_is_key_down(p->graph->mlx, MLX_KEY_S))
        p->posy -= p->posy * MOVE_SPEED;
    if (mlx_is_key_down(p->graph->mlx, MLX_KEY_D))
        p->posx += p->posx * MOVE_SPEED;
    if (mlx_is_key_down(p->graph->mlx, MLX_KEY_A))
        p->posx -= p->posx * MOVE_SPEED;
}

void init_player(t_params *param, t_player *playerrr)
{
    int *pos;
    char p;

    p = get_player(param->map);
    pos = hidenseek(param->map);
    playerrr->posx = pos[0];
    playerrr->posy = pos[1];
    if (p == 'N')
    {
        playerrr->dirx = 0;
        playerrr->diry = -1;
        playerrr->planex = 0.66;
        playerrr->planey = 0;
    }
    else if (p == 'S')
    {
        playerrr->dirx = 0;
        playerrr->diry = 1;
        playerrr->planex = -0.66;
        playerrr->planey = 0;
    }
    else if (p == 'W')
    {
        playerrr->dirx = -1;
        playerrr->diry = 0;
        playerrr->planex = 0;
        playerrr->planey = -0.66;
    }
    else if (p == 'E')
    {
        playerrr->dirx = 1;
        playerrr->diry = 0;
        playerrr->planex = 0;
        playerrr->planey = 0.66;
    }
}
int main(int ac, char **av)
{
    t_params *params;
    t_graphics *graph;
    t_player *playerr;
    
    params = malloc(sizeof(t_params));
    graph = malloc(sizeof(t_graphics));
    playerr = malloc(sizeof(t_player));
    if (ac != 2 || check_path(av[1]))
        return (1);
    if (check_sheet(av[1], &params) || validate_inputs(params))
        return (1);
    initialize_graphics(graph, params);
    init_player(params, playerr);
    mlxdrawmap(graph, params);
    params->graph = graph;
    playerr->graph = graph;
    mlx_loop_hook(graph->mlx, draw_map, params);
    mlx_loop_hook(graph->mlx, draw_player, playerr);
    mlx_loop_hook(graph->mlx, key_hook, playerr);
    mlx_image_to_window(graph->mlx, graph->img, 0, 0);
    mlx_loop(graph->mlx);
}