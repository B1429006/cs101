#include <stdio.h>
#include <string.h>

typedef struct employee {
    int id;
    int age;
    char name[10];
    float salary;
} employee_t;

void emp_info(employee_t emp) {
    printf("employee id = %d\n", emp.id);
    printf("employee name = %s\n", emp.name);
    printf("employee age = %d\n", emp.age);
    printf("employee salary = %.2f\n\n", emp.salary);
}

int emp_average_age(employee_t emp[], int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += emp[i].age;
    }
    return sum / n;
}

void emp_writefile(employee_t emp[], int n) {
    FILE* fp = fopen("employee.bin", "wb+");
    if (!fp) {
        printf("File open error!\n");
        return;
    }
    fwrite(emp, sizeof(employee_t), n, fp);  
    fclose(fp);
}

int emp_readfile(employee_t emp[], int n) {
    FILE* fp = fopen("employee.bin", "rb");
    if (!fp) {
        printf("File open error!\n");
        return 0;
    }
    int count = fread(emp, sizeof(employee_t), n, fp);
    fclose(fp);

    for (int i = 0; i < count; i++) {
        printf("[%d] %d %s\n", i, emp[i].id, emp[i].name);
    }
    return count;
}

int main() {
    employee_t emp[3];

    emp[0].id = 1;
    emp[0].age = 20;
    emp[0].salary = 30000.0;
    strcpy(emp[0].name, "IU");

    emp[1].id = 2;
    emp[1].age = 26;
    emp[1].salary = 36000.0;
    strcpy(emp[1].name, "taylor");

    emp[2].id = 3;
    emp[2].age = 31;
    emp[2].salary = 90000.0;
    strcpy(emp[2].name, "swift");

    emp_writefile(emp, 3);

    employee_t read_emp[10];
    int count = emp_readfile(read_emp, 10);

    for (int i = 0; i < count; i++) {
        emp_info(read_emp[i]);
    }

    printf("Size of employee_t = %d bytes\n", (int)sizeof(employee_t));
    printf("Average age = %d\n", emp_average_age(read_emp, count));

    return 0;
}
