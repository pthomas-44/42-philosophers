/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pthomas <pthomas@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 20:35:55 by pthomas           #+#    #+#             */
/*   Updated: 2021/11/17 00:11:58 by pthomas          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_philo(t_data *data)
{
	size_t	i;

	i = 0;
	memset(data->philo, 0, sizeof(t_philo) * data->nb_of_philo);
	while (i < data->nb_of_philo)
	{
		data->philo[i].data = data;
		data->philo[i].index = i;
		data->philo[i].left_fork = &data->forks[i];
		if (i == data->nb_of_philo - 1)
			data->philo[i].right_fork = &data->forks[0];
		else
			data->philo[i].right_fork = &data->forks[i + 1];
		data->philo[i].nb_of_meal = 0;
		i++;
	}
}

static int	init_mutex(t_data *data)
{
	size_t	i;

	i = 0;
	memset(data->forks, 0, sizeof(pthread_mutex_t) * data->nb_of_forks);
	while (i < data->nb_of_forks)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			break ;
		i++;
	}
	if (i-- != data->nb_of_forks || pthread_mutex_init(&data->speak, NULL))
	{
		print_error("pthread: ", NULL, NULL, errno);
		while (i)
		{
			if (pthread_mutex_destroy(&data->forks[i]))
				print_error("pthread: ", NULL, NULL, errno);
			i--;
		}
		free(data->philo);
		free(data->forks);
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
	data->stop = false;
	data->philo = malloc(sizeof(t_philo) * data->nb_of_philo);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_of_forks);
	if (!data->philo || !data->forks)
	{
		print_error("malloc: ", NULL, NULL, ENOMEM);
		return (EXIT_FAILURE);
	}
	if (init_mutex(data) == -1)
		return (EXIT_FAILURE);
	init_philo(data);
	return (EXIT_SUCCESS);
}
