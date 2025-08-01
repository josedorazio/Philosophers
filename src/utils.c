/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdorazio <jdorazio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:38:14 by jdorazio          #+#    #+#             */
/*   Updated: 2025/07/31 16:41:15 by jdorazio         ###   ########.fr       */
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

long	get_curr_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		error_message("get_time failed"); 
	return (tv.tv_sec * 1000 + (tv.tv_usec / 1000));
}

void	ft_usleep(size_t mls, t_philo *philo)
{
	size_t	start;

	start = get_curr_time();
	while (!program_ended(philo) && (get_curr_time() - start) < mls)
		usleep(100);
}

void	print_action(char *s, t_philo *philo)
{
	long	time;

	pthread_mutex_lock(&philo->data->print_lock);
	time = get_curr_time() - philo->data->start_time ;
	if (program_ended(philo) == 0)
		printf("[%zu] -> Philo[%d] %s \n", time, philo->id, s);
	pthread_mutex_unlock(&philo->data->print_lock);
}