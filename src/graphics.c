/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarif <sarif@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 21:57:37 by kael-ala          #+#    #+#             */
/*   Updated: 2024/11/25 22:43:54 by sarif            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"


void initialize_graphics(t_graphics *graphics, t_params *para)
{
    int *size;
    
    size = get_size(para->map);
    para->w_width = size[0] * TILE_SIZE;
    para->w_height = size[1] * TILE_SIZE;
    graphics->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "New Window", true);
    graphics->img = mlx_new_image(graphics->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
}
