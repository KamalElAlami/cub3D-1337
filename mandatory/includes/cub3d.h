/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarif <sarif@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 02:26:06 by kael-ala          #+#    #+#             */
/*   Updated: 2025/01/08 00:59:45 by sarif            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../../lib/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <math.h>
# include <fcntl.h>
# include "../../MLX42/include/MLX42/MLX42.h" 

# define TILE_SIZE 64
# define WINDOW_WIDTH 1280
# define WINDOW_HEIGHT 720
# define PV_WIDTH 500
# define PV_HEIGHT 500

typedef struct s_dda
{
	double		stepx;
	double		stepy;
	double		yinter;
	double		xinter;
	double		xcheck;
	double		ycheck;
}	t_dda;

typedef struct s_rays
{
	double	rayangle;
	double	distance;
	double	hity;
	double	hitx;
	int		is_horizontal;
	int		is_vertical;
}	t_rays;

typedef struct s_graphics
{
	mlx_t		*mlx;
	mlx_image_t	*img;
}	t_graphics;

typedef struct s_player	t_player;

typedef struct s_params
{
	int				fd;
	char			*north;
	int				no;
	char			*south;
	int				so;
	char			*west;
	int				we;
	char			*east;
	int				ea;
	int				f;
	int				c;
	int				ciel[3];
	int				floor[3];
	char			**map;
	char			**u_map;
	int				w_width;
	int				w_height;
	mlx_texture_t	*t_no;
	mlx_texture_t	*t_so;
	mlx_texture_t	*t_we;
	mlx_texture_t	*t_ea;
	t_graphics		*graph;
	t_player		*player;
}	t_params;

struct s_player
{
	double		fov;
	double		angle;
	double		posx;
	double		posy;
	double		movespeed;
	double		rotspeed;
	t_params	*params;
	t_rays		*ray;
};

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
void		ft_store_data(t_params *param, char *line, int len);
void		ft_init_data(t_params *param);
void		ft_store_rgb(t_params *p, char *line);
int			check_rgb(char *line, int flag);
void		ft_store_rgb_norm(char **degits, t_params *p);
int			ft_isblank(char c);
int			ft_avoid(char *line);
int			is_map_ready(char *line);
int			is_all_blank(char *line);
int			ft_check_data(t_params *p);
int			fill_map(t_params *param, int fd, char *line);
void		ft_init_data(t_params *param);
void		adjust_map_size(t_params *p);
void		check_map_validity(t_params *p);
int			is_player(char c, int flag, t_params *p);
void		run_animation(t_player *player);
int			put_txtr(mlx_image_t *img, mlx_texture_t *txtr, mlx_t *mlx);
void		render_wall(t_player *player, int x);
void		clear_prog(t_params *p, int status, char *err);
void		draw_ciel(int *y, double top, int x, t_params *params);
void		draw_floor(int *y, int x, t_params *params);

// graph 
void		initialize_graphics(t_graphics *graphics, t_params *para);
// uint32_t	ft_get_pixel(t_player *p, int y, double top);

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
int			is_out(t_params *params, double x, double y);
void		init_vertical_dda(t_player *player, t_dda *data, double rayangle);
void		init_horizontal_dda(t_player *player, t_dda *data, double rayangle);

//utils
char		*ft_strdup_gb(const char *s1);
char		*ft_strjoin_gb(char const *s1, char const *s2);

#endif
