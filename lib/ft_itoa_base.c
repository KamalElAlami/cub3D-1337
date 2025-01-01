/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarif <sarif@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 03:31:30 by kael-ala          #+#    #+#             */
/*   Updated: 2024/12/31 11:56:13 by sarif            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"


char *ft_itoa_base(int value, int base)
{
    char *str;
    char *hex;
    int i;
    int neg;
    int temp;

    hex = "0123456789ABCDEF";
    i = 0;
    neg = 0;
    if (value == 0)
        return (ft_strdup("0"));
    if (value < 0 && base == 10)
    {
        neg = 1;
        value = -value;
    }
    temp = value;
    while (temp)
    {
        temp /= base;
        i++;
    }
    str = ft_malloc(sizeof(char) * (i + neg + 1), END);
    str[i + neg] = '\0';
    while (i--)
    {
        str[i + neg] = hex[value % base];
        value /= base;
    }
    if (neg)
        str[0] = '-';
    return (str);
}