/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printers2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-omar <mel-omar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 21:36:42 by mel-omar          #+#    #+#             */
/*   Updated: 2021/04/30 00:40:51 by mel-omar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void 	eat_statement(t_philosopher *philo)
{
	pthread_mutex_lock(&g_global_var.output_manger);
	ft_putnbr(get_time() - g_global_var.program_start);
	ft_putc(' ');
	ft_putnbr(philo->id);
	ft_putstr(" is eating");
	endl();
	pthread_mutex_unlock(&g_global_var.output_manger);
}

void 	think_statement(t_philosopher * philo)
{
	pthread_mutex_lock(&g_global_var.output_manger);
	ft_putnbr(get_time() - g_global_var.program_start);
	ft_putc(' ');
	ft_putnbr(philo->id);
	ft_putstr(" is thinking");
	endl();
	pthread_mutex_unlock(&g_global_var.output_manger);
}

void 	sleep_statement(t_philosopher * philo)
{
	pthread_mutex_lock(&g_global_var.output_manger);
	ft_putnbr(get_time() - g_global_var.program_start);
	ft_putc(' ');
	ft_putnbr(philo->id);
	ft_putstr(" is sleeping");
	endl();
	pthread_mutex_unlock(&g_global_var.output_manger);
}

void 	fork_statement(t_philosopher * philo)
{
	pthread_mutex_lock(&g_global_var.output_manger);
	ft_putnbr(get_time() - g_global_var.program_start);
	ft_putc(' ');
	ft_putnbr(philo->id);
	ft_putstr(" has taken a fork");
	endl();
	pthread_mutex_unlock(&g_global_var.output_manger);
}

void 	death_statement(t_philosopher *philo)
{
	pthread_mutex_lock(&g_global_var.output_manger);
	ft_putnbr(get_time() - g_global_var.program_start);
	ft_putc(' ');
	ft_putnbr(philo->id);
	g_global_var.someone_died = 1;
	ft_putstr(" died");
	endl();
}