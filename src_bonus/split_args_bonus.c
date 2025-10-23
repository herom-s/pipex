/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hermarti <hermarti@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 16:13:50 by hermarti          #+#    #+#             */
/*   Updated: 2025/10/18 16:16:00 by hermarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex_bonus.h"

int	count_args(char *cmd_arg)
{
	char	*ptr;
	int		count;

	ptr = cmd_arg;
	count = 0;
	while (*ptr)
	{
		skip_spaces(&ptr);
		if (*ptr == '\0')
			break ;
		count++;
		if (*ptr == '\'' || *ptr == '\"')
			skip_quoted(&ptr);
		else
			skip_unquoted(&ptr);
	}
	return (count);
}

static void	extract_quoted(char **end, char **start, char **splited, int *i)
{
	char	quote;

	quote = **end;
	(*end)++;
	*start = *end;
	while (**end != quote && **end != '\0')
		(*end)++;
	splited[*i] = ft_substrp(*start, *start, (*end - *start));
	(*i)++;
	if (**end != '\0')
		(*end)++;
}

static void	extract_unquoted(char **end, char **start, char **splited, int *i)
{
	*start = *end;
	skip_unquoted(end);
	splited[*i] = ft_substrp(*start, *start, (*end - *start));
	(*i)++;
}

char	**split_args(char *cmd_arg)
{
	char	**splited;
	char	*start;
	char	*end;
	int		i;

	splited = ft_calloc(count_args(cmd_arg) + 1, sizeof(char *));
	end = cmd_arg;
	i = 0;
	while (*end)
	{
		skip_spaces(&end);
		if (*end == '\0')
			break ;
		if (*end == '\'' || *end == '\"')
			extract_quoted(&end, &start, splited, &i);
		else
			extract_unquoted(&end, &start, splited, &i);
	}
	splited[i] = NULL;
	return (splited);
}
