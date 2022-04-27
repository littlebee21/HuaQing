#ifndef SCHOOL_H
#define SCHOOL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_LEN 20
#define LESSON_LEN 16

enum SEX
{
	M = 'M',
	F = 'F',
};

enum PERSON_TYPE
{
	TEA = 1,
	STU,
};

union data
{
        char lesson[LESSON_LEN];//for teacher
        float score;//for student
};

struct person
{
        char name[NAME_LEN];
        char sex;//enum SEX
        int no;
        int type;//enum PERSON_TYPE
        union data dt;
};

char *mygets(char *pout,int size);
int output_math_teacherinfo(struct person *pt,int cnt);
float get_student_avescore(struct person *pt,int cnt);
int input_persons(struct person *pt,int cnt);

#endif
