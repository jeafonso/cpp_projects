#include "processor.h"

float Processor::Utilization() { 
  float retorno;
  long totalJif = LinuxParser::Jiffies();
  long activeJif = LinuxParser::ActiveJiffies();
  
  retorno = activeJif / totalJif;
  return retorno; 
}