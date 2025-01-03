/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarif <sarif@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 03:20:19 by sarif             #+#    #+#             */
/*   Updated: 2025/01/03 00:06:55 by sarif            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	is_player(char c, int flag, t_params *p)
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
		else if (c != '1' && c != '0' && c != ' ')
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
			if ((p->u_map[j][i] == '0' || is_player(p->u_map[j][i], 1, p))
				&& (p->u_map[j][i + 1] == 32 || p->u_map[j][i + 1] == 0))
				clear_prog(p, 1, "invalid map\n");
			else if ((p->u_map[j][i] == '0' || is_player(p->u_map[j][i], 1, p))
				&& (i == 0 || p->u_map[j][i - 1] == 32))
				clear_prog(p, 1, "invalid map\n");
			else if ((p->u_map[j][i] == '0' || is_player(p->u_map[j][i], 1, p))
				&& (j == 0 || p->u_map[j - 1][i] == 32))
				clear_prog(p, 1, "invalid map\n");
			else if ((p->u_map[j][i] == '0' || is_player(p->u_map[j][i], 1, p))
				&& (j == map_size(p->u_map) - 1 || p->u_map[j + 1][i] == 32))
				clear_prog(p, 1, "invalid map\n");
		}
	}
	is_player(0, 0, p);
}
