/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarif <sarif@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 03:20:19 by sarif             #+#    #+#             */
/*   Updated: 2025/01/08 01:21:20 by sarif            ###   ########.fr       */
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
					clear_prog(p, 1, "not a valid door\n");
			}
		}
	}
}

int	is_player(t_params *p, char c, int flag)
{
	static int	i;

	if (flag)
	{
		if ((c == 'N' || c == 'W' || c == 'S' || c == 'E') && ++i)
		{
			if (i > 4)
				clear_prog(p, 1, "more than 1 player\n");
			else
				return (1);
		}
		else if (c != '1' && c != '0' && c != ' ' && c != 'D')
			clear_prog(p, 1, "forbidden charchter\n");
		else
			return (0);
	}
	else
		if (i == 0)
			clear_prog(p, 1, "player missing\n");
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

static int	check_d(int j, int i, t_params *p)
{
	if (p->u_map[j][i] == '0' || p->u_map[j][i] == 'D')
		return (1);
	return (0);
}

void	check_map_validity(t_params *p)
{
	int	i;
	int	j;

	j = -1;
	while (p->u_map[++j])
	{
		i = -1;
		while (p->u_map[j][++i])
		{
			if ((check_d(j, i, p) || is_player(p, p->u_map[j][i], 1))
				&& (p->u_map[j][i + 1] == 32 || p->u_map[j][i + 1] == 0))
				clear_prog(p, 1, "map invalid\n");
			else if ((check_d(j, i, p) || is_player(p, p->u_map[j][i], 1))
				&& (i == 0 || p->u_map[j][i - 1] == 32))
				clear_prog(p, 1, "map invalid\n");
			else if ((check_d(j, i, p) || is_player(p, p->u_map[j][i], 1))
				&& (j == 0 || p->u_map[j - 1][i] == 32))
				clear_prog(p, 1, "map invalid\n");
			else if ((check_d(j, i, p) || is_player(p, p->u_map[j][i], 1))
				&& (j == map_size(p->u_map) - 1 || p->u_map[j + 1][i] == 32))
				clear_prog(p, 1, "map invalid\n");
		}
	}
	is_player(p, 0, 0);
	check_doors_validity(p);
}
