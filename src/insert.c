/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 11:09:47 by jrameau           #+#    #+#             */
/*   Updated: 2017/05/05 11:09:47 by jrameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

void	insert(void)
{
	char		*database;
	char		*table;
	char		*str;
	char		*path;
	char		*str_to_insert;
	char		**array;
	int			i;
	int			fd;
	FILE		*file;

	printf("Enter the database name:\n->");
	database = (char *)ft_memalloc(sizeof(char) * 20);
	scanf("%s", database);
	if (opendir(database))
	{
		str_to_insert = ft_strdup("");
		printf("Enter the table name:\n->");
		table = (char *)ft_memalloc(sizeof(char) * 20);
		scanf("%s", table);
		path = ft_strjoin(ft_pathjoin(database, table), ".db");
		if (access(path, F_OK) != -1)
		{
			fd = open(path, O_RDONLY);
			file = fopen(path, "a");
			get_next_line(fd, &str);
			get_next_line(fd, &str);
			printf("%s\n", str);
			array = ft_strsplit(str, ';');
			i = -1;
			while (array[++i])
			{
				printf("Enter the value you want to give for '%s'\n",
					ft_strsplit(array[i], ',')[0]);
				scanf("%s", str);
				str_to_insert = ft_strjoin(str_to_insert, ft_strjoin(str, ";"));
			}
			fprintf(file, "%s\n", str_to_insert);
			printf("Successfully inserted new entry to table '%s'\n", table);
			fclose(file);
		}
		else
		{
			printf("The table '%s' does not exist in this database\n", table);
			return ;
		}
	}
	else
	{
		printf("The database '%s' does not exist\n", database);
		return ;
	}
}
