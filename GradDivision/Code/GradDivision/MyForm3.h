#pragma once
#include "applicationContext.h"

namespace GradDivision {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace std;

	/// <summary>
	/// Summary for MyForm3
	/// </summary>
	public ref class MyForm3 : public System::Windows::Forms::Form
	{
	public:
		MyForm3(applicationContext^ argcontext)
		{
			this->context = argcontext;
			InitializeComponent();
		}

	public:

	public:

	public:

	private: applicationContext^ context;
	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm3()
		{
			if (components)
			{
				delete components;
			}
		}

	protected:





	private: System::Windows::Forms::ListBox^  listBox1;






	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::ListBox^  listBox2;
	private: System::Windows::Forms::ListBox^  listBox3;

	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::Button^  button6;


	private: System::Windows::Forms::ListBox^  listBox5;

	private:
		

		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->listBox1 = (gcnew System::Windows::Forms::ListBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->listBox2 = (gcnew System::Windows::Forms::ListBox());
			this->listBox3 = (gcnew System::Windows::Forms::ListBox());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button6 = (gcnew System::Windows::Forms::Button());
			this->listBox5 = (gcnew System::Windows::Forms::ListBox());
			this->SuspendLayout();
			// 
			// listBox1
			// 
			this->listBox1->FormattingEnabled = true;
			this->listBox1->Location = System::Drawing::Point(188, 74);
			this->listBox1->Name = L"listBox1";
			this->listBox1->Size = System::Drawing::Size(302, 82);
			this->listBox1->TabIndex = 6;
			this->listBox1->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm3::listBox1_SelectedIndexChanged);
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(24, 50);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(72, 13);
			this->label4->TabIndex = 13;
			this->label4->Text = L"Degree Type:";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(169, 50);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(43, 13);
			this->label5->TabIndex = 14;
			this->label5->Text = L"School:";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(47, 161);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(49, 13);
			this->label6->TabIndex = 15;
			this->label6->Text = L"Program:";
			// 
			// listBox2
			// 
			this->listBox2->FormattingEnabled = true;
			this->listBox2->Items->AddRange(gcnew cli::array< System::Object^  >(2) { L"Masters", L"PhD" });
			this->listBox2->Location = System::Drawing::Point(47, 76);
			this->listBox2->Name = L"listBox2";
			this->listBox2->Size = System::Drawing::Size(120, 43);
			this->listBox2->TabIndex = 16;
			this->listBox2->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm3::listBox2_SelectedIndexChanged);
			// 
			// listBox3
			// 
			this->listBox3->FormattingEnabled = true;
			this->listBox3->Location = System::Drawing::Point(73, 183);
			this->listBox3->Name = L"listBox3";
			this->listBox3->Size = System::Drawing::Size(389, 95);
			this->listBox3->TabIndex = 17;
			this->listBox3->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm3::listBox3_SelectedIndexChanged);
			// 
			// button2
			// 
			this->button2->Enabled = false;
			this->button2->Location = System::Drawing::Point(576, 302);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(105, 38);
			this->button2->TabIndex = 19;
			this->button2->Text = L"Check In";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm3::button2_Click);
			// 
			// button6
			// 
			this->button6->Location = System::Drawing::Point(668, 376);
			this->button6->Name = L"button6";
			this->button6->Size = System::Drawing::Size(75, 23);
			this->button6->TabIndex = 20;
			this->button6->Text = L"back";
			this->button6->UseVisualStyleBackColor = true;
			this->button6->Click += gcnew System::EventHandler(this, &MyForm3::button6_Click);
			// 
			// listBox5
			// 
			this->listBox5->FormattingEnabled = true;
			this->listBox5->Location = System::Drawing::Point(512, 73);
			this->listBox5->Name = L"listBox5";
			this->listBox5->Size = System::Drawing::Size(231, 212);
			this->listBox5->TabIndex = 23;
			this->listBox5->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm3::listBox5_SelectedIndexChanged);
			// 
			// MyForm3
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(784, 411);
			this->Controls->Add(this->listBox5);
			this->Controls->Add(this->button6);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->listBox3);
			this->Controls->Add(this->listBox2);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->listBox1);
			this->Name = L"MyForm3";
			this->Load += gcnew System::EventHandler(this, &MyForm3::MyForm3_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	
		private: System::Void MyForm3_Load(System::Object^  sender, System::EventArgs^  e) {
			this->context->addSchoolToListBox(this->listBox1);
			if ( this->context->day == 1)
				this->Text = L"Sign Up Day 1";
			else
				this->Text = L"Sign Up Day 2";
		}

		private: System::Void button6_Click(System::Object^  sender, System::EventArgs^  e) {
			this->listBox5->Items->Clear();
			this->Hide();
		}

		private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
			this->button2->Enabled = false;
			string token;
			istringstream ss(msclr::interop::marshal_as< std::string >(this->listBox5->Text));
			getline(ss, token, ' ');
			this->context->checkin(gcnew String(token.c_str()));
		}

		private: System::Void listBox1_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
			this->button2->Enabled = false;
			this->listBox5->Items->Clear();
	
			String^ id = this->listBox1->Text;
			this->listBox3->Items->Clear();
			this->context->findProgram(id, this->listBox3);
		}

		private: System::Void listBox5_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
			if (this->listBox5->Items->Count != 0) {
				this->button2->Enabled = true;
			}
		}
		private: System::Void listBox3_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
			this->button2->Enabled = false;
			this->listBox5->Items->Clear();
			this->context->searchStudent(this->listBox2->Text, this->listBox1->Text, this->listBox3->Text, this->listBox5);
		}
		private: System::Void listBox2_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
			this->button2->Enabled = false;
			this->listBox5->Items->Clear();
		}
	};
}
