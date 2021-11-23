/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pthomas <pthomas@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 20:39:17 by pthomas           #+#    #+#             */
/*   Updated: 2021/11/23 15:53:17 by pthomas          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	check_death(t_data *data)
{
	size_t	i;
	time_t	time;

	i = 0;
	time = get_time();
	while (i < data->nb_of_philo)
	{
		if (time - data->philo[i].last_meal >= data->time_to_die)
		{
			print_action(&data->philo[i], "died");
			data->stop = true;
			return ;
		}
		i++;
	}
}

static int	check_repletion(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->nb_of_philo)
	{
		if (data->philo[i].nb_of_meal < data->meal_goal)
			return (false);
		i++;
	}
	data->stop = true;
	return (true);
}

static int	do_action(t_philo *philo, int action)
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
		if (philo->nb_of_meal == philo->data->meal_goal)
			check_repletion(philo->data);
	}	
	else if (action == THINK)
		print_action(philo, "is thinking");
	pthread_mutex_unlock(&philo->data->speak);
	return (EXIT_SUCCESS);
}

static void	*routine(void	*arg)
{
	t_philo	*philo;

	philo = arg;
	if (philo->index % 2 == 0)
		custom_usleep(philo->data->time_to_eat * 1000L, philo->data);
		// spin_lock(get_time(), philo->data->time_to_eat * 1000L, philo->data);
	while (philo->stop == false)
	{
		pthread_mutex_lock(philo->left_fork);
		philo->stop = do_action(philo, TAKE_FORK);
		if (philo->left_fork == philo->right_fork)
			break ;
		pthread_mutex_lock(philo->right_fork);
		philo->stop = do_action(philo, TAKE_FORK);
		philo->stop = do_action(philo, EAT);
		custom_usleep(philo->data->time_to_eat * 1000L, philo->data);
		// spin_lock(get_time(), philo->data->time_to_eat * 1000L, philo->data);
		philo->stop = do_action(philo, SLEEP);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		custom_usleep(philo->data->time_to_sleep * 1000L, philo->data);
		// spin_lock(get_time(), philo->data->time_to_sleep * 1000L, philo->data);
		philo->stop = do_action(philo, THINK);
	}
	if (philo->left_fork == philo->right_fork)
		pthread_mutex_unlock(philo->right_fork);
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
			print_error("pthread_create", NULL, NULL, errno);
			pthread_mutex_lock(&data->speak);
			data->stop = true;
			pthread_mutex_unlock(&data->speak);
			return (EXIT_FAILURE);
		}
		i++;
	}
	while (1)
	{
		pthread_mutex_lock(&data->speak);
		check_death(data);
		if (data->stop == true)
		{
			pthread_mutex_unlock(&data->speak);
			break ;
		}
		pthread_mutex_unlock(&data->speak);
	}
	return (EXIT_SUCCESS);
}
