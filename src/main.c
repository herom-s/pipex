/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hermarti <hermarti@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 14:01:38 by hermarti          #+#    #+#             */
/*   Updated: 2025/10/22 14:34:33 by hermarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <fcntl.h>
#include <stdlib.h>
#include <sys/select.h>
#include <sys/wait.h>
#include <unistd.h>

static int	get_exit_code(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (EXIT_FAILURE);
}

static int	wait_all_children(t_pipe *pipe)
{
	unsigned int	i;
	int				status;

	i = 0;
	status = 0;
	while (i < pipe->num_cmds)
	{
		waitpid(pipe->childs[i], &status, 0);
		i++;
	}
	return (get_exit_code(status));
}

static int	init_all(t_pipe *pipe, int argc, char *argv[], char *envp[])
{
	char	***cmd_strs;

	cmd_strs = check_args(argc, argv, envp);
	if (!cmd_strs)
		return (-1);
	if (init_pipe(pipe, cmd_strs) < 0)
	{
		free_cmds_strs(cmd_strs, argc - 3);
		return (-1);
	}
	free_cmds_strs(cmd_strs, argc - 3);
	return (0);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipe	pipe;
	int		exit_code;

	if (init_all(&pipe, argc, argv, envp) < 0)
		return (EXIT_FAILURE);
	read_write_pipe(&pipe, argv[1], argv[argc - 1], envp);
	exit_code = wait_all_children(&pipe);
	destroy_pipe(&pipe);
	return (exit_code);
}
