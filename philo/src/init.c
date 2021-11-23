/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pthomas <pthomas@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 20:35:55 by pthomas           #+#    #+#             */
/*   Updated: 2021/11/23 13:08:04 by pthomas          ###   ########lyon.fr   */
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
		data->philo[i].index = i + 1;
		data->philo[i].left_fork = &data->forks[i];
		if (i == data->nb_of_philo - 1)
			data->philo[i].right_fork = &data->forks[0];
		else
			data->philo[i].right_fork = &data->forks[i + 1];
		i++;
	}
}

static int	init_mutex(t_data *data)
{
	int	i;

	i = 0;
	memset(data->forks, 0, sizeof(pthread_mutex_t) * data->nb_of_philo);
	while (i < (int)data->nb_of_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			break ;
		if (pthread_mutex_init(&data->philo[i].meal_mutex, NULL))
			break ;
		i++;
	}
	if (i-- != (int)data->nb_of_philo || pthread_mutex_init(&data->speak, NULL))
	{
		print_error("pthread: ", NULL, NULL, errno);
		while (i > -1)
		{
			if (pthread_mutex_destroy(&data->forks[i]))
				print_error("pthread: ", NULL, NULL, errno);
			if (pthread_mutex_destroy(&data->philo[i].meal_mutex))
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
	ft_atoi_is_overflow(argv[1], (int *)&data->nb_of_philo);
	ft_atoi_is_overflow(argv[2], (int *)&data->time_to_die);
	ft_atoi_is_overflow(argv[3], (int *)&data->time_to_eat);
	ft_atoi_is_overflow(argv[4], (int *)&data->time_to_sleep);
	if (argv[5])
		ft_atoi_is_overflow(argv[5], (int *)&data->meal_goal);
	data->philo = malloc(sizeof(t_philo) * data->nb_of_philo);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_of_philo);
	if (!data->philo || !data->forks)
	{
		free(data->philo);
		free(data->forks);
		print_error("malloc: ", NULL, NULL, ENOMEM);
		return (EXIT_FAILURE);
	}
	if (init_mutex(data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	init_philo(data);
	return (EXIT_SUCCESS);
}
