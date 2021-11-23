/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pthomas <pthomas@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 20:39:17 by pthomas           #+#    #+#             */
/*   Updated: 2021/11/23 20:28:36 by pthomas          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*death_checker(void *arg)
{
	t_data	*data;

	data = arg;
	while (1)
	{
		sem_wait(data->philo.rights);
		if (get_time() - data->philo.last_meal >= data->time_to_die)
		{
			sem_wait(data->speak);
			print_action(data, &data->philo, "died");
			sem_post(data->stop);
			exit(0);
		}
		sem_post(data->philo.rights);
	}
	return (NULL);
}

void	*repletion_checker(void *arg)
{
	t_data	*data;
	size_t	i;

	data = arg;
	i = 0;
	while (i < data->nb_of_philo)
	{
		sem_wait(data->repletion);
		i++;
	}
	sem_wait(data->speak);
	sem_post(data->stop);
	return (NULL);
}

void	do_action(t_data *data, int action)
{
	sem_wait(data->speak);
	sem_wait(data->philo.rights);
	if (action == EAT)
	{
		print_action(data, &data->philo, "is eating");
		data->philo.last_meal = get_time();
	}
	else if (action == TAKE_FORK)
		print_action(data, &data->philo, "has taken a fork");
	else if (action == SLEEP)
	{
		print_action(data, &data->philo, "is sleeping");
		data->philo.nb_of_meal++;
		if (data->philo.nb_of_meal == data->meal_goal)
			sem_post(data->repletion);
	}	
	else if (action == THINK)
		print_action(data, &data->philo, "is thinking");
	sem_post(data->philo.rights);
	sem_post(data->speak);
}

static void	*routine(t_data *data)
{
	if (data->philo.index % 2 == 0)
		custom_usleep(data->time_to_eat * 1000L);
	while (1)
	{
		sem_wait(data->forks);
		do_action(data, TAKE_FORK);
		sem_wait(data->forks);
		do_action(data, TAKE_FORK);
		do_action(data, EAT);
		custom_usleep(data->time_to_eat * 1000L);
		do_action(data, SLEEP);
		sem_post(data->forks);
		sem_post(data->forks);
		custom_usleep(data->time_to_sleep * 1000L);
		do_action(data, THINK);
	}
	return (NULL);
}

int	start_philosopher(t_data *data)
{
	int	i;

	i = 0;
	data->start = get_time();
	while (i < (int)data->nb_of_philo)
	{
		data->philo.index = i + 1;
		data->pid_philo[i] = fork();
		if (data->pid_philo[i] == -1)
		{
			print_error("fork:", NULL, NULL, errno);
			while (--i >= 0)
				kill(data->pid_philo[i], SIGKILL);
			return (EXIT_FAILURE);
		}
		else if (data->pid_philo[i] == 0)
		{
			init_philo(data);
			routine(data);
		}
		i++;
	}
	sem_wait(data->stop);
	return (EXIT_SUCCESS);
}
