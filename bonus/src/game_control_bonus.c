/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_control_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarif <sarif@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 21:00:20 by kael-ala          #+#    #+#             */
/*   Updated: 2025/01/04 22:35:33 by sarif            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	mouse_event(void *player)
{
	t_player	*playerr;
	int32_t		xmouse;
	int32_t		ymouse;
	double		differnce;

	playerr = (t_player *)player;
	mlx_get_mouse_pos(playerr->params->graph->mlx, &xmouse, &ymouse);
	differnce = xmouse - WINDOW_WIDTH / 2;
	playerr->angle += differnce * (playerr->rotspeed / 2);
	mlx_set_mouse_pos(playerr->params->graph->mlx,
		WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	if (mlx_is_mouse_down(playerr->params->graph->mlx, MLX_MOUSE_BUTTON_LEFT)
		&& !playerr->anim_it)
		playerr->anim_it = 1;
	if (playerr->anim_it)
		run_animation(playerr);
}

int	wall_coal(t_player *player, double x, double y)
{
	int	i;
	int	j;
	int	radius;

	i = floor(player->posx + x);
	j = floor(player->posy + y);
	radius = 10;
	if (i < 0 || j < 0 || i >= player->params->w_width
		|| j >= player->params->w_height)
		return (1);
	if (player->params->u_map[j / TILE_SIZE][i / TILE_SIZE] == '1'
		|| player->params->u_map[(j + radius) / TILE_SIZE]
		[(i + radius) / TILE_SIZE] == '1'
		|| player->params->u_map[(j + radius) / TILE_SIZE]
		[(i - radius) / TILE_SIZE] == '1'
		|| player->params->u_map[(j - radius) / TILE_SIZE]
		[(i + radius) / TILE_SIZE] == '1'
		|| player->params->u_map[(j - radius) / TILE_SIZE]
		[(i - radius) / TILE_SIZE] == '1')
		return (1);
	return (0);
}

static void	strafe_movement(t_player *player, double x, double y, int isright)
{
	if (!wall_coal(player, x, y) && isright)
	{
		player->posx += x;
		player->posy += y;
	}
	else if (!wall_coal(player, -x, -y) && !isright)
	{
		player->posx -= x;
		player->posy -= y;
	}
}

static void	stright_movement(t_player *p, double x, double y, int isforward)
{
	if (!wall_coal(p, x, y) && isforward)
	{
		p->posx += x;
		p->posy += y;
	}
	else if (!wall_coal(p, -x, -y) && !isforward)
	{
		p->posx -= x;
		p->posy -= y;
	}
}

void	key_hook(void *player)
{
	double		x;
	double		y;
	t_player	*p;

	p = player;
	x = cos(p->angle) * p->movespeed;
	y = sin(p->angle) * p->movespeed;
	if (mlx_is_key_down(p->params->graph->mlx, MLX_KEY_W))
		stright_movement(p, x, y, 1);
	if (mlx_is_key_down(p->params->graph->mlx, MLX_KEY_S))
		stright_movement(p, x, y, 0);
	if (mlx_is_key_down(p->params->graph->mlx, MLX_KEY_D))
		strafe_movement(p, cos(p->angle + M_PI_2) * p->movespeed,
			sin(p->angle + M_PI_2) * p->movespeed, 1);
	if (mlx_is_key_down(p->params->graph->mlx, MLX_KEY_A))
		strafe_movement(p, cos(p->angle + M_PI_2) * p->movespeed,
			sin(p->angle + M_PI_2) * p->movespeed, 0);
	if (mlx_is_key_down(p->params->graph->mlx, MLX_KEY_LEFT))
		p->angle -= p->rotspeed;
	if (mlx_is_key_down(p->params->graph->mlx, MLX_KEY_RIGHT))
		p->angle += p->rotspeed;
	if (mlx_is_key_down(p->params->graph->mlx, MLX_KEY_ESCAPE))
		clear_prog(p->params, 0, NULL);
}
