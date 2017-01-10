#include "orientation.h"
#include <map>
#include <iostream>
#include <fstream>
#include <array>
#include <list>
#include <msclr/marshal_cppstd.h>

using namespace std;
using namespace System;
namespace GradDivision {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;

	public value struct GDValue {
		String^ id;
		String^ first;
		String^ last;
		String^ degree;
		String^ school;
		String^ program;
		String^ location;
		//String^ day1reg;
		//String^ day2reg;
		//String^ day1signed;
		//String^ day2signed;
		bool    isCheckedInDay1;
		bool    isCheckedInDay2;
	};

#pragma once
	public ref class applicationContext
	{
	public:
		int day;
		orientation *orient;
		System::String^ currentFilename;
	
		applicationContext();
		void readFile();
		void writeFile();
		void checkin(String^ ID);
		void searchStudent(String^ degreeType, String^ school, String^ program, System::Windows::Forms::ListBox^ listBox);
		void mergeFile();
		//form 3 funciton
		void addSchoolToListBox(System::Windows::Forms::ListBox^ listBox);
		void findProgram(String^ school, System::Windows::Forms::ListBox^ listBox);
	private:
		//orientation *orient;
	};
}