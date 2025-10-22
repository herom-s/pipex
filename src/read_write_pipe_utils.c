/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_write_pipe_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hermarti <hermarti@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 16:09:01 by hermarti          #+#    #+#             */
/*   Updated: 2025/10/22 16:09:03 by hermarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

void	child_cleanup(t_pipe *p)
{
	unsigned int	i;

	free_cmds_strs(p->cmds_strs, p->num_cmds);
	if (p->cmds_fd)
	{
		i = 0;
		while (i < p->num_cmds - 1)
		{
			if (p->cmds_fd[i])
				free(p->cmds_fd[i]);
			i++;
		}
		free(p->cmds_fd);
	}
	free(p->childs);
}

void	close_all_pipes(t_pipe *p)
{
	unsigned int	i;

	i = 0;
	while (i < p->num_cmds - 1)
	{
		close(p->cmds_fd[i][INPUT_END]);
		close(p->cmds_fd[i][OUTPUT_END]);
		i++;
	}
}

int	open_file(char *filename, int flags, t_pipe *p)
{
	int	fd;

	fd = open(filename, flags, 0644);
	if (fd == -1)
	{
		ft_dprintf(STDERR_FILENO, "pipex: %s: %s\n", filename, strerror(errno));
		close_all_pipes(p);
		child_cleanup(p);
		exit(EXIT_FAILURE);
	}
	return (fd);
}

void	exec_cmd(char **cmd, char *envp[], t_pipe *p)
{
	if (execve(cmd[0], cmd, envp) < 0)
	{
		ft_dprintf(STDERR_FILENO, "pipex: %s: command not found\n", cmd[0]);
		child_cleanup(p);
		exit(127);
	}
}
