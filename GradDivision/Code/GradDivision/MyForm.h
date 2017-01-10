#pragma once
#include "MyForm1.h"
#include "applicationContext.h"

namespace GradDivision {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(GradDivision::applicationContext^ argcontext)
		{
			InitializeComponent();
			this->context = argcontext;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Button^  button2;
	protected:

	private:
		applicationContext^ context;
	private: System::Windows::Forms::Button^  button3;
	private: System::Windows::Forms::Button^  button4;
	private: System::Windows::Forms::Button^  button5;

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
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->button5 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Enabled = false;
			this->button1->Location = System::Drawing::Point(131, 187);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(108, 45);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Day 1";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// button2
			// 
			this->button2->Enabled = false;
			this->button2->Location = System::Drawing::Point(284, 187);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(108, 45);
			this->button2->TabIndex = 1;
			this->button2->Text = L"Day 2";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(108, 42);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(141, 59);
			this->button3->TabIndex = 2;
			this->button3->Text = L"File to read from";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &MyForm::button3_Click);
			// 
			// button4
			// 
			this->button4->Location = System::Drawing::Point(268, 42);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(141, 59);
			this->button4->TabIndex = 3;
			this->button4->Text = L"File to write to";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &MyForm::button4_Click);
			// 
			// button5
			// 
			this->button5->Location = System::Drawing::Point(444, 266);
			this->button5->Name = L"button5";
			this->button5->Size = System::Drawing::Size(78, 33);
			this->button5->TabIndex = 4;
			this->button5->Text = L"Merge";
			this->button5->UseVisualStyleBackColor = true;
			this->button5->Click += gcnew System::EventHandler(this, &MyForm::button5_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(534, 311);
			this->Controls->Add(this->button5);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Name = L"MyForm";
			this->Text = L"Grad Division";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
		if (this->context->day == 2)
			if (MessageBox::Show("Save File?", "Message", MessageBoxButtons::YesNo) 
				== System::Windows::Forms::DialogResult::Yes)
				this->context->writeFile();
		this->context->day = 1;
		MyForm1^ f1 = gcnew MyForm1(this->context);
		f1->ShowDialog();
	}
	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
		if (this->context->day == 1) {
			if (MessageBox::Show("Save File?", "Message", MessageBoxButtons::YesNo)
				== System::Windows::Forms::DialogResult::Yes)
				this->context->writeFile();
			MessageBox::Show("Read File");
			this->context->readFile();
		}
		this->context->day = 2;
		MyForm1^ f2 = gcnew MyForm1(this->context);
		f2->ShowDialog();
	}
	private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) {
		this->context->readFile();
		if (!this->context->orient->studentMap.empty()) {
			this->button1->Enabled = true;
			this->button2->Enabled = true;
			this->button3->Enabled = false;
		}
		else
			MessageBox::Show("Please choose a file to read.");
	}
	
	private: System::Void button4_Click(System::Object^  sender, System::EventArgs^  e) {
		if ( this->context->day == 1 || this->context->day == 2)
			this->context->writeFile();
		else
			MessageBox::Show("Please choose a day.");
	}
	
	private: System::Void MyForm_Load(System::Object^  sender, System::EventArgs^  e) {
	}

	private: System::Void button5_Click(System::Object^  sender, System::EventArgs^  e) {
		if (!this->context->orient->studentMap.empty())
			if (MessageBox::Show("Save File?", "Message", MessageBoxButtons::YesNo)
				== System::Windows::Forms::DialogResult::Yes)
				this->context->writeFile();
		this->context->mergeFile();
	}
};
}
