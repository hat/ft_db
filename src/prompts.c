/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompts.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 11:13:31 by jrameau           #+#    #+#             */
/*   Updated: 2017/05/05 23:39:17 by jrameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

int		prompt_option(void)
{
	char	buf[2];
	int		ret;

	ret = 1;
	while (ret)
	{
		write(1, "Please select from the following options:\n", 42);
		ft_putstr("(Enter number of option provided)\n");
		ft_putstr("1 - Select\n2 - Create\n3 - Insert\n");
		ft_putstr("4 - Update\n5 - Delete\n6 - Exit ft_db\n-> ");
		read(0, buf, 2);
		if ((buf[0] < '1' || buf[0] > '6') && buf[0] != 'q')
			ft_putendl("Please, use one of the available options.");
		else
		{
			ret = buf[0] - '0';
			break ;
		}
	}
	return (ret);
}

int		prompt_create_option(void)
{
	int		choice;

	choice = 0;
	while (1)
	{
		ft_putstr("Please select from the following options:\n");
		ft_putstr("1 - Create new Database\n2 - Create new ");
		ft_putstr("table\n3 - Go back\n-> ");
		scanf("%d", &choice);
		if (choice < 1 || choice > 3)
			ft_putendl("Please, use one of the available options.");
		else
			break ;
	}
	return (choice);
}

int		prompt_option_delete(void)
{
	int		choice;

	choice = 0;
	while (1)
	{
		ft_putstr("Please choose between theses options:\n(Enter ");
		ft_putstr("number of option provided)\n");
		ft_putstr("1 - Delete database\n2 - Delete table\n3 -");
		ft_putstr(" Delete entry\n4 - Go back\n-> ");
		scanf("%d", &choice);
		if (choice < 1 || choice > 4)
			ft_putendl("Please, use one of the available options.");
		else
			break ;
	}
	return (choice);
}

int		prompt_db_select(char **db)
{
	char	dbtmp[NAME_MAX];
	int		ret;
	DIR		*dir;

	ret = 1;
	while (ret)
	{
		ft_putstr("Specify database name\nPress enter with no input ");
		ft_putstr("to exit\n(100 character max)\n-> ");
		if ((ret = read(0, dbtmp, NAME_MAX)) == NAME_MAX)
			ft_putstr("Name size too large\n");
		else if (ret)
		{
			dbtmp[ret - 1] = 0;
			*db = ft_strdup(dbtmp);
			dir = opendir(*db);
			if (dir)
				break ;
			else
				ft_putstr("Not a valid database\n");
		}
	}
	return (ret);
}

int		prompt_table_select(char **table, char *db)
{
	struct stat	st;
	char		tabletmp[NAME_MAX];
	char		*tmp;
	char		*tmp2;
	char		*tmp3;
	int			ret;

	tmp = NULL;
	ret = 1;
	while (ret)
	{
		ft_putstr("Enter name of table to delete\nPress enter ");
		ft_putstr("with no input to exit\n(100 character max)\n");
		if ((ret = read(0, tabletmp, NAME_MAX)) == NAME_MAX)
			ft_putstr("Name size too large\n");
		else if (ret)
		{
			tabletmp[ret] = 0;
			tmp = ft_strjoin("/", tabletmp);
			tmp2 = ft_strtrim(db);
			tmp3 = ft_strtrim(tmp);
			*table = ft_strjoin(tmp2, tmp3);
			if (stat(ft_strjoin(*table, ".db"), &st) == TABLE_NOT_FOUND)
				ft_putstr("Incorrect entry\n");
			else
				break ;
			free(tmp);
			free(tmp2);
			free(tmp3);
		}
	}
	return (ret);
}
