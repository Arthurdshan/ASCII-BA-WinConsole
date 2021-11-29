#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>

#define n_of_frames 6569
#define path_size 20

#define PROJECT_NAME "C Project - [Touhou] Bad Apple!! [ASCII ART]"
#define rcrs(x, y) printf("\033[%d;%dH", (x), (y))

char *get_frame(const char *file_name)
{
    FILE *f = fopen(file_name, "r");

    if (f == NULL) exit(1);

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

    for (int i = 1; i <= n_of_frames; i++)
    {
        char *file_name = malloc(path_size * sizeof(char));
        sprintf(file_name, "frames\\BA%d.txt", i);
        frames[i - 1] = get_frame(file_name);

        free(file_name);
    }
    return frames;
}

static inline void setup()
{
    system("mode con: cols=80 lines=30");
    printf(PROJECT_NAME);
    printf("\nPlease turn down your volume.\n");
    printf("\nEnjoy. <Press ENTER to start>");
    getchar();
}

int main()
{
    clock_t now, last_frame;

    char **frames = get_all_frames();

    setup();

    system("cls");
    printf("\nLoading...");

    Sleep(500);
    PlaySound("frames\\BA.wav", NULL, SND_ASYNC);

    system("cls");
    rcrs(0, 1);

    last_frame = clock();

    for (int i = 1; i <= n_of_frames; i++)
    {
        now = clock();
        int delta = now - last_frame;

        if (i % 30 == 0)
            last_frame += 43;
        else
            last_frame += 33;

        if (delta < 33)
        {
            Sleep(33 - delta);
            printf("%s", frames[i - 1]);
        }
    }

    Sleep(250);
	system("cls");
	printf("Thanks for watching.\n");
	printf("<Press ENTER to exit>");
	getchar();

    return 0;
}
