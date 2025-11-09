#include <QCoreApplication>
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>
#include <QtSql/QSqlDatabase>
#include <iostream>
#include "classroom.h"
#include "student.h"
#include "teacher.h"
using namespace std;

QSqlDatabase connectDB(const char* db_name);
void createStudentsTables(QSqlDatabase db);

void add_classroom(QSqlDatabase db, Classroom room);
std::vector<Classroom> get_classrooms(QSqlDatabase db);

bool add_student(QSqlDatabase db, Student student);
std::vector<Student> get_students(QSqlDatabase db);

bool add_teacher(QSqlDatabase db, Teacher teacher);
std::vector<Teacher> get_teachers(QSqlDatabase db);

int main(int argc, char* argv[]) {
  QCoreApplication a(argc, argv);

  QSqlDatabase students_db = connectDB("students");
  createStudentsTables(students_db);

  while (true) {
    int menuItem;
    qInfo() << "enter:\n"
               "\t0 - exit\n"
               "\t1 - add class\n"
               "\t2 - print classes\n"
               "\t3 - add student\n"
               "\t4 - show students\n"
               "\t5 - add teacher\n"
               "\t6 - show teachers\n"
               ": ";
    cin >> menuItem;

    if (0 == menuItem) {
      break;
    } else if (1 == menuItem) {
      Classroom room = readClassroom();
      add_classroom(students_db, room);
    } else if (2 == menuItem) {
      vector<Classroom> rooms = get_classrooms(students_db);
      printClassrooms(rooms);
    } else if (3 == menuItem) {
      Student student;
      student = readStudent();
      add_student(students_db, student);

    } else if (4 == menuItem) {
      vector<Student> students = get_students(students_db);
      printStudents(students);
    } else if (5 == menuItem) {
      Teacher teacher = readTeacher();
      add_teacher(students_db, teacher);
    } else if (6 == menuItem) {
      vector<Teacher> teachers = get_teachers(students_db);
      printTeachers(teachers);
    }
  }

  return a.exec();
}

QSqlDatabase connectDB(const char* db_name) {
  QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

  db.setDatabaseName(db_name);
  bool ok = db.open();

  if (ok == false) {
    throw std::runtime_error("connection error");
  }
  return db;
}

void createStudentsTables(QSqlDatabase db) {
  QSqlQuery query(db);
  query.exec("PRAGMA foreign_keys = ON");
  query.exec(
      "CREATE TABLE IF NOT EXISTS classroom ("
      "  id INT NOT NULL,"
      "  name VARCHAR(50) NOT NULL,"
      "  PRIMARY KEY (id)"
      ");");
  query.exec(
      "CREATE TABLE IF NOT EXISTS student ("
      "  id INT NOT NULL,"
      "  name VARCHAR(50) NOT NULL,"
      "  class_number INT,"
      "  PRIMARY KEY (id),"
      "  FOREIGN KEY (class_number) REFERENCES classroom (id)"
      ");");
  query.exec(
      "CREATE TABLE IF NOT EXISTS teacher ("
      "  id INT NOT NULL,"
      "  name VARCHAR(50) NOT NULL,"
      "  class_number INT,"
      "  PRIMARY KEY (id),"
      "  FOREIGN KEY (class_number) REFERENCES classroom (id)"
      ");");

  if (query.lastError().isValid()) {
    throw std::runtime_error(std::string("Create database failed") +
                             db.lastError().text().toStdString());
  }
}

void add_classroom(QSqlDatabase db, Classroom room) {
  QSqlQuery query(db);

  std::string queryText = "INSERT INTO classroom (id, name) VALUES(";
  queryText += std::to_string(room.id) + ", \"" + room.name + "\");";

  query.exec(QString::fromStdString(queryText));

  if (query.lastError().isValid()) {
    throw std::runtime_error(std::string("add classroom failed") +
                             db.lastError().text().toStdString());
  }
}
bool add_teacher(QSqlDatabase db, Teacher teacher) {
  QSqlQuery query(db);

  std::string queryText =
      "INSERT INTO teacher (id, name, class_number) VALUES(";
  queryText += std::to_string(teacher.id) + ", \"" + teacher.name + "\", " +
               std::to_string(teacher.class_number) + ");";

  query.exec(QString::fromStdString(queryText));

  if (query.lastError().isValid()) {
    return false;
  }
  return true;
}

std::vector<Classroom> get_classrooms(QSqlDatabase db) {
  std::vector<Classroom> rooms;
  QSqlQuery query(db);
  query.exec("SELECT id, name FROM classroom WHERE id > 0");

  while (query.next()) {
    Classroom room;
    room.id = query.value(0).toString().toInt();
    room.name = query.value(1).toString().toStdString();
    rooms.push_back(room);
  }
  return rooms;
}

bool add_student(QSqlDatabase db, Student student) {
  QSqlQuery query(db);

  std::string queryText =
      "INSERT INTO student (id, name, class_number) VALUES(";
  queryText += std::to_string(student.id) + ", \"" + student.name + "\", " +
               std::to_string(student.class_number) + ");";

  query.exec(QString::fromStdString(queryText));

  if (query.lastError().isValid()) {
    return false;
  }
  return true;
}
std::vector<Student> get_students(QSqlDatabase db) {
  std::vector<Student> students;
  QSqlQuery query(db);
  query.exec("SELECT id, name, class_number FROM student");

  while (query.next()) {
    Student student;
    student.id = query.value(0).toString().toInt();
    student.name = query.value(1).toString().toStdString();
    student.class_number = query.value(2).toString().toInt();
    students.push_back(student);
  }
  return students;
}

std::vector<Teacher> get_teachers(QSqlDatabase db) {
  std::vector<Teacher> teachers;
  QSqlQuery query(db);
  query.exec("SELECT id, name, class_number FROM teacher");

  while (query.next()) {
    Teacher teacher;
    teacher.id = query.value(0).toString().toInt();
    teacher.name = query.value(1).toString().toStdString();
    teacher.class_number = query.value(2).toString().toInt();
    teachers.push_back(teacher);
  }
  return teachers;
}
