/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarif <sarif@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 00:42:42 by sarif             #+#    #+#             */
/*   Updated: 2025/01/05 15:44:55 by sarif            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

unsigned int	whichcolor(t_player *player, int x, int y)
{
	if (player->params->u_map[y][x] == '1')
		return (0x000000FF);
	else
		return (0xFEEAD3FF);
}

static void	ft_mlx_put_pixel(mlx_image_t *image, int x, int y, uint32_t color)
{
	if (x > MINI_MAP || y > MINI_MAP)
		return ;
	mlx_put_pixel(image, x, y, color);
}

void	draw_player(t_player *p, t_minimap *mini)
{
	int	radius;
	int	x;
	int	y;

	x = 0;
	radius = 10;
	while (x <= radius)
	{
		y = 0;
		while (y <= radius)
		{
			ft_mlx_put_pixel(p->params->graph->minimap,
				(mini->posx - mini->startx) + x,
				(mini->posy - mini->starty) + y, 0xFF0000FF);
			y++;
		}
		x++;
	}
}

void	init_minimap(t_minimap *mini, t_player *player)
{
	mini->w_width = player->params->w_width * ((float)MINI_SCALE / TILE_SIZE);
	mini->w_height = player->params->w_height * ((float)MINI_SCALE / TILE_SIZE);
	mini->posx = player->posx * ((float)MINI_SCALE / TILE_SIZE);
	mini->posy = player->posy * ((float)MINI_SCALE / TILE_SIZE);
	if (mini->w_width > MINI_MAP || mini->w_height > MINI_MAP)
	{
		mini->startx = fmax(0, mini->posx - (MINI_MAP / 2));
		mini->endx = fmin(mini->w_width, mini->posx + (MINI_MAP / 2));
		mini->starty = fmax(0, mini->posy - (MINI_MAP / 2));
		mini->endy = fmin(mini->w_height, mini->posy + (MINI_MAP / 2));
		if (mini->endx == mini->w_width)
			mini->startx = mini->endx - MINI_MAP;
		if (mini->endy == mini->w_height)
			mini->starty = mini->endy - MINI_MAP;
		if (mini->startx == 0)
			mini->endx = mini->w_width;
		if (mini->starty == 0)
			mini->endy = mini->w_height;
	}
	else
	{
		(1) && (mini->startx = 0, mini->starty = 0);
		mini->endx = mini->w_width;
		mini->endy = mini->w_height;
	}
}

void	mini_map(void *player)
{
	t_minimap		*mini;
	unsigned int	color;
	t_player		*p;
	int				x;
	int				y;

	color = 0;
	p = (t_player *)player;
	mini = ft_malloc(sizeof(t_minimap), END);
	init_minimap(mini, p);
	y = mini->starty;
	clr_img(p->params->graph->minimap, MINI_MAP, MINI_MAP);
	while (y < mini->endy)
	{
		x = mini->startx;
		while (x < mini->endx)
		{
			color = whichcolor(p, x / MINI_SCALE, y / MINI_SCALE);
			ft_mlx_put_pixel(p->params->graph->minimap,
				x - mini->startx, y - mini->starty, color);
			x++;
		}
		y++;
	}
	draw_player(p, mini);
}
