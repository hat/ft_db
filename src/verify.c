/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/27 06:24:54 by jrameau           #+#    #+#             */
/*   Updated: 2017/05/05 10:06:13 by jrameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

void	verify_storage(char *storage_path)
{
	if (!opendir(storage_path))
	{
		mkdir(storage_path, S_IRWXU);
		chdir(storage_path);
	}
}

int		verify_db(char *db_name, int ask_to_create)
{
	char	choice;

	choice = 0;
	if (!opendir(db_name))
	{
		if (ask_to_create)
		{
			printf("Database '%s' does not exist. ", db_name);
			printf("Do you want to create it? [Y/n]\n-> ");
			scanf(" %c", &choice);
			if (choice == 'y' || choice == 'Y')
				create_db(db_name);
			else
				return (NONEXISTENT);
		}
		else
			return (NONEXISTENT);
	}
	return (PASS);
}
