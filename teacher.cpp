#include "teacher.h"
#include <QDebug>
#include <iostream>

Teacher readTeacher() {
  Teacher teacher;

  qInfo() << "enter id: ";
  cin >> teacher.id;

  qInfo() << "enter name: ";
  cin >> teacher.name;

  qInfo() << "enter class_number: ";
  cin >> teacher.class_number;

  return teacher;
}

void printTeacher(Teacher teacher) {
  qInfo() << teacher.id << "\t" << teacher.name << "\t" << teacher.class_number
          << "\n";
}

void printTeachers(vector<Teacher> teachers) {
  qInfo() << "id\t\tname\t\tclass_number\n";
  for (int i = 0; i < teachers.size(); ++i) {
    printTeacher(teachers[i]);
  }
}
