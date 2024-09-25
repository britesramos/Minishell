/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_p.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sramos <sramos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 16:00:05 by sramos            #+#    #+#             */
/*   Updated: 2024/09/25 16:33:55 by sramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	error_exit(char *str, int seo)
{
	int	len;

	len = ft_strlen(str);
	write(1, str, len);
	//TODO:Clean_up;
	exit(seo);
}