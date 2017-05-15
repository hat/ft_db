/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_entry.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 22:36:28 by jrameau           #+#    #+#             */
/*   Updated: 2017/05/05 11:46:55 by jrameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

int		get_db_table(char **db, char **table)
{
	struct stat	f;

	printf("Enter database name\n-> ");
	scanf("%s", *db);
	if (verify_db(*db, 0) == NONEXISTENT)
		return (-1);
	printf("Enter a table name\n-> ");
	scanf("%s", *table);
	if (lstat(ft_pathjoin(*db, ft_strjoin(*table, ".db")), &f) == -1)
	{
		printf("This table doesn't exist in the database '%s'\n", *db);
		return (-1);
	}
	return (1);
}

void	update_entry(void)
{
	int			num_cols;
	char		*chosen_db;
	char		*chosen_tbl;
	int			fd;
	char		*line;
	char		**columns;
	int			chosen_column;
	char		*search_term;
	char		**entry;
	int			found;
	FILE		*fd2;
	char		*replace_with;
	int			i;

	chosen_db = (char *)ft_memalloc(sizeof(char) * 256);
	chosen_tbl = (char *)ft_memalloc(sizeof(char) * 256);
	if (get_db_table(&chosen_db, &chosen_tbl) == -1)
		return ;
	fd = open(ft_pathjoin(chosen_db, ft_strjoin(chosen_tbl, ".db")), O_RDONLY);
	fd2 = fopen(ft_pathjoin(chosen_db, "tmp.db"), "w+");
	i = -1;
	while (++i < 2)
	{
		line = NULL;
		get_next_line(fd, &line);
		if (i == 0)
			num_cols = ft_atoi(line);
		else
		{
			columns = ft_strsplit(line, ';');
		}
		fprintf(fd2, "%s\n", line);
		free(line);
	}
	if (fd2)
		fclose(fd2);
	printf("Listing table columns (In order)\n");
	i = -1;
	while (columns[++i])
		printf("%d - %s\n", i + 1, ft_strsplit(columns[i], ',')[0]);
	printf("Choose the number of the column by which you want to search\n-> ");
	chosen_column = 0;
	scanf("%d", &chosen_column);
	if (!chosen_column || chosen_column < 1 || chosen_column > num_cols)
	{
		printf("Wrong column\n");
		return ;
	}
	chosen_column--;
	printf("Enter the value you want to search\n-> ");
	search_term = (char *)ft_memalloc(sizeof(char) * 256);
	scanf("%s", search_term);
	printf("Enter the value you want to replace it with\n-> ");
	replace_with = (char *)ft_memalloc(sizeof(char) * 256);
	scanf("%s", replace_with);
	line = NULL;
	found = 0;
	fd2 = fopen(ft_pathjoin(chosen_db, "tmp.db"), "a");
	while (get_next_line(fd, &line) == 1)
	{
		entry = ft_strsplit(line, ';');
		if (ft_strequ(entry[chosen_column], search_term))
		{
			found = 1;
			i = -1;
			while (entry[++i])
			{
				if (i == chosen_column)
					fprintf(fd2, "%s;", replace_with);
				else
					fprintf(fd2, "%s;", entry[i]);
				if (!entry[i + 1])
					fprintf(fd2, "\n");
			}
		}
		else
		{
			fprintf(fd2, "%s\n", line);
		}
		free(line);
		line = NULL;
	}
	if (fd2)
		fclose(fd2);
	if (!found)
	{
		printf("Could not find the entry '%s' with the value '%s'\n",
			ft_strsplit(columns[chosen_column], ',')[0], search_term);
		rmdir(ft_pathjoin(chosen_db, "tmp.db"));
		return ;
	}
	else
	{
		rmdir(ft_pathjoin(chosen_db, ft_strjoin(chosen_tbl, ".db")));
		if (!rename(ft_pathjoin(chosen_db, "tmp.db"),
				ft_pathjoin(chosen_db, ft_strjoin(chosen_tbl, ".db"))))
			printf("Successfully updated table '%s'\n", chosen_tbl);
		else
			printf("Unable to update table");
	}
	if (fd)
		close(fd);
}
