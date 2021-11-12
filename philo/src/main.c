/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dev <dev@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 21:41:53 by dev               #+#    #+#             */
/*   Updated: 2021/11/12 23:34:15 by dev              ###   ########lyon.fr   */
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
		write(2, "Usage: nb_of_philo time_to_die time_to_eat time_to_sleep [meal_goal]\n", 69);
		return (EXIT_FAILURE);
	}
	i = 1;
	while (argv[i])
	{
		if (!ft_str_isdigit(argv[i]))
		{
			write(2, "philo: ", 7);
			write(2, argv[i], ft_strlen(argv[i]));
			write(2, ": Invalid argument\n", 19);
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_control all;

	if (arguments_checker(argc, argv) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	init_control_struct(&all, argv);
	return (EXIT_SUCCESS);
}