#ifndef CLASSROOM_H
#define CLASSROOM_H
#include <string>
#include <vector>

using namespace std;

struct Classroom {
  int id;
  string name;
};

Classroom readClassroom();
void printClassroom(Classroom room);
void printClassrooms(vector<Classroom> rooms);

#endif  // CLASSROOM_H
