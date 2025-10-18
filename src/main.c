/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hermarti <hermarti@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 14:01:38 by hermarti          #+#    #+#             */
/*   Updated: 2025/10/16 18:29:14 by hermarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <sys/wait.h>
#include <unistd.h>

static void	child_cleanup(t_pipe *p)
{
	free_cmds_strs(p->cmds_strs, p->num_cmds);
	free(p->cmds_fd);
	free(p->childs);
}

int	read_pipe(t_pipe *p, char *infile, char *envp[])
{
	int	infile_fd;

	p->childs[INPUT_END] = fork();
	if (p->childs[INPUT_END] == -1)
	{
		ft_dprintf(STDERR_FILENO, "%s\n", strerror(errno));
		return (0);
	}
	if (p->childs[INPUT_END] == 0)
	{
		infile_fd = open(infile, O_RDONLY);
		if (infile_fd == -1)
		{
			ft_dprintf(STDERR_FILENO, "pipex: %s: %s\n", infile,
				strerror(errno));
			close(p->cmds_fd[INPUT_END]);
			close(p->cmds_fd[OUTPUT_END]);
			child_cleanup(p);
			exit(EXIT_FAILURE);
		}
		dup2(infile_fd, STDIN_FILENO);
		close(infile_fd);
		dup2(p->cmds_fd[OUTPUT_END], STDOUT_FILENO);
		close(p->cmds_fd[INPUT_END]);
		close(p->cmds_fd[OUTPUT_END]);
		if (execve(p->cmds_strs[0][0], p->cmds_strs[0], envp) < 0)
		{
			ft_dprintf(STDERR_FILENO, "pipex: %s: command not found\n",
				p->cmds_strs[0][0]);
			child_cleanup(p);
			exit(127);
		}
	}
	close(p->cmds_fd[OUTPUT_END]);
	return (1);
}

int	write_pipe(t_pipe *p, char *outfile, char *envp[])
{
	int	outfile_fd;

	p->childs[OUTPUT_END] = fork();
	if (p->childs[OUTPUT_END] == -1)
	{
		ft_dprintf(STDERR_FILENO, "%s\n", strerror(errno));
		return (0);
	}
	if (p->childs[OUTPUT_END] == 0)
	{
		outfile_fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (outfile_fd == -1)
		{
			ft_dprintf(STDERR_FILENO, "pipex: %s: %s\n", outfile,
				strerror(errno));
			close(p->cmds_fd[INPUT_END]);
			close(p->cmds_fd[OUTPUT_END]);
			child_cleanup(p);
			exit(EXIT_FAILURE);
		}
		dup2(outfile_fd, STDOUT_FILENO);
		close(outfile_fd);
		dup2(p->cmds_fd[INPUT_END], STDIN_FILENO);
		close(p->cmds_fd[INPUT_END]);
		close(p->cmds_fd[OUTPUT_END]);
		if (execve(p->cmds_strs[1][0], p->cmds_strs[1], envp) < 0)
		{
			ft_dprintf(STDERR_FILENO, "pipex: %s: command not found\n",
				p->cmds_strs[1][0]);
			child_cleanup(p);
			exit(127);
		}
	}
	close(p->cmds_fd[INPUT_END]);
	return (1);
}

int	main(int argc, char *argv[], char *envp[])
{
	int		status;
	int		exit_code;
	char	***cmd_strs;
	t_pipe	pipe;

	cmd_strs = check_args(argc, argv, envp);
	if (!cmd_strs)
		return (EXIT_FAILURE);
	if (init_pipe(&pipe, cmd_strs) < 0)
	{
		free_cmds_strs(cmd_strs, argc - 3);
		return (EXIT_FAILURE);
	}
	free_cmds_strs(cmd_strs, argc - 3);
	read_pipe(&pipe, argv[1], envp);
	write_pipe(&pipe, argv[argc - 1], envp);
	waitpid(pipe.childs[INPUT_END], &status, 0);
	waitpid(pipe.childs[OUTPUT_END], &status, 0);
	destroy_pipe(&pipe);
	if (WIFEXITED(status))
		exit_code = WEXITSTATUS(status);
	else
		exit_code = EXIT_FAILURE;
	return (exit_code);
}
