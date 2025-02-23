#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma pack(push, 1)
struct employee {
    int num;
    char name[10];
    double hours;
};
#pragma pack(pop)

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: Creator <filename> <number of employees>\n");
        return 1;
    }

    const char *filename = argv[1];
    int num_employees = atoi(argv[2]);

    FILE *file = fopen(filename, "wb");
    if (!file) {
        perror("Failed to open file");
        return 1;
    }

    struct employee emp;
    for (int i = 0; i < num_employees; i++) {
        printf("Enter employee %d details:\n", i+1);
        printf("Number: ");
        scanf("%d", &emp.num);
        printf("Name: ");
        scanf("%9s", emp.name);
        printf("Hours: ");
        scanf("%lf", &emp.hours);

        fwrite(&emp, sizeof(struct employee), 1, file);
    }

    fclose(file);
    return 0;
}