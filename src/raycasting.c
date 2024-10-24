/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kael-ala <kael-ala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 13:30:38 by kael-ala          #+#    #+#             */
/*   Updated: 2024/10/24 18:07:29 by kael-ala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/cub3d.h>

double normalize_angle(double angle){
    return fabs(fmod(angle, 2 * M_PI));
}

void raycasting(t_player *playerr)
{
    long dist;
    int i;
    t_rays *ray;
    long rayangle;

    rayangle = normalize_angle(playerr->angle) - (playerr->fov /2);
    ray = malloc(sizeof(t_rays));
    i = 0;
    while (i < playerr->params->w_width)
    {
        dist = cast_ray();
        ray_addback(ray, newray(dist));
        rayangle += playerr->fov / playerr->params->w_width;
    }

    
}