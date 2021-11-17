/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pthomas <pthomas@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 12:24:04 by pthomas           #+#    #+#             */
/*   Updated: 2021/11/16 16:31:44 by pthomas          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//~~ Print les erreurs types du bash

void	print_error(char *cmd, char *value, char *error, int status)
{
	errno = status;
	g_error_number = status;
	ft_putstr_fd("potatoshell: ", STDERR_FILENO);
	if (cmd)
		ft_putstr_fd(cmd, STDERR_FILENO);
	if (value)
	{
		ft_putstr_fd(value, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	if (errno != 258 && errno != EXIT_FAILURE
		&& errno != 127 && errno != 255 && errno != 3)
		perror(NULL);
	if (error)
		ft_putstr_fd(error, STDERR_FILENO);
}

//~~ Free la structure t_cmds

void	free_cmds_struct(t_structs *s)
{
	size_t	i;

	i = 0;
	while (s->cmds && i < s->cmds_size)
	{
		free_array(&s->cmds[i].cmd, 0);
		free(s->cmds[i].path);
		s->cmds[i].path = NULL;
		i++;
	}
	free(s->cmds);
	s->cmds = NULL;
	s->cmds_size = 0;
}

//~~ Affiche les messages d'erreur et libere toute la memoire allouee

void	free_all(t_structs *s, bool is_child)
{
	if (!is_child)
		if (tcsetattr(STDIN_FILENO, TCSANOW, &s->old_term) == -1)
			print_error("termios: ", NULL, NULL, errno);
	free(s->parse_line[0]);
	s->parse_line[0] = NULL;
	free(s->parse_line[1]);
	s->parse_line[1] = NULL;
	free_cmds_struct(s);
	env_clear(s);
	rl_clear_history();
}
