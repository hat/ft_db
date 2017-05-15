/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 20:17:52 by jrameau           #+#    #+#             */
/*   Updated: 2017/05/05 11:20:52 by jrameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

void	update_db(void)
{
	char		*chosen_db;
	char		*new_name;

	chosen_db = (char *)ft_memalloc(sizeof(char) * 256);
	printf("Enter database name\n-> ");
	scanf("%s", chosen_db);
	if (verify_db(chosen_db, 0) == NONEXISTENT)
		return ;
	new_name = (char *)ft_memalloc(sizeof(char) * 256);
	printf("Put a new name for database '%s'\n-> ", chosen_db);
	scanf("%s", new_name);
	if (ft_strequ(new_name, chosen_db))
		return ;
	if (!rename(chosen_db, new_name))
	{
		printf("Database successfully updated.\n");
		return ;
	}
	else
	{
		printf("Unable to update database '%s'\n", chosen_db);
		return ;
	}
}

void	update_table(void)
{
	char		*chosen_db;
	char		*chosen_tbl;
	char		*new_name;
	struct stat	f;

	chosen_db = (char *)ft_memalloc(sizeof(char) * 256);
	printf("Enter database name\n-> ");
	scanf("%s", chosen_db);
	if (verify_db(chosen_db, 0) == NONEXISTENT)
		return ;
	chosen_tbl = (char *)ft_memalloc(sizeof(char) * 256);
	printf("Enter a table name\n-> ");
	scanf("%s", chosen_tbl);
	if (lstat(ft_pathjoin(chosen_db, ft_strjoin(chosen_tbl, ".db")), &f) == -1)
		return (void)printf("Table doesn't exist database '%s'\n", chosen_db);
	printf("Enter the new table name\n-> ");
	new_name = (char *)ft_memalloc(sizeof(char) * 256);
	scanf("%s", new_name);
	if (ft_strequ(new_name, chosen_tbl))
		return ;
	if (!rename(ft_pathjoin(chosen_db, ft_strjoin(chosen_tbl, ".db")),
		ft_pathjoin(chosen_db, ft_strjoin(new_name, ".db"))))
		return (void)printf("Table successfully updated\n");
	printf("Unable to update table '%s'\n", chosen_tbl);
}

void	update(void)
{
	int		update_opt;

	update_opt = prompt_update_option();
	if (update_opt == UPDATE_DB)
		update_db();
	else if (update_opt == UPDATE_TABLE)
		update_table();
	else if (update_opt == UPDATE_ENTRY)
		update_entry();
	else
		return ;
}
