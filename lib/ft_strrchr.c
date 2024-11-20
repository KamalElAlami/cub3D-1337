/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kael-ala <kael-ala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 15:40:26 by kael-ala          #+#    #+#             */
/*   Updated: 2023/11/23 18:07:51 by kael-ala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	int		sl;

	i = 0;
	sl = ft_strlen((char *)s);
	while (i <= sl)
	{
		if (*(s + sl) == (char)c)
			return ((char *)(s + sl));
		sl--;
	}
	return (NULL);
}
