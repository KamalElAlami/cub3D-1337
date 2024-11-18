/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarif <sarif@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 11:50:26 by sarif             #+#    #+#             */
/*   Updated: 2024/11/17 17:16:34 by sarif            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	is_all_blank(char *line)
{
	while (*line)
		if (!ft_isblank(*line++))
			return (0);
	return (1);
}

int	is_map_ready(char *line)
{
	if (!line[0] || is_all_blank(line))
		return (write(2,"1\n",2),0);
	if (!ft_strncmp(line, "NO ", 3) || !ft_strncmp(line, "SO ", 3)
		|| !ft_strncmp(line, "WE ", 3) || !ft_strncmp(line, "EA ", 3)
		|| !ft_strncmp(line, "C ", 2) || !ft_strncmp(line, "F ", 2))
		return (write(2,"2\n",2),0);
	return (write(2,"3\n",2),1);
}

int	check_rgb(char *line, int flag)
{
	int	i;

	i = 0;
	if (flag == 1)
	{
		while (*line)
		{
			if (!ft_isdigit(*line))
				return (1);
			line++;
		}
		return (0);
	}
	else if (flag == 0)
	{
		while (*line)
		{
			if (*line == ',')
				i++;
			line++;
		}
		if (i != 2)
			return (1);
	}
	return (0);
}

int	ft_isblank(char c)
{
	if (c == 32)
		return (1);
	return (0);
}

int	ft_avoid(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (ft_isblank(line[i]))
			i++;
		else
			break ;
	}
	return (i + 3);
}
