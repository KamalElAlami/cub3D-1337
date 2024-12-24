/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kael-ala <kael-ala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 08:17:50 by kael-ala          #+#    #+#             */
/*   Updated: 2024/12/24 08:19:27 by kael-ala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

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
			if (sin(player->ray->rayangle) < 0) // change player angle with ray angel
				tex = player->params->t_no;
			else
				tex = player->params->t_so;
		}
		else
		{
			if (cos(player->ray->rayangle) < 0) // change player angle with ray angel
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
		if (y >= 0 && y < WINDOW_HEIGHT)
			mlx_put_pixel(player->params->graph->img, x, y, rgb_hex(player->params->floor[0], player->params->floor[1], player->params->floor[2]));
		y++;
	}
}