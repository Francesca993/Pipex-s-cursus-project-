/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontini <fmontini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 12:41:18 by fmontini          #+#    #+#             */
/*   Updated: 2025/03/06 15:39:40 by fmontini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main(int argc, char *argv[], char *envp[])
{
    // Controllo che il numero di argomenti sia corretto
    if (argc != 5)
    {
        ft_printf("Errore nell'uso dei parametri.\n");
        ft_printf("Sintassi corretta: infile command command outfile\n");
        return (0);
    }
    
    int fd_in; // File descriptor per il file di input
    int fd_out; // File descriptor per il file di output
    int pipe_fd[2]; // Array per la pipe: pipe_fd[0] per la lettura, pipe_fd[1] per la scrittura
    int pid1; // Process ID per il primo figlio
    int pid2; // Process ID per il secondo figlio

    // Creazione della pipe (comunicazione tra due processi)
    if (pipe(pipe_fd) == -1)
        error_exit("Fallita la creazione della pipe");
    
    // Creazione del primo processo figlio
    pid1 = fork();
    if (pid1 == -1)
        error_exit("Fallita creazione fork per il primo figlio");
    
    // Codice eseguito dal primo figlio
    if (pid1 == 0)
    {    
        // Apro il file di input in sola lettura
        fd_in = open(argv[1], O_RDONLY);
        if (fd_in == -1)
            error_exit("Fallita apertura del primo file");
        
        // Reindirizzo stdin al file di input
        dup2(fd_in, STDIN_FILENO);
        // Reindirizzo stdout alla pipe (scrittura)
        dup2(pipe_fd[1], STDOUT_FILENO);
        
        // Chiudo i file descriptor non più necessari
        close(fd_in);
        close(pipe_fd[0]); // Chiudo la lettura della pipe nel primo figlio
        close(pipe_fd[1]); // Chiudo la scrittura della pipe nel primo figlio
        
        // Eseguo il primo comando
        execute_cmd(argv[2], envp);
    }
    
    // Creazione del secondo processo figlio
    pid2 = fork();
    if (pid2 == -1)
        error_exit("Fallita creazione fork per il secondo figlio");
    
    // Codice eseguito dal secondo figlio
    if (pid2 == 0)
    {
        // Apro il file di output con permessi di scrittura
        // O_WRONLY: Scrittura
        // O_CREAT: Crea il file se non esiste
        // O_TRUNC: Se esiste, svuota il file
        // 0644: Permessi (lettura/scrittura per proprietario, solo lettura per altri)
        fd_out = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd_out == -1)
            error_exit("Fallita apertura del file output");
    
        // Reindirizzo stdin alla pipe (lettura)
        dup2(pipe_fd[0], STDIN_FILENO);
        // Reindirizzo stdout al file di output
        dup2(fd_out, STDOUT_FILENO);
        
        // Chiudo i file descriptor non più necessari
        close(fd_out);
        close(pipe_fd[0]); // Chiudo la lettura della pipe nel secondo figlio
        close(pipe_fd[1]); // Chiudo la scrittura della pipe nel secondo figlio
        
        // Eseguo il secondo comando
        execute_cmd(argv[3], envp);
    }
    
    // Il processo padre chiude la pipe (non serve più)
    close(pipe_fd[0]);
    close(pipe_fd[1]);
    
    // Attende la terminazione dei processi figli
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
    
    return (1);
}
