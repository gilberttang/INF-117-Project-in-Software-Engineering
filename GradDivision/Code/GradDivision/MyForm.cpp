#include "MyForm.h"

using namespace System;
using namespace System::Windows::Forms;

void initParam(GradDivision::applicationContext^ context)
{
}

[STAThread]
void Main(cli::array<System::String ^> ^args)
{
	GradDivision::applicationContext^ context = gcnew GradDivision::applicationContext();

	initParam(context);

	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	GradDivision::MyForm^ form = gcnew GradDivision::MyForm(context);
	Application::Run(form);
}


