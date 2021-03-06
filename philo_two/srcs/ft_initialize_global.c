/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initialize_global.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-omar <mel-omar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 21:09:50 by mel-omar          #+#    #+#             */
/*   Updated: 2021/05/29 21:50:43 by mel-omar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	set_arguments(struct s_global *shared_data, int argc, char *argv[])
{
	int		iterator;

	iterator = 0;
	while (++iterator < argc)
	{
		shared_data->arguments[iterator - 1]
			= (int)string2number(argv[iterator]);
		if ((shared_data->arguments[iterator - 1]) <= 0)
			return (1);
	}
	shared_data->arguments[TIME_TO_EAT] *= 1000;
	shared_data->arguments[TIME_TO_SLEEP] *= 1000;
	shared_data->arguments[TIME_TO_DIE] *= 1000;
	return (0);
}

int	init_global_var(struct s_global *shared_data, int argc, char *argv[])
{
	memset(shared_data->arguments, 0, sizeof(long long) * 5);
	if (set_arguments(shared_data, argc, argv))
		return (1);
	sem_unlink(FORKS_NAME);
	sem_unlink(OUTPUT_MANAGER_NAME);
	sem_unlink(PROTECT_FORKS_NAME);
	shared_data->forks = sem_open(FORKS_NAME, O_CREAT,
			0644, shared_data->arguments[NUMBER_OF_PHILO]);
	shared_data->output_manger = sem_open(OUTPUT_MANAGER_NAME,
			O_CREAT, 0644, 1);
	shared_data->protect_forks = sem_open(PROTECT_FORKS_NAME, O_CREAT, 0644, 1);
	shared_data->program_start = get_time();
	shared_data->someone_died = 0;
	shared_data->all_eat = 0;
	return (0);
}
