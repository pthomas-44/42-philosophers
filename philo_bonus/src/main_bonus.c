/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pthomas <pthomas@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 17:05:05 by pthomas           #+#    #+#             */
/*   Updated: 2021/11/23 19:04:20 by pthomas          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

static void	kill_philosophers(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->nb_of_philo)
	{
		kill(data->pid_philo[i], SIGKILL);
		i++;
	}
}

static void	free_data(t_data *data)
{
	free(data->pid_philo);
	if (sem_close(data->forks))
		print_error("sem_close: ", NULL, NULL, EINVAL);
	if (sem_close(data->speak))
		print_error("sem_close: ", NULL, NULL, EINVAL);
	if (sem_close(data->stop))
		print_error("sem_close: ", NULL, NULL, EINVAL);
	if (sem_close(data->repletion))
		print_error("sem_close: ", NULL, NULL, EINVAL);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (arguments_checker(argc, argv) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (init_data(&data, argv) == EXIT_FAILURE)
	{
		free_data(&data);
		return (EXIT_FAILURE);
	}
	if (start_philosopher(&data) == EXIT_FAILURE)
	{
		free_data(&data);
		return (EXIT_FAILURE);
	}
	kill_philosophers(&data);
	free_data(&data);
	return (EXIT_SUCCESS);
}
