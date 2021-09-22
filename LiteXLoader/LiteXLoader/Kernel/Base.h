#include <string>

class Level;
class Dimension;
bool Raw_Runcmd(const std::string &cmd);
std::pair<bool, std::string> Raw_RuncmdEx(const std::string &cmd);
bool Raw_RegisterCmd(const std::string &cmd, const std::string &describe, int cmdLevel);
bool Raw_SendCmdOutput(const std::string& output);
std::string Raw_GetBDSVersion();
Dimension* Raw_GetDimByLevel(Level* lv, int id);