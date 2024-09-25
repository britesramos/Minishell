/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sramos <sramos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 15:18:51 by sramos            #+#    #+#             */
/*   Updated: 2024/09/25 15:21:54 by sramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	clean_up(t_data *data)
{
	free(data->line); /*This might have to be changed if readline is a loop, so it will alocate multiple times for line.*/
	free(data);
}