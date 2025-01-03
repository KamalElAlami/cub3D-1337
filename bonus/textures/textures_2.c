/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarif <sarif@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 00:23:41 by sarif             #+#    #+#             */
/*   Updated: 2025/01/03 00:49:37 by sarif            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	run_animation(t_player *player)
{
	static int	i;
	static int	cnt;

	if (i >= 22)
	{
		i = 0;
		player->anim_it = 0;
		clr_img(player->pv, WINDOW_WIDTH, WINDOW_HEIGHT);
		put_txtr(player->pv, player->params->frames_t[0]);
	}
	if (cnt == 6 && i < 22)
	{
		clr_img(player->pv, WINDOW_WIDTH, WINDOW_HEIGHT);
		put_txtr(player->pv, player->params->frames_t[i]);
		i++;
		cnt = 0;
	}
	cnt++;
}

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
