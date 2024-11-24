/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kael-ala <kael-ala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 02:37:09 by kael-ala          #+#    #+#             */
/*   Updated: 2024/11/24 18:36:31 by kael-ala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"


int wall_coal(t_player *player, double x, double y)
{
    double new_x;
    double new_y;

    new_x =  player->posx + x;
    new_y =  player->posy + y;

    if (new_x < 0  || new_x >= player->params->w_width || new_y < 0 || new_y >= player->params->w_height)
        return (1);
    if (player->params->map[(int)(new_y / TILE_SIZE)][(int)(new_x / TILE_SIZE)] == '1')
        return (1);
    player->posx += x; 
    player->posy += y; 
    return (0);
}

void key_hook(void *player)
{
    double x;
    double y;

    t_player *p = player;
    x = cos(p->angle) * p->moveSpeed;
    y = sin(p->angle) * p->moveSpeed;
    if (mlx_is_key_down(p->params->graph->mlx, MLX_KEY_W)) 
        wall_coal (p, x, y);
    if (mlx_is_key_down(p->params->graph->mlx, MLX_KEY_S))
        wall_coal (p, -x, -y);
    if (mlx_is_key_down(p->params->graph->mlx, MLX_KEY_D))
        wall_coal (p, -y, -x);
    if (mlx_is_key_down(p->params->graph->mlx, MLX_KEY_A))
        wall_coal (p, y, x);
    if (mlx_is_key_down(p->params->graph->mlx, MLX_KEY_LEFT))
    {
        p->angle -= p->rotSpeed;
        p->dirx = cos(p->angle);
        p->diry = sin(p->angle);
    }
    if (mlx_is_key_down(p->params->graph->mlx, MLX_KEY_RIGHT))
    {
        p->angle += p->rotSpeed;
        p->dirx = cos(p->angle);
        p->diry = sin(p->angle);
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
        return (write(2,"map extention error\n",20), 1);
    ft_init_data(params);
    if (check_sheet(av[1], params))
        return (1);
    initialize_graphics(graph, params);
    init_player(params, playerr);
    params->graph = graph;
    playerr->params = params;
    mlx_loop_hook(graph->mlx, raycasting, playerr);
    mlx_loop_hook(graph->mlx, key_hook, playerr);
    mlx_image_to_window(graph->mlx, graph->img, 0, 0);
    mlx_loop(graph->mlx);
}