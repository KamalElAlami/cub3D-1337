/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarif <sarif@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 02:37:09 by kael-ala          #+#    #+#             */
/*   Updated: 2025/01/07 23:12:32 by sarif            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	init_player(t_params *param, t_player *playerrr)
{
	int		*pos;
	char	p;

	playerrr->pv = mlx_new_image(param->graph->mlx, PV_HEIGHT, PV_WIDTH);
	if (!playerrr->pv)
		clear_prog(param, 1, "can't load image\n");
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

void	ft_loop_hook(mlx_t *mlx, t_player *player)
{
	mlx_loop_hook(mlx, raycasting, player);
	mlx_loop_hook(mlx, key_hook, player);
	mlx_loop_hook(mlx, mouse_event, player);
	mlx_loop_hook(mlx, mini_map, player);
	mlx_loop_hook(mlx, open_close_door, player);
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
	ft_loop_hook(graph->mlx, playerr);
	mlx_image_to_window(graph->mlx, graph->img, 0, 0);
	mlx_image_to_window(graph->mlx, graph->minimap, 0, 520);
	mlx_image_to_window(graph->mlx, playerr->pv, 350, 220);
	put_txtr(playerr->pv, params->frames_t[0]);
	mlx_set_cursor_mode(graph->mlx, MLX_MOUSE_HIDDEN);
	mlx_loop(graph->mlx);
}
