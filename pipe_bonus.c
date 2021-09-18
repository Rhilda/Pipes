/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhilda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 11:56:53 by rhilda            #+#    #+#             */
/*   Updated: 2021/09/18 11:56:57 by rhilda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

void	err(void)
{
	perror("Error");
	exit(1);
}

void	child_b(char *argv, char **envp)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		err();
	pid = fork();
	if (pid == -1)
		err();
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		exe(argv, envp);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		waitpid(pid, NULL, 0);
	}
}

void	here(char *l, int ac)
{
	pid_t	reader;
	int		fd[2];
	char	*line;

	if (ac < 6)
		ft_putstr_fd("<file1> <cmd1> <cmd2> <...> file2\n", 1);
	if (pipe(fd) == -1)
		err();
	reader = fork();
	if (reader == 0)
	{
		close(fd[0]);
		while (gnl(&line, 0, 0, 0))
		{
			if (ft_strncmp(line, l, ft_strlen(l)) == 0)
				exit(0);
			write(fd[1], line, ft_strlen(line));
		}
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		wait(NULL);
	}
}

int	main(int ac, char **av, char **envp)
{
	int	i;
	int	in;
	int	out;

	if (ac >= 5)
	{
		if (ft_strncmp(av[1], "here_doc", 8) == 0)
		{
			i = 3;
			out = file_open(av[ac - 1], 0);
			here(av[2], ac);
		}
		else
		{
			i = 2;
			out = file_open(av[ac - 1], 1);
			in = file_open(av[1], 2);
			dup2(in, STDIN_FILENO);
		}
		while (i < ac - 2)
			child_b(av[i++], envp);
		dup2(out, STDOUT_FILENO);
		exe(av[ac - 2], envp);
	}
	return (0);
}
