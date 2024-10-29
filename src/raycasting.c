/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kael-ala <kael-ala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 13:30:38 by kael-ala          #+#    #+#             */
/*   Updated: 2024/10/28 17:25:47 by kael-ala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/cub3d.h>

double normalize_angle(double angle){
    return fabs(fmod(angle, 2 * M_PI));
}

// double dive_ver(t_player *playerr)
// {

//     while ()
// }

// double cast_ray(t_player *playerr)
// {
//     dive_ver(playerr);
//     dive_hor();
// }

// void raycasting(t_player *playerr)
// {
//     long dist;
//     int i;
//     t_rays *ray;
//     long rayangle;

//     rayangle = normalize_angle(playerr->angle) - (playerr->fov /2);
//     ray = malloc(sizeof(t_rays));
//     i = 0;
//     while (i < playerr->params->w_width)
//     {
//         dist = cast_ray(playerr);
//         ray_addback(ray, newray(dist));
//         rayangle += playerr->fov / playerr->params->w_width;
//     }

    
// }