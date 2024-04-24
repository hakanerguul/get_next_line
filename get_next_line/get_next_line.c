/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aergul <aergul@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 18:14:46 by aergul            #+#    #+#             */
/*   Updated: 2022/02/10 18:29:35 by aergul           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*first_read(int fd, char *buffer)
{
	char	*buff;
	int		rd_byte;

	rd_byte = 1;
	buff = malloc (sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	while (!find_nl_char(buffer) && rd_byte != 0)
	{
		rd_byte = read (fd, buff, BUFFER_SIZE);
		if (rd_byte == -1)
		{
			free (buffer);
			free (buff);
			return (NULL);
		}
		buff[rd_byte] = '\0';
		buffer = strjoin(buffer, buff);
	}
	free (buff);
	return (buffer);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*s_buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	s_buffer = first_read(fd, s_buffer);
	if (s_buffer == NULL)
		return (NULL);
	line = get_new_line(s_buffer);
	s_buffer = get_new_buffer(s_buffer);
	return (line);
}
