/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarif <sarif@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 17:46:11 by kael-ala          #+#    #+#             */
/*   Updated: 2025/01/04 17:37:06 by sarif            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*constr;
	int		sl;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	sl = ft_strlen(s1) + ft_strlen(s2);
	constr = ft_malloc(sizeof(char) * (sl + 1), END);
	if (!constr)
		return (NULL);
	ft_strlcpy(constr, s1, ft_strlen(s1) + 1);
	ft_strlcpy(constr + ft_strlen(s1), s2, ft_strlen(s2) + 1);
	return (constr);
}
