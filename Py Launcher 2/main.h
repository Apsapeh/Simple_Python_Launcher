#pragma once
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <atlconv.h>
#include <msclr/marshal_cppstd.h>
#include <thread>

#include "Main_Window.h"
#include "json.hpp"


using namespace std;
using namespace PyLauncher2;
using Json = nlohmann::json;

struct json_settings
{
	bool is_logging;
};


int CreateChildProcess(LPWSTR chile_pe, int proc_number=-1);
void write_log(string log_info, string first_str="");
void Thread_process_disconnected_handler(Main_Window^ form);

