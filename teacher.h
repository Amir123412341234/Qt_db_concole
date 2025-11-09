#ifndef TEACHER_H
#define TEACHER_H
#include <string>
#include <vector>

using namespace std;

struct Teacher {
  int id;
  string name;
  int class_number;
};

Teacher readTeacher();
void printTeacher(Teacher teacher);
void printTeachers(vector<Teacher> teachers);

#endif  // TEACHER_H
