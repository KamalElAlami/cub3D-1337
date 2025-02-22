/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarif <sarif@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 03:40:14 by kael-ala          #+#    #+#             */
/*   Updated: 2025/01/17 18:27:03 by sarif            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_ciel(int *y, double top, int x, t_params *params)
{
	while (*y < top)
	{
		if (*y >= 0 && *y < WINDOW_HEIGHT)
			mlx_put_pixel(params->graph->img, x, *y,
				rgb_hex(params->ciel[0], params->ciel[1], params->ciel[2]));
		(*y)++;
	}
}

void	draw_floor(int *y, int x, t_params *params)
{
	while (*y < WINDOW_HEIGHT)
	{
		if (*y >= 0 && *y < WINDOW_HEIGHT)
			mlx_put_pixel(params->graph->img, x, *y,
				rgb_hex(params->floor[0], params->floor[1], params->floor[2]));
		(*y)++;
	}
}

static mlx_texture_t	*which_texture(t_player *player)
{
	mlx_texture_t	*tex;

	if (player->ray->is_horizontal)
	{
		if (sin(player->ray->rayangle) < 0)
			tex = player->params->t_no;
		else
			tex = player->params->t_so;
	}
	else
	{
		if (cos(player->ray->rayangle) > 0)
			tex = player->params->t_ea;
		else
			tex = player->params->t_we;
	}
	return (tex);
}

static unsigned int	get_color_tex(t_player *player, mlx_texture_t *tex,
	double wallheight, int y)
{
	unsigned int	x_offset;
	unsigned int	y_offset;
	unsigned int	position;
	unsigned int	test;
	int				scal_x;

	scal_x = tex->width / TILE_SIZE;
	if (player->ray->is_vertical)
		x_offset = ((int)player->ray->hity % TILE_SIZE) * scal_x;
	else
		x_offset = ((int)player->ray->hitx % TILE_SIZE) * scal_x;
	test = 0;
	y_offset = ((y + ((double)wallheight / 2.0) - (WINDOW_HEIGHT / 2.0))
			* ((double)tex->height / wallheight));
	position = (y_offset * tex->width * tex->bytes_per_pixel)
		+ (x_offset * tex->bytes_per_pixel);
	if (position < 0 || position >= tex->width * tex->height * 4)
		test = 0;
	else
		test = tex->pixels[position] << 24 | tex->pixels[position + 1] << 16
			| tex->pixels[position + 2] << 8 | tex->pixels[position + 3];
	return (test);
}

void	render_wall(t_player *player, int x)
{
	double	playerdist;
	double	wallheight;
	double	top;
	double	bot;
	int		y;

	playerdist = 1000;
	wallheight = (TILE_SIZE * playerdist) / player->ray->distance;
	top = (WINDOW_HEIGHT - wallheight) / 2;
	bot = top + wallheight;
	y = 0;
	if (top < 0)
		top = 0;
	if (bot > WINDOW_HEIGHT)
		bot = WINDOW_HEIGHT;
	draw_ciel(&y, top, x, player->params);
	while (y < bot)
	{
		if (y >= 0 && y < WINDOW_HEIGHT)
			mlx_put_pixel(player->params->graph->img, x, y,
				get_color_tex(player, which_texture(player), wallheight, y));
		y++;
	}
	draw_floor(&y, x, player->params);
}
