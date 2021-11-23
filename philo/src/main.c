/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pthomas <pthomas@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 17:05:05 by pthomas           #+#    #+#             */
/*   Updated: 2021/11/23 13:07:20 by pthomas          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	arguments_checker(int argc, char **argv)
{
	size_t	i;
	int		tmp;

	if (argc < 5 || argc > 6)
	{
		print_error("Usage: ", NULL, USAGE_MSG, -1);
		return (EXIT_FAILURE);
	}
	i = 1;
	while (argv[i])
	{
		if (!ft_str_isdigit(argv[i])
			|| ft_atoi_is_overflow(argv[i], &tmp) || tmp == 0)
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
	while (i < data->nb_of_philo)
	{
		if (pthread_mutex_destroy(&data->philo[i].meal_mutex))
			print_error("pthread: ", NULL, NULL, errno);
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
