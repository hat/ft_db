/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 23:06:18 by jrameau           #+#    #+#             */
/*   Updated: 2017/05/05 23:39:58 by jrameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

int		open_delete_table(char *table, int is_verbose)
{
	int		ret;

	if ((ret = remove(ft_strjoin(table, ".db"))) == -1)
		ft_putstr("Something went wrong\n");
	else
	{
		if (is_verbose)
			ft_putstr("Table removed succesfully!\n");
	}
	return (ret);
}

void	delete_table(void)
{
	int				ret;
	char			*table;
	char			*db;

	ret = 1;
	table = NULL;
	db = NULL;
	while (ret != -1)
	{
		ret = prompt_db_select(&db);
		if (ret)
			ret = prompt_table_select(&table, db);
		if (ret)
			ret = open_delete_table(table, 1);
		if (!ret)
			ret = -1;
	}
	table ? free(table) : 0;
	db ? free(db) : 0;
}
