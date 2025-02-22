/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarif <sarif@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 02:37:09 by kael-ala          #+#    #+#             */
/*   Updated: 2025/01/06 18:51:08 by sarif            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_player(t_params *param, t_player *playerrr)
{
	int		*pos;
	char	p;

	p = get_player(param->map);
	pos = hidenseek(param->map);
	playerrr->fov = 60 * (M_PI / 180);
	playerrr->posx = (pos[1] * TILE_SIZE) - TILE_SIZE / 2;
	playerrr->posy = (pos[0] * TILE_SIZE) - TILE_SIZE / 2;
	playerrr->rotspeed = 0.02;
	playerrr->movespeed = 4.5;
	if (p == 'N')
		playerrr->angle = 3 * M_PI / 2;
	else if (p == 'S')
		playerrr->angle = M_PI / 2;
	else if (p == 'W')
		playerrr->angle = M_PI;
	else if (p == 'E')
		playerrr->angle = 0;
}

int	main(int ac, char **av)
{
	t_params	*params;
	t_graphics	*graph;
	t_player	*playerr;

	params = ft_malloc(sizeof(t_params), END);
	graph = ft_malloc(sizeof(t_graphics), END);
	playerr = ft_malloc(sizeof(t_player), END);
	params->player = playerr;
	params->graph = graph;
	playerr->params = params;
	ft_init_data(params);
	if (ac != 2 || check_path(av[1]))
		clear_prog(params, 1, "map extention error\n");
	if (check_sheet(av[1], params))
		return (1);
	initialize_graphics(graph, params);
	init_player(params, playerr);
	mlx_loop_hook(graph->mlx, raycasting, playerr);
	mlx_loop_hook(graph->mlx, key_hook, playerr);
	mlx_image_to_window(graph->mlx, graph->img, 0, 0);
	mlx_loop(graph->mlx);
}
