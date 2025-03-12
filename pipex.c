/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontini <fmontini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 12:41:18 by fmontini          #+#    #+#             */
/*   Updated: 2025/03/06 15:32:14 by fmontini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main(int argc, char *argv[], char *envp[])
{
    if(argc != 5)
    {
        ft_printf("Errore nell'uso dei parametri.\n");
        ft_printf("Sintassi corretta: infile command command outfile");
        return (0);
    }
    int fd_in; //nuovi fd?
    int fd_out;
    int pipe_fd[2]; //array per la pipe
    // pipe_fd[0] sarà usato dal secondo processo (cmd2) per leggere l'output di cmd1.
    // pipe_fd[1] sarà usato dal primo processo (cmd1) per scrivere il suo output nella pipe.
    int pid1;//ProcessID 
    int pid2;

    if (pipe(pipe_fd) == -1)
    // crea un meccanismo di comunicazione tra due processi dove
    //a pipe_fd[0] legge
    // a pipe_fd[1] scrive
        error_exit("Fallita la creazione della pipe");
    //Creiamo un nuovo processo figlio che esegue il primo comando e scrive nella pipe
    pid1 = fork();
    //crea un nuovo processo duplicando il processo chiamante.
    //Dopo l'esecuzione di fork(), avremo due processi
    //il padre continua l esecuzione normale e il figlio sara  uuna copia del padre
    if (pid1 == -1)
        error_exit("Fallita crreazione fork figlio");
        
    //il processo figlio dovra aprire un file e restituire un file descriptor.
    if (pid1 == 0)  //Se fork restituisce 0 siamo nel processo figlio
    {    
    //Se fork() restituisce un numero positivo, siamo nel processo padre e pid1 contiene 
    //l'ID del processo figlio.
        fd_in = open(argv[1], O_RDONLY); //apriamo in sola lettura
        if (fd_in == -1)
            error_exit("Fallita apertura del primo file");
        dup2(fd_in, STDIN_FILENO); // // Legge da file1 invece di stdin
        dup2(pipe_fd[1], STDOUT_FILENO);// Scrive nella pipe invece di stdout
        //Chiudiamo fd_in e pipe_fd[0] perché non servono.
        close(fd_in);//chiudiamo il lato di lettura?
        close(pipe_fd[0]);// lato lettura della pipe
        close(pipe_fd[1]);//chiudiamo il lato di scrittura
        execute_cmd(argv[2], envp);//cos e envp?
    }
    pid2 = fork();
    //crea il secondo figlio dal processo padre che servira per?
    if(pid2 == 0)
    {
        //vado ad aprire il file su cui dovro scrivere
        //O_RDONLY: apre il file in sola lettura.
        //O_WRONLY | O_CREAT | O_TRUNC: apre il file in scrittura, lo crea se non esiste, e lo svuota se già esiste.
        //0644: imposta i permessi del file.
        fd_out = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644); //?? che sono tutte queste sigle?
        if (fd_out == -1)
            error_exit("Fallita apertura del file output");
    
        dup2(pipe_fd[0], STDIN_FILENO); //Legge dalla pipe invece di stdin
        dup2(fd_out, STDOUT_FILENO); //Scrive su file2 invece di stdout
        // perche ogni volta chiudiamo tutto?
        close(fd_out);
        close(pipe_fd[0]);
        close(pipe_fd[1]);
        // e qui cosa fa?
        execute_cmd(argv[3], envp);
    }
    //perche chiudiamo di nuovo?
    close(pipe_fd[0]);
    close(pipe_fd[1]);
    //mi assicuro che il padre aspetti i processi del figlio?
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
    return(1);
}