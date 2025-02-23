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
    if (argc != 4) {
        printf("Usage: Reporter <source file> <report file> <pay per hour>\n");
        return 1;
    }

    const char *src_filename = argv[1];
    const char *report_filename = argv[2];
    double pay_per_hour = atof(argv[3]);

    FILE *src = fopen(src_filename, "rb");
    if (!src) {
        perror("Failed to open source file");
        return 1;
    }

    FILE *report = fopen(report_filename, "w");
    if (!report) {
        perror("Failed to create report file");
        fclose(src);
        return 1;
    }

    fprintf(report, "Отчет по файлу «%s»\n", src_filename);
    fprintf(report, "Номер сотрудника\tИмя сотрудника\tЧасы\tЗарплата\n");

    struct employee emp;
    while (fread(&emp, sizeof(struct employee), 1, src) == 1) {
        double salary = emp.hours * pay_per_hour;
        fprintf(report, "%d\t%s\t%.2lf\t%.2lf\n", emp.num, emp.name, emp.hours, salary);
    }

    fclose(src);
    fclose(report);
    return 0;
}