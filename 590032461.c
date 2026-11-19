/*
 * Project: AI-Assisted Student Record and Result Management System
 * Course: Programming in C (PRC1001)
 * Student SAP ID: 590032461
 *
 * Note: The program starts with five sample records to demonstrate the
 * minimum-record requirement. Records added/deleted during a run are held
 * in memory and reset when the program exits.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_STUDENTS 100
#define NAME_LEN 60
#define PHONE_LEN 20
#define EMAIL_LEN 80
#define MISSING_SGPA (-1.0)

typedef struct {
    long long sapId;
    int rollNo;
    char name[NAME_LEN];
    char phone[PHONE_LEN];
    char email[EMAIL_LEN];
    int year;
    int semester;
    double sgpa[8];
} Student;

Student students[MAX_STUDENTS];
int studentCount = 0;

/* Read a complete line safely, including spaces. */
void readLine(const char *prompt, char *buffer, size_t size) {
    printf("%s", prompt);
    if (fgets(buffer, (int)size, stdin) == NULL) {
        buffer[0] = '\0';
        return;
    }
    buffer[strcspn(buffer, "\n")] = '\0';
}

/* Read and validate an integer. */
int readInt(const char *prompt, int minValue, int maxValue) {
    char line[100], *end;
    long value;

    while (1) {
        readLine(prompt, line, sizeof(line));
        value = strtol(line, &end, 10);
        while (isspace((unsigned char)*end)) end++;

        if (line[0] != '\0' && *end == '\0' &&
            value >= minValue && value <= maxValue) {
            return (int)value;
        }
        printf("Invalid input. Enter a number from %d to %d.\n",
               minValue, maxValue);
    }
}

/* Read and validate a positive SAP ID. */
long long readSapId(const char *prompt) {
    char line[100], *end;
    long long value;

    while (1) {
        readLine(prompt, line, sizeof(line));
        value = strtoll(line, &end, 10);
        while (isspace((unsigned char)*end)) end++;

        if (line[0] != '\0' && *end == '\0' && value > 0) return value;
        printf("Invalid SAP ID. Enter a positive whole number.\n");
    }
}

/* Read SGPA. A blank entry means that semester result is unavailable. */
double readSGPA(int semesterNumber) {
    char line[100], *end;
    double value;

    while (1) {
        char prompt[100];
        snprintf(prompt, sizeof(prompt),
                 "Enter SGPA for semester %d (0-10, blank if unavailable): ",
                 semesterNumber);
        readLine(prompt, line, sizeof(line));

        if (line[0] == '\0') return MISSING_SGPA;

        value = strtod(line, &end);
        while (isspace((unsigned char)*end)) end++;
        if (*end == '\0' && value >= 0.0 && value <= 10.0) return value;

        printf("Invalid SGPA. Enter a value from 0 to 10, or leave blank.\n");
    }
}

int findStudentIndex(long long sapId) {
    int i;
    for (i = 0; i < studentCount; i++) {
        if (students[i].sapId == sapId) return i;
    }
    return -1;
}

double calculateCGPA(const Student *student) {
    double total = 0.0;
    int count = 0, i;

    for (i = 0; i < 8; i++) {
        if (student->sgpa[i] >= 0.0) {
            total += student->sgpa[i];
            count++;
        }
    }
    return (count == 0) ? -1.0 : total / count;
}

void academicAdvisor(const Student *student) {
    double cgpa = calculateCGPA(student);

    printf("\n--- AI-Assisted Academic Advisor ---\n");
    if (cgpa < 0.0) {
        printf("No SGPA data available. Add semester results to receive advice.\n");
    } else if (cgpa >= 9.0) {
        printf("Excellent Performance - maintain your current study pattern "
               "and keep challenging yourself.\n");
    } else if (cgpa >= 7.5) {
        printf("Good Performance - stay consistent and work on small areas "
               "for improvement.\n");
    } else if (cgpa >= 6.0) {
        printf("Needs Improvement - focus more on subjects with lower SGPA "
               "and practise regularly.\n");
    } else {
        printf("Requires Immediate Attention - meet your faculty mentor, "
               "make a study plan and seek help in difficult subjects.\n");
    }
}

void displayStudent(const Student *student) {
    int i;
    double cgpa = calculateCGPA(student);

    printf("\n---------------------------------------------\n");
    printf("SAP ID      : %lld\n", student->sapId);
    printf("Roll No.    : %d\n", student->rollNo);
    printf("Name        : %s\n", student->name);
    printf("Phone       : %s\n", student->phone);
    printf("Email       : %s\n", student->email);
    printf("Year        : %d\n", student->year);
    printf("Semester    : %d\n", student->semester);
    printf("SGPA values : ");
    for (i = 0; i < 8; i++) {
        if (student->sgpa[i] >= 0.0)
            printf("S%d=%.2f ", i + 1, student->sgpa[i]);
        else
            printf("S%d=N/A ", i + 1);
    }
    if (cgpa >= 0.0) printf("\nCGPA        : %.2f\n", cgpa);
    else printf("\nCGPA        : Not available\n");
    printf("---------------------------------------------\n");
}

void addStudent(void) {
    Student newStudent;
    int i;

    if (studentCount >= MAX_STUDENTS) {
        printf("Student list is full.\n");
        return;
    }

    printf("\n--- Add Student ---\n");
    newStudent.sapId = readSapId("Enter SAP ID: ");
    if (findStudentIndex(newStudent.sapId) != -1) {
        printf("A student with this SAP ID already exists.\n");
        return;
    }

    newStudent.rollNo = readInt("Enter roll number: ", 1, 1000000);
    do {
        readLine("Enter student name: ", newStudent.name, sizeof(newStudent.name));
        if (newStudent.name[0] == '\0') printf("Name cannot be empty.\n");
    } while (newStudent.name[0] == '\0');

    readLine("Enter phone number: ", newStudent.phone, sizeof(newStudent.phone));
    readLine("Enter email ID: ", newStudent.email, sizeof(newStudent.email));
    newStudent.year = readInt("Enter year (1-4): ", 1, 4);
    newStudent.semester = readInt("Enter current semester (1-8): ", 1, 8);

    for (i = 0; i < 8; i++) newStudent.sgpa[i] = readSGPA(i + 1);

    students[studentCount++] = newStudent;
    printf("Student record added successfully.\n");
}

void searchStudent(void) {
    long long sapId = readSapId("Enter SAP ID to search: ");
    int index = findStudentIndex(sapId);

    if (index == -1) printf("Student record not found.\n");
    else displayStudent(&students[index]);
}

void displayAllStudents(void) {
    int i;
    if (studentCount == 0) {
        printf("No student records available.\n");
        return;
    }
    for (i = 0; i < studentCount; i++) displayStudent(&students[i]);
}

void displayYearWiseAverageCGPA(void) {
    int year, i, count;
    double total, cgpa;

    printf("\n--- Average CGPA by Year ---\n");
    for (year = 1; year <= 4; year++) {
        total = 0.0;
        count = 0;
        for (i = 0; i < studentCount; i++) {
            if (students[i].year == year) {
                cgpa = calculateCGPA(&students[i]);
                if (cgpa >= 0.0) {
                    total += cgpa;
                    count++;
                }
            }
        }
        if (count > 0)
            printf("Year %d: %.2f (based on %d student(s))\n",
                   year, total / count, count);
        else
            printf("Year %d: No CGPA data available\n", year);
    }
}

void deleteStudent(void) {
    long long sapId = readSapId("Enter SAP ID to delete: ");
    int index = findStudentIndex(sapId);
    int i;

    if (index == -1) {
        printf("Student record not found.\n");
        return;
    }

    for (i = index; i < studentCount - 1; i++)
        students[i] = students[i + 1];

    studentCount--;
    printf("Student record deleted successfully.\n");
}

int compareBySapId(const void *a, const void *b) {
    const Student *s1 = (const Student *)a;
    const Student *s2 = (const Student *)b;
    if (s1->sapId < s2->sapId) return -1;
    if (s1->sapId > s2->sapId) return 1;
    return 0;
}

int compareByName(const void *a, const void *b) {
    const Student *s1 = (const Student *)a;
    const Student *s2 = (const Student *)b;
    return strcmp(s1->name, s2->name);
}

void displaySortedBySapId(void) {
    Student sorted[MAX_STUDENTS];
    if (studentCount == 0) {
        printf("No student records available.\n");
        return;
    }
    memcpy(sorted, students, studentCount * sizeof(Student));
    qsort(sorted, studentCount, sizeof(Student), compareBySapId);
    printf("\n--- Students Sorted by SAP ID (Increasing) ---\n");
    for (int i = 0; i < studentCount; i++) displayStudent(&sorted[i]);
}

void displaySortedByName(void) {
    Student sorted[MAX_STUDENTS];
    if (studentCount == 0) {
        printf("No student records available.\n");
        return;
    }
    memcpy(sorted, students, studentCount * sizeof(Student));
    qsort(sorted, studentCount, sizeof(Student), compareByName);
    printf("\n--- Students Sorted by Name (A-Z) ---\n");
    for (int i = 0; i < studentCount; i++) displayStudent(&sorted[i]);
}

void showAdvisorForStudent(void) {
    long long sapId = readSapId("Enter SAP ID for academic advice: ");
    int index = findStudentIndex(sapId);

    if (index == -1) {
        printf("Student record not found.\n");
        return;
    }
    displayStudent(&students[index]);
    academicAdvisor(&students[index]);
}

void initializeSampleRecords(void) {
    Student sample[5] = {
        {590032101, 101, "Aarav Sharma", "9876500101", "aarav@example.com", 1, 1,
         {9.20, MISSING_SGPA, MISSING_SGPA, MISSING_SGPA, MISSING_SGPA, MISSING_SGPA, MISSING_SGPA, MISSING_SGPA}},
        {590032102, 102, "Diya Verma", "9876500102", "diya@example.com", 1, 1,
         {8.10, MISSING_SGPA, MISSING_SGPA, MISSING_SGPA, MISSING_SGPA, MISSING_SGPA, MISSING_SGPA, MISSING_SGPA}},
        {590032103, 103, "Kabir Singh", "9876500103", "kabir@example.com", 2, 3,
         {6.80, 7.10, MISSING_SGPA, MISSING_SGPA, MISSING_SGPA, MISSING_SGPA, MISSING_SGPA, MISSING_SGPA}},
        {590032104, 104, "Meera Joshi", "9876500104", "meera@example.com", 3, 5,
         {5.20, 5.80, 5.60, 6.00, MISSING_SGPA, MISSING_SGPA, MISSING_SGPA, MISSING_SGPA}},
        {590032105, 105, "Rohan Gupta", "9876500105", "rohan@example.com", 4, 7,
         {9.00, 9.30, 8.90, 9.10, 9.20, 9.40, 9.10, MISSING_SGPA}}
    };

    memcpy(students, sample, sizeof(sample));
    studentCount = 5;
}

void showMenu(void) {
    printf("\n========== STUDENT RECORD & RESULT MANAGEMENT ==========\n");
    printf("1. Add student details\n");
    printf("2. Search and display a student record\n");
    printf("3. Calculate/display a student's CGPA and academic advice\n");
    printf("4. Display average CGPA of each year\n");
    printf("5. Display all student records\n");
    printf("6. Delete a student record\n");
    printf("7. Display records in increasing order of SAP ID\n");
    printf("8. Display records in increasing order of Name\n");
    printf("9. Exit\n");
    printf("=========================================================\n");
}

int main(void) {
    int choice;
    initializeSampleRecords();

    printf("Welcome to the AI-Assisted Student Record and Result Management System!\n");
    printf("Five sample student records have been loaded.\n");

    do {
        showMenu();
        choice = readInt("Enter your choice (1-9): ", 1, 9);

        switch (choice) {
            case 1: addStudent(); break;
            case 2: searchStudent(); break;
            case 3: showAdvisorForStudent(); break;
            case 4: displayYearWiseAverageCGPA(); break;
            case 5: displayAllStudents(); break;
            case 6: deleteStudent(); break;
            case 7: displaySortedBySapId(); break;
            case 8: displaySortedByName(); break;
            case 9: printf("Thank you for using the system. Goodbye!\n"); break;
        }
    } while (choice != 9);

    return 0;
}
