/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kael-ala <kael-ala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 21:57:37 by kael-ala          #+#    #+#             */
/*   Updated: 2024/12/24 22:55:36 by kael-ala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	load_pngs(t_params *para)
{
	int		i;
	char	*path;

	i = 0;
	while (i < 22)
	{
		path = ft_strjoin("./assets/frames/", ft_itoa(i + 1));
		path = ft_strjoin(path, ".png");
		para->frames_t[i] = mlx_load_png(path);
		if (!para->frames_t[i])
			exit(write(2, "can't load image\n", 17));
		i++;
	}
}

void	initialize_graphics(t_graphics *graphics, t_params *para)
{
	int	*size;

	size = get_size(para->map);
	para->w_width = size[0] * TILE_SIZE;
	para->w_height = size[1] * TILE_SIZE;
	graphics->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "New Window", true);
	graphics->img = mlx_new_image(graphics->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	graphics->minimap = mlx_new_image(graphics->mlx, 200, 200);
	para->t_no = mlx_load_png(para->north);
	if (!para->t_no)
		exit(1);
	para->t_so = mlx_load_png(para->south);
	if (!para->t_so)
		exit(1);
	para->t_ea = mlx_load_png(para->east);
	if (!para->t_ea)
		exit(1);
	para->t_we = mlx_load_png(para->west);
	if (!para->t_we)
		exit(1);
	para->i_no = mlx_texture_to_image(graphics->mlx, para->t_no);
	mlx_resize_image(para->i_no, TILE_SIZE, TILE_SIZE);
	para->i_so = mlx_texture_to_image(graphics->mlx, para->t_no);
	mlx_resize_image(para->i_so, TILE_SIZE, TILE_SIZE);
	para->i_we = mlx_texture_to_image(graphics->mlx, para->t_no);
	mlx_resize_image(para->i_we, TILE_SIZE, TILE_SIZE);
	para->i_ea = mlx_texture_to_image(graphics->mlx, para->t_no);
	mlx_resize_image(para->i_ea, TILE_SIZE, TILE_SIZE);
	load_pngs(para);
}

static uint32_t	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

int	put_txtr(mlx_image_t *img, mlx_texture_t *txtr, mlx_t *mlx)
{
	int		i;
	int		x;
	int		y;
	uint32_t	color;
	mlx_image_t	*tmp;

	tmp = mlx_texture_to_image(mlx, txtr);
	if (!tmp || !mlx_resize_image(img, PV_HEIGHT, PV_WIDTH))
		exit(1);// TODO : free and exit
	(1) && (i = 0, y = -1);
	while (++y < (int)img->height)
	{
		x = -1;
		while (++x < (int)img->width)
		{
			color = get_rgba(tmp->pixels[i], tmp->pixels[i + 1], \
					tmp->pixels[i + 2], tmp->pixels[i + 3]);
			mlx_put_pixel(img, x, y, color);
			i += 4;
		}
	}
	mlx_delete_image(mlx, tmp);
	return (1);
}

void	clr_img(mlx_image_t *img)
{
	int			x;
	int			y;
	uint32_t	color;

	y = -1;
	while (++y < WINDOW_HEIGHT)
	{
		x = -1;
		while (++x < WINDOW_WIDTH)
		{
			color = get_rgba(255, 255, 255, 0);
			mlx_put_pixel(img, x, y, color);
		}
	}
}

void run_animation(t_player *player)
{
	static int	i;
	static int	cnt;

	if (i >= 22)
	{
		i = 0;
		player->anim_it = 0;
		clr_img(player->pv);
		put_txtr(player->pv, player->params->frames_t[0], player->params->graph->mlx);
	}
	if (cnt == 3 && i < 22)
	{
		clr_img(player->pv);
		put_txtr(player->pv, player->params->frames_t[i], player->params->graph->mlx);
		i++;
		cnt = 0;
	}
	cnt++;
}
