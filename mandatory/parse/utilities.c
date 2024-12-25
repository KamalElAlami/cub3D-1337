/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kael-ala <kael-ala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 22:04:03 by kael-ala          #+#    #+#             */
/*   Updated: 2024/12/25 16:33:27 by kael-ala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	*get_size(char **map)
{
	int	count;
	int	*size;

	size = malloc(sizeof(int) * 3);
	size[0] = ft_strlen(map[0]) + 1;
	count = 0;
	while (map[count])
		count++;
	size[1] = count;
	return (size);
}

int	*hidenseek(char **map)
{
	int	i;
	int	j;
	int	*location;

	i = 0;
	location = malloc(sizeof(int) * 3);
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S'
				|| map[i][j] == 'W' || map[i][j] == 'E')
			{
				location[0] = i + 1;
				location[1] = j + 1;
				return (location);
			}
			j++;
		}
		i++;
	}
	return (NULL);
}

char	get_player(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S'
				|| map[i][j] == 'E' || map[i][j] == 'W')
				return (map[i][j]);
			j++;
		}
		i++;
	}
	return ('x');
}

uint32_t	rgb_hex(int r, int g, int b)
{
	return (0xFF000000 | (r << 16) | (g << 8) | b);
}

double	normalize_angle(double angle)
{
	angle = fmod(angle, 2 * M_PI);
	if (angle < 0)
		angle += (2 * M_PI);
	return (angle);
}
