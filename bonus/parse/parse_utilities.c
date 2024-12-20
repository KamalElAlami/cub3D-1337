/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utilities.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kael-ala <kael-ala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 21:06:51 by kael-ala          #+#    #+#             */
/*   Updated: 2024/12/20 04:37:05 by kael-ala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_store_rgb_norm(char **degits)
{
	int	i;

	i = 0;
	while (degits[i])
		if (check_rgb(degits[i++], 1))
			exit(write(2, "rgb error 1 \n", 13));
	if (i != 3)
		exit(write(2, "rgb error 2 \n", 13));
}

void	ft_store_rgb(t_params *p, char *line)
{
	char	**degits;

	if (!ft_strncmp(line, "C ", 2) && ++p->c == 1)
	{
		if (check_rgb(line + ft_avoid(line + 2) - 1, 0))
			exit (write(2, "rgb error 0 \n", 13));
		degits = ft_split(line + ft_avoid(line + 3), ',');
		ft_store_rgb_norm(degits);
		(1) && (p->ciel[0] = ft_atoi(degits[0]),
		p->ciel[1] = ft_atoi(degits[1]), p->ciel[2] = ft_atoi(degits[2]));
	}
	else if (!ft_strncmp(line, "F ", 2) && ++p->f == 1)
	{
		if (check_rgb(line + ft_avoid(line + 2) - 1, 0))
			exit (write(2, "rgb error 0 \n", 13));
		degits = ft_split(line + ft_avoid(line + 2) - 1, ',');
		ft_store_rgb_norm(degits);
		(1) && (p->floor[0] = ft_atoi(degits[0]),
		p->floor[1] = ft_atoi(degits[1]), p->floor[2] = ft_atoi(degits[2]));
	}
}

void	ft_store_data(t_params *p, char *line)
{
	line = ft_strtrim(line, " ");// leak
	if (!ft_strncmp(line, "NO ", 3) && ++p->no == 1)
		p->north = ft_strdup(line + ft_avoid(line + 3));
	else if (!ft_strncmp(line, "SO ", 3) && ++p->so)
		p->south = ft_strdup(line + ft_avoid(line + 3));
	else if (!ft_strncmp(line, "WE ", 3) && ++p->we)
		p->west = ft_strdup(line + ft_avoid(line + 3));
	else if (!ft_strncmp(line, "EA ", 3) && ++p->ea)
		p->east = ft_strdup(line + ft_avoid(line + 3));
	else
		ft_store_rgb(p, line);
}

void	ft_init_data(t_params *param)
{
	(1) && (param->north = NULL, param->east = NULL, param->south = NULL,
	param->west = NULL, param->map = NULL);
	(1) && (param->no = 0, param->ea = 0, param->so = 0, param->we = 0,
	param->c = 0, param->f = 0);
	(1) && (param->floor[0] = -1, param->floor[1] = -1, param->floor[2] = -1,
	param->ciel[0] = -1, param->ciel[1] = -1, param->ciel[2] = -1);
}

int	check_path(char *path)
{
	return (ft_strncmp(path + (ft_strlen(path) - 4), ".cub", 4));
}
