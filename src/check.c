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
#include "pipex.h"
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

char	***check_args(int argc, char *argv[], char *envp[])
{
	char	***cmd_strs;
	char	**bin_paths;

	if (argc != 5)
		return (NULL);
	bin_paths = get_bin_paths(envp);
	if (!bin_paths)
		return (NULL);
	cmd_strs = ft_calloc((argc - 3) + 1, sizeof(char **));
	if (!cmd_strs)
		return (free_split(bin_paths), NULL);
	if (!validate_commands(cmd_strs, bin_paths, argv))
	{
		free_split(bin_paths);
		return (NULL);
	}
	free_split(bin_paths);
	return (cmd_strs);
}
