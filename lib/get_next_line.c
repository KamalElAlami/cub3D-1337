/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kael-ala <kael-ala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 17:42:22 by kael-ala          #+#    #+#             */
/*   Updated: 2024/09/29 05:20:32 by kael-ala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_reader(int fd, char *rst)
{
	int		count;
	char	*buff;

	count = 1;
	buff = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	while (ft_strchr(rst, '\n') != 0 && count > 0)
	{
		count = read(fd, buff, BUFFER_SIZE);
		if (count < 0)
		{
			free(rst);
			return (free(buff), NULL);
		}
		buff[count] = '\0';
		rst = ft_strjoin(rst, buff);
	}
	free (buff);
	return (rst);
}

int	new_line_counter(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	return (i);
}

char	*line_stack(char *rst)
{
	int		i;
	int		j;
	char	*buff;

	i = 0;
	if (!rst)
		return (NULL);
	j = new_line_counter(rst);
	buff = malloc(sizeof(char) * j + 1);
	if (!buff)
		return (free(rst), NULL);
	while (i < j)
	{
		buff[i] = rst[i];
		i++;
	}
	buff[i] = '\0';
	return (buff);
}

char	*rst_joiner(char *rst)
{
	int		i;
	int		j;
	char	*restofline;

	i = 0;
	j = 0;
	if (!rst || !*rst)
		return (free(rst), NULL);
	while (rst[i] && rst[i] != '\n')
		i++;
	restofline = malloc(sizeof(char) * (ft_strlen(rst) - i) + 1);
	if (rst[i] != '\0')
		i++;
	while (rst[i])
		restofline[j++] = rst[i++];
	restofline[j] = '\0';
	free(rst);
	return (restofline);
}

char	*get_next_line(int fd)
{
	char		*buff;
	static char	*rst;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	rst = ft_reader(fd, rst);
	if (!rst || !*rst)
		return (free(rst), rst = NULL, NULL);
	buff = line_stack(rst);
	if (!buff)
		return (NULL);
	rst = rst_joiner(rst);
	return (buff);
}
