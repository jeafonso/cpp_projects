#include <dirent.h>
#include <unistd.h>
#include <sstream>
#include <string>
#include <vector>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, kernel, version;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

float LinuxParser::MemoryUtilization() { 
  float freeMem, totalMem, retorno, value;
  std::string key, linha;
  
  std::ifstream stream(kProcDirectory + kMeminfoFilename);
  if(stream.is_open()){
  	
    while(std::getline(stream, linha)){
      	std::istringstream line(linha);
      	while(line >> key >> value){
        	if(key == "MemFree"){
              freeMem = value * 0.001;
            }
          
          	if(key == "MemTotal"){
              totalMem = value * 0.001;
            }
        }
    }
  }
  
  retorno = (totalMem - freeMem) / totalMem; 
  return retorno; 
}

long LinuxParser::UpTime() { 
  std::string linha;
  long retorno = 0;
  long tempo;
  
  std::ifstream stream(kProcDirectory + kUptimeFilename);
  if(stream.is_open()){
    while(std::getline(stream, linha)){
    	std::istringstream line(linha);
      while(line >> tempo){
        retorno = tempo;
        return retorno;
      }
    }
  }
  return retorno; 
}

long LinuxParser::Jiffies() { 
  long idleJiffies = LinuxParser::IdleJiffies();
  long activeJiffies = LinuxParser::ActiveJiffies();
  return idleJiffies + activeJiffies; 
}

long LinuxParser::ActiveJiffies(int pid) { 
  std::string linha, path, value;
  path = kProcDirectory + "/" + std::to_string(pid) + kStatFilename;
  
  long retorno, utime, stime, cutime, cstime;
  int counter = 1;
  
  std::ifstream stream(path);
  if(stream.is_open()){
  	while(std::getline(stream, linha)){
    	std::istringstream line(linha); 
      	while(counter != 14){
        	line >> value;
          	counter++;
        }
      
      line >> utime >> stime >> cutime >> cstime;
      break;
  	}
  }
  retorno = (utime + stime + cutime + cstime) / sysconf(_SC_CLK_TCK);
    
  return retorno; 
}

long LinuxParser::ActiveJiffies() { 
  std::string linha, path, value, key;
  path = kProcDirectory + kStatFilename;
  
  long retorno;
  long user, nice, system, idle, iowait, irq, softirq, steal, active;
  std::ifstream stream(path);
  if(stream.is_open()){
  	while(std::getline(stream, linha)){
    	std::istringstream line(linha);
    	while(line >> key >> user >> nice >> system >> idle >> iowait >>
             irq >> softirq >> steal){
        	if (key == "cpu") {
          		active = user + nice + system + irq + softirq + steal;
        	}
        }
    }
  }
  retorno = active / sysconf(_SC_CLK_TCK);
  return retorno; 
}

long LinuxParser::IdleJiffies() { 
  std::string linha, path, value, key;
  path = kProcDirectory + kStatFilename;
  
  long retorno;
  long user, nice, system, idle, iowait, irq, softirq, steal, idleTime;
  
  std::ifstream stream(path);
  if(stream.is_open()){
  	while(std::getline(stream, linha)){
    	std::istringstream line(linha);
    	while(line >> key >> user >> nice >> system >> idle >> iowait >>
             irq >> softirq >> steal){
        	if (key == "cpu") {
          		idleTime = idle + iowait;
        	}
        }
    }
  }
  retorno = idleTime / sysconf(_SC_CLK_TCK);
  return retorno;  
}

vector<string> LinuxParser::CpuUtilization() { 
  std::vector<std::string> retorno;
  std::string linha, key, value;
  std::ifstream stream(kProcDirectory + kStatFilename);
  
  if(stream.is_open()){
    while(std::getline(stream, linha)){
    	std::istringstream line(linha);  
      	while(line >> key){
        	if(key == "cpu"){
              	line >> value;
            	retorno.push_back(value);
              return retorno;
            }
        }
    }
  }
  return retorno; 
}

int LinuxParser::TotalProcesses() { 
  int retorno = 0;
  int value;
  std::ifstream stream(kProcDirectory + kStatFilename);
  std::string linha, key;
  
  if(stream.is_open()){
  	while(std::getline(stream, linha)){
    	std::istringstream line(linha);
      	while(line >> key >> value){
        	if(key == "processes"){
                retorno = value;
              	return retorno;
            }
        }
    }
  }
  
  return retorno; 
}

int LinuxParser::RunningProcesses() { 
	int retorno = 0;
  	int value;
  	std::ifstream stream(kProcDirectory + kStatFilename);
  	std::string linha; 
  	std::string key;
  
    if(stream.is_open()){
      while(std::getline(stream, linha)){
          std::istringstream line(linha);
          while(line >> key >> value){
              if(key == "procs_running"){
                    retorno = value;
                  	return retorno;
              }
          }
      }
    }
  
  return retorno;  
}

string LinuxParser::Command(int pid) { 
	std::string retorno, path, linha, value;  
  	path = kProcDirectory + "/" + std::to_string(pid) + kCmdlineFilename;
  
  	std::ifstream stream(path);
  	if(stream.is_open()){
    	while(std::getline(stream, linha)){
        	std::istringstream line(linha);
          	while(line >> value){
                retorno = value;
              	return retorno;
            }
        }
    }
  return retorno; 
}

string LinuxParser::Ram(int pid) {  
  	std::string retorno, path, linha, key;  
  	path = kProcDirectory + std::to_string(pid) + kStatusFilename;
  	int ramAux;
  	float value;
  
  	std::ifstream stream(path);
  	if(stream.is_open()){
    	while(std::getline(stream, linha)){
        	std::istringstream line(linha);
          	while(line >> key >> value){
            	if(key == "VmSize:"){
                  	ramAux = value * 0.001;
                	retorno = to_string(ramAux);
                  	return retorno;
                }
            }
        }
    }
  
  return retorno; 
}

string LinuxParser::Uid(int pid) { 
  	std::string retorno, path, linha, key, value;  
  	path = kProcDirectory + std::to_string(pid) + kStatusFilename;
  	
  	std::ifstream stream(path);
  	if(stream.is_open()){
    	while(std::getline(stream, linha)){
     		std::istringstream line(linha);
          	while(line >> key >> value){
            	if(key == "Uid:"){
                	retorno = value;
                  return retorno;
                }
            }
        }
    }
  return retorno; 
}

string LinuxParser::User(int pid) { 
  std::string retorno, path, linha, key, value, lixo, uId; 
  path = kPasswordPath;
  
  std::ifstream stream(path);
  if(stream.is_open()){
    while(std::getline(stream, linha)){
      	std::replace(linha.begin(), linha.end(), ':', ' ');
     	std::istringstream line(linha);
      	
      	while(line >> value >> lixo >> key){
        	if(key == Uid(pid)){
            	retorno = value;
              return retorno;
            }
        }
    }
  }
  return retorno; 
}

long LinuxParser::UpTime(int pid) { 
	long retorno = 0;
  	std::string path, linha, value;
  	int counter = 1;
  	long upTime;
  	
  	path = kProcDirectory + "/" + std::to_string(pid) + kStatFilename;
  	std::ifstream stream(path);
  	if(stream.is_open()){
    	while(std::getline(stream, linha)){
        	std::istringstream line(linha);
          	while(line >> value){
            	if(counter == 21){
                    break;
                }
              	counter++;
            }
          line >> upTime;
        }
    }
  retorno = upTime / sysconf(_SC_CLK_TCK);
  return retorno; 
}