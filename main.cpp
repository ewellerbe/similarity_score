#include "Course.h"
#include "Rating.h"
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <map>

using namespace std;

vector<Course> readCoursesFile(string filename) {
    ifstream file(filename.c_str());
    vector<Course> courses;
    while (true) {
        if (file.eof()) {
            break;
        }

        char line[80];
        file.getline(line, 80);
        string fullLine(line);
        stringstream s(fullLine);
        string prefix;
        s >> prefix;
        int num;
        s >> num;
        if (s.eof()) {
            break;
        }
        Course c(num, fullLine);
        courses.push_back(c);
    }
    return courses;
}

vector<Rating> readRatingsFile(string filename) {
    ifstream file(filename.c_str());
    vector<Rating> ratings;
    int student = 0;
    while (true) {
        if (file.eof()) {
            break;
        }

        char line[80];
        file.getline(line, 80);
        string fullLine(line);
        stringstream s(fullLine);
        while (!s.eof()) {
            int course;
            int rating;
            s >> course >> rating;
            if (s.eof()) {
                break;
            }
            Rating r(student, course, rating);
            ratings.push_back(r);
        }
        student++;
    }
    return ratings;
}

double similarity(const Course &c1, const Course &c2, const vector<Rating> &ratings, const vector<Course> &courses) {
    map<int,pair<double,int>> avgRate;
    
    for (const Rating &rating : ratings) {
        // create a map for student if it doesnt exist
        if (avgRate.find(rating.getStudent()) == avgRate.end() ) {
            avgRate.insert(make_pair(rating.getStudent(), make_pair(rating.getRating(), 1)));
        }
        // already there so we just add
        else {
            avgRate[rating.getStudent()].first += rating.getRating();
            avgRate[rating.getStudent()].second += 1;
        }
    }
    
   double numSum = 0, denomSum1 = 0, denomSum2 = 0;
    // loop through our map instead of making a student array
    for (const auto &pair : avgRate) {
        double Rsi = -1, Rsj = -1;
        int student = pair.first;

        for (const Rating &rating : ratings) {

            if (rating.getStudent() == student) {
                if (rating.getCourse() == c1.getID()) {
                    Rsi = rating.getRating();
                }
                else if(rating.getCourse() == c2.getID()) {
                    Rsj = rating.getRating();
                }
            }
        
        }
        
        avgRate[student].first /= avgRate[student].second;
        if (Rsi != -1 && Rsj != -1){  
            numSum += (Rsi - avgRate[student].first) * (Rsj - avgRate[student].first);
        }

        if (Rsi != -1)
        denomSum1 += pow( (Rsi - avgRate[student].first), 2);
        if (Rsj != -1)
        denomSum2 += pow( (Rsj - avgRate[student].first), 2);
    }

    // calculate simularity
    return ( numSum / (sqrt(denomSum1) * sqrt(denomSum2)) );
}

int main(int argc, char **argv) {
    string courseFilename = string(argv[1]);
    string ratingFilename = string(argv[2]);

    vector<Course> course = readCoursesFile(courseFilename);
    vector<Rating> rating = readRatingsFile(ratingFilename);

    int numA, numB;
    cin >> numA >> numB;
    Course courseA, courseB;

    for (int i = 0; i < course.size(); i++) {
        if (course[i].getID() == numA) {
            courseA = course[i];
        }
        if (course[i].getID() == numB) {
            courseB = course[i];
        }
    }

    fprintf(stdout, "CPSC %d and CPSC %d have a similarity score of %+05.4f\n", numA, numB, similarity(courseA, courseB, rating, course));

    return 0;
}
