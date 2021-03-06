/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pthomas <pthomas@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 17:04:51 by pthomas           #+#    #+#             */
/*   Updated: 2021/11/26 14:15:57 by pthomas          ###   ########lyon.fr   */
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

/*** ~~ DEFINES ~~ ***/

# define EAT		0
# define SLEEP		1
# define THINK		2
# define TAKE_FORK	3
# define USAGE_MSG	"philo number_of_philosophers time_to_die time_to_eat \
time_to_sleep [number_of_times_each_philosopher_must_eat]\n"

/*** ~~ STRUCTURES ~~ ***/

// ~~ Philospher struct

typedef struct s_philo
{
	pthread_t		thread;
	size_t			index;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	time_t			last_meal;
	size_t			nb_of_meal;
	bool			stop;
	t_data			*data;
}					t_philo;

// ~~ Data struct

typedef struct s_data
{
	t_philo			*philo;
	pthread_mutex_t	*forks;
	pthread_mutex_t	speak;
	time_t			start;
	bool			stop;
	size_t			nb_of_philo;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	size_t			meal_goal;
}					t_data;

/*** ~~ PROTOTYPES ~~ ***/

// ~~ init.c
int				init_data(t_data *data, char **argv);
// ~~ program.c
int				start_philosopher(t_data *data);
// ~~ libft_functions.c
void			ft_putstr_fd(const char *s, int fd);
size_t			ft_strlen(const char *str);
int				ft_str_isdigit(char *str);
int				ft_atoi_is_overflow(const char *str, int *nb);
// ~~ utils.c
time_t			get_time(void);
void			print_action(t_philo *philo, char *action);
void			print_error(char *cmd, char *value, char *error, int status);
void			custom_usleep(time_t microseconds, t_data *data);

#endif
