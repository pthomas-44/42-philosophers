/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pthomas <pthomas@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 17:05:05 by pthomas           #+#    #+#             */
/*   Updated: 2021/11/17 02:02:01 by pthomas          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	arguments_checker(int argc, char **argv)
{
	size_t	i;
	int		tmp;

	if (argc < 5 || argc > 6)
	{
		print_error("Usage: ", NULL, "philo number_of_philosophers time_to_die time_to_eat \
time_to_sleep [number_of_times_each_philosopher_must_eat\n", -1);
		return (EXIT_FAILURE);
	}
	i = 1;
	while (argv[i])
	{
		tmp = ft_atoi(argv[i]) / ft_pow(10, ft_strlen(argv[i]) - 1);
		if (!ft_str_isdigit(argv[i]) || ft_atoi(argv[i]) < 1 || !tmp || tmp > 9)
		{
			print_error(NULL, argv[i], NULL, EINVAL);
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

static void	free_data(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->nb_of_philo)
	{
		pthread_join(data->philo[i].thread, NULL);
		i++;
	}
	free(data->philo);
	i = 0;
	while (i < data->nb_of_forks)
	{
		if (pthread_mutex_destroy(&data->forks[i]))
			print_error("pthread: ", NULL, NULL, errno);
		i++;
	}
	free(data->forks);
	if (pthread_mutex_destroy(&data->speak))
		print_error("pthread: ", NULL, NULL, errno);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (arguments_checker(argc, argv) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (init_data(&data, argv) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (start_philosopher(&data) == EXIT_FAILURE)
	{
		free_data(&data);
		return (EXIT_FAILURE);
	}
	free_data(&data);
	return (EXIT_SUCCESS);
}
