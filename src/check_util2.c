/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_util2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hermarti <hermarti@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 16:42:21 by hermarti          #+#    #+#             */
/*   Updated: 2025/10/22 16:44:52 by hermarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

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
