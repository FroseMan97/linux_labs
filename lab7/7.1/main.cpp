#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int pipefd[2]; // [0] чтение из канала, [1] запись в канал
    pid_t cpid1, cpid2;
    char buf1[80], buf2[80];
    char temp;
    int c1, c2;
    FILE *in_1, *in_2, *out;

    if (pipe(pipefd) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    out = fopen("out.txt", "w+");
    if (out == NULL)
    {
        printf("ошибка при открытии out.txt\n");
        return -1;
    }
    else
        printf("выполнено открыт out.txt\n");

    // 1) открыть канал и выходной файл
    // 2) породить двух потомков, которым доступны дескриптор канала для записи
    // и входной файл
    // 3) потомок читает построчно текст и записывает в канал
    // 4) родитель посимвольно читает из канала и пишет в выходной файл

    ////////////////////////////// 1 ////////////////////////////////
    cpid1 = fork();
    if (cpid1 == -1)
    {
        perror("fork1");
        exit(EXIT_FAILURE);
    }

    if (cpid1 == 0)
    {
        in_1 = fopen("in_1.txt", "r+"); // открываем 1 входной файл
        if (in_1 == NULL)
        {
            printf("ошибка при открытии in_1.txt\n");
            return -1;
        }
        else
            printf("выполнено открыт in_1.txt\n");

        close(pipefd[0]); // закрываем канал на чтение

        printf("Текст из файла:\n");
        while (fgets(buf1, 80, in_1))
        {
            printf("     %s", buf1);
            write(pipefd[1], buf1, strlen(buf1));
        }
        printf("Закрытие файла in_1.txt: ");
        if (fclose(in_1) == EOF)
            printf("ошибка\n");
        else
            printf("выполнено\n");
        _exit(EXIT_SUCCESS);
    }
    ////////////////////////////// 1 ////////////////////////////////

    ////////////////////////////// 2 ////////////////////////////////
    cpid2 = fork();
    if (cpid2 == -1)
    {
        perror("fork2");
        exit(EXIT_FAILURE);
    }

    if (cpid2 == 0)
    {
        in_2 = fopen("in_2.txt", "r+");
        if (in_2 == NULL)
        {
            printf("ошибка при открытии in_2.txt\n");
            return -1;
        }
        else
            printf("выполнено открыт in_2.txt\n");
        close(pipefd[0]);
        printf("Текст из файла:\n");
        while (fgets(buf2, 80, in_2))
        {
            printf("     %s", buf2);
            write(pipefd[1], buf2, strlen(buf2));
        }
        printf("Закрытие файла in_2.txt: ");
        if (fclose(in_2) == EOF)
            printf("ошибка\n");
        else
            printf("выполнено\n");
        _exit(EXIT_SUCCESS);
    }
    ////////////////////////////// 2 ////////////////////////////////

    close(pipefd[1]);
    while (read(pipefd[0], &temp, 1) > 0)
    {
        fputc(temp, out);
        printf("%c", temp);
    }

    wait(&cpid1);
    wait(&cpid2);
    close(pipefd[0]);

    printf("Закрытие файла out.txt: ");
    if (fclose(out) == EOF)
        printf("ошибка\n");
    else
        printf("выполнено\n");
    close(pipefd[0]);
    close(pipefd[1]);
    return 0;
}