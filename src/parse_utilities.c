/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utilities.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kael-ala <kael-ala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 21:06:51 by kael-ala          #+#    #+#             */
/*   Updated: 2024/10/08 21:07:32 by kael-ala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void stock_map(char *path, t_params **parameters)
{
    int fd;
    char *line;
    int i;
    
    i = 0;
    fd = open(path, O_RDONLY);
    if (fd == -1)
        return ;
    (*parameters)->map = malloc(sizeof(char *) * get_map_size(path) + 1);
    if (!(*parameters)->map)
        return ;
    line = get_next_line(fd);
    while (line)
    {
        if (!is_map(line))
        {
            while (line)
            {
                (*parameters)->map[i++] = ft_strdup(line);
                line = get_next_line(fd);
                if (!line)
                    break ;
            }
        }
        line = get_next_line(fd);
    }
    (*parameters)->map[i] = NULL;
}

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