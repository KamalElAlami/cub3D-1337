/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarif <sarif@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 01:16:22 by sarif             #+#    #+#             */
/*   Updated: 2024/12/04 00:44:49 by sarif            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// uint32_t	ft_get_pixel(t_player *p, int y, double top)
// {
// 	int	x_offset;
// 	int	y_offset;
// 	mlx_texture_t *tex = p->params->t_no;
// 	uint32_t	position;

// 	// printf("%d\n",p->params->w_height);

// 	if (p->ray->is_vertical)
// 		x_offset = (int)p->ray->hity % TILE_SIZE;
// 	else
// 		x_offset = (int)p->ray->hitx % TILE_SIZE;
// 	y_offset = (y + (top / 2) - (WINDOW_HEIGHT / top)) * ((double)tex->height / top);
// 	position = (y_offset * tex->width * tex->bytes_per_pixel) + (x_offset * tex->bytes_per_pixel);
// 	if (position < 0 || position >= tex->width * tex->height * 4)
//     	return (0);
// 	return(tex->pixels[position] << 24 | tex->pixels[position + 1] << 16 | tex->pixels[position + 2] << 8 | tex->pixels[position + 3]);
// }
