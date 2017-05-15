/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 10:53:14 by jrameau           #+#    #+#             */
/*   Updated: 2017/05/05 23:06:08 by jrameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

void	open_delete_database(char *db)
{
	DIR				*dir;
	struct dirent	*sd;

	if (!prompt_check_delete_db(db))
		return ;
	dir = opendir(db);
	while ((sd = readdir(dir)))
	{
		if (sd->d_name[0] != '.' || !ft_strequ(sd->d_name, ".."))
			open_delete_table(ft_pathjoin(db, sd->d_name), 0);
	}
	if (dir)
		closedir(dir);
	if (!rmdir(db))
		printf("'%s' deleted succesfully.\n", db);
	else
		printf("Unable to delete '%s'\n", db);
}

void	delete_database(void)
{
	int			ret;
	char		*db;

	db = NULL;
	ret = prompt_db_select(&db);
	if (ret)
		open_delete_database(db);
	db ? free(db) : 0;
}

void	prompt_columns(char **columns, int *chosen_column, int num_cols)
{
	int i;

	printf("Listing table columns (In order)\n");
	i = -1;
	while (columns[++i])
		printf("%d - %s\n", i + 1, ft_strsplit(columns[i], ',')[0]);
	printf("Choose the number of the column by which you want to search\n-> ");
	*chosen_column = 0;
	scanf("%d", chosen_column);
	if (!*chosen_column || *chosen_column < 1 || *chosen_column > num_cols)
	{
		printf("Wrong column\n");
		return ;
	}
	(*chosen_column)--;
}

void	delete_entry(void)
{
	int			num_cols;
	char		*chosen_db;
	char		*chosen_table;
	int			fd;
	char		*line;
	char		**columns;
	int			chosen_column;
	char		*search_term;
	char		**entry;
	int			found;
	FILE		*fd2;
	int			i;

	chosen_db = (char *)ft_memalloc(sizeof(char) * 256);
	chosen_table = (char *)ft_memalloc(sizeof(char) * 256);
	if (get_db_table(&chosen_db, &chosen_table) == -1)
		return ;
	fd = open(ft_pathjoin(chosen_db, ft_strjoin(chosen_table, ".db")),
		O_RDONLY);
	fd2 = fopen(ft_pathjoin(chosen_db, "tmp.db"), "w+");
	i = -1;
	while (++i < 2)
	{
		line = NULL;
		get_next_line(fd, &line);
		if (i == 0)
			num_cols = ft_atoi(line);
		else
			columns = ft_strsplit(line, ';');
		fprintf(fd2, "%s\n", line);
		free(line);
	}
	if (fd2)
		fclose(fd2);
	prompt_columns(columns, &chosen_column, num_cols);
	printf("Enter the value you want to search\n-> ");
	search_term = (char *)ft_memalloc(sizeof(char) * 256);
	scanf("%s", search_term);
	line = NULL;
	found = 0;
	fd2 = fopen(ft_pathjoin(chosen_db, "tmp.db"), "a");
	while (get_next_line(fd, &line) == 1)
	{
		entry = ft_strsplit(line, ';');
		if (!ft_strequ(entry[chosen_column], search_term))
			fprintf(fd2, "%s\n", line);
		else
			found = 1;
		free(line);
		line = NULL;
	}
	if (fd2)
		fclose(fd2);
	if (!found)
	{
		printf("Could not find the entry '%s' with the value '%s'\n",
			ft_strsplit(columns[chosen_column], ',')[0], search_term);
		remove(ft_pathjoin(chosen_db, "tmp.db"));
		return ;
	}
	else
	{
		rmdir(ft_pathjoin(chosen_db, ft_strjoin(chosen_table, ".db")));
		if (!rename(ft_pathjoin(chosen_db, "tmp.db"), ft_pathjoin(chosen_db,
			ft_strjoin(chosen_table, ".db"))))
			printf("Successfully Removed entry/entries '%s'\n", search_term);
		else
			printf("Unable to update table");
	}
	if (fd)
		close(fd);
}

void	delete(void)
{
	int		option;

	option = prompt_option_delete();
	if (option == DELETE_DB)
		delete_database();
	else if (option == DELETE_TABLE)
		delete_table();
	else if (option == DELETE_ENTRY)
		delete_entry();
	else
		return ;
	return ;
}
