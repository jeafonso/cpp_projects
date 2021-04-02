#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>

#include "process.h"
#include "processor.h"
#include "system.h"
#include "linux_parser.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;

Processor& System::Cpu() { return cpu_; }

vector<Process>& System::Processes() { 
  std::vector<int> pids = LinuxParser::Pids();
  processes_.clear();
  
  for(auto pid: pids){
  	Process aux(pid);
    processes_.push_back(aux);
  }
  std::sort(processes_.begin(), processes_.end());
  return processes_; 
}

std::string System::Kernel() { 
  std::string retorno = LinuxParser::Kernel();
  return retorno; 
}

float System::MemoryUtilization() { 
  float retorno = LinuxParser::MemoryUtilization();
  return retorno; 
}

std::string System::OperatingSystem() { 
  std::string retorno = LinuxParser::OperatingSystem();
  return retorno; 
}

int System::RunningProcesses() { 
  int retorno = LinuxParser::RunningProcesses();
  return retorno; 
}

int System::TotalProcesses() { 
  int retorno = LinuxParser::TotalProcesses();
  return retorno; 
}

long int System::UpTime() { 
  long int retorno = LinuxParser::UpTime();
  return retorno; 
}