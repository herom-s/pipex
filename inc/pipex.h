/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hermarti <hermarti@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 17:31:25 by hermarti          #+#    #+#             */
/*   Updated: 2025/10/22 14:33:36 by hermarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <sys/types.h>
# define INPUT_END 0
# define OUTPUT_END 1

typedef enum e_pipe_type
{
	INPUT_FILE,
	OUTPUT_FILE
}					t_pipe_type;

typedef struct s_pipe
{
	int				files_fd[2];
	unsigned int	num_cmds;
	int				**cmds_fd;
	char			***cmds_strs;
	pid_t			*childs;
}					t_pipe;

int					init_pipe(t_pipe *p, char ***cmds_strs);
void				destroy_pipe(t_pipe *p);

int					read_write_pipe(t_pipe *p, char *infile, char *outfile,
						char *envp[]);
void				child_cleanup(t_pipe *p);
void				close_all_pipes(t_pipe *p);
int					open_file(char *filename, int flags, t_pipe *p);
void				exec_cmd(char **cmd, char *envp[], t_pipe *p);

char				***check_args(int argc, char *argv[], char *envp[]);
int					validate_commands(char ***cmd_strs, char **bin_paths,
						char *argv[]);

char				**split_args(char *cmd_arg);
int					count_args(char *cmd_arg);
void				skip_spaces(char **str);
void				skip_quoted(char **str);
void				skip_unquoted(char **str);

char				**allocate_cmd_str(char **cmd_split, int *count);
char				**build_cmd_str(char **cmd_split, char *bin_path);
void				free_cmds_strs(char ***cmds_strs, unsigned int num_cmds);
char				***create_cmds_strs(char ***cmds_strs,
						unsigned int num_cmds);

void				*free_split(char **arr);
#endif
