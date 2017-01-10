//
//  orientation.cpp
//  Grad Orientation
//
//  Created by test on 22/5/2016.
//  Copyright © 2016年 gilbertan. All rights reserved.
//
#include "orientation.h"

//search and check-in for a student at the same time, input: student ID and day(day1 or day2)
bool orientation::lookup(string school, string program, string degreeType, map<int, student> &result){
    for (std::map<int, student>::iterator it = studentMap.begin(); it!=studentMap.end(); ++it){
        if ( it->second.school == school && it->second.program == program && it->second.degreeType == degreeType)
            result.insert(pair<int, student>(it->first, it->second));
    }
    if (!result.empty())
        return true;
    else
        return false;
}

bool orientation::checkIn(int ID, int day){
    std::map<int, student>::iterator searchIt = studentMap.find(ID);
    if ( searchIt != studentMap.end()){
        if ( searchIt->second.registered != 'R')
            searchIt->second.walkup = true;
        if ( day == 1)
            searchIt->second.day1 = true;
        else if (day == 2)
            searchIt->second.day2 = true;
        else
            return false;
        printStudent(searchIt);
        return true;
    }
    else
        return false;
}

//print all the student info
void orientation::printAllStudent(){
    for (std::map<int, student>::iterator student = studentMap.begin(); student!=studentMap.end(); ++student){
        printStudent(student);
    }
}

void orientation::printStudent(std::map<int, student>::iterator student){
    cout <<"Orient ID: " << student->first << endl;
    cout <<"Student ID: " << student->second.ID << endl;
    cout <<"First Name: " << student->second.firstName << endl;
    cout <<"Last Name: " << student->second.lastName << endl;
    cout <<"Class Level: " << student->second.degreeType << endl;
    cout <<"School: " << student->second.school << endl;
    cout <<"Program: " << student->second.program << endl;
    cout <<"Email Address: " << student->second.email << endl;
    cout <<"Region: " << student->second.region << endl;
    cout <<"Registered: " << student->second.registered << endl;
    cout <<"Walk up: " << student->second.walkup << endl;
    cout <<"Day 1 Check in: " << student->second.day1 << endl;
    cout <<"Day 2 Check in: " << student->second.day2 << endl << '\n';
}

//create a map for every school with value(total student number in that school, and majorMap: the major which corresponding to that school)
void orientation::findSchool(int day){
    for (std::map<int, student>::iterator student = studentMap.begin(); student!=studentMap.end(); ++student){
        school tempschool;
        schoolMap.insert(pair<string, school>(student->second.school, tempschool));
    }
	if (day == 2) {
		for (std::map<int, student>::iterator student = studentMap.begin(); student != studentMap.end(); ++student) {
			schoolMap[student->second.school].totalstudent++;
			if (student->second.registered == 'R')
				schoolMap[student->second.school].numOfReg++;
			if (student->second.day2 == true && !student->second.walkup)
				schoolMap[student->second.school].totalAttend++;
			if (student->second.walkup == true)
				schoolMap[student->second.school].numOfwalkup++;
			//program
			schoolMap[student->second.school].programMap[studentMap[student->first].program].totalstudent++;
			if (student->second.day2 == true)
				schoolMap[student->second.school].programMap[studentMap[student->first].program].totalAttend++;
		}
	}
	if (day == 1) {
		for (std::map<int, student>::iterator student = studentMap.begin(); student != studentMap.end(); ++student) {
			if (student->second.region == 'I') {
				schoolMap[student->second.school].totalstudent++;
				if (student->second.registered == 'R')
					schoolMap[student->second.school].numOfReg++;
				if (student->second.day1 == true && !student->second.walkup)
					schoolMap[student->second.school].totalAttend++;
				if (student->second.walkup == true)
					schoolMap[student->second.school].numOfwalkup++;
				//program
				schoolMap[student->second.school].programMap[studentMap[student->first].program].totalstudent++;
				if (student->second.day1 == true)
					schoolMap[student->second.school].programMap[studentMap[student->first].program].totalAttend++;
			}
		}
	}

   // saveStat(day);
//    for (std::map<string, orientation::school>::iterator school = schoolMap.begin(); school != schoolMap.end(); ++school){
//        cout << school->first << ": \n" << "Total Student: " << school->second.totalstudent << endl;
//        cout <<  "Registered Attendees: " << school->second.numOfReg << endl;
//        cout <<  "Total Attendees: " << school->second.totalAttend << endl;
//        cout <<  "Walk-ups: " << school->second.numOfwalkup << endl;
//        for (std::map<string, program>::iterator it = school->second.programMap.begin(); it!= school->second.programMap.end(); ++it){
//            cout << it->first << ": \n" << it->second.totalstudent << endl;
//            cout << it->second.totalAttend << endl;
//            cout << it->second.totalstudent - it->second.totalAttend << endl;
//        }
//        std::cout << endl;
//    }
}

void orientation::saveStat(int day, string statName){
    ofstream myfile;
	myfile.open(statName);
    if (day == 1)
        myfile<<"Day 1\n\n";
    else if (day == 2)
        myfile<<"Day 2\n\n";
    else{
        cout << "Wrong day." << endl;
        return;
    }
    myfile<<"Alphabetical by School"<<endl;
    myfile<< "School,New Students,Registered Attendees,% of Registered out of New Students,Total Attendees,% of Attendees out of New Students,% of Attendees out of Registered,Walk-ups,No-shows\n";
    
    for (map<string, school>::iterator it = schoolMap.begin(); it != schoolMap.end(); ++it){
        myfile<<it->first<<","<<it->second.totalstudent<<","<<it->second.numOfReg<<","
        <<ceil(((double)it->second.numOfReg/(double)it->second.totalstudent)*100)<<","<<it->second.totalAttend<<","
        <<ceil(((double)it->second.totalAttend/(double)it->second.totalstudent)*100)<<","
        <<ceil(((double)it->second.totalAttend/(double)it->second.numOfReg)*100)<<","
        <<it->second.numOfwalkup<<","<<it->second.numOfReg-it->second.totalAttend+it->second.numOfwalkup<< endl;
    }
    
    myfile<<"\n\nAttendance Breakdown by School Department/Program"<<endl;
    set<string> schoolOrder;
    for (map<string, school>::iterator it = schoolMap.begin(); it != schoolMap.end(); ++it){
        myfile<<it->first<<": "<< it->second.totalAttend<<"\n";
        for ( map<string, program>::iterator programIt = it->second.programMap.begin(); programIt != it->second.programMap.end()
             ; ++programIt )
            myfile<<","<<programIt->first<<": "<< programIt->second.totalAttend<<endl;
        myfile<<"\n";
    }
    
//    myfile<<
//    
//    set<map<string, program>::iterator> programOrder;
//    for( set<string>::iterator it = schoolOrder.begin(); it != schoolOrder.end(); ++it){
//        programOrder.insert(schoolMap[*it].programMap.begin());
//    }
//    
//    for(  set<map<string, program>::iterator> ::iterator it = programOrder.begin(); it!= programOrder.end(); ++it){
//        if (!(*it)->first.empty())
//            myfile<< (*it)->first<< ": " << (*it)->second.totalAttend << ",";
//    }
    
    myfile.close();
    schoolMap.clear();
}

//get that data from CSV file and put the student Info in studentMap
void orientation::pullDatafromCSV(ifstream &file){
    bool getData = false;
    string value;
	cout << "This is working" << endl;
    while ( file.good() )
    {
        getline ( file, value );
        if (getData){
            istringstream ss(value);
            string token;
            int k = 0, ID = 0;
            student tempStudent;
            while(std::getline(ss, token, ',')) {
                std::transform(token.begin(), token.end(),token.begin(), ::toupper);
                if ( k == attribute[attr_studentID])
                    tempStudent.ID = stoi(token);
                if ( k == attribute[attr_orientID])
                    ID = stoi(token);
                if ( k == attribute[attr_lastName])
                    tempStudent.lastName = token;
                if ( k == attribute[attr_firstName])
                    tempStudent.firstName = token;
                if ( k == attribute[attr_degreeType])
                    tempStudent.degreeType = token;
                if ( k == attribute[attr_school])
                    tempStudent.school = token;
                if ( k == attribute[attr_program])
                    tempStudent.program = token;
                if ( k == attribute[attr_email])
                    tempStudent.email = token;
                if ( k == attribute[attr_region])
                    tempStudent.region = token[0];
                if ( k == attribute[attr_register])
                    tempStudent.registered = token[0];
                if (  k == attribute[attr_Day1] && attribute[attr_Day1])
                    tempStudent.day1 = stoi(token);
                if (  k == attribute[attr_Day2] && attribute[attr_Day2])
                    tempStudent.day2 = stoi(token);
                if (  k == attribute[attr_walkup] && attribute[attr_walkup])
                    tempStudent.walkup = stoi(token);
                k++;
            }
            if (ID != 0){
                studentMap.insert(pair<int, student>(ID,tempStudent));
            }
        }
        
        if ( value.substr(0,10) == attr_studentID){
            getData = true;
            istringstream ss(value);
            string token;
            int k = 0;
            while(std::getline(ss, token, ',')){
                if ( token == attr_studentID)
                    attribute.insert(pair<string,int>(attr_studentID, k));
                if ( token == attr_orientID)
                    attribute.insert(pair<string,int>(attr_orientID, k));
                if ( token == attr_lastName)
                    attribute.insert(pair<string,int>(attr_lastName, k));
                if ( token == attr_firstName)
                    attribute.insert(pair<string,int>(attr_firstName, k));
                if ( token == attr_degreeType)
                    attribute.insert(pair<string,int>(attr_degreeType, k));
                if ( token == attr_school)
                    attribute.insert(pair<string,int>(attr_school, k));
                if ( token == attr_program)
                    attribute.insert(pair<string,int>(attr_program, k));
                if ( token == attr_email)
                    attribute.insert(pair<string,int>(attr_email, k));
                if ( token == attr_region)
                    attribute.insert(pair<string,int>(attr_region, k));
                if ( token == attr_register)
                    attribute.insert(pair<string,int>(attr_register, k));
                if ( token == attr_Day1)
                    attribute.insert(pair<string,int>(attr_Day1, k));
                if ( token == attr_Day2)
                    attribute.insert(pair<string,int>(attr_Day2, k));
                if ( token == attr_walkup)
                    attribute.insert(pair<string,int>(attr_walkup, k));
                k++;
            }
        }
    }
    file.close();
}

//Save studentInfo in a CSV file
void orientation::saveData(int day, string filename){
    ofstream myfile;
	myfile.open(filename);
	
	if ( day == 1)
		myfile << "Orientation Day 1\n\n";
	else if (day == 2)
		myfile << "Orientation Day 2\n\n";

    myfile <<attr_studentID<<","<< attr_orientID<<","<<attr_lastName<<","<<attr_firstName<<","<<attr_degreeType<<","
    <<attr_school<<","<<attr_program<<","<<attr_email<<","<<attr_region<<","<<attr_register<<","<<attr_walkup<<","<<
    attr_Day1<<","<<attr_Day2<<"\n";
    for (std::map<int, student>::iterator it = studentMap.begin(); it!=studentMap.end(); ++it){
        myfile << it->second.ID  << "," <<  it->first << "," << it->second.lastName << "," << it->second.firstName << ","
        << it->second.degreeType << "," << it->second.school << "," << it->second.program << "," << it->second.email
        << "," << it->second.region << "," << it->second.registered << "," << it->second.walkup
        << "," << it->second.day1 << "," << it->second.day2 << endl;
    }
    myfile.close();
    //studentMap.clear();
}

void statistics(){
    
}

