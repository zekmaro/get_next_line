/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarama <anarama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 11:21:46 by anarama           #+#    #+#             */
/*   Updated: 2024/04/16 18:40:02 by anarama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_calloc(size_t num, size_t size)
{
	char	*mem;
	char	*temp_mem;
	size_t	total_size;

	total_size = size * num;
	if (num == 0 || size == 0)
		total_size = 0;
	if (SIZE_MAX / num < size)
		return (NULL);
	mem = (char *)malloc(total_size);
	if (!mem)
		return (NULL);
	temp_mem = mem;
	while (total_size > 0)
	{
		*mem++ = 0;
		total_size--;
	}
	return ((void *)temp_mem);
}

char    *ft_strchr(char *str, char c)
{
	if (str == NULL)
		return (NULL);
    while (*str)
    {
        if (*str == c)
            return (str);
        str++;
    }
    if (c == '\0')
        return (str);
    return (NULL);
}

size_t ft_strlen(char const *s)
{
    size_t    i;

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

char    *ft_strjoin(char const *s1, char const *s2)
{
    size_t    len_s1;
    size_t    len_s2;
    char      *cat_result;
    char      *temp_cat_result;

	if (s1 == NULL)
		return (ft_strdup(s2));
    len_s1 = ft_strlen(s1);
    len_s2 = ft_strlen(s2);
    cat_result = (char *)ft_calloc((len_s1 + len_s2) + 1, 1);
    if (!cat_result)
        return (NULL);
    temp_cat_result = cat_result;
    while (*s1)
        *cat_result++ = *s1++;
    while (*s2)
        *cat_result++ = *s2++;
    return (temp_cat_result);
}

char    *ft_strdup(const char *s)
{
    size_t      len_s;
    char        *dup_s;
    char        *temp_dup_s;

	if (s == NULL)
		return (NULL);
    len_s = ft_strlen(s);
    dup_s = (char *)malloc(sizeof(char) * len_s + 1);
    if (!dup_s)
        return (NULL);
    temp_dup_s = dup_s;
    while (*s)
        *dup_s++ = *s++;
    *dup_s = '\0';
    return (temp_dup_s);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
    char        *temp_dest;
    char        *temp_src;

    if (dest == NULL && src == NULL)
        return (NULL);
    temp_dest = (char *)dest;
    temp_src = (char *)src;
    while (n--)
        *temp_dest++ = *temp_src++;
    return (dest);
}
