/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdorazio <jdorazio@student.42.madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:38:14 by jdorazio          #+#    #+#             */
/*   Updated: 2025/05/19 15:42:41 by jdorazio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/philo.h"

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

void	check_av(char **av)
{
	// check number of philo
	if (ft_atoi(av[1]) < 1||ft_atoi(av[1]) > PHILO_MAX)
		error_message("Num. Philo. must be between 1 - 200");
	// check time to die
	if (ft_atoi(av[2]) <= 0)
		error_message("time to die must be bigger than 0");
	// check time to eat
	if (ft_atoi(av[3]) <= 0)
		error_message("time to eat must be bigger than 0");
	// check time to sleep
	if (ft_atoi(av[4]) <= 0)
		error_message("time to sleep must be bigger than 0");
	if (av[5] && (ft_atoi(av[5]) < 0))
		error_message("invalid number of eating times\n"); 
}


size_t	get_current_time(void)
{
	struct timeval tv;

	if (gettimeofday(&tv, NULL))
		error_message("failed to gettimeofday()");
	return(tv.tv_sec * 1000 + tv.tv_usec / 1000);
}
