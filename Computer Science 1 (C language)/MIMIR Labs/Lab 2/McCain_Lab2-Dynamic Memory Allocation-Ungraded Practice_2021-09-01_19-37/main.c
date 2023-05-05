#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "leak_detector_c.h"

#define NAMEMAX 51 //last name will now have max char length of 50...


typedef struct student
{
    char *lname;
    int assignment;
    int finalExam;
    int total;
    int *quizzes;
} student;


student** readCourses(FILE *in, int *C, int *N, int *M)
{
    student **courses;
    char lname[NAMEMAX];
    int i, j;
    
    //read the first line for C, N, and M...
    fscanf(in, "%d %d %d", C, N, M);

    //allocate the memory for C number of courses...
    courses = (struct student **) malloc(*C *(sizeof(struct student *)));

    //read C number of courses...
    int cn, sn, qn;

     //allocate memory for the list of students for each course
     for(cn = 0; cn < *C; cn++)
     {
        //Array of students for cnth course
        courses[cn] = (struct student *) malloc(*N * sizeof(struct student));
         
        //now access each students of course[cn]
        for(sn = 0; sn < *N; sn++)
        {
            int total = 0; //total for the student...

            //read name and get the length of the name
            fscanf(in, "%s", lname);
            int nameLength = strlen(lname) + 1;
            //1 extra space for NULL char as we will allocate memory
            courses[cn][sn].lname = malloc(sizeof(char) * nameLength);
            strcpy(courses[cn][sn].lname, lname);

            //take assignment score
            fscanf(in, "%d", &courses[cn][sn].assignment);
            total += courses[cn][sn].assignment;

            //allocate memory for M number of quizzes for that particular student
            courses[cn][sn].quizzes = (int *) malloc (*M * sizeof(int));
            //take all quiz scores
            for(qn = 0; qn < *M; qn++)
            {
                fscanf(in, "%d", &courses[cn][sn].quizzes[qn]);
                total += courses[cn][sn].quizzes[qn];
            }

            //input the final exam score
            fscanf(in, "%d", &courses[cn][sn].finalExam);
            total += courses[cn][sn].finalExam;
            courses[cn][sn].total = total;
        }
    }
    
    return courses;
}

void printHighestTotal(FILE *outFile, student** courses, int C, int N, int M)
{
    //we need to know which course and which student so that we can print the details...
    int maxTotal = -1;
    int maxCourseIdx = 0;
    int maxStudentIdx = 0;

    for(int cn = 0; cn < C; cn++) //for each course number...
    {
        for(int sn = 0; sn < N; sn++) //for each student number...
        {
            if(courses[cn][sn].total > maxTotal) //check if current student's total is higher...
            {
                maxTotal = courses[cn][sn].total;
                maxCourseIdx = cn;
                maxStudentIdx = sn;
            }
        }
    }

    //output to console...
    printf("Name: %s\n", courses[maxCourseIdx][maxStudentIdx].lname);
    printf("Assignment: %d\n", courses[maxCourseIdx][maxStudentIdx].assignment);

    printf("Quizzes: ");
    for(int q = 0; q < M; q++)
    {
        printf("%d ", courses[maxCourseIdx][maxStudentIdx].quizzes[q]);
    }
    printf("\nFinal exam: %d", courses[maxCourseIdx][maxStudentIdx].finalExam);
    printf("\nTotal: %d", courses[maxCourseIdx][maxStudentIdx].total);
    printf("\nCourse number: %d\n", maxCourseIdx+1);
    
    //output to out.txt file...
    fprintf(outFile, "Name: %s\n", courses[maxCourseIdx][maxStudentIdx].lname);
    fprintf(outFile, "Assignment: %d\n", courses[maxCourseIdx][maxStudentIdx].assignment);

    fprintf(outFile, "Quizzes: ");
    for(int q = 0; q < M; q++)
    {
        fprintf(outFile, "%d ", courses[maxCourseIdx][maxStudentIdx].quizzes[q]);
    }
    fprintf(outFile, "\nFinal exam: %d", courses[maxCourseIdx][maxStudentIdx].finalExam);
    fprintf(outFile, "\nTotal: %d", courses[maxCourseIdx][maxStudentIdx].total);
    fprintf(outFile, "\nCourse number: %d\n", maxCourseIdx+1);
}

void release_memory(student ** st, int C, int N, int M)
{
    //release the quizzes and last names of the students in the course...
    for(int cn = 0; cn < C; cn++)
    {
        for(int sn = 0; sn < N; sn++)
        {
            free(st[cn][sn].lname);
            free(st[cn][sn].quizzes);
        }
        //release the students in the course...
        free(st[cn]);
    }
    //release the course...
    free(st);
}

int main()
{
    atexit(report_mem_leak); //for memory leak detector...
    student **courseList;
    FILE *inFile, *outFile;
    int i, j,C, N, M;
    
    //open input file...
    inFile = fopen("in.txt", "r");

    if(inFile!=NULL)
    {
        //pass by reference of C, N, and M so that we get the data from the file...
        courseList = readCourses(inFile, &C, &N, &M);

        //open output file...
        outFile = fopen("out.txt", "w");

        //find and output highest student total...
        printHighestTotal(outFile, courseList, C, N, M);

        //free memory...
        release_memory(courseList, C, N, M);
        
        //close input and output files...
        fclose(inFile);
        fclose(outFile);

    }
    else
    {
        printf("Please provide correct input file");
        exit(-1);
    }

    return 0;
}
