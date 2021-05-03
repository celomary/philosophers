/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-omar <mel-omar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 17:04:42 by mel-omar          #+#    #+#             */
/*   Updated: 2021/05/02 23:25:57 by mel-omar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"


long long 	difference_ab(long long a, long long b)
{
	return (a - b);
}

int		count_finished_philosophers(t_philosopher *ph)
{
	int		iter;
	int		counter;

	iter = 0;
	counter = 0;
	while (iter < g_global_var.arguments[NUMBER_OF_PHILO])
	{
		if (ph[iter].time_eat >= g_global_var.arguments[NUMBER_MUST_EAT]
		&& g_global_var.arguments[NUMBER_MUST_EAT])
			counter++;
		iter++;
	}
	return (counter);
}

int		check_someone_died(t_philosopher *ph)
{
	int		iter;

	iter = 0;
	while (iter < g_global_var.arguments[NUMBER_OF_PHILO])
	{
		if (ph[iter].state != EATING  && difference_ab(get_time(), ph[iter].last_time_eat) >= g_global_var.arguments[TIME_TO_DIE])
		{
			death_statement(&ph[iter]);
			return (1);
		}
		iter++;
	}
	return (0);
}

void	checker_state(t_philosopher *ph)
{
	while (1)
	{
		if (check_someone_died(ph))
		{
			g_global_var.someone_died = 1;
			break ;
		}
		if (count_finished_philosophers(ph))
			break ;
	}
}

void	mysleep(int timer)
{
	int start;

	start = get_time();
	usleep(timer - 200000);
	while (get_time() - start <= timer);
}

void	*philosopher_function(void *philo)
{
	t_philosopher	*ph;

	ph = philo;
	while ((ph->time_eat < g_global_var.arguments[NUMBER_MUST_EAT]
		|| !g_global_var.arguments[NUMBER_MUST_EAT])
		&& !g_global_var.someone_died)
	{
		think_statement(ph);
		ph->state = THINKING;
		pthread_mutex_lock(&g_global_var.forks[ph->id]);
		fork_statement(ph);
		pthread_mutex_lock(&g_global_var.forks[(ph->id + 1)
			% g_global_var.arguments[NUMBER_OF_PHILO]]);
		fork_statement(ph);
		ph->state = EATING;
		eat_statement(ph);
		ph->time_eat++;
		ph->last_time_eat = get_time();
		usleep(g_global_var.arguments[TIME_TO_EAT] - 1000);
		pthread_mutex_unlock(&g_global_var.forks[ph->id]);
		pthread_mutex_unlock(&g_global_var.forks[(ph->id + 1) % g_global_var.arguments[NUMBER_OF_PHILO]]);
		sleep_statement(ph);
		ph->state = SLEEPING;
		usleep(g_global_var.arguments[TIME_TO_SLEEP]);
	}
	return (NULL);
}

void	run_philosophers(t_philosopher *ph)
{
	int 	iter;

	iter = 0;
	while (iter < g_global_var.arguments[NUMBER_OF_PHILO])
	{
		pthread_create(&ph[iter].thread, NULL, philosopher_function, &ph[iter]);
		iter++;
	}
}

void	wait4philosophers(t_philosopher *ph)
{
		int 	iter;

	iter = 0;
	while (iter < g_global_var.arguments[NUMBER_OF_PHILO])
	{
		pthread_join(ph[iter].thread, NULL);
		iter++;
	}	
}

int		check4errors(int argc, char **argv)
{
	int		iterator;
	int		nested_iter;

	if (argc < 5 || argc > 6)
		return (1);
	iterator = 1;
	while (iterator < argc)
	{
		nested_iter = 0;
		while (argv[iterator][nested_iter])
		{
			if (!isdigits(argv[iterator][nested_iter]))
				return (1);
			nested_iter++;
		}
		iterator++;
	}
	return (0);
}

int		main(int argc, char *argv[])
{
	t_philosopher	*ph;

	if (check4errors(argc, argv))
	{
		ft_putstr("arguments error\n");
		return (1);
	}
	init_global_var(argc, argv);
	ph = init_philosophers();
	run_philosophers(ph);
	checker_state(ph);
	if (!g_global_var.someone_died)
		wait4philosophers(ph);
	free(g_global_var.forks);
	free(ph);
	return (0);
}
