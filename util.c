/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhilda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 11:56:34 by rhilda            #+#    #+#             */
/*   Updated: 2021/09/18 11:56:37 by rhilda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

char	*find_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	int		i;
	char	*part_path;

	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, F_OK) == 0)
			return (path);
		i++;
	}
	return (0);
}

void	exe(char *argv, char **envp)
{
	char	**cmd;

	cmd = ft_split(argv, ' ');
	if (execve(find_path(cmd[0], envp), cmd, envp) == -1)
		exit(1);
}

int	gnl(char **line, int i, int r, char c)
{
	char	*buf;

	buf = (char *)malloc(10000);
	if (!buf)
		return (-1);
	r = read(0, &c, 1);
	while (r && c != '\n' && c != '\0')
	{
		if (c != '\n' && c != '\0')
			buf[i] = c;
		i++;
		r = read(0, &c, 1);
	}
	buf[i] = '\n';
	buf[++i] = '\0';
	*line = buf;
	free(buf);
	return (r);
}

int	file_open(char *argv, int i)
{
	int	file;

	file = 0;
	if (i == 0)
		file = open(argv, O_WRONLY | O_CREAT | O_APPEND, 0777);
	else if (i == 1)
		file = open(argv, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (i == 2)
		file = open(argv, O_RDONLY, 0777);
	if (file == -1)
	{
		perror("Error");
		exit(1);
	}
	return (file);
}
