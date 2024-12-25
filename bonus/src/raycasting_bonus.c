/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kael-ala <kael-ala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 13:30:38 by kael-ala          #+#    #+#             */
/*   Updated: 2024/12/24 21:06:32 by kael-ala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

t_rays	*fill_ray(t_player *player, double rayangle, t_dda *data, int isvert)
{
	t_rays		*temp;

	temp = malloc(sizeof(t_rays));
	temp->rayangle = rayangle;
	temp->hitx = data->xinter;
	temp->hity = data->yinter;
	temp->is_horizontal = !isvert;
	temp->is_vertical = isvert;
	temp->distance = sqrt(pow(data->xinter - player->posx, 2)
			+ pow(data->yinter - player->posy, 2));
	return (temp);
}

t_rays	*vertical_distance(t_player *playerr, double rayangle)
{
	t_dda		data;
	t_looking	direction;

	direction = raydirection(rayangle);
	init_vertical_dda(playerr, &data, rayangle);
	while (1)
	{
		if (is_wall(playerr->params, data.xcheck, data.yinter)
			|| is_out(playerr->params, data.xinter, data.yinter))
			break ;
		data.xinter += data.stepx;
		data.yinter += data.stepy;
		data.xcheck = data.xinter;
		if (direction.left)
			data.xcheck -= 1;
	}
	return (fill_ray(playerr, rayangle, &data, 1));
}

t_rays	*horizontal_distance(t_player *playerr, double rayangle)
{
	t_looking	direction;
	t_dda		data;
	t_rays		*temp;

	temp = malloc(sizeof(t_rays));
	direction = raydirection(rayangle);
	init_horizontal_dda(playerr, &data, rayangle);
	while (1)
	{
		if (is_wall(playerr->params, data.xinter, data.ycheck)
			|| is_out(playerr->params, data.xinter, data.yinter))
			break ;
		data.xinter += data.stepx;
		data.yinter += data.stepy;
		data.ycheck = data.yinter;
		if (direction.up)
			data.ycheck -= 1;
	}
	return (fill_ray(playerr, rayangle, &data, 0));
}

t_rays	*raydistance(t_player *playerr, double rayangle)
{
	t_rays	*vertical;
	t_rays	*horizontal;

	vertical = vertical_distance(playerr, rayangle);
	horizontal = horizontal_distance(playerr, rayangle);
	if (horizontal->distance < vertical->distance)
		return (horizontal);
	else
		return (vertical);
}

void	raycasting(void *playerr)
{
	t_player	*player;
	double		rayangle;
	double		increament;
	int			i;

	i = 0;
	player = playerr;
	rayangle = player->angle - (player->fov / 2);
	increament = player->fov / WINDOW_WIDTH;
	player->ray = malloc(sizeof(t_rays));
	while (i < WINDOW_WIDTH)
	{
		rayangle = normalize_angle(rayangle);
		player->ray = raydistance(player, rayangle);
		player->ray->distance = player->ray->distance
			* cos(player->angle - player->ray->rayangle);
		render_wall(player, i);
		rayangle += increament;
		i++;
	}
}
