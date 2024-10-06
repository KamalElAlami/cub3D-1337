/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kael-ala <kael-ala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 02:37:09 by kael-ala          #+#    #+#             */
/*   Updated: 2024/10/06 02:14:02 by kael-ala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int check_player(char *line, int *player)
{
    int i = 0;
    while (line[i])
    {
        if (line[i] == 'N' || line[i] == 'S' || line[i] == 'E' || line[i] == 'W')
            *player += 1;
        i++;
    }
    return (0);
}

int map_size(char **map)
{
    int i = 0;
    while (map[i])
        i++;
    return (i);
}

int check_map(char **map)
{
    int i = 0;
    int player = 0;
    
    if (!map)
        return (1);
    while (map[0][i])
    {
        if (map[0][i] != '1' && map[0][i] != '\n')
            return (1);
        i++;
    }
    i = 0;
    while (map[map_size(map) - 1][i])
    {
        if (map[map_size(map) - 1][i] != '1')
            return (1);
        i++;
    }
    i = 0;
    while (map[i])
    {
        if (map[i][0] != '1' || map[i][ft_strlen(map[i]) - 2] != '1')
            return (1);
        check_player(map[i], &player);
        i++;
    }
    if (player > 1 || player <= 0)
        return (1);
    return (0);
}

int validate_inputs(t_params *params)
{
    if (!params->north || !params->south || !params->west || !params->east)
        return (1);
    if (params->ciel[0] < 0 || params->ciel[0] > 255 || params->ciel[1] < 0 || params->ciel[1] > 255 || params->ciel[2] < 0 || params->ciel[2] > 255)
        return (1);
    if (params->floor[0] < 0 || params->floor[0] > 255 || params->floor[1] < 0 || params->floor[1] > 255 || params->floor[2] < 0 || params->floor[2] > 255)
        return (1);
    if (check_map(params->map))
        return (1);
    return (0);
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
    (*parameters)->map = malloc(sizeof(char *) * get_map_size(path) + 1);
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
    (*parameters)->map[i] = NULL;
    return (0);
}

int main(int ac, char **av)
{
    t_params *params;
    
    params = malloc(sizeof(t_params));
    if (ac != 2 || check_path(av[1]))
        return (1);
    if (check_sheet(av[1], &params) || validate_inputs(params))
        return (1);
}