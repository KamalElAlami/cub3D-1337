/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarif <sarif@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 14:32:42 by kael-ala          #+#    #+#             */
/*   Updated: 2024/12/14 16:09:43 by sarif            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	is_wall(t_params *params, double x, double y)
{
	int	gridx;
	int	gridy;

	gridx = (int)floor(x / TILE_SIZE);
	gridy = (int)floor(y / TILE_SIZE);
	if (gridx < 0 || gridy < 0
		|| gridx >= (params->w_width / TILE_SIZE)
		|| gridy >= (params->w_height / TILE_SIZE))
		return (1);
	if (params->map[gridy][gridx] == '1')
		return (1);
	return (0);
}

double	normalize_angle(double angle)
{
	angle = fmod(angle, 2 * M_PI);
	if (angle < 0)
		angle += (2 * M_PI);
	return (angle);
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
