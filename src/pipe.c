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
#include "pipex.h"
#include <unistd.h>

static void	cleanup_init(t_pipe *p)
{
	if (p->files_fd[INPUT_END] >= 0)
		close(p->files_fd[INPUT_END]);
	if (p->files_fd[OUTPUT_END] >= 0)
		close(p->files_fd[OUTPUT_END]);
	if (p->cmds_fd)
	{
		if (p->cmds_fd[INPUT_END] >= 0)
			close(p->cmds_fd[INPUT_END]);
		if (p->cmds_fd[OUTPUT_END] >= 0)
			close(p->cmds_fd[OUTPUT_END]);
		free(p->cmds_fd);
	}
	if (p->childs)
		free(p->childs);
}

int	init_pipe(t_pipe *p, char ***cmds_strs)
{
	unsigned int	i;

	ft_memset(p, 0, sizeof(t_pipe));
	i = 0;
	while (cmds_strs[i])
		i++;
	p->num_cmds = i;
	p->cmds_fd = ft_calloc(2, sizeof(int));
	p->childs = ft_calloc(i, sizeof(pid_t));
	if (!p->cmds_fd || !p->childs)
		return (cleanup_init(p), -1);
	if (pipe(p->cmds_fd) != 0)
		return (cleanup_init(p), -1);
	p->cmds_strs = create_cmds_strs(cmds_strs, p->num_cmds);
	if (!p->cmds_strs)
		return (cleanup_init(p), -1);
	return (1);
}

void	destroy_pipe(t_pipe *p)
{
	if (p->files_fd[INPUT_END] >= 0)
		close(p->files_fd[INPUT_END]);
	if (p->files_fd[OUTPUT_END] >= 0)
		close(p->files_fd[OUTPUT_END]);
	if (p->cmds_fd)
	{
		if (p->cmds_fd[INPUT_END] >= 0)
			close(p->cmds_fd[INPUT_END]);
		if (p->cmds_fd[OUTPUT_END] >= 0)
			close(p->cmds_fd[OUTPUT_END]);
		free(p->cmds_fd);
	}
	if (p->childs)
		free(p->childs);
	if (p->cmds_strs)
		free_cmds_strs(p->cmds_strs, p->num_cmds);
}
