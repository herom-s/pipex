/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hermarti <hermarti@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 17:38:50 by hermarti          #+#    #+#             */
/*   Updated: 2025/10/16 17:38:55 by hermarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex_bonus.h"
#include <stdlib.h>
#include <unistd.h>

static int	check_path(char *path, char *argv)
{
	char	*tmp_path;
	char	*full_path;
	int		result;

	tmp_path = ft_strjoin(path, "/");
	full_path = ft_strjoin(tmp_path, argv);
	free(tmp_path);
	result = access(full_path, X_OK);
	free(full_path);
	return (result == 0);
}

static char	**create_fallback_cmd(char **cmd_split)
{
	char	**cmd_str;

	cmd_str = ft_calloc(2, sizeof(char *));
	if (!cmd_str)
		return (free_split(cmd_split));
	cmd_str[0] = ft_strdup(cmd_split[0]);
	cmd_str[1] = NULL;
	free_split(cmd_split);
	return (cmd_str);
}

static char	**is_command_valid(char **bin_paths, char *cmd_arg)
{
	char	**cmd_split;
	char	**cmd_str;
	int		i;

	cmd_split = split_args(cmd_arg);
	if (!cmd_split || !cmd_split[0])
	{
		if (cmd_split)
			free_split(cmd_split);
		return (NULL);
	}
	i = 0;
	while (bin_paths[i])
	{
		if (check_path(bin_paths[i], cmd_split[0]))
		{
			cmd_str = build_cmd_str(cmd_split, bin_paths[i]);
			free_split(cmd_split);
			return (cmd_str);
		}
		i++;
	}
	return (create_fallback_cmd(cmd_split));
}

int	validate_commands(char ***cmd_strs, char **bin_paths, char *argv[],
		unsigned int start_idx)
{
	int	i;
	int	j;

	i = 0;
	j = start_idx;
	while (argv[j + 1])
	{
		cmd_strs[i] = is_command_valid(bin_paths, argv[j]);
		if (!cmd_strs[i])
		{
			free_cmds_strs(cmd_strs, i);
			return (0);
		}
		j++;
		i++;
	}
	cmd_strs[i] = NULL;
	return (1);
}
