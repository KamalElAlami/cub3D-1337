/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kael-ala <kael-ala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 04:03:26 by kael-ala          #+#    #+#             */
/*   Updated: 2023/12/01 00:09:39 by kael-ala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	int_count(int n)
{
	int	i;

	i = 0;
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static void	rev_buffer(char *buffer, int size)
{
	int		j;
	int		k;
	char	tmp;

	j = 0;
	k = size - 1;
	while (j < k)
	{
		tmp = buffer[j];
		buffer[j] = buffer[k];
		buffer[k] = tmp;
		j++;
		k--;
	}
	buffer[size] = '\0';
}

static void	set_char(char *buffer, int n, int extra)
{
	int	i;

	i = 0;
	while (n > 0)
	{
		buffer[i++] = (n % 10) + '0';
		n /= 10;
	}
	if (extra == 2)
		buffer[i++] = '-';
	rev_buffer(buffer, i);
}

char	*ft_itoa(int n)
{
	char	*buffer;
	int		i;
	int		extra;

	extra = 1;
	i = 0;
	if (n == 0)
		return (ft_strdup("0"));
	if (n == INT_MIN)
		return (ft_strdup("-2147483648"));
	if (n < 0)
	{
		n *= -1;
		extra = 2;
	}
	buffer = malloc(sizeof(char) * (int_count(n) + extra));
	if (!buffer)
		return (NULL);
	set_char(buffer, n, extra);
	return (buffer);
}
