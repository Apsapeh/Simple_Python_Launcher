#pragma once
#include <vector>
#include <string>
#include <Windows.h>

extern std::vector<PROCESS_INFORMATION> procs_info;
extern std::vector<std::string> scripts_name;
extern std::vector<unsigned short> del_scripts;        // Массив хранящий удалённые потоки
extern bool thr_process_dis_pass;              // "Приостанавливает" поток обработки закрытия скрипта



namespace PyLauncher2 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для Main_Window
	/// </summary>
	public ref class Main_Window : public System::Windows::Forms::Form
	{
	public:
		System::Collections::Generic::List<System::Windows::Forms::Panel^>^ sc_panels = gcnew System::Collections::Generic::List<System::Windows::Forms::Panel^>();
		
		Main_Window(void)
		{
			InitializeComponent();

			this->WindowState = FormWindowState::Minimized;
			this->ShowInTaskbar = false;
			this->Hide();

		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~Main_Window()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ Big_name;
	private: System::Windows::Forms::Label^ author_lbl;
	protected:	private: System::Windows::Forms::Label^ label2;

	private: System::Windows::Forms::NotifyIcon^ notifyIcon1;
	private: System::Windows::Forms::Button^ refresh_scripts_btn;

	private: System::ComponentModel::IContainer^ components;


	protected:

	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(Main_Window::typeid));
			this->Big_name = (gcnew System::Windows::Forms::Label());
			this->author_lbl = (gcnew System::Windows::Forms::Label());
			this->notifyIcon1 = (gcnew System::Windows::Forms::NotifyIcon(this->components));
			this->refresh_scripts_btn = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// Big_name
			// 
			this->Big_name->Font = (gcnew System::Drawing::Font(L"Jura", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->Big_name->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(236)), static_cast<System::Int32>(static_cast<System::Byte>(179)),
				static_cast<System::Int32>(static_cast<System::Byte>(101)));
			this->Big_name->Location = System::Drawing::Point(156, 47);
			this->Big_name->Name = L"Big_name";
			this->Big_name->Size = System::Drawing::Size(289, 35);
			this->Big_name->TabIndex = 0;
			this->Big_name->Text = L"Python Launcher";
			// 
			// author_lbl
			// 
			this->author_lbl->AutoSize = true;
			this->author_lbl->Font = (gcnew System::Drawing::Font(L"Jura", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->author_lbl->Location = System::Drawing::Point(436, 65);
			this->author_lbl->Name = L"author_lbl";
			this->author_lbl->Size = System::Drawing::Size(70, 12);
			this->author_lbl->TabIndex = 2;
			this->author_lbl->Text = L"by Apsapeh";
			// 
			// notifyIcon1
			// 
			this->notifyIcon1->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"notifyIcon1.Icon")));
			this->notifyIcon1->Text = L"PyLauncher";
			this->notifyIcon1->Visible = true;
			this->notifyIcon1->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Main_Window::TrayIcon_MouseDoubleClick);
			// 
			// refresh_scripts_btn
			// 
			this->refresh_scripts_btn->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"close_btn")));
			this->refresh_scripts_btn->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->refresh_scripts_btn->FlatAppearance->BorderSize = 0;
			this->refresh_scripts_btn->FlatAppearance->MouseDownBackColor = System::Drawing::Color::Transparent;
			this->refresh_scripts_btn->FlatAppearance->MouseOverBackColor = System::Drawing::Color::Transparent;
			this->refresh_scripts_btn->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->refresh_scripts_btn->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(236)),
				static_cast<System::Int32>(static_cast<System::Byte>(179)), static_cast<System::Int32>(static_cast<System::Byte>(101)));
			this->refresh_scripts_btn->Location = System::Drawing::Point(505, 150);
			this->refresh_scripts_btn->Name = L"refresh_scripts_btn";
			this->refresh_scripts_btn->Size = System::Drawing::Size(80, 23);
			this->refresh_scripts_btn->TabIndex = 3;
			this->refresh_scripts_btn->Text = L"Обновить";
			this->refresh_scripts_btn->UseVisualStyleBackColor = true;
			this->refresh_scripts_btn->Click += gcnew System::EventHandler(this, &Main_Window::Refresh_Scripts_Click);
			this->refresh_scripts_btn->MouseLeave += gcnew System::EventHandler(this, &Main_Window::Button_MouseLeave);
			this->refresh_scripts_btn->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &Main_Window::Button_MouseMove);
			// 
			// Main_Window
			// 
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::None;
			this->AutoScroll = true;
			this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(4)), static_cast<System::Int32>(static_cast<System::Byte>(28)),
				static_cast<System::Int32>(static_cast<System::Byte>(50)));
			this->ClientSize = System::Drawing::Size(640, 360);
			this->Controls->Add(this->refresh_scripts_btn);
			this->Controls->Add(this->author_lbl);
			this->Controls->Add(this->Big_name);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MaximizeBox = false;
			this->Name = L"Main_Window";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"PyLauncher";
			this->Resize += gcnew System::EventHandler(this, &Main_Window::Main_Window_Resize);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion


/////////////////////////////////   Дополнительные фунции и фунции обработки событий   /////////////////////////////////////////////

public:
	// Функия добавления панели скипта на форму
	System::Void add_script_panel(unsigned short script_number, System::String^ script_name, const wchar_t* tag_arg);

	// Фунция отключения панели
	System::Void off_panel(Panel^ panel);


private: 
	// Функция разворачивающая окно из трей
	System::Void TrayIcon_MouseDoubleClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);
	// Функция сворачивающая окно в трей
	System::Void Main_Window_Resize(System::Object^ sender, System::EventArgs^ e);


	// Функция закрвыающя скрипт
	System::Void Exit_Button_Click(System::Object^ sender, System::EventArgs^ e);
	// Функция обновляющая список скриптов
	System::Void Refresh_Scripts_Click(System::Object^ sender, System::EventArgs^ e);
	// Функция перезапускающая скрипт
	System::Void Restart_Button_Click(System::Object^ sender, System::EventArgs^ e);
	// Функции для "анимирования" кнопки
	System::Void Button_MouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);
	System::Void Button_MouseLeave(System::Object^ sender, System::EventArgs^ e);
	
};
}
