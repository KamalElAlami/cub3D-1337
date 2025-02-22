/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarif <sarif@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 03:29:40 by kael-ala          #+#    #+#             */
/*   Updated: 2025/01/08 00:59:28 by sarif            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	*ft_add_spaces(char *line, int size)
{
	char	*result;
	int		i;

	result = ft_malloc(size + 1, END);
	i = 0;
	while (i < size)
	{
		if (*line)
			result[i++] = *line++;
		else
			result[i++] = ' ';
	}
	result[i] = '\0';
	return (result);
}

void	adjust_map_size(t_params *p)
{
	int		len;
	int		i;
	int		max;
	char	*line;

	(1) && (len = 0, max = 0, i = 0);
	while (p->map[i])
	{
		len = ft_strlen(p->map[i]);
		if (len > max)
			max = len;
		i++;
	}
	p->u_map = ft_malloc (sizeof (char *) * (i + 1), END);
	i = 0;
	while (p->map[i])
	{
		line = ft_add_spaces(p->map[i], max);
		p->u_map[i++] = ft_strdup_gb(line);
	}
	p->u_map[i] = NULL;
}

int	fill_map(t_params *param, int fd, char *line)
{
	char	*onelinemap;

	onelinemap = NULL;
	if (!line)
		clear_prog(param, 1, "map vide\n");
	line[ft_strlen(line)] = '\n';
	while (line)
	{
		if (line[0] == '\n')
			clear_prog(param, 1, "empty line in map\n");
		onelinemap = ft_strjoin_gb(onelinemap, line);
		line = get_next_line(fd);
	}
	param->map = ft_split(onelinemap, '\n');
	adjust_map_size(param);
	check_map_validity(param);
	return (0);
}

int	ft_check_data(t_params *p)
{
	if (p->c != 1 || p->f != 1 || p->no != 1
		|| p->ea != 1 || p->we != 1 || p->so != 1)
		clear_prog(p, 1, "map data error\n");
	if (!p->north || !p->so || !p->east || !p->west)
		clear_prog(p, 1, "textures needed\n");
	if (p->ciel[0] < 0 || p->ciel[0] > 255 || p->ciel[1] < 0
		|| p->ciel[1] > 255 || p->ciel[2] < 0 || p->ciel[2] > 255)
		clear_prog(p, 1, "Something is wrong with ciel RGB Colors\n");
	if (p->floor[0] < 0 || p->floor[0] > 255 || p->floor[1] < 0
		|| p->floor[1] > 255 || p->floor[2] < 0 || p->floor[2] > 255)
		clear_prog(p, 1, "Something is wrong with Floor RGB Colors\n");
	return (0);
}

int	check_sheet(char *path, t_params *param)
{
	char	*line;

	param->fd = open(path, O_RDONLY);
	if (param->fd == -1)
		clear_prog(param, 1, "fail to open fd");
	line = get_next_line(param->fd);
	while (line)
	{
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		ft_store_data(param, ft_strtrim(line, " "), ft_strlen(line));
		if (is_map_ready(line))
			break ;
		line = get_next_line(param->fd);
	}
	if (ft_check_data(param))
		return (1);
	if (fill_map(param, param->fd, line))
		return (1);
	return (0);
}
