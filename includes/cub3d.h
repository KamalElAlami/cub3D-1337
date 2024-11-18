/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarif <sarif@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 02:26:06 by kael-ala          #+#    #+#             */
/*   Updated: 2024/11/18 03:41:38 by sarif            ###   ########.fr       */
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
	char		*north;
	int			no;
	char		*south;
	int			so;
	char		*west;
	int			we;
	char		*east;
	int			ea;
	int			f;
	int			c;
	int			ciel[3];
	int			floor[3];
	char		**map;
	char		**uni_map;
	int			w_width;
	int			w_height;
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
int     check_sheet(char *path, t_params *param);

// graph 
void initialize_graphics(t_graphics *graphics, t_params *para);
void mlxdrawmap(t_graphics *graphic, t_params *parameters);

// utils 
int *hidenseek(char **map);
int *get_size(char **map);
char get_player(char **map);

//raycast
void init_player(t_params *param, t_player *playerrr);


//soufiix
void	ft_store_data(t_params *param, char *line);
void	ft_init_data(t_params *param);
void	ft_store_rgb(t_params *p, char *line);
int		check_rgb(char *line, int flag);
void	ft_store_rgb_norm(char **degits);
int		ft_isblank(char c);
int		ft_avoid(char *line);
int		is_map_ready(char *line);
int		is_all_blank(char *line);
int		ft_check_data(t_params *p);
int		fill_map(t_params *param, int fd, char *line);
void	ft_init_data(t_params *param);
void	adjust_map_size(t_params *p);
void	check_map_validity(t_params *p);
void	check_f_l_line(t_params *p);

#endif