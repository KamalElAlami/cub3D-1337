/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kael-ala <kael-ala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 13:30:38 by kael-ala          #+#    #+#             */
/*   Updated: 2024/11/20 11:56:22 by kael-ala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/cub3d.h>

double normalize_angle(double angle){
    return fabs(fmod(angle, 2 * M_PI));
}

int is_wall(t_params *params, double x, double y)
{
    int gridx;
    int gridy;

 
    gridx = floor(x / TILE_SIZE);
    gridy = floor(y / TILE_SIZE);

    if (gridx < 0 || gridy < 0 || 
        gridx >= (params->w_width / TILE_SIZE) || 
        gridy >= (params->w_height / TILE_SIZE))
        return (1);

    if  (params->map[gridy][gridx] == '1')
        return (1);
    return (0);
}
double horizontal_distance(t_player *playerr, double rayangle)
{
    int lookup = 0;
    int lookdown = 0;
    int lookleft = 0;
    int lookright = 0;
    double xinter, yinter;
    double stepx, stepy;
    double horx = 0, hory = 0;
    int flag = 0;
    double yflag;

    // hna kan check where exaclty direction of the player is 
    rayangle = normalize_angle(rayangle);
    if (rayangle > 0 && rayangle < M_PI)
        lookdown = 1;
    if (rayangle > M_PI && rayangle < 2 * M_PI)
        lookup = 1;
    if (rayangle < 0.5 * M_PI || rayangle > 1.5 * M_PI)
        lookright = 1;
    if (rayangle > 0.5 * M_PI && rayangle < 1.5 * M_PI)
        lookleft = 1;
    // after ma kan set l flags d direction khasni n detect awl intersection
    yinter = floor(playerr->posy / TILE_SIZE) * TILE_SIZE;
    // Mathalan: player.y = 150
    // 150/64 = 2.34375
    // floor(2.94375) = 2
    // 2 * 64 = 128  <- had grid line lewla
    if (lookdown) // ila kan direction kaychuf l ta7t 128 + tile_size = 192 donc next grid line lee ta7t
        yinter = yinter + TILE_SIZE;
    xinter = playerr->posx + (yinter - playerr->posy) / tan(rayangle);
    stepy = TILE_SIZE;
    if (lookup)
        stepy = -TILE_SIZE;
    stepx = TILE_SIZE / tan(rayangle);
    if ((lookleft && stepx > 0) || (lookright && stepx < 0))
        stepx = -stepx;
    yflag = yinter;
    while (!flag)
    {
        if (lookup)
            yflag -= 1;
        if (xinter < 0 || xinter >= playerr->params->w_width || yinter < 0 || yinter >= playerr->params->w_height)
            break;
        if (is_wall(playerr->params, xinter , yflag))
        {
            flag = 1;
            horx = xinter;
            hory = yinter;
        }
            xinter += stepx;
            yinter += stepy;
            yflag = yinter;
    }
    double distance = sqrt(pow(horx - playerr->posx, 2) + pow(hory - playerr->posy, 2));
    return (distance);
}
double vertical_distance(t_player *playerr, double rayangle)
{
    int lookup = 0;
    int lookdown = 0;
    int lookleft = 0;
    int lookright = 0;
    double xinter, yinter;
    double stepx, stepy;
    double horx, hory;
    int flag = 0;
    double xflag;

    if (rayangle > 0 && rayangle < M_PI)
        lookdown = 1;
    if (rayangle > M_PI && rayangle < 2 * M_PI)
        lookup = 1;
    if (rayangle < 0.5 * M_PI || rayangle > 1.5 * M_PI)
        lookright = 1;
    if (rayangle > 0.5 * M_PI && rayangle < 1.5 * M_PI)
        lookleft = 1;
    // after ma kan set l flags d direction khasni n detect awl intersection
    xinter = floor(playerr->posx / TILE_SIZE) * TILE_SIZE;
    // Mathalan: player.y = 150
    // 150/64 = 2.34375
    // floor(2.94375) = 2
    // 2 * 64 = 128  <- had grid line lewla
    if (lookdown) // ila kan direction kaychuf l ta7t 128 + tile_size = 192 donc next grid line lee ta7t
        xinter = xinter + TILE_SIZE;
    yinter = playerr->posy + (xinter - playerr->posx) * tan(rayangle);
    stepx = TILE_SIZE;
    if (lookleft)
        stepx = -TILE_SIZE;
    stepy = TILE_SIZE * tan(rayangle);
    if ((lookup && stepy > 0) || (lookdown && stepy < 0))
        stepy = -stepy;
    xflag = xinter;
    while (!flag)
    {
        if (lookleft)
            xflag -= 1;
       if (xinter < 0 || xinter >= (playerr->params->w_width * TILE_SIZE) || yinter < 0 || yinter >= (playerr->params->w_height * TILE_SIZE))
            break;
        if (is_wall(playerr->params,xflag, yinter))
        {
            flag = 1;
            horx = xinter;
            hory = yinter;
        }
        xinter += stepx;
        yinter += stepy;
        xflag = xinter;
        
    }
    double distance = sqrt(pow(horx - playerr->posx, 2) + pow(hory - playerr->posy, 2));
    return (distance);
}


void    draw_ray(t_graphics *data, t_player *player, double ray_angle, double distance)
{
    // Starting point (player position)
    double start_x = player->posx;
    double start_y = player->posy;
    
    // Length of the ray (you can adjust this)
    int ray_length = (int)round(distance);
    
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
void raycasting(t_player *playerr, t_graphics *graphic)
{
    int i;
    double rayangle;
    double horiz;
    double verti;
    double distance;

    rayangle = playerr->angle - (playerr->fov / 2);
    i = 0;
    while (i < playerr->params->w_width)
    {
        rayangle = normalize_angle(rayangle);
        horiz = horizontal_distance(playerr, rayangle);
        verti = vertical_distance(playerr, rayangle);
        if(horiz < verti)
            distance = horiz;
        else
            distance = verti;
        draw_ray(graphic, playerr, rayangle, distance);
        // printf("posx => %f\nposy => %f\n", playerr->posx, playerr->posy);
        // printf("horizontal distance>>> %f\n vertical distance>>> %f\n rayangle>>> %f\n", horiz, verti, rayangle);
        rayangle += playerr->fov / (playerr->params->w_width );
        i++;
    }

    
}