/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pthomas <pthomas@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 17:05:05 by pthomas           #+#    #+#             */
/*   Updated: 2021/11/16 20:39:38 by pthomas          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	arguments_checker(int argc, char **argv)
{
	size_t	i;
	int		tmp;

	if (argc < 5 || argc > 6)
	{
		ft_putstr_fd("Usage: philo number_of_philosophers time_to_die time_to_eat \
time_to_sleep [number_of_times_each_philosopher_must_eat]\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	i = 1;
	while (argv[i])
	{
		tmp = ft_atoi(argv[i]) / ft_pow(10, ft_strlen(argv[i]) - 1);
		if (!ft_str_isdigit(argv[i]) || ft_atoi(argv[i]) < 0 || !tmp || tmp > 9)
		{
			ft_putstr_fd("philo: ", STDERR_FILENO);
			ft_putstr_fd(argv[i], STDERR_FILENO);
			ft_putstr_fd(": Invalid argument\n", STDERR_FILENO);
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

static void	free_data(t_data *data)
{
	size_t	i;

	free(data->philo);
	i = 0;
	while (i < data->nb_of_forks)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	free(data->forks);
	pthread_mutex_destroy(&data->speak);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (arguments_checker(argc, argv) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (init_data(&data, argv) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	// start_philosopher(&data);
	free_data(&data);
	return (EXIT_SUCCESS);
}

// data->start = get_time();
// data->philo[i].last_meal = data->start;
// pthread_create(&data->philo[i].thread, NULL, &routine, &data->philo[i]);
