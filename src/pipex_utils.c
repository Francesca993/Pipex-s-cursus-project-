/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontini <fmontini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 13:48:03 by fmontini          #+#    #+#             */
/*   Updated: 2025/03/12 16:10:07 by fmontini         ###   ########.fr       */
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

void first_child(char *infile, int *pipe_fd, char *in_cmd, char **envp)
{
    int fd_in;
    fd_in = open(infile, O_RDONLY);
    if(fd_in == -1)
        error_exit("Fallita apertura del primo file");
    dup2(fd_in, STDIN_FILENO);
    dup2(pipe_fd[1], STDOUT_FILENO);


    close(fd_in);
    close(pipe_fd[0]);
    close(pipe_fd[1]);
    // Eseguo il primo comando
        execute_cmd(in_cmd, envp);
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
void    second_child(char *out_cmd, int *pipe_fd, char **envp, char *outfile)
{
    int fd_out;
    fd_out = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644); 
    if (fd_out == -1)
        error_exit("Fallita apertura del file output");
    dup2(pipe_fd[0], STDIN_FILENO); //Legge dalla pipe invece di stdin
    dup2(fd_out, STDOUT_FILENO); //Scrive su file2 invece di stdout
    close(fd_out);
    close(pipe_fd[0]);
    close(pipe_fd[1]);
    execute_cmd(out_cmd, envp);
}

void error_exit(const char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}
/**
//execve(path, argv, envp) esegue un nuovo programma sostituendo 
//l'attuale processo con il comando specificato.
///bin/sh" → Usa la shell per eseguire cmd.
//"-c" → Indica alla shell di eseguire il comando cmd.
//envp per trovare il percorso dei comandi all'interno di PATH, ad esempio
void    execute_cmd(char *cmd, char **envp)
{
    char *argv[] = {"/bin/sh", "-c", cmd, NULL};
    if (execve("/bin/sh", argv, envp) == -1)
        error_exit("execve fallita");  
}
*/

void    free_paths(char **paths)
{
    int    i;
    
    i = 0;
    while (paths[i])
    {
        free(paths[i]);
        i++;
    }
    free(paths);
}
/*
Scorro la matrice con dentro tutti i vari path per cercare il comando 
e testa in ognuno con (access(path, F_OK | X_OK) == 0)
*/

char *construct_path(char *cmd, char **paths)
{
    int     i;
    char    *part_path;
    char    *path;

    i = 0;
    while (paths[i])
    {
        part_path = ft_strjoin(paths[i], "/");
        path = ft_strjoin(part_path, cmd);
        free(part_path);
        if (access(path, F_OK | X_OK) == 0)
        {
            free_paths(paths);
            return (path);
        }
        free(path);
        i++;
    }
    return (NULL);
}
/*
Vado a scorrere l'envp conm ft_strnstr che cerca PATH
creo una matrice con tutti vari path con split separando per i :
vado a cercare il path funzionante con construct path
libero la memoria e ritorno il path corretto
*/
char *find_path(char *cmd, char **envp)
{
    char    **paths;
    char    *path;
    int     i;
    
    i = 0;
    while ((envp[i]) && (ft_strnstr(envp[i], "PATH=", 5) == NULL))
        i++;
    if (!envp[i])
        return (NULL);
    paths = ft_split(envp[i] + 5, ':');
    path = construct_path(cmd, paths);
    free_paths(paths);
    return (path);
}
/*
La funzione execute Divide il comando e i suoi argomenti con split
perché execve richiede un array di stringhe (char **argv) per 
eseguire correttamente il programma.
 usa find_path per trovare 
il comando e poi lo esegue con execve
*/
void    execute(char *argv, char **envp)
{
    char    **cmd
    char    *path;
    int     i;
}