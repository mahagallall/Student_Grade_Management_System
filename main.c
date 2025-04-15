#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define MAX_STUDENTS 100
#define MAX_SUBJECTS 10


typedef enum {
    A, B, C, D, F
} Grade;


typedef struct {
    int id;
    char name[50];
    int scores[MAX_SUBJECTS];
    int num_subjects;
    Grade grades[MAX_SUBJECTS];
} Student;


Student students[MAX_STUDENTS];
int student_count = 0;


void gotoxy(int x, int y);
void draw_box(void);
void addStudent();
void updateStudent();
Grade calculateGrade(int score);
void displayStudentResults();
void displayScreen(const char* message);
void searchStudent();
void deleteStudent();
void showAllStudents();
void saveToFile();
void loadFromFile();
void displayTopPerformers();
void displayGradeSummary();

HANDLE console;

int main() {
    SetConsoleTextAttribute(console, 6);
    console = GetStdHandle(STD_OUTPUT_HANDLE);
    loadFromFile();
    draw_box();
    saveToFile();
    return 0;
}

void gotoxy(int x, int y) {
    COORD coord = {0, 0};
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(console, coord);
}

void draw_box(void) {
    int i;
    int position = 1;
    char ch;

    while (1) {
        system("cls");


        SetConsoleTextAttribute(console, 14);


        gotoxy(39, 9);
        printf("%c", 201);
        for (i = 0; i < 30; i++) {
            printf("%c", 205);
        }
        printf("%c", 187);

        for (i = 10; i <= 22; i++) {
            gotoxy(39, i);
            printf("%c", 186);
            gotoxy(70, i);
            printf("%c", 186);
        }

        gotoxy(39, 23);
        printf("%c", 200);
        for (i = 0; i < 30; i++) {
            printf("%c", 205);
        }
        printf("%c", 188);


        gotoxy(40, 11);
        SetConsoleTextAttribute(console, position == 1 ? 13 : 11);
        printf("1. Add Student");
        gotoxy(40, 12);
        SetConsoleTextAttribute(console, position == 2 ? 13 : 11);
        printf("2. Update Student");
        gotoxy(40, 13);
        SetConsoleTextAttribute(console, position == 3 ? 13 : 11);
        printf("3. Display Student Results");
        gotoxy(40, 14);
        SetConsoleTextAttribute(console, position == 4 ? 13 : 11);
        printf("4. Search Student by ID");
        gotoxy(40, 15);
        SetConsoleTextAttribute(console, position == 5 ? 13 : 11);
        printf("5. Delete Student");
        gotoxy(40, 16);
        SetConsoleTextAttribute(console, position == 6 ? 13 : 11);
        printf("6. Show All Students");
        gotoxy(40, 17);
        SetConsoleTextAttribute(console, position == 7 ? 13 : 11);
        printf("7. Save Data to File");
        gotoxy(40, 18);
        SetConsoleTextAttribute(console, position == 8 ? 13 : 11);
        printf("8. Load Data from File");
        gotoxy(40, 19);
        SetConsoleTextAttribute(console, position == 9 ? 13 : 11);
        printf("9. Display Top Performers");
        gotoxy(40, 20);
        SetConsoleTextAttribute(console, position == 10 ? 13 : 11);
        printf("10. Display Grade Summary");
        gotoxy(40, 21);
        SetConsoleTextAttribute(console, position == 11 ? 13 : 11);
        printf("11. Exit");


        SetConsoleTextAttribute(console, 15);


        ch = getch();
        if (ch == -32) {
            ch = getch();
            if (ch == 72) {
                position--;
                if (position < 1) position = 11;
            } else if (ch == 80) {
                position++;
                if (position > 11) position = 1;
            }
        } else if (ch == 13) {
            switch (position) {
                case 1:
                    displayScreen("Add Student Screen");
                    addStudent();
                    break;
                case 2:
                    displayScreen("Update Student Screen");
                    updateStudent();
                    break;
                case 3:
                    displayScreen("Display Student Results Screen");
                    displayStudentResults();
                    break;
                case 4:
                    displayScreen("Search Student Screen");
                    searchStudent();
                    break;
                case 5:
                    displayScreen("Delete Student Screen");
                    deleteStudent();
                    break;
                case 6:
                    displayScreen("All Students Screen");
                    showAllStudents();
                    break;
                case 7:
                    displayScreen("Saving Data to File...");
                    saveToFile();
                    break;
                case 8:
                    displayScreen("Loading Data from File...");
                    loadFromFile();
                    break;
                case 9:
                    displayScreen("Top Performers Screen");
                    displayTopPerformers();
                    break;
                case 10:
                    displayScreen("Grade Summary Screen");
                    displayGradeSummary();
                    break;
                case 11:
                    printf("Exiting the menu...\n");
                    return;
            }
        }
    }
}


void displayScreen(const char* message) {
    system("cls");
    SetConsoleTextAttribute(console, 6);
    gotoxy(10, 5);
    printf("%s\n", message);
    SetConsoleTextAttribute(console, 15);
}

void addStudent() {
    if (student_count >= MAX_STUDENTS) {
        printf("Maximum student limit reached.\n");
        return;
    }

    SetConsoleTextAttribute(console, 6);
    Student new_student;
    printf("Enter Student ID: ");
    scanf("%d", &new_student.id);

    printf("Enter Student Name: ");
    getchar();
    fgets(new_student.name, 50, stdin);
    new_student.name[strcspn(new_student.name, "\n")] = 0;

    printf("Enter number of subjects: ");
    scanf("%d", &new_student.num_subjects);

    for (int i = 0; i < new_student.num_subjects; i++) {
        printf("Enter score for subject %d: ", i + 1);
        scanf("%d", &new_student.scores[i]);
        new_student.grades[i] = calculateGrade(new_student.scores[i]);
    }

    students[student_count++] = new_student;
    printf("Student added successfully.\n");
    printf("Press any key to continue...");
    getch();
}

void updateStudent() {
    int id;
    SetConsoleTextAttribute(console, 6);
    printf("Enter Student ID to update: ");
    scanf("%d", &id);

    for (int i = 0; i < student_count; i++) {
        if (students[i].id == id) {
            printf("Updating scores for %s:\n", students[i].name);
            for (int j = 0; j < students[i].num_subjects; j++) {
                printf("Enter new score for subject %d: ", j + 1);
                scanf("%d", &students[i].scores[j]);
                students[i].grades[j] = calculateGrade(students[i].scores[j]);
            }
            printf("Student scores updated successfully.\n");
            printf("Press any key to continue...");
            getch();
            return;
        }
    }

    printf("Student with ID %d not found.\n", id);
    printf("Press any key to continue...");
    getch();
}

Grade calculateGrade(int score) {
    if (score >= 90) return A;
    else if (score >= 80) return B;
    else if (score >= 70) return C;
    else if (score >= 60) return D;
    else return F;
}

void searchStudent() {
    int id;
    printf("Enter Student ID to search: ");
    scanf("%d", &id);

    for (int i = 0; i < student_count; i++) {
        if (students[i].id == id) {
            printf("\nStudent Found:\n");
            SetConsoleTextAttribute(console, 6);
            printf("ID: %d\n", students[i].id);
            printf("Name: %s\n", students[i].name);
            printf("Scores and Grades:\n");
            for (int j = 0; j < students[i].num_subjects; j++) {
                printf("Subject %d: Score = %d, Grade = %c\n", j + 1, students[i].scores[j], 'A' + students[i].grades[j]);
            }
            SetConsoleTextAttribute(console, 15);
            printf("\nPress any key to continue...");
            getch();
            return;
        }
    }

    printf("Student with ID %d not found.\n", id);
    printf("Press any key to continue...");
    getch();
}



void showAllStudents() {
    SetConsoleTextAttribute(console, 6);
    if (student_count == 0) {
        printf("No students available.\n");
        printf("Press any key to continue...");
        getch();
        return;
    }

    float highest_avg = 0;
    int highest_avg_index = 0;
    float total_score = 0;
    int total_subjects = 0;

    printf("\nAll Students:\n");
    printf("***********************************************************************\n");
    for (int i = 0; i < student_count; i++) {
        float student_total_score = 0;
        printf("ID: %d\n", students[i].id);
        printf("Name: %s\n", students[i].name);
        printf("Scores and Grades:\n");
        for (int j = 0; j < students[i].num_subjects; j++) {
            printf("Subject %d: Score = %d, Grade = %c\n", j + 1, students[i].scores[j], 'A' + students[i].grades[j]);
            student_total_score += students[i].scores[j];
        }

        float avg = student_total_score / students[i].num_subjects;
        total_score += student_total_score;
        total_subjects += students[i].num_subjects;

        if (avg > highest_avg) {
            highest_avg = avg;
            highest_avg_index = i;
        }

        printf("\n");
    }

    printf("***********************************************************************\n");
    printf("\nHighest Average Score Student:\n");
    printf("ID: %d\n", students[highest_avg_index].id);
    printf("Name: %s\n", students[highest_avg_index].name);
    printf("Average Score: %.2f\n", highest_avg);

    printf("***********************************************************************\n");

    printf("\nAverage Score of All Students: %.2f\n", total_score / total_subjects);

    printf("***********************************************************************\n");

    printf("\nPassed Students:\n");
    for (int i = 0; i < student_count; i++) {
        int passed = 1;
        for (int j = 0; j < students[i].num_subjects; j++) {
            if (students[i].grades[j] == F) {
                passed = 0;
                break;
            }
        }
        if (passed) {
            printf("ID: %d, Name: %s\n", students[i].id, students[i].name);
        }
    }

    printf("***********************************************************************\n");
    printf("\nFailed Students:\n");
    for (int i = 0; i < student_count; i++) {
        int failed = 0;
        for (int j = 0; j < students[i].num_subjects; j++) {
            if (students[i].grades[j] == F) {
                failed = 1;
                break;
            }
        }
        if (failed) {
            printf("ID: %d, Name: %s\n", students[i].id, students[i].name);
        }
    }

    printf("\nPress any key to continue...");
    getch();
}
void deleteStudent() {
    SetConsoleTextAttribute(console, 6);
    if (student_count == 0) {
        printf("No students to delete.\n");
        printf("Press any key to continue...");
        getch();
        return;
    }

    int id;
    printf("Enter Student ID to delete: ");
    scanf("%d", &id);

    for (int i = 0; i < student_count; i++) {
        if (students[i].id == id) {

            for (int j = i; j < student_count - 1; j++) {
                students[j] = students[j + 1];
            }
            student_count--;
            printf("Student with ID %d has been deleted successfully.\n", id);
            printf("Press any key to continue...");
            getch();
            return;
        }
    }

    printf("Student with ID %d not found.\n", id);
    printf("Press any key to continue...");
    getch();
}

void displayStudentResults() {
    int id;
    SetConsoleTextAttribute(console, 6);
    printf("Enter Student ID to display results: ");
    scanf("%d", &id);

    for (int i = 0; i < student_count; i++) {
        if (students[i].id == id) {
            printf("Results for %s (ID: %d):\n", students[i].name, students[i].id);
            float total_score = 0;
            for (int j = 0; j < students[i].num_subjects; j++) {
                printf("Subject %d: Score = %d, Grade = %c\n", j + 1, students[i].scores[j], 'A' + students[i].grades[j]);
                total_score += students[i].scores[j];
            }
            printf("Average Score: %.2f\n", total_score / students[i].num_subjects);
            printf("Press any key to continue...");
            getch();
            return;
        }
    }

    printf("Student with ID %d not found.\n", id);
    printf("Press any key to continue...");
    getch();
}


void saveToFile() {
    SetConsoleTextAttribute(console, 6);
    FILE *file = fopen("students.dat", "wb");
    if (!file) {
        printf("Error: Unable to save data.\n");
        return;
    }
    fwrite(&student_count, sizeof(int), 1, file);
    fwrite(students, sizeof(Student), student_count, file);
    fclose(file);
    printf("Data saved successfully.\n");
    printf("Press any key to continue...");
    getch();
}

void loadFromFile() {
    SetConsoleTextAttribute(console, 6);
    FILE *file = fopen("students.dat", "rb");
    if (!file) {
        printf("No saved data found.\n");
        return;
    }
    fread(&student_count, sizeof(int), 1, file);
    fread(students, sizeof(Student), student_count, file);
    fclose(file);
    printf("Data loaded successfully.\n");
    printf("Press any key to continue...");
    getch();
}

void displayTopPerformers() {
    SetConsoleTextAttribute(console, 6);
    if (student_count == 0) {
        printf("No students available.\n");
        printf("Press any key to continue...");
        getch();
        return;
    }

    printf("\nTop Performers:\n");
    for (int i = 0; i < student_count; i++) {
        float total_score = 0;
        for (int j = 0; j < students[i].num_subjects; j++) {
            total_score += students[i].scores[j];
        }
        float avg = total_score / students[i].num_subjects;
        if (avg >= 90) {
            printf("ID: %d, Name: %s, Average: %.2f\n", students[i].id, students[i].name, avg);
        }
    }
    printf("\nPress any key to continue...");
    getch();
}

void displayGradeSummary() {
    SetConsoleTextAttribute(console, 6);
    int grade_count[5] = {0};
    for (int i = 0; i < student_count; i++) {
        for (int j = 0; j < students[i].num_subjects; j++) {
            grade_count[students[i].grades[j]]++;
        }
    }

    printf("\nGrade Summary:\n");
    printf("A: %d\n", grade_count[A]);
    printf("B: %d\n", grade_count[B]);
    printf("C: %d\n", grade_count[C]);
    printf("D: %d\n", grade_count[D]);
    printf("F: %d\n", grade_count[F]);

    printf("\nPress any key to continue...");
    getch();
}

