/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pthomas <pthomas@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 20:35:55 by pthomas           #+#    #+#             */
/*   Updated: 2021/11/17 19:35:26 by pthomas          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	init_philo(t_data *data, t_philo *philo)
{
	char	name[3];

	name[0] = 'p';
	name[1] = philo->index + '0';
	name[2] = '\0';
	philo->last_meal = data->start;
	philo->meal_goal = data->meal_goal;
	if (pthread_create(philo->thread, NULL, &death_checker, &philo))
	{
		print_error("pthread_create", NULL, NULL, errno);
		sem_post(data->stop);
		return (EXIT_FAILURE);
	}
	philo->rights = sem_open(name, O_CREAT | O_EXCL, 0644, data->nb_of_forks);
	sem_unlink(name);
	sem_unlink("forks");
	sem_unlink("speak");
	sem_unlink("stop");
}

static int	init_sempahore(t_data *data)
{
	data->forks = sem_open("forks", O_CREAT | O_EXCL, 0644, data->nb_of_forks);
	if (data->forks == SEM_FAILED)
	{
		print_error("sem_open: ", NULL, NULL, errno);
		return (EXIT_FAILURE);
	}
	data->speak = sem_open("speak", O_CREAT | O_EXCL, 0644, 1);
	if (data->speak == SEM_FAILED)
	{
		sem_close(data->forks);
		print_error("sem_open: ", NULL, NULL, errno);
		return (EXIT_FAILURE);
	}
	data->stop = sem_open("stop", O_CREAT | O_EXCL, 0644, 0);
	if (data->stop == SEM_FAILED)
	{
		sem_close(data->forks);
		sem_close(data->speak);
		print_error("sem_open: ", NULL, NULL, errno);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	init_thread(t_data *data)
{
	if (pthread_create(data->thread, NULL, &repletion_checker, &data))
	{
		print_error("pthread_create", NULL, NULL, errno);
		return (EXIT_FAILURE);
	}
}

int	init_data(t_data *data, char **argv)
{
	memset(data, 0, sizeof(t_data));
	data->nb_of_philo = ft_atoi(argv[1]);
	data->nb_of_forks = data->nb_of_philo;
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		data->meal_goal = ft_atoi(argv[5]);
	data->philo = malloc(sizeof(pid_t) * data->nb_of_philo);
	if (!data->philo)
	{
		print_error("malloc: ", NULL, NULL, ENOMEM);
		return (EXIT_FAILURE);
	}
	memset(data->philo, 0, sizeof(pid_t) * data->nb_of_philo);
	if (init_thread(data) == EXIT_FAILURE
		|| init_sempahore(data) == EXIT_FAILURE)
	{
		free(data->philo);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
