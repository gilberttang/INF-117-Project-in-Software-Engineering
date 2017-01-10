//
//  Header.h
//  Grad Orientation
//
//  Created by test on 22/5/2016.
//  Copyright © 2016年 gilbertan. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

using namespace std;


#ifndef orientation_H
#define orientation_H

class  orientation
{
    public:
		orientation() {}
		~orientation() {}
        //student structure: as a value of studentMap
        typedef struct{
            int ID;
            string lastName;
            string firstName;
            string degreeType;
            string school;
            string program;
            string email;
            bool day1 = false;
            bool day2 = false;
            bool walkup = false;
            char registered;
            char region;
        }student;
 
        //program structure
        typedef struct{
            int totalstudent = 0;
            int totalAttend = 0;
        }program;
    
        //school structure: as a value of schoolMap
        typedef struct{
            int totalstudent = 0;
            int numOfReg = 0;
            int totalAttend = 0;
            int numOfwalkup = 0;
            map<string, program> programMap = std::map<string, program>();
        }school;
		map <int, student> studentMap; //store all the student info
		map<string, school> schoolMap; //store school info and the major's which corresonding to that school

        void printAllStudent();
        void printStudent(map<int, student>::iterator student);
        bool lookup(string school, string program, string degreeType, map<int, student> &result);
        bool checkIn(int ID, int day);
        void findSchool(int day);
        void pullDatafromCSV(ifstream &file);
        void saveData(int day, string filename);
        //void checkIn(int day); // Use case, probably UI will handle it
        void saveStat(int day, string statName);
    
    private:
        //private memeber
        map<string, int> attribute;// store the index of the column that is corresponding to an attribute
        const string attr_studentID = "student_id", attr_lastName = "last_name", attr_firstName = "first_name",
        attr_degreeType = "Class Level", attr_school = "School", attr_program = "Major",
        attr_email = "email_address", attr_region = "Region", attr_orientID = "orient_id", attr_register = "Register",
        attr_Day1 = "Day1",  attr_Day2 = "Day2", attr_walkup = "Walkup";
};

#endif
