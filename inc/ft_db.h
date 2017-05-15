/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_db.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/27 07:10:13 by jrameau           #+#    #+#             */
/*   Updated: 2017/05/05 23:20:24 by jrameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DB_H
# define FT_DB_H

# include "libft.h"
# include <dirent.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <stdio.h>
# include <stdlib.h>

# define SELECT_OPT				1
# define CREATE_OPT				2
# define INSERT_OPT				3
# define UPDATE_OPT				4
# define DELETE_OPT				5

# define CREATE_DB				1
# define CREATE_TABLE			2
# define CREATE_EXIT			3

# define DELETE_DB				1
# define DELETE_TABLE			2
# define DELETE_ENTRY			3
# define DELETE_EXIT			4

# define UPDATE_DB				1
# define UPDATE_TABLE			2
# define UPDATE_ENTRY			3
# define UPDATE_EXIT			4

# define NONEXISTENT			-1

# define PASS					1

# define TABLE_NOT_FOUND		-1
# define NAME_MAX				101

typedef struct					s_select
{
	char						**selected_val;
	int							nb_selected_val;
	char						*table_name;
	char						***condition;
}								t_select;

typedef struct					s_entry
{
	char						*name;
	char						type;
	struct s_entry				*next;
}								t_entry;

typedef struct					s_create
{
	char						*name;
	int							nb_entry;
	t_entry						*entry;
}								t_create;

typedef struct					s_selected
{
	char						*database;
	char						*table;
	char						*str;
	char						*path;
	char						**array;
	char						*select;
	int							fields[100];
	int							fd;
	int							i;
	int							j;
	int							x;
	char						**selection;
}								t_selected;

int								start_select(char *str);
int								prompt_option(void);
void							delete(void);
int								prompt_option_delete(void);
void							delete_table(void);
void							delete_entry(void);
int								prompt_db_select(char **db);
int								prompt_table_select(char **table, char *db);
int								open_delete_table(char *table, int is_verbose);
void							create_db(char *db_name);
int								prompt_create_option(void);
void							verify_storage(char *storage_path);
int								verify_db(char *db_name, int ask_to_create);
void							fill_entry(t_entry *entry, char *new_name,
	char new_type);
void							create_table(void);
int								prompt_check_delete_db(char *db);
void							insert(void);
int								prompt_update_option(void);
void							select_field(void);
void							update(void);
void							update_entry(void);
int								get_db_table(char **db, char **table);
#endif
