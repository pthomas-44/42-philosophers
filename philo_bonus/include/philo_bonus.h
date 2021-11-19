/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pthomas <pthomas@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 17:04:51 by pthomas           #+#    #+#             */
/*   Updated: 2021/11/19 14:32:53 by pthomas          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

/*** ~~ LIBS ~~ ***/

# include <string.h>
# include <stdio.h>
# include <unistd.h>
# include <errno.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdbool.h>
# include <limits.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <semaphore.h>
# include <signal.h>

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
	pthread_t		monitor;
	sem_t			*rights;
	unsigned int	index;
	time_t			last_meal;
	size_t			nb_of_meal;
	size_t			meal_goal;
}					t_philo;

// ~~ Datas struct

typedef struct s_data
{
	t_philo			philo;
	pid_t			*pid_philo;
	sem_t			*forks;
	sem_t			*speak;
	sem_t			*stop;
	sem_t			*repletion;
	pthread_t		monitor;
	time_t			start;
	size_t			nb_of_philo;
	size_t			nb_of_forks;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	size_t			meal_goal;
}					t_data;

/*** ~~ PROTOTYPES ~~ ***/

// ~~ init_bonus.c
int				init_data(t_data *data, char **argv);
void			init_philo(t_data *data);
// ~~ program_bonus.c
int				start_philosopher(t_data *data);
void			*death_checker(void *arg);
void			*repletion_checker(void *arg);
// ~~ libft_functions_bonus.c
int				ft_str_isdigit(char *str);
size_t			ft_strlen(const char *str);
int				ft_atoi(const char *str);
void			ft_putstr_fd(const char *s, int fd);
int				ft_atoi_is_overflow(const char *str, int *nb);
// ~~ utils_bonus.c
time_t			get_time(void);
void			print_action(t_data *data, t_philo *philo, char *action);
void			print_error(char *cmd, char *value, char *error, int status);
void			spin_lock(time_t starting_time, time_t waiting_time);
void			custom_usleep(long long microseconds);

#endif
