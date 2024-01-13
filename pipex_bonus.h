/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-jira <mel-jira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 14:52:26 by mel-jira          #+#    #+#             */
/*   Updated: 2024/01/13 17:46:50 by mel-jira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# include <stdio.h>
# include <strings.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/wait.h>

typedef struct s_list
{
	int				lastpipe;
	int				here_doc;
	int				i;
	char			*path;
	int				f;
	pid_t			pid;
	char			*cmd;
	char			**allcmd;
	char			*cmdpath;
	char			**argv;
	char			**envp;
	int				argc;
}	t_list;

size_t	ft_strlen(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	ft_putstr(char *str);

void	free_strings(char **strs);
char	*find_path(char **strs);
char	*get_command(char **paths, char *command);
void	free_everything(t_list *info);

char	*get_next_line(int fd);
char	*ft_strchr(char *str, char c);
int		ft_strlenx(char *str);
char	*ft_strjoinx(char *remain, char *buffer);
char	*ft_strdup(char *str);
char	*ft_read_file(int fd, char *remain);
char	*ft_get_line(char *remain);
char	*ft_remove_line(char *remain);

void	get_info(t_list **info, char **argv, char **paths, int x);
void	clean_and_save(t_list **info, int*fd);
void	first_cmd(char **argv, char **paths, int *fd, t_list *info);
void	midle_cmd(char **argv, char **paths, t_list *info);
void	last_cmd(char **argv, char **paths, t_list *info);
void	check_heredoc(t_list *info);
void	short_here_doc_line(t_list **info, char **argv);
void	short_normal_line(t_list **info, char **argv);
void	short_fun_midle(t_list **info, int *pipefd);

#endif
