/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tax_collector.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarif <sarif@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 04:58:43 by kael-ala          #+#    #+#             */
/*   Updated: 2025/01/03 21:43:55 by sarif            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void ft_perror(char *msg)
{
	write(2, &msg, ft_strlen(msg));
	exit(1);
}

static	void	collect_taxes(t_collector **taxes)
{
	t_collector	*current;
	t_collector	*temp;

	if (!taxes || !*taxes)
		return ;
	current = *taxes;
	while (current)
	{
		temp = current;
		current = current->next;
		if (temp->ptr)
			free(temp->ptr);
		if (temp)
			free(temp);
	}
	*taxes = NULL;
}

static void	appand_taxes(t_collector **taxes, void *ptr)
{
	t_collector	*new_tax;

	new_tax = malloc(sizeof(t_collector));
	if (!new_tax)
		return (ft_perror("Malloc :"));
	new_tax->ptr = ptr;
	new_tax->next = *taxes;
	*taxes = new_tax;
}

void	*ft_malloc(size_t size, t_malloc flag)
{
	static t_collector	*end_taxes;
	void				*ptr;

	if (flag == END)
	{
		ptr = malloc(size);
		if (!ptr)
			return (ft_perror("Malloc :"), NULL);
		return (appand_taxes(&end_taxes, ptr), ptr);
	}
	else if (flag == CLEAR_END)
		collect_taxes(&end_taxes);
	return (NULL);
}