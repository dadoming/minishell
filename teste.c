#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>

typedef struct teste_s
{
    int idade;
    char* nome;
}  teste_t;



int main(int argc, char **argv)
{
    static teste_t var;

    var.idade = argc;
    char *buffer;
    write(STDIN_FILENO, &buffer, strlen(buffer));
    var.nome = buffer;
    printf("%d %s\n", var.idade, var.nome);
    printf("id size is %d name size is %d var %d struct %d\n", sizeof(&var.idade), sizeof(&var.nome), sizeof(var), sizeof(teste_t));
    return (0);
}
