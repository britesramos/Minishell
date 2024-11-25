/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   clean_up.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: marvin <marvin@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/25 15:18:51 by sramos        #+#    #+#                 */
/*   Updated: 2024/11/25 11:26:38 by sramos        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_cmd_list(t_cmd *list)
{
	t_cmd	*next;

	while (list)
	{
		next = list->pipe;
		if (list->cmd)
			ft_free_array(list->cmd);
		if (list->infile)
			free_close_fd(list->infile, list->fd_in);
		if (list->outfile)
			free_close_fd(list->outfile, list->fd_out);
		free(list);
		list = NULL;
		list = next;
	}
	list = NULL;
}

void	free_envp(t_envp *envp_head)
{
	t_envp	*next;

	while (envp_head)
	{
		next = envp_head->next;
		if (envp_head->key)
			ft_free_string(&envp_head->key);
		if (envp_head->value)
			ft_free_string(&envp_head->value);
		free(envp_head);
		envp_head = NULL;
		envp_head = next;
	}
	envp_head = NULL;
}

void	clean_up(t_data *data)
{
	if (data->envp_head)
		free_envp(data->envp_head);
	if (data->cmd_head)
		free_cmd_list(data->cmd_head);
	if (data->line)
		ft_free_string(&data->line);
	if (data->hd_line)
		ft_free_string(&data->hd_line);
	if (data)
		free(data);
	rl_clear_history();
}

void	clean_up_token_list(t_token	*token_list)
{
	free_token_list(token_list);
	token_list = NULL;
}

void	clean_up_parse_input(t_data *data, t_token *token_list)
{
	if (token_list)
		clean_up_token_list(token_list);
	if (data->cmd_head)
	{
		free_cmd_list(data->cmd_head);
		data->cmd_head = NULL;
	}
	data->nbr_pipes = 0;
	data->std[IN] = STDIN_FILENO;
	data->std[OUT] = STDOUT_FILENO;
}

void	free_split(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free (array[i]);
		i++;
	}
	free(array);
}
