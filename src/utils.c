/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdorazio <jdorazio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:38:14 by jdorazio          #+#    #+#             */
/*   Updated: 2025/07/30 21:43:10 by jdorazio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_atoi(const char *nptr)
{
	int	num;
	int	sign;

	num = 0;
	sign = 1;
	while ((9 <= *nptr && *nptr <= 13) || *nptr == 32)
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign = -sign;
		nptr++;
	}
	while (*nptr)
	{
		if (!('0' <= *nptr && *nptr <= '9'))
			error_message("Not a (positive) number");
		num = (num * 10) + (*nptr - '0');
		nptr++;
	}
	return (sign * num);
}

void	error_message(char *error)
{
	printf("ERROR: %s\n", error);
	exit(EXIT_FAILURE);
}

size_t	get_current_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		error_message("failed to gettimeofday()");
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	print_action(char *s, t_philo *philo)
{
	size_t	time;

	pthread_mutex_lock(&philo->data->simulation_lock);
	if (!philo->data->simulation_running)
	{
		pthread_mutex_unlock(&philo->data->simulation_lock);
		return ;
	}
	time = get_current_time() - philo->data->start_time ;
	pthread_mutex_lock(&philo->data->print_lock);
	printf("[%zu] -> Philo[%d] %s \n", time, philo->id, s);
	pthread_mutex_unlock(&philo->data->print_lock);
	pthread_mutex_unlock(&philo->data->simulation_lock);
}

int	ft_usleep(int mls)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < (size_t) mls)
		usleep(mls *1000 / 10);
	return (0);
}
