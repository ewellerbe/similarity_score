#ifndef COURSE_H
#define COURSE_H

#include <vector>
#include <string>

class Course{
 private:
  int id;
  std::string name;
 public:
  Course(){ id = -1; name = ""; };
  Course( int i , std::string n ){ id = i; name = n; };
  Course( const Course &c ){ id = c.getID() , name = c.getName(); };
  int getID() const { return id; };
  std::string getName() const { return name; };
};

#endif
