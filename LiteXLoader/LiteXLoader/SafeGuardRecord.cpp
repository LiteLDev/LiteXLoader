#include <fstream>
#include <filesystem>
#include <Configs.h>
using namespace std;

ofstream record;

void InitSafeGuardRecord()
{
	filesystem::create_directories("logs/LiteXLoader");
	record.open(string("logs/LiteXLoader/Sensitive_Operation_Records-") + LXL_SCRIPT_LANG_TYPE + ".log", ios::app);
}

void RecordOperation(const string& pluginName, const std::string &operation, const string& content)
{
	if (record.is_open())
		record << "[" << operation << "]<" << pluginName << "> " << content << endl;
}