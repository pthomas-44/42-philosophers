/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pthomas <pthomas@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 20:00:44 by pthomas           #+#    #+#             */
/*   Updated: 2021/11/23 13:04:47 by pthomas          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

time_t	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000L + time.tv_usec / 1000L);
}

void	print_action(t_philo *philo, char *action)
{
	time_t	time;

	time = get_time() - philo->data->start;
	ft_putnbr_fd(time, 1);
	write(1, " ", 1);
	ft_putnbr_fd(philo->index, 1);
	write(1, " ", 1);
	ft_putstr_fd(action, 1);
	write(1, "\n", 1);
}

void	print_error(char *cmd, char *value, char *error, int status)
{
	errno = status;
	ft_putstr_fd("philo: ", STDERR_FILENO);
	if (cmd)
		ft_putstr_fd(cmd, STDERR_FILENO);
	if (value)
	{
		ft_putstr_fd(value, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	if (errno == EINVAL)
		ft_putstr_fd("Invalid argument\n", STDERR_FILENO);
	else if (errno == EBUSY)
		ft_putstr_fd("Device or resource busy\n", STDERR_FILENO);
	else if (errno == EAGAIN)
		ft_putstr_fd("Try again\n", STDERR_FILENO);
	else if (errno == ENOMEM)
		ft_putstr_fd("Out of memory\n", STDERR_FILENO);
	else if (errno == EPERM)
		ft_putstr_fd("Operation not permitted\n", STDERR_FILENO);
	else if (error)
		ft_putstr_fd(error, STDERR_FILENO);
	else
		ft_putstr_fd("Undefined error\n", STDERR_FILENO);
}

void	spin_lock(long long starting_time, long long waiting_time, t_data *data)
{
	while (get_time() - starting_time < waiting_time / 1000LL)
	{
		pthread_mutex_lock(&data->speak);
		if (data->stop == true)
		{
			pthread_mutex_unlock(&data->speak);
			break ;
		}
		pthread_mutex_unlock(&data->speak);
	}
}

void	custom_usleep(long long microseconds, t_data *data)
{
	long long	start;

	start = get_time();
	while (get_time() - start < microseconds / 1000)
	{
		pthread_mutex_lock(&data->speak);
		if (data->stop == true)
		{
			pthread_mutex_unlock(&data->speak);
			break ;
		}
		pthread_mutex_unlock(&data->speak);
		usleep(100);
	}
}
