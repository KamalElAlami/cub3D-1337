/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarif <sarif@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 13:30:38 by kael-ala          #+#    #+#             */
/*   Updated: 2024/12/17 23:33:36 by sarif            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/cub3d.h>

t_rays	*vertical_distance(t_player *playerr, double rayangle)
{
	t_looking	direction;
	double		stepx;
	double		stepy;
	double		yinter;
	double		xinter;
	double		xcheck;
	t_rays		*temp;

	temp = malloc(sizeof(t_rays));
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
	temp->hitx = xinter;
	temp->hity = yinter;
	temp->is_horizontal = 0;
	temp->is_vertical = 1;
	temp->distance = sqrt(pow(xinter - playerr->posx, 2) + pow(yinter - playerr->posy, 2));
	return (temp);
}

t_rays	*horizontal_distance(t_player *playerr, double rayangle)
{
	t_looking	direction;
	double		stepx;
	double		stepy;
	double		yinter;
	double		xinter;
	double		ycheck;
	t_rays		*temp;

	temp = malloc(sizeof(t_rays));
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
	temp->hitx = xinter;
	temp->hity = yinter;
	temp->is_horizontal = 1;
	temp->is_vertical = 0;
	temp->distance = sqrt(pow(xinter - playerr->posx, 2) + pow(yinter - playerr->posy, 2));
	return (temp);
}

t_rays	*raydistance(t_player *playerr, double rayangle)
{
	t_rays	*vertical;
	t_rays	*horizontal;

	vertical = vertical_distance(playerr, rayangle);
	horizontal = horizontal_distance(playerr, rayangle);
	if (horizontal->distance < vertical->distance)
		return (horizontal);
	else
		return (vertical);
}

void	render_wall(t_player *player, int x)
{
	double	playerdist;
	double	wallheight;
	double	top;
	double	bot;
	int		y;
	u_int32_t	x_offset;
	u_int32_t	y_offset;
	uint16_t position;
	uint32_t test;
	mlx_texture_t *tex;
	

	playerdist = (player->params->w_width / 2) / tan(player->fov / 2);
	wallheight = (TILE_SIZE * playerdist) / player->ray->distance;
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
	if (player->ray->is_vertical)
		x_offset = (int)player->ray->hity % TILE_SIZE;
	else
		x_offset = (int)player->ray->hitx % TILE_SIZE;
	while (y < bot)
	{
		if (player->ray->is_horizontal)
		{
			if (sin(player->angle) < 0) // change player angle with ray angel
				tex = player->params->t_no;
			else
				tex = player->params->t_so;
		}
		else
		{
			if (cos(player->angle) < 0) // change player angle with ray angel
				tex = player->params->t_ea;
			else
				tex = player->params->t_we;
		}
		if (y >= 0 && y < WINDOW_HEIGHT){
			int y_top = y + (wallheight / 2) - (WINDOW_HEIGHT / 2);
			y_offset = y_top * ((double)tex->height / wallheight);
			position = (y_offset * tex->width * tex->bytes_per_pixel) + (x_offset * tex->bytes_per_pixel);
			if (position < 0 || position >= tex->width * tex->height * 4)
    			test = 0;
			else
				test = tex->pixels[position] << 24 | tex->pixels[position + 1] << 16 | tex->pixels[position + 2] << 8 | tex->pixels[position + 3];
			mlx_put_pixel(player->params->graph->img, x, y, test);
		}
		y++;
	}
	while (y < WINDOW_HEIGHT)
	{
		if (y >= 0 && y < WINDOW_HEIGHT){
			
			mlx_put_pixel(player->params->graph->img, x, y, rgb_hex(player->params->floor[0], player->params->floor[1], player->params->floor[2]));
		}
		y++;
	}
}

void	raycasting(void *playerr)
{
	t_player	*player;
	double		rayangle;
	double		increament;
	int			i;

	i = 0;
	player = playerr;
	rayangle = player->angle - (player->fov / 2);
	increament = player->fov / WINDOW_WIDTH;
	player->ray = malloc(sizeof(t_rays));
	while (i < WINDOW_WIDTH)
	{
		rayangle = normalize_angle(rayangle);
		player->ray = raydistance(player, rayangle);
		render_wall(player, i);
		rayangle += increament;
		i++;
	}
}
