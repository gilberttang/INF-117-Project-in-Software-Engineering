#include "applicationContext.h"
#include <string>
#include <array>

using namespace System;

GradDivision::applicationContext::applicationContext()
{
	orient = new orientation();
}

void GradDivision::applicationContext::readFile()
{
	orient->schoolMap.clear();
	orient->studentMap.clear();
	OpenFileDialog^ openFileDialog1 = gcnew OpenFileDialog();
	if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			String^ strFileName = openFileDialog1->InitialDirectory + openFileDialog1->FileName;
			std::string filename = msclr::interop::marshal_as< std::string >(strFileName);
			std::ifstream file(filename);
			orient->pullDatafromCSV(file);
			std::string variable = orient->studentMap[1501].lastName;
			String^ str2 = gcnew String(variable.c_str());
			MessageBox::Show(str2);
	}
}


void GradDivision::applicationContext::writeFile()
{
	SaveFileDialog^ saveFileDialog1 = gcnew SaveFileDialog();
	if (saveFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			String^ tempName = saveFileDialog1->InitialDirectory + saveFileDialog1->FileName;
			String^ writeFileName = tempName + ".csv";
			std::string filename = msclr::interop::marshal_as< std::string >(writeFileName);
			orient->saveData(day, filename);
			MessageBox::Show("File is saved successfully .\n" + writeFileName);
	}	
}

void  GradDivision::applicationContext::checkin(String^ id) {
	if (id == "")
		MessageBox::Show("ENTER ID");
	else {
		int orientID;
		if (!int::TryParse(id, orientID)) {
			MessageBox::Show("STUDENT NOT FOUND. PLEASE ENTER ID AGAIN.");
			return;
		}
		if (orient->studentMap.find(orientID) == orient->studentMap.end())
			MessageBox::Show("STUDENT NOT FOUND. PLEASE ENTER ID AGAIN.");
		else {
			orientation::student studentFound = orient->studentMap[Convert::ToInt32(id)];
			if (day == 1 && studentFound.region != 'I')
				MessageBox::Show("INTERNATIONAL ONLY");
			else {
				orient->checkIn(Convert::ToInt32(id), day);
				string message = "CHECKED IN \n\n" + to_string(studentFound.ID) + " " + studentFound.lastName + "\n" + studentFound.degreeType +
					"\n" + studentFound.school + "\n" + studentFound.program;
				MessageBox::Show(gcnew String(message.c_str()));
			}
		}
	}
}

void  GradDivision::applicationContext::addSchoolToListBox(System::Windows::Forms::ListBox^ listBox){
	orient->findSchool(day);
	for (map<string, orientation::school>::iterator school = orient->schoolMap.begin(); 
		school != orient->schoolMap.end(); ++school)
		listBox->Items->Add(gcnew String(school->first.c_str()));
}

void  GradDivision::applicationContext::findProgram(String^ school, System::Windows::Forms::ListBox^ listBox) {
	map<string, orientation::program> programMap = orient->schoolMap[msclr::interop::marshal_as< std::string >(school)].programMap;
	for (map<string, orientation::program>::iterator program = programMap.begin(); program != programMap.end(); ++program)
		listBox->Items->Add(gcnew String(program->first.c_str()));
}

void  GradDivision::applicationContext::searchStudent(String^ degreeType, String^ school, String^ program,
	System::Windows::Forms::ListBox^ listBox) {
	map<int, orientation::student> result;
	string degreeTypeS = msclr::interop::marshal_as< std::string >(degreeType);
	transform(degreeTypeS.begin(), degreeTypeS.end(), degreeTypeS.begin(), ::toupper);
	string schoolS = msclr::interop::marshal_as< std::string >(school);
	string programS = msclr::interop::marshal_as< std::string >(program);

	orient->lookup(schoolS, programS, degreeTypeS, result);
	if (!result.empty()){
		map<string, int> searchResult;
		for (map<int, orientation::student>::iterator student = result.begin(); student != result.end(); ++student)
			searchResult.insert(pair<string, int>(student->second.lastName + "," + student->second.firstName, student->first));
		
		for (map<string, int>::iterator show = searchResult.begin(); show != searchResult.end(); ++show) {
			string temp = to_string(show->second) + " " + show->first;
			listBox->Items->Add(gcnew String(temp.c_str()));
		}
	}
	else
		listBox->Items->Add("NONE STUDENT FOUND");
	result.clear();
}


void  GradDivision::applicationContext::mergeFile() {
	OpenFileDialog^ openFileDialog1 = gcnew OpenFileDialog;
	openFileDialog1->Multiselect = true;
	bool mapEmpty = true, schoolEmpty = true;
	map <int, orientation::student> tempMap;
	map<string, orientation::school> schoolMap;
	list<map <int, orientation::student>> listOfMap;
	if (!orient->studentMap.empty()) {
		mapEmpty = false;
		tempMap.insert(orient->studentMap.begin(), orient->studentMap.end());
		orient->studentMap.clear();
	}
	if (!orient->schoolMap.empty()) {
		schoolEmpty = false;
		schoolMap.insert(orient->schoolMap.begin(), orient->schoolMap.end());
		orient->schoolMap.clear();
	}

	//Read multiple files at time
	if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
		cli::array<System::String^>^ files = openFileDialog1->FileNames;
		for each (String^ strfilename in files) {
			String^ strFileName = openFileDialog1->InitialDirectory + openFileDialog1->FileName;
			std::string filename = msclr::interop::marshal_as< std::string >(strFileName);
			std::ifstream file(filename);
			orient->pullDatafromCSV(file);
			listOfMap.push_back(orient->studentMap);
		}
	}

	//merge files
	for (list<map <int, orientation::student>>::iterator merge = listOfMap.begin(); merge!= listOfMap.end(); ++merge) {
		for (map <int, orientation::student>::iterator it = merge->begin(); it != merge->end(); ++it) {
			if (it->second.day1)
				orient->studentMap[it->first].day1 = true;
			if (it->second.day2)
				orient->studentMap[it->first].day2 = true;
			if (it->second.walkup)
				orient->studentMap[it->first].walkup = true;
		}
	}

	//save merge map and the statistics
	SaveFileDialog^ saveFileDialog1 = gcnew SaveFileDialog();
	if (saveFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
		String^ tempName = saveFileDialog1->InitialDirectory + saveFileDialog1->FileName;
		String^ writeFileName = tempName + ".csv";
		std::string filename = msclr::interop::marshal_as< std::string >(writeFileName);
		orient->saveData(day, filename);

		String^ writeStatName = tempName + "_stat.csv";
		std::string statname = msclr::interop::marshal_as< std::string >(writeStatName);
		orient->findSchool(day);
		orient->saveStat(day, statname);
		MessageBox::Show("Files are saved successfully .\n" + writeFileName + "\n" + writeStatName);
	}
	orient->schoolMap.clear();
	orient->studentMap.clear();
	if (!mapEmpty) 
		orient->studentMap.insert(tempMap.begin(), tempMap.end());
	if (!schoolEmpty)
		orient->schoolMap.insert(schoolMap.begin(), schoolMap.end());
};