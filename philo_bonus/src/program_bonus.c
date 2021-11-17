/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pthomas <pthomas@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 20:39:17 by pthomas           #+#    #+#             */
/*   Updated: 2021/11/17 19:48:37 by pthomas          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*death_checker(void *arg)
{
	t_philo	*philo;
	time_t	start;

	philo = arg;
	start = philo->last_meal;
	while (1)
	{
		sem_wait(philo->rights);
		if (philo->nb_of_meal >= philo->meal_goal)
		{
			sem_post(data->stop);
			repletion = false;
		}
		if (time - data->philo[i].last_meal >= data->time_to_die)
		{
			print_action(&data->philo[i], "died");
			return (true);
		}
		sem_post(philo->rights);
	}
}

void	*repletion_checker(void *arg)
{
	t_data	*data;

	data = arg;
}

void	do_action(t_data *data, t_philo *philo, int action)
{
	sem_wait(data->speak);
	sem_wait(philo->rights);
	if (action == EAT)
	{
		print_action(data, philo, "is eating");
		philo->last_meal = get_time();
	}
	else if (action == TAKE_FORK)
		print_action(data, philo, "has taken a fork");
	else if (action == SLEEP)
	{
		print_action(data, philo, "is sleeping");
		philo->nb_of_meal++;
	}	
	else if (action == THINK)
		print_action(data, philo, "is thinking");
	sem_post(philo->rights);
	sem_post(data->speak);
}

void	*routine(t_data *data, t_philo *philo)
{
	if (philo->index % 2 == 0)
		spin_lock(get_time(), data->time_to_eat, data);
	while (1)
	{
		sem_wait(data->forks);
		do_action(data, philo, TAKE_FORK);
		sem_wait(data->forks);
		do_action(data, philo, TAKE_FORK);
		do_action(data, philo, EAT);
		spin_lock(get_time(), data->time_to_eat, data);
		do_action(data, philo, SLEEP);
		sem_post(data->forks);
		sem_post(data->forks);
		spin_lock(get_time(), data->time_to_sleep, data);
		do_action(data, philo, THINK);
	}
	return (NULL);
}

int	start_philosopher(t_data *data)
{
	t_philo	philo;
	size_t	i;

	i = 0;
	memset(&philo, 0, sizeof(t_philo));
	data->start = get_time();
	while (i < data->nb_of_philo)
	{
		philo.index = i + 1;
		data->philo[i] = fork();
		if (data->philo[i] == -1)
		{
			print_error("fork:", NULL, NULL, errno);
			break ;
		}
		else if (data->philo[i] == 0)
		{
			init_philo(data, &philo);
			routine(data, &philo);
		}
		i++;
	}
	if (i == data->nb_of_philo)
		sem_wait(data->stop);
	return (EXIT_SUCCESS);
}
