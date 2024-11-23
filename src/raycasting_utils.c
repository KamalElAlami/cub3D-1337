/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kael-ala <kael-ala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 14:32:42 by kael-ala          #+#    #+#             */
/*   Updated: 2024/11/23 07:35:02 by kael-ala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void init_player(t_params *param, t_player *playerrr)
{
    int *pos;
    char p;

    p = get_player(param->map);
    pos = hidenseek(param->map);
    playerrr->fov = 60 * (M_PI / 180);
    playerrr->posx = (pos[1] * 32) - 16;
    playerrr->posy = (pos[0] * 32) - 16;
    playerrr->rotSpeed = 0.05;
    playerrr->moveSpeed = 5;

    // Set initial angle based on direction
    if (p == 'N')
    {
        playerrr->angle = 3 * M_PI / 2;  // Looking up
        playerrr->dirx = 0;
        playerrr->diry = -1;
    }
    else if (p == 'S')
    {
        playerrr->angle = M_PI / 2;     // Looking down
        playerrr->dirx = 0;
        playerrr->diry = 1;   
    }
    else if (p == 'W')
    {
        playerrr->angle = M_PI;         // Looking left
        playerrr->dirx = -1;
        playerrr->diry = 0;
    }
    else if (p == 'E')
    {
        playerrr->angle = 0;            // Looking right
        playerrr->dirx = 1;
        playerrr->diry = 0;
    }
}

void    draw_ray(t_graphics *data, t_player *player, double ray_angle, double distance)
{
    // Starting point (player position)
    double start_x = player->posx;
    double start_y = player->posy;
    
    // Length of the ray (you can adjust this)
    int ray_length = (int)floor(distance);
    
    // Calculate end point using cos and sin
    double end_x = start_x + (cos(ray_angle) * ray_length);
    double end_y = start_y + (sin(ray_angle) * ray_length);
    
    // Variables for DDA line drawing
    double dx = end_x - start_x;
    double dy = end_y - start_y;
    
    // Number of steps needed (use the bigger delta)
    int steps = (fabs(dx) > fabs(dy)) ? fabs(dx) : fabs(dy);
    
    // Calculate increment per step
    double x_inc = dx / (double)steps;
    double y_inc = dy / (double)steps;
    
    // Start drawing from player position
    double x = start_x;
    double y = start_y;
    
    // Draw the line step by step
    for (int i = 0; i <= steps; i++)
    {
        // Put pixel if it's within window bounds
        if (x >= 0 && x < player->params->w_width && y >= 0 && y < player->params->w_height)
            mlx_put_pixel(data->img, (int)x, (int)y, 0xFF0000ff);
        
        // Move to next position
        x += x_inc;
        y += y_inc;
    }
}

int is_wall(t_params *params, double x, double y)
{
    int gridx;
    int gridy;

 
    gridx = (int)floor(x / TILE_SIZE);
    gridy = (int)floor(y / TILE_SIZE);

    if (gridx < 0 || gridy < 0 || 
        gridx >= (params->w_width / TILE_SIZE) || 
        gridy >= (params->w_height / TILE_SIZE))
        return (1);

    if  (params->map[gridy][gridx] == '1')
        return (1);
    return (0);
}