/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarif <sarif@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 14:32:42 by kael-ala          #+#    #+#             */
/*   Updated: 2025/01/03 00:48:56 by sarif            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	ft_is_door(t_params *params, double x, double y)
{
	int	gridx;
	int	gridy;

	gridx = (int)floor(x / TILE_SIZE);
	gridy = (int)floor(y / TILE_SIZE);
	if (gridx < 0 || gridy < 0
		|| gridx >= (params->w_width / TILE_SIZE)
		|| gridy >= (params->w_height / TILE_SIZE))
		return ;
	if (params->map[gridy][gridx] == 'D')
		params->is_door = 1;
}

int	is_wall(t_player *player, t_dda *data, int isvert)
{
	int	gridx;
	int	gridy;

	if (isvert)
	{
		gridx = (int)floor(data->xcheck / TILE_SIZE);
		gridy = (int)floor(data->yinter / TILE_SIZE);
	}
	else
	{
		gridx = (int)floor(data->xinter / TILE_SIZE);
		gridy = (int)floor(data->ycheck / TILE_SIZE);
	}
	if (gridx < 0 || gridy < 0
		|| gridx >= (player->params->w_width / TILE_SIZE)
		|| gridy >= (player->params->w_height / TILE_SIZE))
		return (1);
	if (player->params->map[gridy][gridx] == '1')
		return (1);
	if (player->params->map[gridy][gridx] == 'D')
		return (data->isdoor = 1, 1);
	return (0);
}

t_looking	raydirection(double angle)
{
	t_looking	direction;

	direction.up = (angle > M_PI);
	direction.down = !direction.up;
	direction.left = (angle > M_PI_2 && angle < 3 * M_PI_2);
	direction.right = !direction.left;
	return (direction);
}

void	init_vertical_dda(t_player *player, t_dda *data, double rayangle)
{
	t_looking	direction;

	direction = raydirection(rayangle);
	data->xinter = floor(player->posx / TILE_SIZE) * TILE_SIZE;
	if (direction.right)
		data->xinter += TILE_SIZE;
	data->yinter = player->posy
		+ ((data->xinter - player->posx) * tan(rayangle));
	data->stepx = TILE_SIZE;
	if ((direction.left && data->stepx > 0)
		|| (direction.right && data->stepx < 0))
		data->stepx = -TILE_SIZE;
	data->stepy = fabs(TILE_SIZE * tan(rayangle));
	if ((direction.up && data->stepy > 0)
		|| (direction.down && data->stepy < 0))
		data->stepy = -data->stepy;
	data->xcheck = data->xinter;
	if (direction.left)
		data->xcheck -= 1;
}

void	init_horizontal_dda(t_player *player, t_dda *data, double rayangle)
{
	t_looking	direction;

	direction = raydirection(rayangle);
	data->yinter = floor(player->posy / TILE_SIZE) * TILE_SIZE;
	if (direction.down)
		data->yinter += TILE_SIZE;
	data->xinter = player->posx
		+ ((data->yinter - player->posy) / tan(rayangle));
	data->stepy = TILE_SIZE;
	if ((direction.up && data->stepy > 0)
		|| (direction.down && data->stepy < 0))
		data->stepy = -TILE_SIZE;
	data->stepx = fabs(TILE_SIZE / tan(rayangle));
	if ((direction.left && data->stepx > 0)
		|| (direction.right && data->stepx < 0))
		data->stepx = -data->stepx;
	data->ycheck = data->yinter;
	if (direction.up)
		data->ycheck -= 1;
}
