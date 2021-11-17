/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pthomas <pthomas@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 20:39:17 by pthomas           #+#    #+#             */
/*   Updated: 2021/11/17 00:19:17 by pthomas          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_deaths_and_repletion(t_data *data)
{
	size_t	i;
	bool	repletion;
	time_t	time;

	i = 0;
	if (!data->meal_goal)
		repletion = false;
	else
		repletion = true;
	time = get_time();
	while (i < data->nb_of_philo)
	{
		if (repletion == true && data->philo[i].nb_of_meal < data->meal_goal)
			repletion = false;
		if (time - data->philo[i].last_meal >= data->time_to_die)
		{
			print_action(&data->philo[i], "died");
			return (true);
		}
	}
	return (repletion);
}

int	do_action(t_philo *philo, int action)
{
	pthread_mutex_lock(&philo->data->speak);
	if (philo->data->stop)
	{
		pthread_mutex_unlock(&philo->data->speak);
		return (EXIT_FAILURE);
	}
	if (action == EAT)
	{
		print_action(philo, "is eating");
		philo->last_meal = get_time();
	}
	else if (action == TAKE_FORK)
		print_action(philo, "has taken a fork");
	else if (action == SLEEP)
	{
		print_action(philo, "is sleeping");
		philo->nb_of_meal++;
	}	
	else if (action == THINK)
		print_action(philo, "is thinking");
	pthread_mutex_unlock(&philo->data->speak);
	return (EXIT_SUCCESS);
}

void	*routine(void	*arg)
{
	t_philo	*philo;
	bool	stop;

	philo = arg;
	stop = false;
	if (philo->index % 2 == 0)
		usleep(philo->data->time_to_eat * 1000);
	while (stop == false)
	{
		pthread_mutex_lock(philo->left_fork);
		stop = do_action(philo, TAKE_FORK);
		pthread_mutex_lock(philo->right_fork);
		stop = do_action(philo, TAKE_FORK);
		stop = do_action(philo, EAT);
		usleep(philo->data->time_to_eat * 1000);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		stop = do_action(philo, SLEEP);
		usleep(philo->data->time_to_sleep * 1000);
		stop = do_action(philo, THINK);
	}
	return (NULL);
}

int	start_philosopher(t_data *data)
{
	size_t	i;

	i = 0;
	data->start = get_time();
	while (i < data->nb_of_philo)
	{
		data->philo[i].last_meal = data->start;
		if (pthread_create(&data->philo[i].thread,
				NULL, &routine, &data->philo[i]))
		{
			pthread_mutex_lock(&data->speak);
			data->stop = true;
			pthread_mutex_unlock(&data->speak);
			return (EXIT_FAILURE);
		}
		pthread_detach(data->philo[i].thread);
	}
	while (!data->stop)
	{
		pthread_mutex_lock(&data->speak);
		data->stop = check_deaths_and_repletion(data);
		pthread_mutex_unlock(&data->speak);
	}
	return (EXIT_SUCCESS);
}
