/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkerman <rkerman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 16:46:22 by rkerman           #+#    #+#             */
/*   Updated: 2025/01/01 17:39:39 by rkerman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

void ft_bzero(void *s, size_t n)
{
	unsigned char *str;

	str = (unsigned char *)s;
	while (n--)
		*str++ = '\0';
}

void *ft_calloc(size_t nmemb, size_t size)
{
	void	*mem;

	if (size && nmemb > SIZE_MAX / size)
		return (NULL);
	mem = malloc(nmemb * size);
	if (!mem)
		return (NULL);
	ft_bzero(mem, nmemb * size);
	return (mem);
}

size_t ft_strlen(char *s)
{
	size_t i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void *ft_memcpy(void *dest, const void *src, size_t n)
{
	const unsigned char	*srccast;
	unsigned char		*destcast;

	srccast = (const unsigned char *)src;
	destcast = (unsigned char *)dest;
	if (n == 0 || (!dest && !src))
		return (dest);
	while (n--)
		*destcast++ = *srccast++;
	return (dest);
}

void *ft_realloc(void *ptr, size_t size)
{
	size_t			old_size;
	unsigned char	*nptr;
	unsigned char	*cptr;

	if (!ptr)
		return (ft_calloc(size, 1));
	old_size = ft_strlen(ptr);
	cptr = (unsigned char *)ptr;
	if (old_size >= size)
		return (ptr);
	nptr = ft_calloc(size, 1);
	if (!nptr)
		return (NULL);
	ft_memcpy(nptr, ptr, old_size);
	free(ptr);
	return ((void *)nptr);
}

int ft_strchr(char *s, char c)
{
	int	i;

	i = 0;
	while (s && s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

char *get_line(char *w)
{
	char	*l;
	int		p;
	int		i;

	i = 0;
	if (ft_strchr(w, '\n') > -1)
		p = ft_strchr(w, '\n');
	else
		p = ft_strchr(w, '\0');
	l = ft_calloc(p + 1, sizeof(char));
	if (!l)
		return (NULL);
	while (i < p)
	{
		l[i] = w[i];
		i++;
	}
	return (l);
}

char *get_next_line(int fd)
{
	static char *stash;
	int			read_bytes;
	size_t		size_stash;
	char		*line;

	read_bytes = 1;
	if (fd == -1 || read(fd, NULL, 0) == -1 || BUFFER_SIZE < 1)
		return (NULL);
	if (!stash)
		stash = ft_realloc(stash, BUFFER_SIZE + 1);
	if (!stash)
		return (NULL);
	while(read_bytes && ft_strchr(stash, '\n') == -1)
	{
		size_stash = ft_strlen(stash);
		stash = ft_realloc(stash, size_stash + BUFFER_SIZE + 1);
		if (!stash)
		{
			free(stash);
			return (NULL);
		}
		read_bytes = read(fd, &stash[size_stash], BUFFER_SIZE);
	}
	line = get_line(stash);
	if (!read_bytes || line == NULL)
		free(stash);
	return (line);
}

#include <fcntl.h>

int main(void)
{
	int	fd;
	char *s;

	fd = open("test.txt", O_RDONLY);
	s = get_next_line(fd);
	printf("%s", s);
	free(s);
	s = get_next_line(fd);
	printf("%s", s);
	free(s);

	close(fd);	
}
