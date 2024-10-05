/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kael-ala <kael-ala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 02:37:09 by kael-ala          #+#    #+#             */
/*   Updated: 2024/10/05 16:48:49 by kael-ala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
int count_map(char *line)
{
    int count;

    count = 0;
    while (*line)
    {
        if (*line == '1')
            count++;
        line++;
    }
    return (count);
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
    return (size);
}

int check_sheet(char *path, t_params **parameters)
{
    int fd;
    char *line;
    char **degits;
    int i = 0;

    fd = open(path, O_RDONLY);
    if (fd == -1)
        return (1);
    (*parameters)->map = malloc(sizeof(char *) * get_map_size(path));
    if (!(*parameters)->map)
        return (1);
    while ((line = get_next_line(fd)))
    {
        if (ft_strncmp(line, "NO ", 3) == 0)
            (*parameters)->north = ft_strdup(line + 3);
        else if (ft_strncmp(line, "SO ", 3) == 0)
            (*parameters)->south = ft_strdup(line + 3);
        else if (ft_strncmp(line, "WE ", 3) == 0)
            (*parameters)->west = ft_strdup(line + 3);
        else if (ft_strncmp(line, "EA ", 3) == 0)
            (*parameters)->east = ft_strdup(line + 3);
        else if (ft_strncmp(line, "F ", 2) == 0)
        {
            degits = ft_split(line + 2, ',');
            (*parameters)->floor[0] = ft_atoi(degits[0]);
            (*parameters)->floor[1] = ft_atoi(degits[1]);
            (*parameters)->floor[2] = ft_atoi(degits[2]);
        }
        else if (ft_strncmp(line, "C ", 2) == 0)
        {
            degits = ft_split(line + 2, ',');
            (*parameters)->ciel[0] = ft_atoi(degits[0]);
            (*parameters)->ciel[1] = ft_atoi(degits[1]);
            (*parameters)->ciel[2] = ft_atoi(degits[2]);
        }
        else if (!is_map(line))
            (*parameters)->map[i++] = ft_strdup(line);
    }
    return (0);
}

int main(int ac, char **av)
{
    t_params *params;
    
    params = malloc(sizeof(t_params));
    if (ac != 2 || check_path(av[1]))
        return (1);
    if (check_sheet(av[1], &params))
        return (1);
}