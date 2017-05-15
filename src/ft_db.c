/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_db.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 20:08:37 by jrameau           #+#    #+#             */
/*   Updated: 2017/05/05 11:05:47 by jrameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

void	fill_entry(t_entry *entry, char *new_name, char new_type)
{
	ft_strtolower(&new_name);
	entry->name = ft_strdup(new_name);
	entry->type = new_type;
	entry->next = NULL;
}

void	create(void)
{
	int		create_opt;

	create_opt = prompt_create_option();
	if (create_opt == CREATE_DB)
		create_db(NULL);
	else if (create_opt == CREATE_TABLE)
		create_table();
	else
		return ;
}

void	select_operation(int option)
{
	if (option == SELECT_OPT)
		select_field();
	else if (option == CREATE_OPT)
		create();
	else if (option == INSERT_OPT)
		insert();
	else if (option == UPDATE_OPT)
		update();
	else if (option == DELETE_OPT)
		delete();
	else
		exit(0);
}

int		main(void)
{
	int		option;
	char	*path;

	path = ft_pathjoin(getcwd(NULL, 0), "/data");
	verify_storage(path);
	chdir(path);
	option = 1;
	ft_putendl("Welcome to ft_db!");
	while (option)
	{
		option = prompt_option();
		verify_storage(path);
		select_operation(option);
	}
	free(path);
	return (0);
}
