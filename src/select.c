/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 20:08:37 by jrameau           #+#    #+#             */
/*   Updated: 2017/05/03 20:05:04 by jrameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

void	print_selection(char *select, int fd, char *str, int fields[100])
{
	int			x;
	char		**select_split;
	char		**cur_field;

	printf("\n\n-----------------------------------\n");
	x = 0;
	select_split = ft_strsplit(select, ' ');
	while (select_split[x])
	{
		printf("%s\t", select_split[x]);
		x++;
	}
	printf("\n-----------------------------------\n");
	while (get_next_line(fd, &str))
	{
		x = 0;
		while (fields[x] != -1)
		{
			cur_field = ft_strsplit(str, ';');
			printf("%s\t", cur_field[fields[x++]]);
		}
		printf("\n");
	}
	printf("\n-----------------------------------\n");
	close(fd);
}

void	select_field(void)
{
	int			i;
	int			j;
	int			x;
	t_selected	slct;

	slct.database = malloc(sizeof(char) * 20);
	slct.table = malloc(sizeof(char) * 20);
	slct.select = malloc(sizeof(char) * 256);
	if (!slct.database || !slct.table || !slct.select)
		return (void)printf("ERROR: malloc failure at line 47-49 of select.c");
	x = 0;
	while (x++ < 100)
		slct.fields[x] = -1;
	if (get_db_table(&slct.database, &slct.table) == -1)
		return ;
	slct.path = ft_strjoin(ft_pathjoin(slct.database, slct.table), ".db");
	slct.fd = open(slct.path, O_RDONLY);
	get_next_line(slct.fd, &slct.str);
	get_next_line(slct.fd, &slct.str);
	slct.array = ft_strsplit(slct.str, ';');
	i = -1;
	printf("You can select from the following fields: \n");
	while (slct.array[++i])
	{
		printf("%s", ft_strsplit(slct.array[i], ',')[0]);
		if (slct.array[i + 1])
			printf(", ");
	}
	printf("\n");
	get_next_line(1, &slct.select);
	printf("SELECT %s FROM %s\n", slct.select, slct.table);
	slct.selection = ft_strsplit(slct.select, ' ');
	j = -1;
	x = 0;
	while (slct.array[++j] && slct.selection[x])
	{
		if (!strcmp(slct.array[j], ft_strjoin(slct.selection[x],
			(slct.array[j] + ft_strlen(slct.array[j]) - 2))))
		{
			slct.fields[x++] = j;
			j = -1;
		}
	}
	print_selection(slct.select, slct.fd, slct.str, slct.fields);
}
