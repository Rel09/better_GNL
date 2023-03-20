/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotvin <dpotvin@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 02:08:16 by dpotvin           #+#    #+#             */
/*   Updated: 2023/03/20 03:01:44 by dpotvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gnl.h"

// Basic Strlen (0) and Count until \n (1)
static size_t	ft_strlenz(char *s, t_bool flag)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	if (!flag)
	{
		while (s[i])
			i++;
	}
	else
	{
		while (s[i] && s[i] != '\n')
			i++;
	}
	return (i);
}
// Join Two string Together
static char	*ft_strjoin(char *s1, char *s2)
{
	char	*new_str;
	int		i;
	int		j;

	if (!s1)
	{
		s1 = malloc(1);
		*s1 = '\0';
	}
	if (!s1 && !s2)
		return (0);
	new_str = malloc(ft_strlenz(s1, 0) + ft_strlenz(s2, 0) + 1);
	if (!new_str)
		return (0);
	i = 0;
	j = -1;
	while (s1[++j])
		new_str[j] = s1[j];
	while (s2[i])
		new_str[j++] = s2[i++];
	new_str[j] = '\0';
	free(s1);
	return (new_str);
}
// Check if there's a new line in this string
static t_bool	ft_find_nl(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (TRUE);
		i++;
	}
	return (FALSE);
}
// Get what's after the \n and keep it in the buffer if so
static char	*ft_save(char *buff)
{
	int		i;
	int		j;
	char	*s;

	i = ft_strlenz(buff, 1);
	if (!buff[i])
	{
		free(buff);
		return (0);
	}
	s = malloc(ft_strlenz(buff, 0) - i + 1);
	if (!s)
		return (0);
	j = 0;
	while (buff[++i])
		s[j++] = buff[i];
	s[j] = '\0';
	free(buff);
	return (s);
}
// Get the string BEFORE newline (if there's one)
static char	*ft_line(char *buff)
{
	int		i;
	char	*s;

	i = 0;
	if (!buff[i])
		return (0);
	s = malloc(ft_strlenz(buff, 1) + 1);
	if (!s)
		return (0);
	while (buff[i] && buff[i] != '\n')
	{
		s[i] = buff[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}
// Read Buffer Size OR until we meet a \n
static char *ft_read(int fd, char *buffer)
{
	char	*str;
	int		b;
	
	str = malloc(BUFFER_SIZE + 1);
	if (!str) {
		printf("x\n");
		return (0);
	}
	b = 1;
	while (b != 0 && !ft_find_nl(buffer))
	{
		b = read(fd, str, BUFFER_SIZE);
		if (b == -1)
		{
			free(buffer);
			free(str);
			printf("y\n");
			return (0);
		}
		str[b] = '\0';
		buffer = ft_strjoin(buffer, str);
	}
	free(str);
	return (buffer);
}
// Get Next line "Main" entry
t_gnl *better_gnl(int fd)
{
	static char		*buffer;
	static t_gnl	t;
	
	// Check if the FD is valid and Buffer size isnt stupid
	if (fd < 0 || BUFFER_SIZE < 1) 
		return (0);

	buffer = ft_read(fd, buffer);
	if (!buffer)
		return (0);
	if (t.string)
		free(t.string);
	t.string = ft_line(buffer);
	t.strlen = ft_strlenz(t.string, 0);
	buffer = ft_save(buffer);
	return (&t);
}
