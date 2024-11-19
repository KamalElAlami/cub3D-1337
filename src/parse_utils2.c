/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarif <sarif@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 03:20:19 by sarif             #+#    #+#             */
/*   Updated: 2024/11/19 03:14:06 by sarif            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	map_size(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

void	check_m_lines(t_params *p)
{
	int	i;
	int	len;

	i = 0;
	while (p->map[++i])
	{
		len = ft_strlen(p->map[i]) - 1;
		if (p->map[i][0] != '1' || p->map[i][len] != '1')
		{
			printf("line :[%s]\nthe first char is {%c} and the second one is {%c}\nthe len is %d\n", p->map[i], p->map[i][0], p->map[i][len], len);	
			exit(write(2, "middle lines error\n", 19));
		}
	}
}

void	check_f_l_line(t_params *p)
{
	int	i;
	int	size;

	(1) && (i = -1, size = map_size(p->map) - 1);
	while (p->map[0][++i])
	{
		if (p->map[0][i] != '1' && p->map[0][i] != ' ')
			exit(write(2, "first line error\n", 18));
	}
	i = -1;
	while (p->map[size][++i])
	{
		if (p->map[size][i] != '1' && p->map[size][i] != 32)
			exit(write(2, "last line error\n", 18));
	}
}

// void	check_zero(char *line, char *previous, char *next)
// {
// 	int	i;

// 	i = 0;
// 	while (line[i])
// 	{
// 		if (line[i] == '0' && line[i + 1] )
// 	}
// }

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
			if ((p->uni_map[j][i] == '0' || p->uni_map[j][i] == 'P') &&
				(p->uni_map[j][i + 1] == 32 || p->uni_map[j][i + 1] == 0)) // right
				exit(write(2, "ERROR\n", 6));
			if ((p->uni_map[j][i] == '0' || p->uni_map[j][i] == 'P') &&
				(i == 0 || p->uni_map[j][i - 1] == 32)) // left
				exit(write(2, "ERROR\n", 6));
			if ((p->uni_map[j][i] == '0' || p->uni_map[j][i] == 'P') &&
				(j == 0 || p->uni_map[j - 1][i] == 32)) // up
				exit(write(2, "ERROR\n", 6));
			if ((p->uni_map[j][i] == '0' || p->uni_map[j][i] == 'P') &&
				(j == map_size(p->uni_map) - 1 || p->uni_map[j + 1][i] == 32)) // down
				exit(write(2, "ERROR\n", 6));
		}
	}
	// check_f_l_line(p);
	// check_m_lines(p);
}
