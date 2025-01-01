/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarif <sarif@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 08:17:50 by kael-ala          #+#    #+#             */
/*   Updated: 2025/01/01 17:29:06 by sarif            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

mlx_texture_t	*which_texture(t_player *player)
{
	mlx_texture_t	*tex;

	if (player->ray->isdoor == 1)
		tex = player->params->t_door;
	else if (player->ray->is_horizontal)
	{
		if (sin(player->ray->rayangle) < 0)
			tex = player->params->t_no;
		else
			tex = player->params->t_so;
	}
	else
	{
		if (cos(player->ray->rayangle) < 0)
			tex = player->params->t_ea;
		else
			tex = player->params->t_we;
	}
	return (tex);
}

unsigned int	get_color_tex(t_player *player, mlx_texture_t *tex,
	double wallheight, int y)
{
	unsigned int	x_offset;
	unsigned int	y_offset;
	unsigned int	position;
	unsigned int	test;
	int				y_top;

	if (player->ray->is_vertical)
		x_offset = (int)player->ray->hity % TILE_SIZE;
	else
		x_offset = (int)player->ray->hitx % TILE_SIZE;
	test = 0;
	if (y >= 0 && y < WINDOW_HEIGHT)
	{
		y_top = y + (wallheight / 2) - (WINDOW_HEIGHT / 2);
		y_offset = y_top * ((double)tex->height / wallheight);
		position = (y_offset * tex->width * tex->bytes_per_pixel)
			+ (x_offset * tex->bytes_per_pixel);
		if (position < 0 || position >= tex->width * tex->height * 4)
			test = 0;
		else
			test = tex->pixels[position] << 24 | tex->pixels[position + 1] << 16
				| tex->pixels[position + 2] << 8 | tex->pixels[position + 3];
	}
	return (test);
}

void	render_wall(t_player *player, int x)
{
	double	playerdist;
	double	wallheight;
	double	top;
	double	bot;
	int		y;

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
	while (y < bot)
	{
		if (y >= 0 && y < WINDOW_HEIGHT)
			mlx_put_pixel(player->params->graph->img, x, y,
				get_color_tex(player, which_texture(player), wallheight, y));
		y++;
	}
	player->ray->isdoor = 0;
	while (y < WINDOW_HEIGHT)
	{
		if (y >= 0 && y < WINDOW_HEIGHT)
			mlx_put_pixel(player->params->graph->img, x, y, rgb_hex(player->params->floor[0], player->params->floor[1], player->params->floor[2]));
		y++;
	}
}

void	clear_prog(t_params *p, int status, char *err)
{
	int	i;

	i = -1;
	while (++i < 22)
		if (p->frames_t[i])
			mlx_delete_texture(p->frames_t[i]);
	if (err)
		write(2, err, ft_strlen(err));
	if (p->t_no)
		mlx_delete_texture(p->t_no);
	if (p->t_so)
		mlx_delete_texture(p->t_so);
	if (p->t_we)
		mlx_delete_texture(p->t_we);
	if (p->t_ea)
		mlx_delete_texture(p->t_ea);
	if (p->t_door)
		mlx_delete_texture(p->t_door);
	if (p->player->pv)
		mlx_delete_image(p->graph->mlx, p->player->pv);
	if (p->graph->minimap)
		mlx_delete_image(p->graph->mlx, p->graph->minimap);
	if (p->graph->img)
		mlx_delete_image(p->graph->mlx, p->graph->img);
	if (p->graph->mlx)
		mlx_close_window(p->graph->mlx);
	ft_malloc(0, CLEAR_END);
	exit (status);
}
