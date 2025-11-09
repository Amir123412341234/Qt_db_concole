#include "student.h"
#include <QDebug>
#include <iostream>

Student readStudent() {
  Student student;
  qInfo() << "id: ";
  cin >> student.id;
  qInfo() << "name: ";
  cin >> student.name;
  qInfo() << "class.number: ";
  cin >> student.class_number;

  return student;
}
void printStudent(Student student) {
  qInfo() << student.id << "\t" << student.name << "\t" << student.class_number
          << "\n";
}
void printStudents(vector<Student> student) {
  qInfo() << "id\t\tname\tclass.number\n";
  for (int i = 0; i < student.size(); ++i) {
    printStudent(student[i]);
  }
}
