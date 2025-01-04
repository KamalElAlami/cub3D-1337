/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarif <sarif@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 21:57:37 by kael-ala          #+#    #+#             */
/*   Updated: 2025/01/04 17:33:26 by sarif            ###   ########.fr       */
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
	para->t_so = mlx_load_png(para->south);
	para->t_ea = mlx_load_png(para->east);
	para->t_we = mlx_load_png(para->west);
	if (!para->t_no || !para->t_so || !para->t_ea || !para->t_we)
		clear_prog(para, 1, "can't load texture\n");
}

void	clear_prog(t_params *p, int status, char *err)
{
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
	if (p->graph->img)
		mlx_delete_image(p->graph->mlx, p->graph->img);
	if (p->graph->mlx)
		mlx_close_window(p->graph->mlx);
	ft_malloc(0, CLEAR_END);
	exit (status);
}
