#ifndef RATING_H
#define RATING_H

#include <vector>

class Rating{
private:
  int studentID;
  int courseID;
  int score;
public:
  Rating( int s , int c , int r ){ studentID = s; courseID = c; score = r; };
  int getStudent() const{ return studentID; };
  int getCourse() const{ return courseID; };
  int getRating() const{ return score; }; 
};

#endif
