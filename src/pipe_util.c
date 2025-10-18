/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hermarti <hermarti@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 17:41:51 by hermarti          #+#    #+#             */
/*   Updated: 2025/10/16 17:43:06 by hermarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	free_cmds_strs(char ***cmds_strs, unsigned int num_cmds)
{
	unsigned int	i;
	unsigned int	j;

	if (!cmds_strs)
		return ;
	i = 0;
	while (i < num_cmds)
	{
		if (cmds_strs[i])
		{
			j = 0;
			while (cmds_strs[i][j])
			{
				free(cmds_strs[i][j]);
				j++;
			}
			free(cmds_strs[i]);
		}
		i++;
	}
	free(cmds_strs);
}

static char	**copy_cmd_str(char **cmd_str)
{
	char			**res;
	unsigned int	j;

	j = 0;
	while (cmd_str[j])
		j++;
	res = ft_calloc(j + 1, sizeof(char *));
	if (!res)
		return (NULL);
	j = 0;
	while (cmd_str[j])
	{
		res[j] = ft_strdup(cmd_str[j]);
		if (!res[j])
			return (NULL);
		j++;
	}
	return (res);
}

char	***create_cmds_strs(char ***cmds_strs, unsigned int num_cmds)
{
	char			***res;
	unsigned int	i;

	if (!cmds_strs)
		return (NULL);
	res = ft_calloc(num_cmds + 1, sizeof(char **));
	if (!res)
		return (NULL);
	i = 0;
	while (i < num_cmds)
	{
		res[i] = copy_cmd_str(cmds_strs[i]);
		if (!res[i])
			return (free_cmds_strs(res, i), NULL);
		i++;
	}
	return (res);
}
