/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kael-ala <kael-ala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 21:53:30 by kael-ala          #+#    #+#             */
/*   Updated: 2023/11/28 23:24:02 by kael-ala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dstl;
	size_t	srcl;
	size_t	i;

	i = 0;
	if (!dst && !size)
		return (0);
	dstl = ft_strlen(dst);
	srcl = ft_strlen(src);
	if (!size)
		return (srcl);
	if (size <= ft_strlen(dst))
		return (size + srcl);
	while (i < size - dstl - 1 && src[i])
	{
		dst[dstl + i] = src[i];
		i++;
	}
	dst[dstl + i] = '\0';
	return (dstl + srcl);
}
