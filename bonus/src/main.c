/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarif <sarif@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 02:37:09 by kael-ala          #+#    #+#             */
/*   Updated: 2024/12/28 23:42:39 by sarif            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	close_door(t_player *player, int player_y, int player_x)
{
	t_player	*p;
	int			i;
	int			j;
	float		close_distance;
	float		distance;

	(1) && (i = -1, close_distance = 2.0, p = (t_player *)player);

	while (++i < p->params->map_height)
	{
		j = -1;
		while (++j < p->params->map_width)
		{
			if (p->params->map[i][j] == 'O')
			{
				distance = sqrt(pow(player_x - j, 2) + pow(player_y - i, 2));
				if (distance > close_distance)
					p->params->map[i][j] = 'D';
			}
		}
	}
}

void	open_close_door(void *player)
{
	int			i;
	int			j;
	t_player	*p;

	p = (t_player *)player;
	i = p->posy / TILE_SIZE;
	j = p->posx / TILE_SIZE;

	if (j > 0 && p->params->map[i][j - 1] == 'D')
		p->params->map[i][j - 1] = 'O';

	if (j < p->params->map_width - 1 && p->params->map[i][j + 1] == 'D')
		p->params->map[i][j + 1] = 'O';

	if (i > 0 && p->params->map[i - 1][j] == 'D')
		p->params->map[i - 1][j] = 'O';

	if (i < p->params->map_height - 1 && p->params->map[i + 1][j] == 'D')
		p->params->map[i + 1][j] = 'O';
	close_door(player, i, j);
}

unsigned int  whichcolor(t_player *player, int x, int y)
{
	if (player->params->map[y][x] == '1')
		return (0x000000FF);
	if (player->params->map[y][x] == 'N' || player->params->map[y][x] == 'S'
		|| player->params->map[y][x] == 'W' || player->params->map[y][x] == 'E')
		return (0xE7625FFF);
	else
		return (0xFEEAD3FF);
}

void mini_map(void *player)
{
	unsigned int color;
	int mapsize = 200;
	t_player *p;
	double startx;
	double starty;
	double endx;
	double endy;
	int x;
	int y;

	p = (t_player *)player;

	if (p->posx < mapsize/2)
		startx = 0;
	else
		startx = p->posx - mapsize/2;
	if (p->posx + mapsize/2 > p->params->w_width)
		endx = p->params->w_width;
	else
		endx = p->posx + mapsize/2;
	if (p->posy < mapsize/2)
		starty = 0;
	else
		starty = p->posy - mapsize/2;

	if (p->posy + mapsize/2 > p->params->w_height)
		endy =  p->params->w_height;
	else
		endy = p->posy + mapsize/2;
	x = startx;
	y = starty;

	while (y < endy)
	{
		x = startx;
		while (x < endx)
		{
			color = whichcolor(p, x / TILE_SIZE, y / TILE_SIZE);
			mlx_put_pixel(p->params->graph->minimap, x - startx, y - starty, color);
			x++;	
		}
		y++;
	}

}

void	init_player(t_params *param, t_player *playerrr)
{
	int		*pos;
	char	p;

	playerrr->pv = mlx_new_image(param->graph->mlx, PV_HEIGHT, PV_WIDTH);
	if (!playerrr->pv)
		exit(1); // TODO : free and exit
	p = get_player(param->map);
	pos = hidenseek(param->map);
	playerrr->fov = 60 * (M_PI / 180);
	playerrr->posx = (pos[1] * TILE_SIZE) - TILE_SIZE / 2;
	playerrr->posy = (pos[0] * TILE_SIZE) - TILE_SIZE / 2;
	playerrr->rotspeed = 0.02;
	playerrr->movespeed = 4.5;
	param->map_width = ft_strlen(param->map[0]);
	param->map_height = map_size(param->map);
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
	playerr->anim_it = 0;
	initialize_graphics(graph, params);
	params->graph = graph;
	playerr->params = params;
	init_player(params, playerr);
	mlx_loop_hook(graph->mlx, raycasting, playerr);
	mlx_loop_hook(graph->mlx, key_hook, playerr);
	mlx_loop_hook(graph->mlx, mouse_event, playerr);
	mlx_loop_hook(graph->mlx, mini_map, playerr);
	mlx_loop_hook(graph->mlx, open_close_door, playerr) ;
	mlx_image_to_window(graph->mlx, graph->img, 0, 0);
	mlx_image_to_window(graph->mlx, graph->minimap, 0, 520);
	mlx_image_to_window(graph->mlx, playerr->pv, 350, 220);
	put_txtr(playerr->pv, params->frames_t[0], graph->mlx);
	mlx_set_cursor_mode(graph->mlx, MLX_MOUSE_HIDDEN);
	mlx_loop(graph->mlx);
}
