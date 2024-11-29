/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarif <sarif@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 20:34:10 by kael-ala          #+#    #+#             */
/*   Updated: 2024/11/29 22:01:05 by sarif            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*destt;
	unsigned char	*srcc;

	if (!dest && !src)
		return (NULL);
	srcc = ((unsigned char *)src);
	destt = ((unsigned char *)dest);
	if (destt > srcc)
		while (n--)
			destt[n] = srcc[n];
	else
		ft_memcpy(destt, srcc, n);
	return (destt);
}
