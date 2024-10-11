/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kael-ala <kael-ala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 02:37:09 by kael-ala          #+#    #+#             */
/*   Updated: 2024/10/11 22:43:34 by kael-ala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int *get_size(char **map)
{
    int count;
    int *size;
    
    size = malloc(sizeof(int) * 3);
    size[0] = ft_strlen(map[0]) - 1;
    count = 0;
    while (map[count])
        count++;
    size[1] = count;
    return (size);
}

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
    uint32_t color;

    i = 0;
    while (parameters->map[i])
    {
        j = 0;
        while (parameters->map[i][j])
        {
            if (parameters->map[i][j] == '0')
                color = 0xFFFFFFFF;
            else if (parameters->map[i][j] == '1')
                color = 0x000000FF;
            else if (parameters->map[i][j] == 'N' || parameters->map[i][j] == 'S' || parameters->map[i][j] == 'E' || parameters->map[i][j] == 'W')
                color = 0xFF0000FF;
            for (int x = 0; x < 32; x++)
            {
                for (int y = 0; y < 32; y++)
                    mlx_put_pixel(graphic->img, j * 32 + x, i * 32 + y, color);
            }
            j++;
        }
        i++;
    }
}

int main(int ac, char **av)
{
    t_params *params;
    t_graphics *graph;
    
    params = malloc(sizeof(t_params));
    graph = malloc(sizeof(t_graphics));
    if (ac != 2 || check_path(av[1]))
        return (1);
    if (check_sheet(av[1], &params) || validate_inputs(params))
        return (1);
    initialize_graphics(graph, params);
    mlxdrawmap(graph, params);
    mlx_image_to_window(graph->mlx, graph->img, 0, 0);
    mlx_loop(graph->mlx);
}