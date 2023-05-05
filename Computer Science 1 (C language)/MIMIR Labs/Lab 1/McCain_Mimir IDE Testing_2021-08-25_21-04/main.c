#include <stdio.h>
#define MAXSIZE 500

struct Student
{
    int student_ID;
    int g1, g2, g3;
    float average;
};

struct Student getMaxAverageStudent(struct Student *s, int n)
{
    int i;
    float current_max = 0.0; //will store the highest average score from all the students...
    int student_index = 0; //will store the index for the student with the highest average score...
    
    for (int i = 0; i < n; i++)
    {
        if (s[i].average > current_max)
        {
            current_max = s[i].average;
            student_index = i;
        }
    }
    
    return s[student_index]; //return the index of the student with the highest average score...
}

int main()
{
    struct Student students[MAXSIZE]; //create an array of 500 students...
    int i;
    int n;
    FILE *infile; //will used to point to students.txt input file...
    FILE *outfile; //will be used for file output...
    
    infile = fopen("students.txt", "r"); //read from input file...
    outfile = fopen("out.txt", "w"); //write to output file...
    
    fscanf(infile, "%d", &n); //stores the first line (int 5) in txt file to n...
    
    for (i = 0; i < n; i++)
    {
        fscanf(infile, "%d", &students[i].student_ID); //store student_ID..
        fscanf(infile, "%d %d %d", &students[i].g1, &students[i].g2, &students[i].g3); //store grades...
        
        students[i].average = (students[i].g1 + students[i].g2 + students[i].g3) / 3.0; //store average (must divide by float)...
        
        printf("%d %d %d %d %0.2f\n", students[i].student_ID, students[i].g1, students[i].g2, students[i].g3, students[i].average); //print to console...
        fprintf(outfile, "%d %d %d %d %0.2f\n", students[i].student_ID, students[i].g1, students[i].g2, students[i].g3, students[i].average); //write to output file...
    }
    
    struct Student maxStudent = getMaxAverageStudent(students, n);
    
    printf("\nMaximum Average is %0.2f and the student is %d\n", maxStudent.average, maxStudent.student_ID); //print to console...
    fprintf(outfile, "\nMaximum Average is %0.2f and the student is %d\n", maxStudent.average, maxStudent.student_ID); //write to output file...
    
    
    //close files...
    fclose(infile);
    fclose(outfile);
    
    return 0;
}