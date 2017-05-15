/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/27 04:37:48 by jrameau           #+#    #+#             */
/*   Updated: 2017/05/05 20:58:10 by jrameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

void	create_db(char *db_name)
{
	char *database;

	if (!db_name)
	{
		printf("Enter the database name:\n-> ");
		database = (char *)ft_memalloc(sizeof(char) * 256);
		scanf("%s", database);
	}
	else
		database = ft_strdup(db_name);
	ft_strtolower(&database);
	if (!opendir(database))
	{
		if (!mkdir(database, S_IRWXU))
			printf("Database '%s' created successfully.\n", database);
		else
			printf("There was an error creating database '%s'\n", database);
	}
	else
		return ((void)printf("The database '%s' already exists\n", database));
}

void	create_instructions(void)
{
	printf("Enter the name of each entry you want to put ");
	printf("in your table and its type separated by a space. ");
	printf("Use this format: 'entry_name entry_type'. ");
	printf("Valid entry types are: s (string) d (decimal) f (float).");
	printf("Type 'exit 0' when you are done\n");
}

int		is_exit(char *name, int num)
{
	if (ft_strequ(name, "exit"))
	{
		if (num == 0)
		{
			ft_putstr("Error: No table was created since you ");
			ft_putstr("did not enter any entry\n");
			return (2);
		}
		return (1);
	}
	return (0);
}

void	create_table(void)
{
	char		*table;
	char		*chosen_db;
	t_create	create;
	t_entry		*entry_head;
	char		*tmp_name;
	char		tmp_type;
	t_entry		*prev;
	FILE		*file;
	int			ret;
	struct stat f;

	table = (char *)ft_memalloc(sizeof(char) * 256);
	chosen_db = (char *)ft_memalloc(sizeof(char) * 256);
	printf("Select the database\n-> ");
	scanf("%s", chosen_db);
	if (verify_db(chosen_db, 1) == NONEXISTENT)
		return ;
	printf("Enter the table name:\n-> ");
	scanf("%s", table);
	if (lstat(ft_pathjoin(chosen_db, table), &f) != -1)
		return ((void)printf("Table '%s' already exists in database\n", table));
	create.name = ft_strdup(table);
	create.nb_entry = 0;
	create_instructions();
	prev = NULL;
	while (1)
	{
		tmp_name = (char *)ft_memalloc(sizeof(char) * 256);
		scanf("%s %c", tmp_name, &tmp_type);
		if ((ret = is_exit(tmp_name, create.nb_entry)))
		{
			if (ret == 2)
				return ;
			break ;
		}
		create.entry = (t_entry *)ft_memalloc(sizeof(t_entry));
		fill_entry(create.entry, tmp_name, tmp_type);
		if (prev != NULL)
			prev->next = create.entry;
		prev = create.entry;
		if (create.nb_entry == 0)
			entry_head = create.entry;
		create.nb_entry++;
		create.entry = create.entry->next;
		free(tmp_name);
	}
	create.entry = entry_head;
	file = fopen(ft_strjoin(ft_pathjoin(chosen_db, create.name), ".db"),
		"wb");
	fprintf(file, "%d\n", create.nb_entry);
	while (create.entry)
	{
		fprintf(file, "%s,%c;", create.entry->name, create.entry->type);
		create.entry = create.entry->next;
	}
	fprintf(file, "\n");
	printf("The table '%s' was created\n", table);
	fclose(file);
}
