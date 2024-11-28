/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kael-ala <kael-ala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 02:26:06 by kael-ala          #+#    #+#             */
/*   Updated: 2024/11/28 04:36:54 by kael-ala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../lib/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <math.h>
# include <fcntl.h>
# include "../MLX42/include/MLX42/MLX42.h"

# define TILE_SIZE 32
# define WINDOW_WIDTH 1260
# define WINDOW_HEIGHT 720

typedef struct s_graphics
{
	mlx_t		*mlx;
	mlx_image_t	*img;
}	t_graphics;

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
	t_graphics	*graph;
}	t_params;

typedef struct s_player
{
	double		fov;
	double		angle;
	double		posx;
	double		posy;
	double		dirx;
	double		diry;
	double		movespeed;
	double		rotspeed;
	t_params	*params;
}	t_player;

typedef struct s_looking
{
	int	up;
	int	down;
	int	left;
	int	right;
}	t_looking;

// parse 
int			check_path(char *path);
int			is_map(char *line);
int			get_map_size(char *path);
void		stock_map(char *path, t_params **parameters);
int			check_player(char *line, int *player);
int			map_size(char **map);
int			check_map(char **map);
int			validate_inputs(t_params *params);
int			check_sheet(char *path, t_params *param);
//soufiix
void		ft_store_data(t_params *param, char *line);
void		ft_init_data(t_params *param);
void		ft_store_rgb(t_params *p, char *line);
int			check_rgb(char *line, int flag);
void		ft_store_rgb_norm(char **degits);
int			ft_isblank(char c);
int			ft_avoid(char *line);
int			is_map_ready(char *line);
int			is_all_blank(char *line);
int			ft_check_data(t_params *p);
int			fill_map(t_params *param, int fd, char *line);
void		ft_init_data(t_params *param);
void		adjust_map_size(t_params *p);
void		check_map_validity(t_params *p);
int			ft_is_player(char c, int flag);
// graph 
void		initialize_graphics(t_graphics *graphics, t_params *para);

// utils 
int			*hidenseek(char **map);
int			*get_size(char **map);
char		get_player(char **map);
void		key_hook(void *player);
u_int32_t	rgb_hex(int r, int g, int b);

//raycasting
void		init_player(t_params *param, t_player *playerrr);
void		raycasting(void *playerr);
double		normalize_angle(double angle);
int			is_wall(t_params *params, double x, double y);
t_looking	raydirection(double angle);

// helpers remove later 
void		draw_line(t_graphics *graphic, t_player *player);
void		draw_direction_line(t_graphics *graphic, t_player *player);
void		render_player(t_graphics *graphic, t_player *player);
void		draw_player(void *ptr);
void		mlxdrawmap(t_graphics *graphic, t_params *parameters);
void		draw_map(void *ptr);
#endif