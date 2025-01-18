/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarif <sarif@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 21:57:37 by kael-ala          #+#    #+#             */
/*   Updated: 2025/01/18 17:41:45 by sarif            ###   ########.fr       */
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
		path = ft_strjoin_gb("./assets/frames/", ft_itoa(i + 1));
		path = ft_strjoin_gb(path, ".png");
		para->frames_t[i] = mlx_load_png(path);
		if (!para->frames_t[i])
			clear_prog(para, 1, "can't load image\n");
		i++;
	}
}

void	initialize_graphics(t_graphics *graphics, t_params *para)
{
	int	*size;

	size = get_size(para->u_map);
	para->w_width = size[0] * TILE_SIZE;
	para->w_height = size[1] * TILE_SIZE;
	graphics->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3D_Bonus", true);
	graphics->img = mlx_new_image(graphics->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	graphics->minimap = mlx_new_image(graphics->mlx, 200, 200);
	(1) && (para->t_no = NULL, para->t_so = NULL, para->t_ea = NULL,
		para->t_we = NULL, para->t_door = NULL);
	para->t_no = mlx_load_png(para->north);
	para->t_so = mlx_load_png(para->south);
	para->t_ea = mlx_load_png(para->east);
	para->t_we = mlx_load_png(para->west);
	para->t_door = mlx_load_png("./assets/door.png");
	if (!para->t_no || !para->t_so || !para->t_ea || !para->t_we
		|| !para->t_door)
		clear_prog(para, 1, "can't load texture\n");
	load_pngs(para);
}

unsigned int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

int	put_txtr(mlx_image_t *img, mlx_texture_t *txtr)
{
	int				i;
	int				x;
	int				y;
	unsigned int	color;

	(1) && (i = 0, y = -1);
	while (++y < (int)img->height)
	{
		x = -1;
		while (++x < (int)img->width)
		{
			color = get_rgba(txtr->pixels[i], txtr->pixels[i + 1], \
					txtr->pixels[i + 2], txtr->pixels[i + 3]);
			mlx_put_pixel(img, x, y, color);
			i += 4;
		}
	}
	return (1);
}

void	clr_img(mlx_image_t *img, int width, int height)
{
	int			x;
	int			y;
	uint32_t	color;

	y = -1;
	while (++y < height)
	{
		x = -1;
		while (++x < width)
		{
			color = get_rgba(255, 255, 255, 0);
			mlx_put_pixel(img, x, y, color);
		}
	}
}
