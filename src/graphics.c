/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kael-ala <kael-ala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 21:57:37 by kael-ala          #+#    #+#             */
/*   Updated: 2024/10/14 04:35:35 by kael-ala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"


void initialize_graphics(t_graphics *graphics, t_params *para)
{
    int *size; 
    
    size = get_size(para->map);
    graphics->mlx = mlx_init(size[0] * 32, size[1] * 32, "New Window", true);
    graphics->img = mlx_new_image(graphics->mlx, size[0] * 32, size[1] * 32);
}


void mlxdrawmap(t_graphics *graphic, t_params *parameters)
{
    int i;
    int j;
    int x;
    int y;
    uint32_t color;

    i = 0;
    while (parameters->map[i])
    {
        j = 0;
        while (parameters->map[i][j])
        {
            if (parameters->map[i][j] == '1' || parameters->map[i][j] == '\n')
                color = 0x000000FF;
            else
                color = 0xFFFFFFFF;
            x = 0;
            while (x < 32)
            {
                y = 0;
                while (y < 32)
                {
                    mlx_put_pixel(graphic->img, j * 32 + x, i * 32 + y, color);
                    y++;
                }
                x++;
            }
            j++;
        }
        i++;
    }
}


void draw_map(void *ptr) {
    t_params   *p = ptr;

    mlxdrawmap(p->graph, p);
}