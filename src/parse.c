/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarif <sarif@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 03:29:40 by kael-ala          #+#    #+#             */
/*   Updated: 2024/11/21 12:40:25 by sarif            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	*ft_add_spaces(char *line, int size)
{
	char	*result;
	int		i;

	result = malloc(size + 1);
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
	p->uni_map = malloc (sizeof (char *) * i + 1);
	i = 0;
	while (p->map[i])
	{
		line = ft_add_spaces(p->map[i], max);
		p->uni_map[i++] = ft_strdup(line);
	}
	p->uni_map[i] = NULL;
	// for (i = 0; p->uni_map[i]; i++)
	// 	printf("[%s]\n",p->uni_map[i]);
}

int	fill_map(t_params *param, int fd, char *line)
{
	char	*onelinemap;

	onelinemap = NULL;
	if (!line)
		exit (write (2,"map vide\n",9));
	line[ft_strlen(line)] = '\n';// to check it later
	while (line)
	{
		if (line[0] == '\n')
			exit(write(2,"empty line in map\n",18));
		onelinemap = ft_strjoin(onelinemap, line);
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
		return (write(2, "map data error\n", 15), 1);
	if (!p->north || !p->so || !p->east || !p->west)
		return (write(2, "textures needed\n", 16), 1);
	if (p->ciel[0] < 0 || p->ciel[0] > 255 || p->ciel[1] < 0
		|| p->ciel[1] > 255 || p->ciel[2] < 0 || p->ciel[2] > 255)
		return (write(1, "Something is wrong with ciel RGB Colors\n", 42), 1);
	if (p->floor[0] < 0 || p->floor[0] > 255 || p->floor[1] < 0
		|| p->floor[1] > 255 || p->floor[2] < 0 || p->floor[2] > 255)
		return (write(1, "Something is wrong with Floor RGB Colors\n", 42), 1);
	return (0);
}

int	check_sheet(char *path, t_params *param)
{
	int		fd;
	char	*line;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (write(2, "fail to open fd", 15), 1);
	line = get_next_line(fd);
	while (line)
	{
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		ft_store_data(param, line);
		if (is_map_ready(line))
			break ;
		line = get_next_line(fd);
	}
	if (ft_check_data(param))
		return (1);
	if (fill_map(param, fd, line))
		return (1);
	return (0);
}
