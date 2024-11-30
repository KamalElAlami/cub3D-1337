/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kael-ala <kael-ala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 13:30:38 by kael-ala          #+#    #+#             */
/*   Updated: 2024/11/30 13:45:36 by kael-ala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/cub3d.h>

double	vertical_distance(t_player *playerr, double rayangle)
{
	t_looking	direction;
	double		stepx;
	double		stepy;
	double		yinter;
	double		xinter;
	int			wallhit;
	double		xcheck;

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
		if (is_wall(playerr->params, xcheck, yinter) || (xinter < 0
				|| yinter < 0 || xinter >= (playerr->params->w_width)
				|| yinter >= (playerr->params->w_height)))
			break ;
		xinter += stepx;
		yinter += stepy;
		xcheck = xinter;
		if (direction.left)
			xcheck -= 1;
	}
	return (sqrt(pow(xinter - playerr->posx, 2)
			+ pow(yinter - playerr->posy, 2)));
}

double	horizontal_distance(t_player *playerr, double rayangle)
{
	t_looking	direction;
	double		stepx;
	double		stepy;
	double		yinter;
	double		xinter;
	int			wallhit;
	double		ycheck;

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
		if (is_wall(playerr->params, xinter, ycheck) || (xinter < 0
				|| yinter < 0 || xinter >= (playerr->params->w_width)
				|| yinter >= (playerr->params->w_height)))
			break ;
		xinter += stepx;
		yinter += stepy;
		ycheck = yinter;
		if (direction.up)
			ycheck -= 1;
	}
	return (sqrt(pow(xinter - playerr->posx, 2)
			+ pow(yinter - playerr->posy, 2)));
}

double	raydistance(t_player *playerr, double rayangle)
{
	double	vertical;
	double	horizontal;

	vertical = vertical_distance(playerr, rayangle);
	horizontal = horizontal_distance(playerr, rayangle);
	if (horizontal < vertical)
		return (horizontal);
	else
		return (vertical);
}

void	render_wall(t_player *player, double distance, int x)
{
	double	playerdist;
	double	wallheight;
	double	top;
	double	bot;
	int		y;

	playerdist = (player->params->w_width / 2) / tan(player->fov / 2);
	wallheight = (TILE_SIZE * playerdist) / distance;
	top = (WINDOW_HEIGHT - wallheight) / 2;
	bot = top + wallheight;
	y = 0;
	if (top < 0)
		top = 0;
	if (bot > WINDOW_HEIGHT)
		bot = WINDOW_HEIGHT;
	while (y < top)
	{
		if (y >= 0 && y < WINDOW_HEIGHT)
			mlx_put_pixel(player->params->graph->img, x, y, rgb_hex(player->params->ciel[0], player->params->ciel[1], player->params->ciel[2]));
		y++;
	}
	while (y < bot)
	{
		if (y >= 0 && y < WINDOW_HEIGHT)
			mlx_put_pixel(player->params->graph->img, x, y, 0x808080FF);
		y++;
	}
	while (y < WINDOW_HEIGHT)
	{
		if (y >= 0 && y < WINDOW_HEIGHT)
			mlx_put_pixel(player->params->graph->img, x, y, rgb_hex(player->params->floor[0], player->params->floor[1], player->params->floor[2]));
		y++;
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

void	raycasting(void *playerr)
{
	t_player	*player;
	double		distance;
	double		rayangle;
	double		increament;
	int			i;

	i = 0;
	player = playerr;
	rayangle = player->angle - (player->fov / 2);
	increament = player->fov / WINDOW_WIDTH;
	while (i < WINDOW_WIDTH)
	{
		rayangle = normalize_angle(rayangle);
		distance = raydistance(player, rayangle);
		render_wall(player, distance, i);
		// draw_ray(player->params->graph, player, rayangle, distance);
		rayangle += increament;
		i++;
	}
}
