/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompts.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 11:13:31 by jrameau           #+#    #+#             */
/*   Updated: 2017/05/05 11:19:37 by jrameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

int		prompt_check_delete_db(char *db)
{
	char	*user_input;

	user_input = (char *)malloc(sizeof(char) * 4);
	printf("Are you sure you want to delete %s (y/n): ", db);
	scanf("%s", user_input);
	if (user_input[0] == 'y' || !strcmp("yes", user_input))
	{
		free(user_input);
		return (1);
	}
	free(user_input);
	return (0);
}

int		prompt_update_option(void)
{
	int		choice;

	choice = 0;
	while (1)
	{
		ft_putstr("Please select from the following options:\n");
		ft_putstr("1 - Update a Database\n2 - Update a table\n3 - ");
		ft_putstr("Update an entry\n4 - Go back\n-> ");
		scanf("%d", &choice);
		if (choice < 1 || choice > 4)
			ft_putendl("Please, use one of the available options.");
		else
			break ;
	}
	return (choice);
}
