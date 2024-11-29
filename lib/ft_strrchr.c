/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarif <sarif@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 15:40:26 by kael-ala          #+#    #+#             */
/*   Updated: 2024/11/29 22:01:26 by sarif            ###   ########.fr       */
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