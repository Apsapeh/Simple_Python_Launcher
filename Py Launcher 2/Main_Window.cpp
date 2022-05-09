#include "main.h"

std::vector<PROCESS_INFORMATION> procs_info;    // ������ �������� ��������� � ��������� �������
std::vector<unsigned short> del_scripts;        // ������ �������� �������� ������
std::vector<string> scripts_name;               // ������ �������� ����� ��������, ����� ������ ��� ����������� � ����������� �������
bool thr_process_dis_pass = false;              // "����������������" ����� ��������� �������� �������
json_settings settings;

Json scripts_json; // Json �� ���������

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
//int main()
{
    USES_CONVERSION;

	Application::SetCompatibleTextRenderingDefault(false);
	Application::EnableVisualStyles();
	Main_Window^ form = gcnew Main_Window;

    // ������ Scripts.json
    ifstream readed("Settings.json");
    scripts_json = Json::parse(readed);
    readed.close();

    settings = {scripts_json["Settings"]["is_logging"]};

    write_log("!     ������ ���������     !", "\n");

    string* temp_str            = new string;               // ������ �������� ������� �� �������������� � LPWSTR
    string* temp_script_name    = new string;               // ������ �������� ��� �������
    LPWSTR* command             = new LPWSTR;               // ��������� �������� ������� � LPWSTR
    unsigned short* num         = new unsigned short(0);    // ��������� �������
    for (auto script : scripts_json["Scripts"])
    {
        *temp_script_name = script["name"];
        ifstream file_is_exist(*temp_script_name);
        if (script["turn"] && file_is_exist.good() && find(scripts_name.begin(), scripts_name.end(), script["name"]) == scripts_name.end())
        {
            file_is_exist.close();
            *temp_str = "python ";
            *temp_str += script["name"];

            *command = A2W(temp_str->c_str(), temp_str->length()); // ������������� ������� �� std::string � LPWSTR

            
            if (CreateChildProcess(*command) == 0) // ������ �����, � ���� ������� �������, �� ��������� ������ ������� �� �����
            {
                form->add_script_panel(*num, gcnew System::String(temp_script_name->c_str()), std::to_wstring(*num).std::wstring::c_str());
                scripts_name.push_back(*temp_script_name);
                write_log("������ \"" + *temp_script_name + "\" �������");
                ++*num;
            }
        }
    }
    delete num;     
    delete temp_script_name;
    delete temp_str;
    delete command;

    // ��������� ����� � ���������� ���������� ������
    thread process_dis_handler(&Thread_process_disconnected_handler, ref(form));
    
	Application::Run(form);
}

// �������, ������� ������ ����������
int CreateChildProcess(LPWSTR chile_pe, int proc_number)
{
    HANDLE Jobject;
    JOBOBJECT_EXTENDED_LIMIT_INFORMATION JBLI;
    PROCESS_INFORMATION pi;
    ZeroMemory(&pi, sizeof(pi));
    STARTUPINFO si;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    try
    {
        Jobject = CreateJobObjectW(NULL, L"Job");
        if (Jobject == NULL)
            throw "COULD NOT CREATE JOB OBJECT!";

        if (!AssignProcessToJobObject(Jobject, OpenProcess(PROCESS_ALL_ACCESS, FALSE, GetCurrentProcessId())))
            return 1;

        if (!QueryInformationJobObject(Jobject, JobObjectExtendedLimitInformation, &JBLI, sizeof(JBLI), NULL))
            return 2;

        JBLI.BasicLimitInformation.LimitFlags = JOB_OBJECT_LIMIT_KILL_ON_JOB_CLOSE;
        if (!SetInformationJobObject(Jobject, JobObjectExtendedLimitInformation, &JBLI, sizeof(JBLI)))
            return 3;

        if (!CreateProcess(NULL, chile_pe, NULL, NULL, FALSE, CREATE_NO_WINDOW, NULL, NULL, &si, &pi))
        {
            cout << "CreateProcess failed with " << GetLastError() << endl;
            return 4;
        }

        //cout << "Child Process ID: " << pi.dwProcessId << "\tThread ID: " << pi.dwThreadId << "\tHandle: " << pi.hProcess << endl;
        if (proc_number == -1)
            procs_info.push_back(pi);
        else
            procs_info[proc_number] = pi;
        return 0;
    }
    catch (char* Message)
    {
        cout << Message << " " << GetLastError() << endl;
        return -1;
    }
}


// ������� ����������� ���������
static inline string ADDZERO(string str, bool ms=false) {return (str.length()==1) ? ms?"00"+str:"0"+str : (str.length() == 2 && ms) ? "0"+str : str;}
void write_log(string log_info, string first_str)
{
    if (settings.is_logging)
    {
        string log_text;
        SYSTEMTIME *sys_time = new SYSTEMTIME;
    
        GetLocalTime(sys_time);

        log_text = first_str + "[" + ADDZERO(to_string(sys_time->wDay)) + "." + ADDZERO(to_string(sys_time->wMonth)) + "." + to_string(sys_time->wYear) + " | "
            + ADDZERO(to_string(sys_time->wHour)) + ":" + ADDZERO(to_string(sys_time->wMinute)) + ":"
            + ADDZERO(to_string(sys_time->wSecond)) + "." + ADDZERO(to_string(sys_time->wMilliseconds), true) + "]  " + log_info + "\n\n";
    
        // ����� ����� ���� ��� �� ����������
        if (system("cd Logs\\PyLauncher") != 0)
            cout << system("mkdir Logs\\PyLauncher") << endl;

        ofstream opened("Logs\\PyLauncher\\"+ADDZERO(to_string(sys_time->wMonth))+"."+to_string(sys_time->wYear)+".txt", ios::app);
        opened << log_text;
        opened.close();
    }
}


// ����� �������������� ���������� ���������
void Thread_process_disconnected_handler(Main_Window ^form)
{
    DWORD exit_code;        // ��� ����������
    unsigned short num = 0; // ����� �������

    while (true)
    {
        num = 0; // ���������� ����� �������
        for (PROCESS_INFORMATION info : procs_info)
        {
            GetExitCodeProcess(info.hProcess, &exit_code); // �������� ������� ������ ��������
            if (exit_code != STILL_ACTIVE && find(del_scripts.begin(), del_scripts.end(), num) == del_scripts.end() && form->InvokeRequired && !thr_process_dis_pass)
            {
                write_log("������ \"" + scripts_name[num] + "\" �������� � ����� " + to_string(exit_code));
                form->Invoke(gcnew System::Action<System::Windows::Forms::Panel^>(form, &Main_Window::off_panel), form->sc_panels[num]); // �������� ������� ����������� ������
                del_scripts.push_back(num); // ��������� ����� ������ � ������ � ��������� ���������
            }
            ++num;
        }

        Sleep(100); // ���� 10 ����, ����� �� ��� �������
    }
    
}


