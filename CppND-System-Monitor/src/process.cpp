#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"
#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;

int Process::Pid() { return pid_; }

float Process::CpuUtilization() { 
  float retorno;
  long time = LinuxParser::ActiveJiffies(Pid());
  long lpTime = LinuxParser::UpTime();
  long prcTime = Process::UpTime();
  
  long seconds = lpTime - prcTime;
  retorno = (float)time / seconds;
  return retorno; 
}

string Process::Command() { 
  return LinuxParser::Command(Pid()); 
}

string Process::Ram() { 
  return LinuxParser::Ram(Pid()); 
}

string Process::User() { 
  return LinuxParser::User(Pid()); 
}

long int Process::UpTime() { 
  return LinuxParser::UpTime(Pid()); 
}

bool Process::operator<(Process const& a) const { 
  if(this->cpuUtilization_ > a.cpuUtilization_ ){
  	return true;
  }
  return false; 
}