/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initialize_phiosopher.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-omar <mel-omar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 21:23:26 by mel-omar          #+#    #+#             */
/*   Updated: 2021/05/26 16:12:55 by mel-omar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void		init_philosopher(t_philosopher *philo, int id, struct s_global *shared_data)
{
	philo->id = id;
	philo->time_eat = 0;
	philo->last_time_eat = get_time();
	philo->state = THINKING;
	philo->shared_data = shared_data;
}

t_philosopher *init_philosophers(struct s_global *shared_data)
{
	t_philosopher	*philosophers;
	int				iterator;

	philosophers = malloc(sizeof(t_philosopher) * shared_data->arguments[NUMBER_OF_PHILO]);
	iterator = 0;
	while (iterator < shared_data->arguments[NUMBER_OF_PHILO])
	{
		init_philosopher(&philosophers[iterator], iterator, shared_data);
		iterator++;
	}
	return (philosophers);
}
