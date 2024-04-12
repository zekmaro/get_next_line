/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarama <anarama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:14:30 by anarama           #+#    #+#             */
/*   Updated: 2024/04/12 20:37:12 by anarama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
			return (NULL);
		ft_memcpy(line, *leftovers, len_line);
		new_leftovers = ft_strdup(newline_index + 1);
		if (!new_leftovers)
			return (NULL);
		free(*leftovers);
		*leftovers = new_leftovers;
	}
	else 
	{
		line = ft_strdup(*leftovers);
		free(*leftovers);
		*leftovers = NULL;
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*leftovers = NULL;
	ssize_t		read_bytes;
	char		*buffer;
	char		*temp;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd == 1 || fd == 2)
		return (NULL);
	while (ft_strchr(leftovers, '\n') == NULL)
	{
		buffer = (char *)ft_calloc(BUFFER_SIZE + 1, 1);
		if (!buffer)
		{
			free(leftovers);
			return (NULL);
		}
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes <= 0)
		{
			free(buffer);
			break ;
		}
		temp = ft_strjoin(leftovers, buffer);
		free(leftovers);
		free(buffer);
		if (temp == NULL)
			return (NULL);
		leftovers = temp;
	}
	return (extract_line(&leftovers));
}

// int	main(void)
// {
// 	int		fd;
// 	char	*line;

// 	fd = open("testfile.txt", O_RDONLY);
// 	if (fd < 0)
// 		return (1);
// 	line = get_next_line(fd);
// 	printf("%s", line);
// 	free(line);
// 	while (line)
// 	{
// 		line = get_next_line(fd);
// 		printf("%s", line);
// 		free(line);
// 	}
// 	close(fd);
// }
