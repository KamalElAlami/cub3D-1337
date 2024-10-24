/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kael-ala <kael-ala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 14:32:42 by kael-ala          #+#    #+#             */
/*   Updated: 2024/10/24 11:39:53 by kael-ala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void init_player(t_params *param, t_player *playerrr)
{
    int *pos;
    char p;

    p = get_player(param->map);
    pos = hidenseek(param->map);
    playerrr->fov = 60 * (M_PI / 180);
    playerrr->posx = (pos[0] * 32) - 16;
    playerrr->posy = (pos[1] * 32) - 16;
    playerrr->planex = 0.66;
    playerrr->planey = 0;
    playerrr->rotSpeed = 0.05;
    playerrr->moveSpeed = 5;
    if (p == 'N')
    {
        playerrr->angle = -M_PI / 2;
        playerrr->dirx = 0;
        playerrr->diry = -1;
    }
    else if (p == 'S')
    {
        playerrr->angle = M_PI / 2;
        playerrr->dirx = 0;
        playerrr->diry = 1;   
    }
    else if (p == 'W')
    {
        playerrr->angle = M_PI;
        playerrr->dirx = -1;
        playerrr->diry = 0;
    }
    else if (p == 'E')
    {
        playerrr->angle = 0;
        playerrr->dirx = 1;
        playerrr->diry = 0;
    }
}

// void cast_rays(t_player *playerrr)
// {
//     int i = 0;
//     int rays;
//     int thickness;
//     double rayangle;

//     thickness = 3;
//     rays = playerrr->params->w_width / thickness;
//     // bach kan check l angle feen ana kanchuf o kanbda men half dl fov lowl 
//     rayangle = playerrr->angle - (playerrr->fov / 2);
    
//     while (i < rays)
//     {
        
//         rayangle += playerrr->fov / 320;
//     }
    
    
// }