/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kael-ala <kael-ala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 17:05:03 by kael-ala          #+#    #+#             */
/*   Updated: 2023/12/01 16:16:58 by kael-ala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	char	*str;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	end = ft_strlen(s1) - 1;
	while (ft_strchr(set, s1[start]) && start <= end)
		start++;
	if (start > end)
	{
		return (ft_strdup(s1 + end + 1));
	}
	while (ft_strchr(set, s1[end]) && end >= 0)
		end--;
	str = malloc(end - start + 1 + 1);
	if (!str)
		return (NULL);
	ft_strlcpy(str, &s1[start], end - start + 2);
	return (str);
}
