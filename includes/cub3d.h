/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kael-ala <kael-ala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 02:26:06 by kael-ala          #+#    #+#             */
/*   Updated: 2024/10/24 17:55:40 by kael-ala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

# include "../lib/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <math.h>
# include <fcntl.h>
# include "../MLX42/include/MLX42/MLX42.h"

#define TILE_SIZE 32


typedef struct s_graphics {
    mlx_t* mlx;
    mlx_image_t* img;
} t_graphics;

typedef struct s_rays
{
    long distance;
    struct s_rays *next;
}   t_rays;

typedef struct s_params
{
    char *north;
    char *south;
    char *west;
    char *east;
    int ciel[3];
    int floor[3];
    char **map;
    int w_width;
    int w_height;
    t_graphics *graph;
}   t_params;

typedef struct s_player
{
    double fov;
    double angle;
    double posx;
    double posy;
    double dirx;
    double diry;
    double planex;
    double planey;
    double    moveSpeed;
    double    rotSpeed;
    t_params *params;
} t_player;

// parse 
void draw_map(void *ptr);
int		check_path(char *path);
int     is_map(char *line);
int     get_map_size(char *path);
void    stock_map(char *path, t_params **parameters);
int     check_player(char *line, int *player);
int     map_size(char **map);
int     check_map(char **map);
int     validate_inputs(t_params *params);
int     check_sheet(char *path, t_params **parameters);

// graph 
void initialize_graphics(t_graphics *graphics, t_params *para);
void mlxdrawmap(t_graphics *graphic, t_params *parameters);

// utils 
int *hidenseek(char **map);
int *get_size(char **map);
char get_player(char **map);

//raycast
void init_player(t_params *param, t_player *playerrr);

#endif