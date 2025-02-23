#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#pragma pack(push, 1)
struct employee {
    int num;
    char name[10];
    double hours;
};
#pragma pack(pop)

void print_binary_file(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Failed to open binary file for reading");
        return;
    }

    struct employee emp;
    printf("Contents of binary file '%s':\n", filename);
    printf("Number\tName\tHours\n");
    while (fread(&emp, sizeof(struct employee), 1, file) == 1) {
        printf("%d\t%s\t%.2lf\n", emp.num, emp.name, emp.hours);
    }

    fclose(file);
}

void print_text_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open report file");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }

    fclose(file);
}

int main() {
    char bin_filename[256];
    int num_employees;

    printf("Enter binary file name: ");
    scanf("%255s", bin_filename);
    printf("Enter number of employees: ");
    scanf("%d", &num_employees);

    char cmd_creator[512];
    sprintf(cmd_creator, "Creator.exe \"%s\" %d", bin_filename, num_employees);

    STARTUPINFO si_creator = { sizeof(STARTUPINFO) };
    PROCESS_INFORMATION pi_creator;
    if (!CreateProcess(NULL, cmd_creator, NULL, NULL, FALSE, 0, NULL, NULL, &si_creator, &pi_creator)) {
        fprintf(stderr, "Failed to start Creator\n");
        return 1;
    }

    WaitForSingleObject(pi_creator.hProcess, INFINITE);
    CloseHandle(pi_creator.hProcess);
    CloseHandle(pi_creator.hThread);

    print_binary_file(bin_filename);

    char report_filename[256];
    double pay_per_hour;

    printf("Enter report file name: ");
    scanf("%255s", report_filename);
    printf("Enter pay per hour: ");
    scanf("%lf", &pay_per_hour);

    char cmd_reporter[512];
    sprintf(cmd_reporter, "Reporter.exe \"%s\" \"%s\" %.2lf", bin_filename, report_filename, pay_per_hour);

    STARTUPINFO si_reporter = { sizeof(STARTUPINFO) };
    PROCESS_INFORMATION pi_reporter;
    if (!CreateProcess(NULL, cmd_reporter, NULL, NULL, FALSE, 0, NULL, NULL, &si_reporter, &pi_reporter)) {
        fprintf(stderr, "Failed to start Reporter\n");
        return 1;
    }

    WaitForSingleObject(pi_reporter.hProcess, INFINITE);
    CloseHandle(pi_reporter.hProcess);
    CloseHandle(pi_reporter.hThread);

    printf("\nReport contents:\n");
    print_text_file(report_filename);

    return 0;
}