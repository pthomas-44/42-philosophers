/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pthomas <pthomas@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 17:04:51 by pthomas           #+#    #+#             */
/*   Updated: 2021/11/16 20:39:14 by pthomas          ###   ########lyon.fr   */
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
# include <stdbool.h>

/*** ~~ TYPES ~~ ***/

typedef struct s_philo	t_philo;
typedef struct s_data	t_data;

/*** ~~ STRUCTURES ~~ ***/

// ~~ Philospher struct

typedef struct s_philo
{
	unsigned int	index;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	time_t			last_meal;
	t_data			*data;
}					t_philo;

// ~~ Datas struct

typedef struct s_data
{
	t_philo			*philo;
	pthread_mutex_t	*forks;
	pthread_mutex_t	speak;
	time_t			start;
	bool			stop;
	size_t			nb_of_philo;
	size_t			nb_of_forks;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	size_t			meal_goal;
}					t_data;

// ~~ Command line struct

/*** ~~ PROTOTYPES ~~ ***/

// ~~ init.c
int				init_data(t_data *data, char **argv);
// ~~ libft_functions.c
int				ft_str_isdigit(char *str);
size_t			ft_strlen(const char *str);
int				ft_atoi(const char *str);
void			ft_putstr_fd(const char *s, int fd);
unsigned long	ft_pow(int nb, size_t exp);
// ~~ utils.c
time_t			get_time(void);

#endif
