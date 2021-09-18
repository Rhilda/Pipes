/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhilda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 11:55:56 by rhilda            #+#    #+#             */
/*   Updated: 2021/09/18 11:56:04 by rhilda           ###   ########.fr       */
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

void	child(char **av, char **envp, int *fd)
{
	int		filein;
	char	**cmd;

	filein = open(av[1], O_RDONLY, 0777);
	if (filein == -1)
		exit(1);
	dup2(fd[1], STDOUT_FILENO);
	dup2(filein, STDIN_FILENO);
	close(fd[0]);
	cmd = ft_split(av[2], ' ');
	if (execve(find_path(cmd[0], envp), cmd, envp) == -1)
		exit(1);
}

void	parent(char **av, char **envp, int *fd)
{
	int		fileout;
	char	**cmd;

	fileout = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fileout == -1)
		exit(1);
	dup2(fd[0], STDIN_FILENO);
	dup2(fileout, STDOUT_FILENO);
	close(fd[1]);
	cmd = ft_split(av[3], ' ');
	if (execve(find_path(cmd[0], envp), cmd, envp) == -1)
		exit(1);
}

int	main(int ac, char **av, char **envp)
{
	int	fd[2];
	int	pid1;

	if (ac == 5)
	{
		if (pipe(fd) == -1)
			exit(1);
		pid1 = fork();
		if (pid1 == -1)
			exit(1);
		if (pid1 == 0)
			child(av, envp, fd);
		waitpid(pid1, NULL, 0);
		parent(av, envp, fd);
		close(fd[0]);
		close(fd[1]);
	}
	ft_putstr_fd("<file1> <cmd1> <cmd2> file2\n", 1);
	return (0);
}
