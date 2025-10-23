/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hermarti <hermarti@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 17:34:48 by hermarti          #+#    #+#             */
/*   Updated: 2025/10/15 18:32:47 by hermarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex_bonus.h"
#include <unistd.h>

static int	cleanup_init(t_pipe *p)
{
	unsigned int	i;

	i = 0;
	if (p->files_fd[INPUT_END] >= 0)
		close(p->files_fd[INPUT_END]);
	if (p->files_fd[OUTPUT_END] >= 0)
		close(p->files_fd[OUTPUT_END]);
	if (p->cmds_fd)
	{
		while (i < p->num_cmds - 1)
		{
			if (p->cmds_fd[i][INPUT_END] >= 0)
				close(p->cmds_fd[i][INPUT_END]);
			if (p->cmds_fd[i][OUTPUT_END] >= 0)
				close(p->cmds_fd[i][OUTPUT_END]);
			free(p->cmds_fd[i]);
			i++;
		}
		free(p->cmds_fd);
	}
	if (p->childs)
		free(p->childs);
	return (-1);
}

static int	create_pipes(t_pipe *p)
{
	unsigned int	i;

	i = 0;
	while (i < p->num_cmds - 1)
	{
		p->cmds_fd[i] = ft_calloc(2, sizeof(int));
		if (!p->cmds_fd[i])
			return (cleanup_init(p));
		if (pipe(p->cmds_fd[i]) != 0)
		{
			free(p->cmds_fd[i]);
			p->cmds_fd[i] = NULL;
			return (cleanup_init(p));
		}
		i++;
	}
	return (0);
}

int	init_pipe(t_pipe *p, char ***cmds_strs)
{
	unsigned int	i;

	ft_memset(p, 0, sizeof(t_pipe));
	i = 0;
	while (cmds_strs[i])
		i++;
	p->num_cmds = i;
	p->cmds_fd = ft_calloc(p->num_cmds - 1, sizeof(int *));
	p->childs = ft_calloc(i, sizeof(pid_t));
	if (!p->cmds_fd || !p->childs)
		return (cleanup_init(p));
	if (create_pipes(p) != 0)
		return (-1);
	p->cmds_strs = create_cmds_strs(cmds_strs, p->num_cmds);
	if (!p->cmds_strs)
		return (cleanup_init(p));
	return (1);
}

void	destroy_pipe(t_pipe *p)
{
	unsigned int	i;

	i = 0;
	if (p->files_fd[INPUT_END] >= 0)
		close(p->files_fd[INPUT_END]);
	if (p->files_fd[OUTPUT_END] >= 0)
		close(p->files_fd[OUTPUT_END]);
	if (p->cmds_fd)
	{
		while (i < p->num_cmds - 1)
		{
			if (p->cmds_fd[i][INPUT_END] >= 0)
				close(p->cmds_fd[i][INPUT_END]);
			if (p->cmds_fd[i][OUTPUT_END] >= 0)
				close(p->cmds_fd[i][OUTPUT_END]);
			free(p->cmds_fd[i]);
			i++;
		}
		free(p->cmds_fd);
	}
	if (p->childs)
		free(p->childs);
	if (p->cmds_strs)
		free_cmds_strs(p->cmds_strs, p->num_cmds);
}
