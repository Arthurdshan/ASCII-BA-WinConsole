#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define n_of_frames 6569
#define path_size 20

void progress_bar(int counter)
{
    int cost, x;

    float p = (float)((float)counter/n_of_frames)*100;

    cost = 25;
    x = (counter *(68 - cost)) / n_of_frames;

    printf("Loading frames: %d/%d ", counter, n_of_frames);

    printf("[");

    for(int i = 0; i <= x; i++)
        printf("#");

    for(int i = 0; i < 68 - cost - x; i++)
        printf("-");

    printf("] (%.1f%%)\r", p);
}

char *get_frame(const char *file_name)
{
    FILE *f = fopen(file_name, "r");

    fseek(f, 0, SEEK_END);
    long fsize = ftell(f);
    fseek(f, 0, SEEK_SET);

    char *str = malloc(fsize + 1);
    fread(str, 1, fsize, f);

    fclose(f);

    str[fsize] = '\0';

    return str;
}

char **get_all_frames()
{
    char **frames = malloc(n_of_frames * sizeof(char *));

    for(int i = 1; i <= n_of_frames; i++)
    {
        char *file_name = malloc(path_size * sizeof(char));
        sprintf(file_name, "frames\\BA%d.txt", i);
        frames[i - 1] = get_frame(file_name);

        progress_bar(i);

        free(file_name);
    }
    return frames;
}

int main()
{
    printf("Bad Apple!! In Windows Terminal.\n");

    char **frames = get_all_frames();

	printf("\n<Press ENTER to start>");

    getchar();

	PlaySound("frames\\BA.wav", NULL, SND_ASYNC);

    for (int i = 1; i < n_of_frames; i++)
    {
        printf("%s", frames[i - 1]);
        _sleep(28);
    }

    return 0;
}
