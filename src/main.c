/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdorazio <jdorazio@student.42.madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 18:56:10 by jdorazio          #+#    #+#             */
/*   Updated: 2025/03/27 18:56:10 by jdorazio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	start_program(t_data *data)
{
	size_t		i;

	if (pthread_create(&data->monitor_thread, NULL, &routine_monitor, data) != 0)
		return (printf("failing in monitor"), 0);
	i = 0;
	while (i < data->num_of_philos)
	{
		if (pthread_create(&data->philos[i].thread, NULL,
				&routine_philo, &data->philos[i]) != 0)
			return (printf("failing in philo [%ld]", i), 0);
		i++;
	}
	data->start_time = get_curr_time();
	set_status(&data->sim_lock, &data->all_threads_ready);
	return (1);
}

static int	end_program(t_data *data)
{
	size_t	i;

	if (pthread_join(data->monitor_thread, NULL) != 0)
		return (0);
	i = 0;
	while (i < data->num_of_philos)
	{
		if (pthread_join(data->philos[i].thread, NULL) != 0)
			return (0);
		i++;
	}
	return (1);
}

static void	check_av(int ac, char **av)
{
	if (ac != 5 && ac != 6)
		error_message("Number of arguments not 4 or 5.");
	if (ft_atoi(av[1]) < 1 || ft_atoi(av[1]) > PHILO_MAX)
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

int	main(int ac, char **av)
{
	t_data	data;

	check_av(ac, av);
	if (!init_data(&data, ac, av))
		return (printf("Initialization error\n"), EXIT_FAILURE);
	if (!start_program(&data))
		return (printf("Thread craetion error\n"), EXIT_FAILURE);
	if (!end_program(&data))
	{
		destroy_all(&data);
		return (printf("Thread join error error\n"), EXIT_FAILURE);
	}
	destroy_all(&data);
	return (EXIT_SUCCESS);
}
