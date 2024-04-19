/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarama <anarama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:14:30 by anarama           #+#    #+#             */
/*   Updated: 2024/04/19 13:14:20 by anarama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char const *s)
{
	size_t	i;

	i = 0;
	if (s == NULL)
		return (0);
	while (*s)
	{
		i++;
		s++;
	}
	return (i);
}

char	*extract_line(char	**leftovers)
{
	char	*line;
	char	*newline_index;
	size_t	len_line;
	char	*new_leftovers;

	newline_index = ft_strchr(*leftovers, '\n');
	if (newline_index)
	{
		len_line = newline_index - *leftovers + 1;
		line = ft_calloc(len_line + 1, 1);
		if (!line)
			return (ft_free(leftovers), NULL);
		line = ft_memcpy(line, *leftovers, len_line);
		new_leftovers = ft_strdup(newline_index + 1);
		ft_free(leftovers);
		if (!new_leftovers)
			return (ft_free(&line), NULL);
		*leftovers = new_leftovers;
	}
	else
	{
		line = ft_strdup(*leftovers);
		ft_free(leftovers);
	}
	return (line);
}

void	ft_free(char **str)
{
	free(*str);
	*str = NULL;
}

char	*get_next_line(int fd)
{
	static char	*leftovers = NULL;
	ssize_t		read_bytes;
	char		*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (ft_strchr(leftovers, '\n') == NULL)
	{
		buffer = (char *)ft_calloc(BUFFER_SIZE + 1, 1);
		if (!buffer)
			return (ft_free(&leftovers), ft_free(&buffer), NULL);
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes < 0)
			return (ft_free(&leftovers), ft_free(&buffer), NULL);
		if (read_bytes == 0)
		{
			ft_free(&buffer);
			if (leftovers == NULL || *leftovers == '\0')
				return (ft_free(&leftovers), NULL);
			break ;
		}
		leftovers = ft_strjoin(leftovers, buffer);
	}
	return (extract_line(&leftovers));
}

// what if i put non existing fd? handle max possible fd

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("a.out", O_RDONLY);
	if (fd < 0)
		return (1);
	line = get_next_line(fd);
	printf("%s", line);
	free(line);
	while (line)
	{
		line = get_next_line(fd);
		printf("%s", line);
		free(line);
	}
	close(fd);
}