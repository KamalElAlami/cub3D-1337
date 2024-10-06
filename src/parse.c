/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kael-ala <kael-ala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 03:29:40 by kael-ala          #+#    #+#             */
/*   Updated: 2024/10/06 02:14:32 by kael-ala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int check_path(char *path)
{
    return(ft_strncmp(path + (ft_strlen(path) - 4), ".cub", 4));
}

int is_map(char *line)
{
    int i = 0;
    if (ft_strlen(line) == 1 && line[i] == '\n')
        return (1);
    while (line[i])
    {
        if (line[i] != '1' && line[i] != '0' && line[i] != ' '  && line[i] != 'S' && line[i] != 'N'  && line[i] != 'E' && line[i] != 'W' && line[i] != '\n')
            return (1);
        i++;
    }
    return (0);
}
int get_map_size(char *path)
{
    int fd;
    int size;
    char *line;

    fd = open(path, O_RDONLY);
    size = 0;
    while ((line = get_next_line(fd)))
    {
        if(!is_map(line))
            size++;
        free(line);
    }
    close(fd);
    return (size + 1);
}