/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denis <dprudnik@student.42wolfsburg.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 20:37:36 by denis             #+#    #+#             */
/*   Updated: 2026/05/23 20:50:40 by denis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* All bellow functions are for exec_export_no_args */
void	swap_vars(t_var **a, t_var **b)
{
	t_var	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

int	cmp_names(char *s1, char *s2)
{
	size_t	len1;
	size_t	len2;
	size_t	max;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (len1 > len2)
		max = len1;
	else
		max = len2;
	return (ft_strncmp(s1, s2, max));
}

void	print_export_var(t_var *var)
{
	printf("declare -x %s", var->name);
	if (var->value)
		printf("=\"%s\"", var->value);
	printf("\n");
}

void	sort_vars(t_var **arr, int size)
{
	int	i;
	int	j;

	i = 0;
	while (i < size - 1)
	{
		j = 0;
		while (j < size - i - 1)
		{
			if (cmp_names(arr[j]->name, arr[j + 1]->name) > 0)
				swap_vars(&arr[j], &arr[j + 1]);
			j++;
		}
		i++;
	}
}

t_var	**vars_to_array(t_var *vars, int *size)
{
	t_var	**arr;
	int		i;

	*size = var_count(vars);
	arr = malloc(sizeof(t_var *) * (*size));
	if (!arr)
		return (NULL);
	i = 0;
	while (vars)
	{
		arr[i++] = vars;
		vars = vars->next;
	}
	sort_vars(arr, *size);
	return (arr);
}
