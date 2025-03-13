/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontini <fmontini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:26:48 by fmontini          #+#    #+#             */
/*   Updated: 2025/03/13 11:02:39 by fmontini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
fd_in -> FileDescriptor per il file di input
Apro il file di input in sola lettura
Reindirizzo stdin al file di input
Reindirizzo stdout alla pipe (scrittura)
Chiudo i file descriptor non più necessari
Eseguo il primo comando
*/
void	first_child(char *infile, int *pipe_fd, char *in_cmd, char **envp)
{
	int	fd_in;

	fd_in = open(infile, O_RDONLY);
	if (fd_in == -1)
		error_exit("Fallita apertura del primo file");
	dup2(fd_in, STDIN_FILENO);
	dup2(pipe_fd[1], STDOUT_FILENO);
	close(fd_in);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	execute(in_cmd, envp);
}

/*
Apro il file di output con permessi di scrittura
O_WRONLY: Scrittura
O_CREAT: Crea il file se non esiste
O_TRUNC: Se esiste, svuota il file
0644: Permessi (lettura/scrittura per proprietario, solo lettura per altri)
Reindirizzo stdin alla pipe (lettura)
Reindirizzo stdout al file di output
Chiudo i file descriptor non più necessari
*/
void	second_child(char *out_cmd, int *pipe_fd, char **envp, char *outfile)
{
	int	fd_out;

	fd_out = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_out == -1)
		error_exit("Fallita apertura del file output");
	dup2(pipe_fd[0], STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
	close(fd_out);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	execute(out_cmd, envp);
}

int	main(int argc, char *argv[], char *envp[])
{
	int	pipe_fd[2];
	int	pid1;
	int	pid2;

	if (argc != 5)
		error_exit("Sintassi corretta: infile command command outfile");
	if (pipe(pipe_fd) == -1)
		error_exit("Fallita la creazione della pipe");
	pid1 = fork();
	if (pid1 == -1)
		error_exit("Fallita creazione fork per il primo figlio");
	if (pid1 == 0)
		first_child(argv[1], pipe_fd, argv[2], envp);
	pid2 = fork();
	if (pid2 == -1)
		error_exit("Fallita creazione fork per il secondo figlio");
	if (pid2 == 0)
		second_child(argv[3], pipe_fd, envp, argv[4]);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (1);
}
