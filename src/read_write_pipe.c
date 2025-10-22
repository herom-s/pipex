/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_write_pipe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hermarti <hermarti@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 14:28:29 by hermarti          #+#    #+#             */
/*   Updated: 2025/10/22 14:34:28 by hermarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

static void	handle_first_cmd(t_pipe *p, char *infile, char *envp[],
		unsigned int i)
{
	int	file_fd;

	file_fd = open_file(infile, O_RDONLY, p);
	dup2(file_fd, STDIN_FILENO);
	close(file_fd);
	dup2(p->cmds_fd[i][OUTPUT_END], STDOUT_FILENO);
	close_all_pipes(p);
	exec_cmd(p->cmds_strs[i], envp, p);
}

static void	handle_last_cmd(t_pipe *p, char *outfile, char *envp[],
		unsigned int i)
{
	int	file_fd;

	file_fd = open_file(outfile, O_WRONLY | O_CREAT | O_TRUNC, p);
	dup2(file_fd, STDOUT_FILENO);
	close(file_fd);
	dup2(p->cmds_fd[i - 1][INPUT_END], STDIN_FILENO);
	close_all_pipes(p);
	exec_cmd(p->cmds_strs[i], envp, p);
}

static void	handle_middle_cmd(t_pipe *p, char *envp[], unsigned int i)
{
	dup2(p->cmds_fd[i - 1][INPUT_END], STDIN_FILENO);
	dup2(p->cmds_fd[i][OUTPUT_END], STDOUT_FILENO);
	close_all_pipes(p);
	exec_cmd(p->cmds_strs[i], envp, p);
}

static void	execute_child(t_pipe *p, char *files[2], char *envp[],
		unsigned int i)
{
	if (i == 0)
		handle_first_cmd(p, files[INPUT_END], envp, i);
	else if (i == p->num_cmds - 1)
		handle_last_cmd(p, files[OUTPUT_END], envp, i);
	else
		handle_middle_cmd(p, envp, i);
}

int	read_write_pipe(t_pipe *p, char *infile, char *outfile, char *envp[])
{
	char			*files[2];
	unsigned int	i;

	i = 0;
	files[0] = infile;
	files[1] = outfile;
	while (i < p->num_cmds)
	{
		p->childs[i] = fork();
		if (p->childs[i] == -1)
			return (ft_dprintf(STDERR_FILENO, "%s\n", strerror(errno)), 0);
		if (p->childs[i] == 0)
			execute_child(p, files, envp, i);
		i++;
	}
	close_all_pipes(p);
	return (1);
}
