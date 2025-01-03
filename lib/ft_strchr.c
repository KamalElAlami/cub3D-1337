/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kael-ala <kael-ala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 15:00:55 by kael-ala          #+#    #+#             */
/*   Updated: 2024/11/25 11:19:11 by kael-ala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strchr(const char *s, int c)
{
	if (!s)
		return (1);
	while (*s)
	{
		if (*s == (char)c)
			return (0);
		s++;
	}
	return (1);
}