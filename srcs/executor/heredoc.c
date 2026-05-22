/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dprudnik <dprudnik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 00:00:00 by aleriaza          #+#    #+#             */
/*   Updated: 2026/05/22 16:06:49 by dprudnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Read one heredoc body line: readline in interactive, fgets otherwise */
// FIX : not allowed to use fgets!
static char	*read_hd_line(int interactive)
{
	char	buf[4096];
	size_t	len;

	if (interactive)
		return (readline("> "));
	if (!fgets(buf, sizeof(buf), stdin))
		return (NULL);
	len = ft_strlen(buf);
	if (len > 0 && buf[len - 1] == '\n')
		buf[len - 1] = '\0';
	return (ft_strdup(buf));
}

/* Read lines until bare delimiter line; return collected body or NULL */
static char	*collect_heredoc_body(char *delim, int interactive)
{
	char	*body;
	char	*line;
	char	*tmp;
	int		len;

	body = ft_strdup("");
	len = ft_strlen(delim);
	while (body)
	{
		line = read_hd_line(interactive);
		if (!line || (ft_strncmp(line, delim, len) == 0 && line[len] == '\0'))
			return (free(line), body);
		tmp = ft_strjoin(line, "\n");
		free(line);
		body = ft_strjoin_free(body, tmp);
		free(tmp);
	}
	return (NULL);
}

/* Write body to a unique temp file; return heap-allocated path */
static char	*heredoc_tmpfile(char *body)
{
	char	path[] = "/tmp/ms_hd_XXXXXX";
	int		fd;

	fd = mkstemp(path);
	if (fd == -1)
		return (NULL);
	write(fd, body, ft_strlen(body));
	close(fd);
	return (ft_strdup(path));
}

/* Expand redir filename or, for heredoc, collect body into tmp file */
void	resolve_last_redir(t_redir *last, t_shell *shell)
{
	char	*resolved;

	if (last->type == REDIR_HEREDOC)
		resolved = handle_heredoc(last->file, shell);
	else
		resolved = expand_token(last->file, shell);
	free(last->file);
	last->file = resolved;
}

/* Orchestrate heredoc: detect quoting, collect body, expand, write tmp file */
char	*handle_heredoc(char *delim, t_shell *shell)
{
	int		expand;
	char	*clean;
	char	*body;
	char	*path;

	expand = !is_quote(delim[0]);
	clean = expand_token(delim, shell);
	if (!clean)
		return (NULL);
	body = collect_heredoc_body(clean, isatty(STDIN_FILENO));
	free(clean);
	if (!body)
		return (NULL);
	if (expand)
	{
		clean = expand_token(body, shell);
		free(body);
		body = clean;
	}
	path = heredoc_tmpfile(body);
	free(body);
	return (path);
}
