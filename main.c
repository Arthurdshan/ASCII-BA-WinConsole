#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>

#define n_of_frames 6569
#define path_size 20

#define TITLE "[Touhou] Bad Apple!!"
#define rcrs(x, y) printf("\033[%d;%dH", (x), (y))
#define hide_crs() printf("\e[?25l")

void setup()
{
    system("CHCP 932");
    system("mode con: cols=80 lines=38");

    printf(TITLE);

    printf("\nEnjoy. <Press ENTER to start>");

    getchar();

    system("cls");
    printf("\nLoading...");

    PlaySound("frames\\BA.wav", NULL, SND_ASYNC);
    Sleep(250);
    PlaySound(NULL, 0, 0);

    system("cls");
    rcrs(0, 1);
}

char *get_frame(const char *file_name)
{
    FILE *f = fopen(file_name, "r");

    if (f == NULL)
        exit(1);

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

void print_progress_box(int min, int sec, int frame, int total_frames)
{
    printf("\n -----------------------------------------------------------------------------\n");
    printf(" | Elapsed Time: %02d:%02d \t\t\t\t\t    Frame: %04d/%d |", min, sec, frame, total_frames);
    printf("\n -----------------------------------------------------------------------------\n");
}

int main()
{
    int time_sec, min, sec, delta;
    clock_t now, last_frame, start_time;

    char **frames = get_all_frames();

    setup();

    PlaySound("frames\\BA.wav", NULL, SND_ASYNC);

    start_time = last_frame = clock();

    for (int i = 1; i <= n_of_frames; i++)
    {
        now = clock();
        delta = now - last_frame;
        last_frame += i % 30 == 0 ? 43 : 33;

        time_sec = (now - start_time) / CLOCKS_PER_SEC;
        min = time_sec / 60;
        sec = time_sec % 60;

        if (delta < 33)
        {
            Sleep(33 - delta);

            hide_crs();

            printf("%s\n\n", TITLE);

            printf("%s", frames[i - 1]);

            free(frames[i - 1]);

            print_progress_box(min, sec, i, n_of_frames);

            rcrs(0, 1);
        }
    }

    free(frames);

    system("cls");
    printf("Thank you for watching.\n");
    printf("Press enter to exit.\n");
    getchar();

    return 0;
}
