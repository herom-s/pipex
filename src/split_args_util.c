/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args_util.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hermarti <hermarti@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 16:15:10 by hermarti          #+#    #+#             */
/*   Updated: 2025/10/18 16:15:46 by hermarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	skip_spaces(char **str)
{
	while (**str == ' ')
		(*str)++;
}

void	skip_quoted(char **str)
{
	char	quote;

	quote = **str;
	(*str)++;
	while (**str != quote && **str != '\0')
		(*str)++;
	if (**str != '\0')
		(*str)++;
}

void	skip_unquoted(char **str)
{
	while (**str != ' ' && **str != '\0')
		(*str)++;
}
