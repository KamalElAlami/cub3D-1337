/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kael-ala <kael-ala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 18:23:54 by kael-ala          #+#    #+#             */
/*   Updated: 2023/11/23 18:07:43 by kael-ala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;

	if (*needle == '\0')
		return ((char *)haystack);
	while (len--)
	{
		i = 0;
		while (haystack[i] == needle[i] && haystack[i] && i <= len)
		{
			i++;
			if (needle[i] == '\0')
				return ((char *)haystack);
		}
		if (*haystack == '\0')
			return (NULL);
		haystack++;
	}
	return (NULL);
}
