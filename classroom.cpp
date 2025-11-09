#include "classroom.h"
#include <QDebug>
#include <iostream>

Classroom readClassroom() {
  Classroom room;

  qInfo() << "enter id: ";
  cin >> room.id;

  qInfo() << "enter name: ";
  cin >> room.name;

  return room;
}

void printClassroom(Classroom room) {
  qInfo() << room.id << "\t" << room.name << "\n";
}

void printClassrooms(vector<Classroom> rooms) {
  qInfo() << "id\t\tname\n";
  for (int i = 0; i < rooms.size(); ++i) {
    printClassroom(rooms[i]);
  }
}
