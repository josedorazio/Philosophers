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

void	error_message(char *error)
{
	printf("ERROR: %s\n", error);
	exit(EXIT_FAILURE);
}

long	now(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + (tv.tv_usec / 1000));
}

void	ft_usleep(size_t mls)
{
	size_t	start;

	start = now();
	while ((now() - start) < mls)
		usleep(100);
}
