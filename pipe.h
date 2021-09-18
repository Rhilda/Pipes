/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhilda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 11:56:16 by rhilda            #+#    #+#             */
/*   Updated: 2021/09/18 11:56:20 by rhilda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPE_H
# define PIPE_H

# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "libft/libft.h"

void	err(void);
void	child(char **av, char **envp, int *fd);
char	*find_path(char *cmd, char **envp);
void	child_b(char *argv, char **envp);
void	parent(char **av, char **envp, int *fd);
int		gnl(char **line, int i, int r, char c);
void	exe(char *argv, char **envp);
int		file_open(char *argv, int i);

#endif
