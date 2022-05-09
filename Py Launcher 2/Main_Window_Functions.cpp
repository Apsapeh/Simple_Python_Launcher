#include "Main_Window.h"
#include "main.h"
using namespace PyLauncher2;

// Функия добавления панели скипта на форму
System::Void Main_Window::add_script_panel(unsigned short script_number, System::String^ script_name, const wchar_t* tag_arg)
{
	System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(Main_Window::typeid));
	Button^ script_exit_btn = gcnew Button;
	Button^ script_restart_btn = gcnew Button;
	Panel^ script_panel = gcnew Panel;
	Label^ script_name_lbl = gcnew Label;
	Label^ script_status = gcnew Label;

	// Кнопка завершения процесса скрипта
	script_exit_btn->BackColor = System::Drawing::Color::Transparent;
	script_exit_btn->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"close_btn")));
	script_exit_btn->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
	script_exit_btn->Cursor = System::Windows::Forms::Cursors::Default;
	script_exit_btn->FlatAppearance->BorderSize = 0;
	script_exit_btn->FlatAppearance->MouseDownBackColor = System::Drawing::Color::Transparent;
	script_exit_btn->FlatAppearance->MouseOverBackColor = System::Drawing::Color::Transparent;
	script_exit_btn->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
	script_exit_btn->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(236)), static_cast<System::Int32>(static_cast<System::Byte>(179)),
		static_cast<System::Int32>(static_cast<System::Byte>(101)));
	script_exit_btn->Location = System::Drawing::Point(382, 8);
	script_exit_btn->Margin = System::Windows::Forms::Padding(0);
	script_exit_btn->Name = L"Script_exit_btn";
	script_exit_btn->Size = System::Drawing::Size(110, 33);
	script_exit_btn->TabIndex = 1;
	script_exit_btn->Text = L"Завершить";
	script_exit_btn->Tag = *tag_arg;
	script_exit_btn->UseVisualStyleBackColor = false;
	script_exit_btn->Click += gcnew System::EventHandler(this, &Main_Window::Exit_Button_Click);
	script_exit_btn->MouseLeave += gcnew System::EventHandler(this, &Main_Window::Button_MouseLeave);
	script_exit_btn->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &Main_Window::Button_MouseMove);

	// Кнопка переpапуска скрипта
	script_restart_btn->BackColor = System::Drawing::Color::Transparent;
	script_restart_btn->Cursor = System::Windows::Forms::Cursors::Default;
	script_restart_btn->FlatAppearance->BorderSize = 1;
	script_restart_btn->FlatAppearance->MouseDownBackColor = System::Drawing::Color::Transparent;
	script_restart_btn->FlatAppearance->MouseOverBackColor = System::Drawing::Color::Transparent;
	script_restart_btn->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
	script_restart_btn->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(236)), static_cast<System::Int32>(static_cast<System::Byte>(179)),
		static_cast<System::Int32>(static_cast<System::Byte>(101)));
	script_restart_btn->Location = System::Drawing::Point(505, 12);
	script_restart_btn->Margin = System::Windows::Forms::Padding(0);
	script_restart_btn->Name = L"Script_restart_btn";
	script_restart_btn->Size = System::Drawing::Size(24, 24);
	script_restart_btn->TabIndex = 1;
	script_restart_btn->Text = L"R";
	script_restart_btn->Tag = *tag_arg;
	script_restart_btn->UseVisualStyleBackColor = false;
	script_restart_btn->Click += gcnew System::EventHandler(this, &Main_Window::Restart_Button_Click);

	// Панель скрипта
	script_panel->BackColor = System::Drawing::Color::Transparent;
	script_panel->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"panel")));
	script_panel->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
	script_panel->Controls->Add(script_name_lbl);
	script_panel->Controls->Add(script_exit_btn);
	script_panel->Controls->Add(script_status);
	script_panel->Controls->Add(script_restart_btn);
	script_panel->Location = System::Drawing::Point(50, 177 + script_number * 63); // 177 + n(48+10)
	script_panel->Name = L"Script_panel";
	script_panel->Size = System::Drawing::Size(540, 48);
	script_panel->TabIndex = 3;
	script_panel->Margin = System::Windows::Forms::Padding(25);

	// Название скрипта
	script_name_lbl->AutoSize = false;
	script_name_lbl->AutoEllipsis = true;
	script_name_lbl->Font = (gcnew System::Drawing::Font(L"Jura", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	script_name_lbl->ForeColor = System::Drawing::Color::White;
	script_name_lbl->Location = System::Drawing::Point(10, 13);
	script_name_lbl->Name = L"Script_name";
	script_name_lbl->Size = System::Drawing::Size(270, 21);
	script_name_lbl->TabIndex = 2;
	script_name_lbl->Text = script_name;

	// Статус скрипта
	script_status->AutoEllipsis = true;
	script_status->Font = (gcnew System::Drawing::Font(L"Jura", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	script_status->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(16)), static_cast<System::Int32>(static_cast<System::Byte>(111)),
		static_cast<System::Int32>(static_cast<System::Byte>(15)));
	script_status->Location = System::Drawing::Point(275, 17);
	script_status->Name = L"Script_status";
	script_status->RightToLeft = System::Windows::Forms::RightToLeft::No;
	script_status->Size = System::Drawing::Size(100, 16);
	script_status->TabIndex = 3;
	script_status->Text = L"Работает";
	script_status->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;


	this->Controls->Add(script_panel); // Добавляет панель на форму
	sc_panels->Add(script_panel);	   // Сохраняет панель в массив
}

// Фунция отключения панели
System::Void Main_Window::off_panel(Panel^ panel)
{
	panel->Controls["Script_status"]->Text = L"Не работает";
	panel->Controls["Script_status"]->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(122)), static_cast<System::Int32>(static_cast<System::Byte>(12)),
		static_cast<System::Int32>(static_cast<System::Byte>(10)));

	panel->Controls["Script_exit_btn"]->Text = L"Завершено";
	panel->Controls["Script_exit_btn"]->Enabled = false;

}



///////////////////////////////////////////   Обработка событий   /////////////////////////////////////////////
// Функция разворачивающая окно из трей
System::Void Main_Window::TrayIcon_MouseDoubleClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
{
	this->Show();
	this->ShowInTaskbar = true;
	this->WindowState = FormWindowState::Normal;
}

// Функция сворачивающая окно в трей
System::Void Main_Window::Main_Window_Resize(System::Object^ sender, System::EventArgs^ e)
{
	if (this->WindowState == FormWindowState::Minimized)
		this->Hide();
}


// Функция закрвыающя скрипт
System::Void Main_Window::Exit_Button_Click(System::Object^ sender, System::EventArgs^ e)
{
	System::String^ str = safe_cast<Button^>(sender)->Tag->ToString(); // Тэг сохраняется строкой
	safe_cast<Button^>(sender)->Text = L"Закрывается";

	int proc_num = System::Int32::Parse(str); // Тэг сохраняет как число
	TerminateProcess(procs_info[proc_num].hProcess, 0); // Закрывает процесс
}

// Функция обновляющая список скриптов
System::Void Main_Window::Refresh_Scripts_Click(System::Object^ sender, System::EventArgs^ e)
{
	USES_CONVERSION;
	
	Json scripts_json; // Json со скриптами
	extern std::vector<string> scripts_name;
	
	// Чтение Scripts.json
	ifstream readed("Settings.json");
	scripts_json = Json::parse(readed);
	readed.close();

	write_log("! Обновление списка скриптов", "\n");

	string* temp_str = new string;               // Строка хранящая команду до преодразования в LPWSTR
	string* temp_script_name = new string;               // Строка хранящая имя скрипта
	LPWSTR* command = new LPWSTR;               // Перменная хранящая команду в LPWSTR
	unsigned short* num = new unsigned short(scripts_name.size());    // Нумерация скрипта
	for (auto script : scripts_json["Scripts"])
	{
		*temp_script_name = script["name"];
		ifstream file_is_exist(*temp_script_name);
		if (script["turn"] && file_is_exist.good() && find(scripts_name.begin(), scripts_name.end(), script["name"]) == scripts_name.end())
		{
			file_is_exist.close();
			*temp_script_name = script["name"];
			*temp_str = "python ";
			*temp_str += script["name"];

			*command = A2W(temp_str->c_str(), temp_str->length()); // Преобраование команды из std::string в LPWSTR

			if (CreateChildProcess(*command) == 0) // Создаёт поток, и если создано успешно, то добваляет панель скрипта на форму
			{
				this->add_script_panel(*num, gcnew System::String(temp_script_name->c_str()), std::to_wstring(*num).std::wstring::c_str());
				scripts_name.push_back(*temp_script_name);
				write_log("Скрипт \"" + *temp_script_name + "\" запущен");
				++*num;
			}
		}
	}
	delete num;
	delete temp_script_name;
	delete temp_str;
	delete command;
}

// Функция перезгружающая скрипт
System::Void Main_Window::Restart_Button_Click(System::Object^ sender, System::EventArgs^ e)
{
	USES_CONVERSION;
	int proc_num = System::Int32::Parse(safe_cast<Button^>(sender)->Tag->ToString());
	string command = "python " + scripts_name[proc_num];

	DWORD exit_code;        // Код завершения
	thr_process_dis_pass = true;
	
	GetExitCodeProcess(procs_info[proc_num].hProcess, &exit_code); // Получает текущий статус процесса
	if (exit_code == STILL_ACTIVE)
	{
		TerminateProcess(procs_info[proc_num].hProcess, 0);
	}
	
	if (CreateChildProcess(A2W(command.c_str(), command.length()), proc_num) == 0)
	{
		if (find(del_scripts.begin(), del_scripts.end(), proc_num) != del_scripts.end())
			del_scripts.erase(find(del_scripts.begin(), del_scripts.end(), proc_num));

		sc_panels[proc_num]->Controls["Script_status"]->Text = L"Работает";
		sc_panels[proc_num]->Controls["Script_status"]->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(16)), static_cast<System::Int32>(static_cast<System::Byte>(111)),
			static_cast<System::Int32>(static_cast<System::Byte>(15)));

		sc_panels[proc_num]->Controls["Script_exit_btn"]->Text = L"Завершить";
		sc_panels[proc_num]->Controls["Script_exit_btn"]->Enabled = true;

		write_log("Скрипт \"" + scripts_name[proc_num] + "\" перезапущен");
	}
	
	thr_process_dis_pass = false;
}

// Функции для "анимирования" кнопки
System::Void Main_Window::Button_MouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
{
	System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(Main_Window::typeid));
	safe_cast<Button^>(sender)->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"close_btn_hover")));
}

System::Void Main_Window::Button_MouseLeave(System::Object^ sender, System::EventArgs^ e)
{
	System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(Main_Window::typeid));
	safe_cast<Button^>(sender)->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"close_btn")));
}