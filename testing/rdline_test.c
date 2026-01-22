/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdline_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dprudnik <dprudnik@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 18:27:43 by dprudnik          #+#    #+#             */
/*   Updated: 2026/01/21 19:58:23 by dprudnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>


int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

int	ft_strncmp(char *s1, char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		if (s1[i] == '\0' && s2[i] == '\0')
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

static void	shell_loop(void)
{
	char	*line;

	while (1)
	{
		line = readline("minishell> ");
		if (!line)
		{
			printf("exit\n");
			break ;
		}
		if (*line)
			add_history(line);
		if (0 == ft_strncmp(line, "exit", ft_strlen(line)))
		{
			free(line);
			break ;
		}
		printf("%s\n",line);
		free(line);
	}
	rl_clear_history();
}

int	main(void)
{
	shell_loop();
	return (0);
}

// gcc -Wall -Werror -Wextra  testing/rdline_test.c -o test -lreadline
