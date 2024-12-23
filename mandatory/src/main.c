/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kael-ala <kael-ala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 02:37:09 by kael-ala          #+#    #+#             */
/*   Updated: 2024/12/23 22:13:57 by kael-ala         ###   ########.fr       */
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
	printf("x = %f\ny = %f\n", playerrr->posx, playerrr->posy);
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

	params = malloc(sizeof(t_params));
	graph = malloc(sizeof(t_graphics));
	playerr = malloc(sizeof(t_player));
	if (ac != 2 || check_path(av[1]))
		return (write(2, "map extention error\n", 20), 1);
	ft_init_data(params);
	if (check_sheet(av[1], params))
		return (1);
	initialize_graphics(graph, params);
	init_player(params, playerr);
	params->graph = graph;
	playerr->params = params;
	mlx_loop_hook(graph->mlx, raycasting, playerr);
	mlx_loop_hook(graph->mlx, key_hook, playerr);
	mlx_image_to_window(graph->mlx, graph->img, 0, 0);
	mlx_loop(graph->mlx);
}
