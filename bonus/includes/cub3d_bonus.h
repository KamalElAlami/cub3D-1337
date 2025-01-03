/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarif <sarif@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 02:26:06 by kael-ala          #+#    #+#             */
/*   Updated: 2025/01/03 01:15:55 by sarif            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

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
# define MINI_SCALE 30
# define MINI_MAP 200	

typedef struct s_minimap
{
	double	startx;
	double	starty;
	double	endx;
	double	endy;
	double	w_width;
	double	w_height;
	double	posx;
	double	posy;
}	t_minimap;

typedef struct s_dda
{
	double		stepx;
	double		stepy;
	double		yinter;
	double		xinter;
	double		xcheck;
	double		ycheck;
	int			isdoor;
}	t_dda;

typedef struct s_rays
{
	double	rayangle;
	double	distance;
	double	hity;
	double	hitx;
	int		is_horizontal;
	int		is_vertical;
	int		isdoor;
}	t_rays;

typedef struct s_graphics
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	mlx_image_t	*minimap;
}	t_graphics;

typedef struct s_player	t_player;

typedef struct s_params
{
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
	int				map_width;
	int				map_height;
	char			**u_map;
	int				w_width;
	int				w_height;
	mlx_texture_t	*t_no;
	mlx_texture_t	*t_so;
	mlx_texture_t	*t_we;
	mlx_texture_t	*t_ea;
	mlx_texture_t	*frames_t[22];
	t_graphics		*graph;
	t_player		*player;
	int				is_door;
	mlx_texture_t	*t_door;
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
	mlx_image_t	*pv;
	int			anim_it;
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
void		ft_store_data(t_params *param, char *line);
void		ft_init_data(t_params *param);
void		ft_store_rgb(t_params *p, char *line);
int			check_rgb(char *line, int flag);
void		ft_store_rgb_norm(t_params *p, char **degits);
int			ft_isblank(char c);
int			ft_avoid(char *line);
int			is_map_ready(char *line);
int			is_all_blank(char *line);
int			ft_check_data(t_params *p);
int			fill_map(t_params *param, int fd, char *line);
void		ft_init_data(t_params *param);
void		adjust_map_size(t_params *p);
void		check_map_validity(t_params *p);
int			is_player(t_params *p, char c, int flag);
void		run_animation(t_player *player);
int			put_txtr(mlx_image_t *img, mlx_texture_t *txtr);
void		render_wall(t_player *player, int x);
void		check_doors_validity(t_params *p);
void		clr_img(mlx_image_t *img, int width, int height);
void		clear_prog(t_params *p, int status, char *err);
void		draw_ciel(int *y, double top, int x, t_params *params);
void		draw_floor(int *y, int x, t_params *params);
void		open_close_door(void *player);
void		close_door(t_player *player, int player_y, int player_x);

// graph 

// utils
int			*hidenseek(char **map);
int			*get_size(char **map);
char		get_player(char **map);
void		key_hook(void *player);
void		mouse_event(void *player);
u_int32_t	rgb_hex(int r, int g, int b);

//raycasting
void		init_player(t_params *param, t_player *playerrr);
void		raycasting(void *playerr);
double		normalize_angle(double angle);
int			is_wall(t_player *player, t_dda *data, int isvert);
t_looking	raydirection(double angle);
int			is_out(t_params *params, double x, double y);
void		init_vertical_dda(t_player *player, t_dda *data, double rayangle);
void		init_horizontal_dda(t_player *player, t_dda *data, double rayangle);
// minimap
void		mini_map(void *player);
void		init_minimap(t_minimap *mini, t_player *player);
void		draw_player(t_player *p, t_minimap *mini);
void		initialize_graphics(t_graphics *graphics, t_params *para);
// colors
unsigned	int	whichcolor(t_player *player, int x, int y);
unsigned	int	get_rgba(int r, int g, int b, int a);

//utils
char	*ft_strdup_gb(const char *s1);
char	*ft_strjoin_gb(char const *s1, char const *s2);
#endif
