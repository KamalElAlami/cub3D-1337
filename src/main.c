/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarif <sarif@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 02:37:09 by kael-ala          #+#    #+#             */
/*   Updated: 2024/11/29 22:05:28 by sarif            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void mouse_event(void *player)
{
	t_player	*playerr;
	int32_t		xmouse;
	int32_t		ymouse;
	double 		differnce;

	playerr = (t_player *)player;
	mlx_get_mouse_pos(playerr->params->graph->mlx, &xmouse, &ymouse);
	differnce = xmouse - WINDOW_WIDTH / 2;
	playerr->angle += differnce * playerr->rotspeed;
	mlx_set_mouse_pos(playerr->params->graph->mlx, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
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
	// mlx_loop_hook(graph->mlx, draw_map, params);
	// mlx_loop_hook(graph->mlx, draw_player, playerr);
	mlx_loop_hook(graph->mlx, raycasting, playerr);
	mlx_loop_hook(graph->mlx, key_hook, playerr);
	mlx_loop_hook(graph->mlx, mouse_event, playerr);
	mlx_image_to_window(graph->mlx, graph->img, 0, 0);
	mlx_loop(graph->mlx);
}
