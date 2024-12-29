/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarif <sarif@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 03:20:19 by sarif             #+#    #+#             */
/*   Updated: 2024/12/30 00:12:21 by sarif            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	check_doors_validity(t_params *p)
{
	char	**map;
	int		i;
	int		j;

	map = p->map;
	j = -1;
	while (map[++j])
	{
		i = -1;
		while (map[j][++i])
		{
			if (map[j][i] == 'D')
			{
				if (!((i > 0 && i < (int)ft_strlen(map[j]) - 1
							&& map[j][i - 1] == '1' && map[j][i + 1] == '1')
					|| (j > 0 && map[j - 1][i] == '1' && map[j + 1]
					&& map[j + 1][i] == '1')))
				{
					exit(write(2, "not a valid door\n", 17));
				}
			}
		}
	}
}

int	ft_is_player(char c, int flag)
{
	static int	i;

	if (flag)
	{
		if ((c == 'N' || c == 'W' || c == 'S' || c == 'E') && ++i)
		{
			if (i > 4)
				exit(write(2, "more than 1 player\n", 19));
			else
				return (1);
		}
		else if (c != '1' && c != '0' && c != ' ' && c != 'D')
			exit (write(2, "forbidden charchter\n", 20));
		else
			return (0);
	}
	else
		if (i == 0)
			exit(write(2, "player missing\n", 16));
	return (0);
}

int	map_size(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

void	check_map_validity(t_params *p)
{
	int	i;
	int	j;

	j = -1;
	while (p->uni_map[++j])
	{
		i = -1;
		while (p->uni_map[j][++i])
		{
			if ((p->uni_map[j][i] == '0' || ft_is_player(p->uni_map[j][i], 1)) &&
				(p->uni_map[j][i + 1] == 32 || p->uni_map[j][i + 1] == 0)) // right
				exit(write(2, "ERROR\n", 6));
			else if ((p->uni_map[j][i] == '0' || ft_is_player(p->uni_map[j][i], 1)) &&
				(i == 0 || p->uni_map[j][i - 1] == 32)) // left
				exit(write(2, "ERROR\n", 6));
			else if ((p->uni_map[j][i] == '0' || ft_is_player(p->uni_map[j][i], 1)) &&
				(j == 0 || p->uni_map[j - 1][i] == 32)) // up
				exit(write(2, "ERROR\n", 6));
			else if ((p->uni_map[j][i] == '0' || ft_is_player(p->uni_map[j][i], 1)) &&
				(j == map_size(p->uni_map) - 1 || p->uni_map[j + 1][i] == 32)) // down
				exit(write(2, "ERROR\n", 6));
		}
	}
	ft_is_player(0, 0);
	check_doors_validity(p);
}