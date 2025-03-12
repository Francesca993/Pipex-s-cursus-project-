/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontini <fmontini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:26:48 by fmontini          #+#    #+#             */
/*   Updated: 2025/03/12 15:57:38 by fmontini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main(int argc, char *argv[], char *envp[])
{
    if (argc != 5)
        error_exit("Sintassi corretta: infile command command outfile");
    int pipe_fd[2];
    int pid1;
    int pid2;
    
    if(pipe(pipe_fd) == -1)
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
