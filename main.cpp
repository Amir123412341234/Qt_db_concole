#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "authform.h"

using namespace std;

struct User {
  int id;
  string name;
  string password;
  enum Role { Teacher = 1, Student } role;
};

struct SessionRequest {
  int id;
  string subject_name;
  int author_id;
  int hour_cost;
  bool is_active;
};

struct Response {
  int id;
  string subject_name;
  int author_id;
  int request_id;
};

string roleToString(User::Role role) {
  if (role == User::Role::Teacher) {
    return "teacher";
  }
  return "student";
}

User read(istream& ist) {
  User user;
  int role;
  ist >> user.name >> user.password >> role;
  while (role < 1 || role > 2) {
    cout << "Wrong role(need 1 or 2): ";
    ist >> role;
  }
  user.role = (User::Role)role;
  return user;
}

struct IMenu {
  virtual void show() = 0;
};

struct StudentMenu : public IMenu {
  void show() {
    int item;
    cout << "enter:\n"
         << "\t0-leave\n"
         << "\t1-search rep\n"
         << "\t2-see otkliks\n"
         << "\t3-add application\n"
         << "\t4-choose rep\n: ";
    cin >> item;
    if (item == 0) {
      return;
    } else if (item == 1) {
    } else if (item == 2) {
    } else if (item == 3) {
    }
    show();
  }
};

struct TeacherMenu : public IMenu {
  void show() {
    int item;
    cout << "enter:\n"
         << "\t0-leave\n"
         << "\t1-show\n"
         << "\t2-show otclicks\n"
         << "\t3-add otclick\n: ";
    cin >> item;
    if (item == 0) {
      return;
    } else if (item == 1) {
    } else if (item == 2) {
    }
    show();
  }
};

struct UsersModel {
  vector<User> users;

  bool checkUser(string login, string password) {
    bool isFind = false;
    for (int i = 0; i < users.size(); i++) {
      if (users[i].name == login && users[i].password == password) {
        isFind = true;
        break;
      }
    }
    return isFind;
  }

  string getRole(string login) {
    for (int i = 0; i < users.size(); i++) {
      if (users[i].name == login) {
        return roleToString(users[i].role);
      }
    }
    throw runtime_error("Can't open file");
  }

  UsersModel(string filename) {
    ifstream ifst;
    ifst.open(filename);
    if (!ifst) {
      throw runtime_error("Can't open file");
    }
    while (true) {
      User user = read(ifst);
      if (!ifst) {
        break;
      }
      users.push_back(user);
    }
  }
};

struct AuthMenu {
  void show() {
    string login;
    string password;
    cout << "login:" << endl;
    cin >> login;
    cout << "password:" << endl;
    cin >> password;

    if (m_model.checkUser(login, password) == false) {
      cout << "no User";
    } else {
      if (m_model.getRole(login) == "student") {
        StudentMenu menu;
        menu.show();
      } else {
        TeacherMenu menu;
        menu.show();
      }
    }
  }
  AuthMenu(UsersModel model) : m_model(model) {}
  UsersModel& m_model;
};

/*int main(int argc, char* argv[]) {
  UsersModel model("users.txt");
  AuthMenu menu(model);
  menu.show();
}*/
int main(int argc, char* argv[]) {
  QApplication app(argc, argv);
  AuthForm w;
  w.show();
  app.exec();
}
