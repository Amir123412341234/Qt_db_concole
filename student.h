#ifndef STUDENT_H
#define STUDENT_H
#include <string>
#include <vector>

using namespace std;

struct Student {
  int id;
  string name;
  int class_number;
};

Student readStudent();
void printStudent(Student student);
void printStudents(vector<Student> student);

#endif  // STUDENT_H
