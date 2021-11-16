/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pthomas <pthomas@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 17:05:05 by pthomas           #+#    #+#             */
/*   Updated: 2021/11/16 17:08:16 by pthomas          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_control_struct(t_control *all, char **argv)
{
	all->args.nb_of_philo = ft_atol(argv[1]);
	all->args.nb_of_forks = all->args.nb_of_philo;
	all->args.time_to_die = ft_atol(argv[2]);
	all->args.time_to_eat = ft_atol(argv[3]);
	all->args.time_to_sleep = ft_atol(argv[4]);
	if (argv[5])
		all->args.meal_goal = ft_atol(argv[5]);
}

static int	arguments_checker(int argc, char **argv)
{
	size_t	i;

	if (argc < 5 || argc > 6)
	{
		write(STDERR_FILENO, "Usage: nb_of_philo time_to_die", 30);
		write(STDERR_FILENO, "time_to_eat time_to_sleep [meal_goal]\n", 38);
		return (EXIT_FAILURE);
	}
	i = 1;
	while (argv[i])
	{
		if (!ft_str_isdigit(argv[i]))
		{
			write(STDERR_FILENO, "philo: ", 7);
			write(STDERR_FILENO, argv[i], ft_strlen(argv[i]));
			write(STDERR_FILENO, ": Invalid argument\n", 19);
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_control	all;

	if (arguments_checker(argc, argv) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	init_control_struct(&all, argv);
	return (EXIT_SUCCESS);
}
