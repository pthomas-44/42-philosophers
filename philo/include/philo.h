/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pthomas <pthomas@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 17:04:51 by pthomas           #+#    #+#             */
/*   Updated: 2021/11/16 17:04:53 by pthomas          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/*** ~~ LIBS ~~ ***/

# include <string.h>
# include <stdio.h>
# include <unistd.h>
# include <errno.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

/*** ~~ STRUCTURES ~~ ***/

// ~~ Arguments struct

typedef struct s_args
{
	size_t			nb_of_philo;
	size_t			nb_of_forks;
	suseconds_t		time_to_die;
	suseconds_t		time_to_eat;
	suseconds_t		time_to_sleep;
	size_t			meal_goal;
}					t_args;


// ~~ Control struct

typedef struct	s_control
{
	t_args			args;
	struct timeval	starting_time;
	struct timeval	current_time;
}					t_control;

// ~~ Command line struct

/*** ~~ PROTOTYPES ~~ ***/

// ~~ utils.c
int		ft_str_isdigit(char *str);
size_t	ft_strlen(char *str);
long	ft_atol(const char *str);

#endif
