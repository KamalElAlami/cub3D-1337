/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarif <sarif@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 00:27:05 by sarif             #+#    #+#             */
/*   Updated: 2025/01/04 21:13:24 by sarif            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	clear_prog_norm(t_params *p)
{
	if (p->t_no)
		mlx_delete_texture(p->t_no);
	if (p->t_so)
		mlx_delete_texture(p->t_so);
	if (p->t_we)
		mlx_delete_texture(p->t_we);
	if (p->t_ea)
		mlx_delete_texture(p->t_ea);
	if (p->t_door)
		mlx_delete_texture(p->t_door);
}

void	clear_prog(t_params *p, int status, char *err)
{
	int	i;

	i = -1;
	while (++i < 22)
		if (*p->frames_t && p->frames_t[i])
			mlx_delete_texture(p->frames_t[i]);
	if (err)
		write(2, err, ft_strlen(err));
	clear_prog_norm(p);
	if (p->player->pv)
		mlx_delete_image(p->graph->mlx, p->player->pv);
	if (p->graph->minimap)
		mlx_delete_image(p->graph->mlx, p->graph->minimap);
	if (p->graph->img)
		mlx_delete_image(p->graph->mlx, p->graph->img);
	if (p->graph->mlx)
		mlx_close_window(p->graph->mlx);
	ft_malloc(0, CLEAR_END);
	exit (status);
}

int	is_out(t_params *params, double x, double y)
{
	return (x < 0 || y < 0 || x >= params->w_width || y >= params->w_height);
}

char	*ft_strdup_gb(const char *s1)
{
	int		len;
	char	*res;
	int		i;

	i = 0;
	len = ft_strlen(s1);
	res = ft_malloc(sizeof(char) * (len + 1), END);
	if (!res)
		return (NULL);
	while (*s1)
	{
		res[i] = *s1;
		s1++;
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	*ft_strjoin_gb(char const *s1, char const *s2)
{
	char	*constr;
	int		sl;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup_gb(s2));
	if (!s2)
		return (ft_strdup_gb(s1));
	sl = ft_strlen(s1) + ft_strlen(s2);
	constr = ft_malloc(sizeof(char) * (sl + 1), END);
	if (!constr)
		return (NULL);
	ft_strlcpy(constr, s1, ft_strlen(s1) + 1);
	ft_strlcpy(constr + ft_strlen(s1), s2, ft_strlen(s2) + 1);
	return (constr);
}
