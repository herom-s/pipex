/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hermarti <hermarti@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 17:41:48 by hermarti          #+#    #+#             */
/*   Updated: 2025/10/15 18:06:16 by hermarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex_bonus.h"
#include <unistd.h>

static char	**get_bin_paths(char *envp[])
{
	char	**default_paths;

	while (*envp && ft_strncmp(*envp, "PATH=", 5) != 0)
		envp++;
	if (!*envp)
	{
		default_paths = ft_calloc(6, sizeof(char *));
		if (!default_paths)
			return (NULL);
		default_paths[0] = ft_strdup("/usr/local/bin");
		default_paths[1] = ft_strdup("/usr/bin");
		default_paths[2] = ft_strdup("/bin");
		default_paths[3] = ft_strdup("/usr/sbin");
		default_paths[4] = ft_strdup("/sbin");
		default_paths[5] = NULL;
		return (default_paths);
	}
	return (ft_split(*envp + 5, ':'));
}

static void	set_parse_params(int argc, char *argv[], int *start_idx,
		int *num_cmds)
{
	*start_idx = 2;
	*num_cmds = argc - 3;
	if (ft_strcmp(argv[1], "here_doc") == 0)
	{
		*start_idx = 3;
		*num_cmds = argc - 4;
	}
}

char	***check_args(int argc, char *argv[], char *envp[])
{
	unsigned int	start_idx;
	int				num_cmds;
	char			***cmd_strs;
	char			**bin_paths;

	if (argc < 5 || (ft_strcmp(argv[1], "here_doc") == 0 && argc < 6))
		return (NULL);
	set_parse_params(argc, argv, (int *)&start_idx, &num_cmds);
	bin_paths = get_bin_paths(envp);
	if (!bin_paths)
		return (NULL);
	cmd_strs = ft_calloc(num_cmds + 1, sizeof(char **));
	if (!cmd_strs)
		return (free_split(bin_paths));
	if (!validate_commands(cmd_strs, bin_paths, argv, start_idx))
		return (free_split(bin_paths));
	free_split(bin_paths);
	return (cmd_strs);
}
