/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kael-ala <kael-ala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 02:26:06 by kael-ala          #+#    #+#             */
/*   Updated: 2024/10/11 22:48:42 by kael-ala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

# include "../libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <math.h>
# include <fcntl.h>
# include "../MLX42/include/MLX42/MLX42.h"

typedef struct s_player
{
    double posx;
    double posy;
} t_player;

typedef struct s_graphics {
    mlx_t* mlx;
    mlx_image_t* img;
} t_graphics;

typedef struct s_params
{
    char *north;
    char *south;
    char *west;
    char *east;
    int ciel[3];
    int floor[3];
    char **map;
}   t_params;

int		check_path(char *path);
int     is_map(char *line);
int     get_map_size(char *path);
void    stock_map(char *path, t_params **parameters);
int     check_player(char *line, int *player);
int     map_size(char **map);
int     check_map(char **map);
int     validate_inputs(t_params *params);
int     check_sheet(char *path, t_params **parameters);

#endif