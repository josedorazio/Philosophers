/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdorazio <jdorazio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:38:14 by jdorazio          #+#    #+#             */
/*   Updated: 2025/07/13 22:48:26 by jdorazio         ###   ########.fr       */
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

void	check_av(int ac, char **av)
{
	if (ac != 5 && ac != 6)
		error_message("Number of arguments not 4 or 5.");
	if (ft_atoi(av[1]) < 1||ft_atoi(av[1]) > PHILO_MAX)
		error_message("Num. Philo. must be between 1 - 200");
	if (ft_atoi(av[2]) <= 0)
		error_message("time to die must be bigger than 0");
	if (ft_atoi(av[3]) <= 0)
		error_message("time to eat must be bigger than 0");
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

void	print_action(char *s, t_philo *philo)
{
	size_t	time;

	time = get_current_time() - philo->data->start_time ;
	pthread_mutex_lock(&philo->data->print_lock);
	printf("TS[%zu] -> Philo[%d] %s \n", time, philo->id, s);
	pthread_mutex_unlock(&philo->data->print_lock);
}

void	ft_usleep(int mls)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < (size_t) mls)
		usleep(10);
}
