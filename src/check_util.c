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
#include "pipex.h"
#include <stdlib.h>
#include <unistd.h>

char	**allocate_cmd_str(char **cmd_split, int *count)
{
	char	**cmd_str;

	*count = 0;
	while (cmd_split[*count])
		(*count)++;
	cmd_str = ft_calloc(*count + 1, sizeof(char *));
	return (cmd_str);
}

char	**build_cmd_str(char **cmd_split, char *bin_path)
{
	char	**cmd_str;
	char	*tmp_str;
	int		count;
	int		j;

	cmd_str = allocate_cmd_str(cmd_split, &count);
	if (!cmd_str)
		return (NULL);
	tmp_str = ft_strjoin(bin_path, "/");
	cmd_str[0] = ft_strjoin(tmp_str, cmd_split[0]);
	free(tmp_str);
	j = 1;
	while (j < count)
	{
		cmd_str[j] = ft_strdup(cmd_split[j]);
		j++;
	}
	return (cmd_str);
}

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

static char	**is_command_valid(char **bin_paths, char *cmd_arg)
{
	char	**cmd_split;
	char	**cmd_str;
	int		i;

	cmd_split = split_args(cmd_arg);
	if (!cmd_split)
		return (NULL);
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
	cmd_str = ft_calloc(2, sizeof(char *));
	if (!cmd_str)
		return (free_split(cmd_split));
	cmd_str[0] = ft_strdup(cmd_split[0]);
	cmd_str[1] = NULL;
	free_split(cmd_split);
	return (cmd_str);
}

int	validate_commands(char ***cmd_strs, char **bin_paths, char *argv[])
{
	int	j;

	j = 2;
	while (argv[j + 1])
	{
		cmd_strs[j - 2] = is_command_valid(bin_paths, argv[j]);
		if (!cmd_strs[j - 2])
		{
			free_cmds_strs(cmd_strs, j - 2);
			return (0);
		}
		j++;
	}
	cmd_strs[j - 2] = NULL;
	return (1);
}
