/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kael-ala <kael-ala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 02:37:09 by kael-ala          #+#    #+#             */
/*   Updated: 2024/11/22 12:52:39 by kael-ala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"


void draw_direction_line(t_graphics *graphic, t_player *player)
{
    const int LINE_LENGTH = 20;
    int player_x = (int)(player->posx);
    int player_y = (int)(player->posy);
    
    int end_x = player_x + (int)(player->dirx * LINE_LENGTH);
    int end_y = player_y + (int)(player->diry * LINE_LENGTH);
    int dx = end_x - player_x;
    int dy = end_y - player_y;
    int steps = (abs(dx) > abs(dy)) ? abs(dx) : abs(dy);

    float x_inc = dx / (float)steps;
    float y_inc = dy / (float)steps;

    float x = player_x;
    float y = player_y;

    for (int i = 0; i <= steps; i++)
    {
        mlx_put_pixel(graphic->img, (int)roundf(x + 1), (int)roundf(y), 0xFF0000FF);
        mlx_put_pixel(graphic->img, (int)roundf(x), (int)roundf(y), 0xFF0000FF);
        mlx_put_pixel(graphic->img, (int)roundf(x - 1), (int)roundf(y), 0xFF0000FF);
        mlx_put_pixel(graphic->img, (int)roundf(x), (int)roundf(y -1), 0xFF0000FF);
        mlx_put_pixel(graphic->img, (int)roundf(x), (int)roundf(y), 0xFF0000FF);
        mlx_put_pixel(graphic->img, (int)roundf(x), (int)roundf(y + 1), 0xFF0000FF);
        x += x_inc;
        y += y_inc;
    }
}

void render_player(t_graphics *graphic, t_player *player)
{
    const int PLAYER_SIZE = 8;

    int player_x = (int)player->posx ;
    int player_y = (int)player->posy ;
    
    uint32_t player_color = 0xFF0000FF;
    for (int y = -PLAYER_SIZE/2; y < PLAYER_SIZE/2; y++)
    {
        for (int x = -PLAYER_SIZE/2; x < PLAYER_SIZE/2; x++)
        {
            if (x*x + y*y <= (PLAYER_SIZE/2)*(PLAYER_SIZE/2))
                mlx_put_pixel(graphic->img, player_x + x, player_y + y, player_color);
        }
    }
    draw_direction_line(graphic, player);
}

void draw_player(void *ptr)
{
    t_player *p = ptr;
    render_player(p->params->graph, p);
    raycasting(p, p->params->graph);
}

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
        return (1);
    if (check_sheet(av[1], &params) || validate_inputs(params))
        return (1);
    initialize_graphics(graph, params);
    init_player(params, playerr);
    mlxdrawmap(graph, params);
    params->graph = graph;
    playerr->params = params;
    mlx_loop_hook(graph->mlx, draw_map, params);
    mlx_loop_hook(graph->mlx, draw_player, playerr);
    mlx_loop_hook(graph->mlx, key_hook, playerr);
    mlx_image_to_window(graph->mlx, graph->img, 0, 0);
    mlx_loop(graph->mlx);
}