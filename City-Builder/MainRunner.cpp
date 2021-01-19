
#include "UsefulStuff.h"
#include "UserInputForm.h"

[System::STAThread]

int main() {

	std::vector<std::pair<std::pair<int, int>, OBJECT_TYPE>> objects;
	int coolorMapWidth;
	int colorMapHeight;

	System::Windows::Forms::Application::EnableVisualStyles();
	System::Windows::Forms::Application::SetCompatibleTextRenderingDefault(false);
	System::Windows::Forms::Application::Run(gcnew GUI::UserInputForm(objects, colorMapHeight, coolorMapWidth));


	return 0;
}