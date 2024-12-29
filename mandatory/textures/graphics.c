/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarif <sarif@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 21:57:37 by kael-ala          #+#    #+#             */
/*   Updated: 2024/12/30 00:03:31 by sarif            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	initialize_graphics(t_graphics *graphics, t_params *para)
{
	int	*size;

	size = get_size(para->map);
	para->w_width = size[0] * TILE_SIZE;
	para->w_height = size[1] * TILE_SIZE;
	graphics->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "New Window", true);
	graphics->img = mlx_new_image(graphics->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
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
}
