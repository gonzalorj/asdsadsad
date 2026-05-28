/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gorodrig <gorodrig@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 08:40:16 by gorodrig          #+#    #+#             */
/*   Updated: 2024/06/03 10:28:32 by gorodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_fd_reader(int fd, char *readed)
{
	char			*buff;
	ssize_t			readed_chars;

	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	readed_chars = 1;
	while (readed_chars > 0)
	{
		readed_chars = read(fd, buff, BUFFER_SIZE);
		if (readed_chars < 0)
		{
			free(buff);
			return (NULL);
		}
		buff[readed_chars] = '\0';
		readed = ft_append(readed, buff);
		if (find_newline(readed))
			break ;
	}
	free(buff);
	return (readed);
}

char	*ft_new_line(char *readed)
{
	int		i;
	int		j;
	char	*s;

	i = 0;
	j = 0;
	if (!readed[i])
		return (NULL);
	while (readed[i] && readed[i] != '\n')
		i++;
	s = (char *)malloc(sizeof(char) * (i + 2));
	if (!s)
		return (NULL);
	i = 0;
	while (readed[i] && readed[i] != '\n')
		s[j++] = readed[i++];
	if (readed[i] == '\n')
		s[j++] = '\n';
	s[j] = '\0';
	return (s);
}

char	*ft_return_rest(char *readed)
{
	int		i;
	int		j;
	char	*s;

	i = 0;
	j = 0;
	while (readed[i] && readed[i] != '\n')
		i++;
	if (!readed[i])
	{
		free(readed);
		return (NULL);
	}
	s = (char *)malloc(sizeof(char) * (ft_strlen(readed) - i + 1));
	if (!s)
		return (NULL);
	i++;
	while (readed[i])
		s[j++] = readed[i++];
	s[j] = '\0';
	free(readed);
	return (s);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*readed;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	readed = ft_fd_reader(fd, readed);
	if (!readed)
		return (NULL);
	line = ft_new_line(readed);
	readed = ft_return_rest(readed);
	return (line);
}
