/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kael-ala <kael-ala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 13:30:38 by kael-ala          #+#    #+#             */
/*   Updated: 2024/11/23 11:22:52 by kael-ala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/cub3d.h>

double  normalize_angle(double angle)
{
    angle = fmod(angle, 2 * M_PI);
    if (angle < 0)
        angle += (2 * M_PI);
    return (angle);
}


t_looking    raydirection(double angle)
{
    t_looking direction;
    
    direction.up = (angle > M_PI);
    direction.down = !direction.up;
    direction.left = (angle > M_PI_2 && angle < 3 * M_PI_2);
    direction.right = !direction.left;
    return (direction);
}

double vertical_distance(t_player *playerr, double rayangle)
{
    t_looking direction;
    double stepx;
    double stepy;
    double yinter;
    double xinter;
    int wallhit;
    double xcheck;

    wallhit = 0;
    direction = raydirection(rayangle);
    xinter = floor(playerr->posx / TILE_SIZE) * TILE_SIZE;
    if (direction.right)
        xinter += TILE_SIZE;
    yinter = playerr->posy + ((xinter - playerr->posx) * tan(rayangle));
    stepx = TILE_SIZE;
    if ((direction.left && stepx > 0) || (direction.right && stepx < 0))
        stepx = -TILE_SIZE;
    stepy = TILE_SIZE * tan(rayangle);
    if ((direction.up && stepy > 0) || (direction.down && stepy < 0))
        stepy = -stepy;
    xcheck = xinter;
    if (direction.left)
        xcheck -= 1;
    while (1)
    {
        if (is_wall(playerr->params, xcheck, yinter) || (xinter < 0 || yinter < 0 || xinter >= (playerr->params->w_width) || yinter >= (playerr->params->w_height)))
            break ;
        xinter += stepx;
        yinter += stepy;
        xcheck = xinter;
        if (direction.left)
            xcheck -= 1;
    }
     return (sqrt(pow(xinter - playerr->posx, 2) + pow(yinter - playerr->posy, 2)));
}
double horizontal_distance(t_player *playerr, double rayangle)
{
    t_looking direction;
    double stepx;
    double stepy;
    double yinter;
    double xinter;
    int wallhit;
    double ycheck;

    wallhit = 0;
    direction = raydirection(rayangle);
    yinter = floor(playerr->posy / TILE_SIZE) * TILE_SIZE;
    if (direction.down)
        yinter += TILE_SIZE;
    xinter = playerr->posx + ((yinter - playerr->posy) / tan(rayangle));
    stepy = TILE_SIZE;
    if ((direction.up && stepy > 0) || (direction.down && stepy < 0))
        stepy = -TILE_SIZE;
    stepx = TILE_SIZE / tan(rayangle);
    if ((direction.left && stepx > 0) || (direction.right && stepx < 0))
        stepx = -stepx;
    ycheck = yinter;
    if (direction.up)
        ycheck -= 1;
    while (1)
    {
        if (is_wall(playerr->params, xinter, ycheck) || (xinter < 0 || yinter < 0 || xinter >= (playerr->params->w_width) || yinter >= (playerr->params->w_height)))
            break ;
        xinter += stepx;
        yinter += stepy;
        ycheck = yinter;
        if (direction.up)
            ycheck -= 1;
    }
     return (sqrt(pow(xinter - playerr->posx, 2) + pow(yinter - playerr->posy, 2)));
}

double raydistance(t_player *playerr, double rayangle)
{
    double vertical;
    double horizontal;

    vertical = vertical_distance(playerr, rayangle);
    horizontal = horizontal_distance(playerr, rayangle);

    if (horizontal < vertical)
        return (horizontal);
    else
        return (vertical);
}

void render_wall(t_player *player, double distance, int x)
{
    double playerdist;
    double wallheight;
    double top;
    double bot;
    int y;

    playerdist = (player->params->w_width / 2) / tan(player->fov / 2);
    wallheight = (TILE_SIZE * playerdist) / distance;
    top = (player->params->w_height -  wallheight) / 2;
    bot = top + wallheight;
    y = 0;
    while (y < top)
    {
        if (y >= 0 && y < player->params->w_height)
            mlx_put_pixel(player->params->graph->img, x, y, 0x000000FF);
         y++;
    }
    while (y < bot)
    {
        if (y >= 0 && y < player->params->w_height)
            mlx_put_pixel(player->params->graph->img, x, y, 0x808080FF);
        y++;
    }
    while (y < player->params->w_height)
    {
        if (y >= 0 && y < player->params->w_height)
            mlx_put_pixel(player->params->graph->img, x, y, 0x404040FF);
        y++;
    }
}

void raycasting(t_player *playerr)
{
    double distance;
    double rayangle;
    double increament;
    int i;

    i = 0;
    rayangle = playerr->angle - (playerr->fov / 2);
    increament = playerr->fov / (playerr->params->w_width - 1);

    while (i <= playerr->params->w_width)
    {
        rayangle = normalize_angle(rayangle);
        distance = raydistance(playerr, rayangle);
        // draw_ray(playerr->params->graph, playerr, rayangle, distance);
        render_wall(playerr, distance, i);
        rayangle += increament;
        i++;
    }
    
}
