/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pthomas <pthomas@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 20:35:55 by pthomas           #+#    #+#             */
/*   Updated: 2021/11/19 15:18:53 by pthomas          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	init_philo(t_data *data)
{
	char	name[3];

	name[0] = 'p';
	name[1] = data->philo.index + '0';
	name[2] = '\0';
	data->philo.last_meal = data->start;
	data->philo.rights
		= sem_open(name, O_CREAT | O_EXCL, 0644, data->nb_of_forks);
	sem_unlink(name);
	sem_unlink("forks");
	sem_unlink("speak");
	sem_unlink("stop");
	sem_unlink("repletion");
	if (pthread_create(&data->philo.monitor, NULL, &death_checker, data))
	{
		print_error("pthread_create", NULL, NULL, errno);
		sem_post(data->stop);
	}
}

static int	init_sempahore(t_data *data)
{
	data->forks = sem_open("forks", O_CREAT | O_EXCL, 0644, data->nb_of_forks);
	data->speak = sem_open("speak", O_CREAT | O_EXCL, 0644, 1);
	data->stop = sem_open("stop", O_CREAT | O_EXCL, 0644, 0);
	data->repletion = sem_open("repletion", O_CREAT | O_EXCL, 0644, 0);
	if (data->forks == SEM_FAILED
		|| data->speak == SEM_FAILED
		|| data->stop == SEM_FAILED
		|| data->repletion == SEM_FAILED)
	{
		print_error("sem_open: ", NULL, NULL, errno);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	init_thread(t_data *data)
{
	if (pthread_create(&data->monitor, NULL, &repletion_checker, &data))
	{
		print_error("pthread_create", NULL, NULL, errno);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
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
	data->pid_philo = malloc(sizeof(pid_t) * data->nb_of_philo);
	if (!data->pid_philo)
	{
		print_error("malloc: ", NULL, NULL, ENOMEM);
		return (EXIT_FAILURE);
	}
	memset(data->pid_philo, 0, sizeof(pid_t) * data->nb_of_philo);
	if (init_thread(data) == EXIT_FAILURE
		|| init_sempahore(data) == EXIT_FAILURE)
	{
		free(data->pid_philo);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
