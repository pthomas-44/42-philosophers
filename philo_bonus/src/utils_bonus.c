/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pthomas <pthomas@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 20:00:44 by pthomas           #+#    #+#             */
/*   Updated: 2022/01/12 13:44:13 by pthomas          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

time_t	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000L + time.tv_usec / 1000L);
}

void	print_action(t_data *data, t_philo *philo, char *action)
{
	time_t	time;

	time = get_time() - data->start;
	printf("%ld %ld %s\n", time, philo->index, action);
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

void	custom_usleep(time_t microseconds, t_data *data)
{
	time_t	start;

	start = get_time();
	while (get_time() - start < microseconds)
	{
		if (data->nb_of_philo < 100)
			usleep(100);
		else
			usleep(1000);
	}
}

char	*gen_sem_name(int philo_id)
{
	int		index;
	int		tmp;
	char	*name;

	index = 2;
	tmp = philo_id;
	while (tmp > 9)
	{
		tmp /= 10;
		index++;
	}
	name = malloc(index * sizeof(char));
	name[0] = 'p';
	name[index--] = '\0';
	while (philo_id > 9)
	{
		name[index] = philo_id % 10 + '0';
		philo_id /= 10;
		index--;
	}
	name[index] = philo_id % 10 + '0';
	return (name);
}
