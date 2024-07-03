/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 13:05:13 by rothiery          #+#    #+#             */
/*   Updated: 2024/06/18 14:46:58 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*saveread(int fd, char *save)
{
	int		brd;
	char	*rd;

	brd = 1;
	rd = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (rd == NULL)
		return (NULL);
	while (!(ft_strchr(save, '\n')) && brd > 0)
	{
		brd = read(fd, rd, BUFFER_SIZE);
		if (brd == -1)
			return (free(rd), free(save), NULL);
		rd[brd] = '\0';
		save = ft_strjoinfr(save, rd);
		if (save == NULL)
			return (free(rd), NULL);
	}
	if (brd == 0 && save[brd] == '\0')
		return (free(save), free(rd), NULL);
	return (free(rd), save);
}

char	*linesep(char *save)
{
	char	*line;
	int		i;

	i = 0;
	while (!(save[i] == '\n' || save[i] == '\0'))
		i++;
	line = (char *)malloc(sizeof(char) * (i + 2));
	if (line == NULL)
		return (NULL);
	i = 0;
	while (save[i] != '\n' && save[i] != '\0')
	{
		line[i] = save[i];
		i++;
	}
	if (save[i] == '\n')
	{
		line[i] = save[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

static char	*saveend(char *save)
{
	char	*temp;
	int		i;
	int		j;

	j = 0;
	i = 0;
	if (save == NULL)
		return (NULL);
	while (!(save[i] == '\n' || save[i] == '\0'))
		i++;
	if (save[i] == '\0')
		return (free(save), NULL);
	i++;
	temp = (char *)malloc(sizeof(char) * (ft_strlen(save)));
	if (temp == NULL)
		return (NULL);
	while (save[i])
	{
		temp[j] = save[i];
		i++;
		j++;
	}
	temp[j] = '\0';
	return (free(save), temp);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*save[32767];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (save[fd] == NULL)
		save[fd] = ft_strdup("");
	save[fd] = saveread(fd, save[fd]);
	if (!save[fd])
		return (NULL);
	line = linesep(save[fd]);
	save[fd] = saveend(save[fd]);
	return (line);
}

// #include <stdlib.h>
// #include <libgen.h>
// #include <string.h>
// #include <fcntl.h>
// #include <unistd.h>

// int	main(void)
// {
// 	// First Test
// 	int		fd1 = open("test.txt", O_RDONLY);
// 	char	*line1 = get_next_line(fd1);

// 	printf("test.txt file:");
// 	while (line1 != NULL)
// 	{
// 		printf("%s", line1);
// 		free(line1);
// 		line1 = get_next_line(fd1);
// 	}
// 	close(fd1);
// 	return (0);
// }

// int	main(void)
// {
// //	int	i;
// 	int	fd1 = open("test.txt", O_RDONLY);
// 	char	*line1 = get_next_line(fd1);

// //	i = 0;
// 	printf("%s", line1);
// //	free(line1);
// //	line1 = get_next_line();
// //	printf("%s\n", line1);
// 	free(line1);
// }