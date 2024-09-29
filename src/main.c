/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kael-ala <kael-ala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 02:37:09 by kael-ala          #+#    #+#             */
/*   Updated: 2024/09/29 05:43:00 by kael-ala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// int check_sheet(char *path, t_params **parameters)
// {
    
// }

int main(int ac, char **av)
{
	(void)ac;
	(void)av;
    // t_params *params;
    
    // params = ft_malloc(sizeof(t_params), END);
    // if (ac != 2 || check_path(av[1]))
    //     return (1);
    // if (check_sheet(av[1], &params))
	int fd = open("./maps/file.cub", O_RDWR);
	printf("%s\n", get_next_line(fd));
    
}