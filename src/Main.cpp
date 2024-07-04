#include <iostream>
#include <string>
#include <vector>
#include "./Enums/Enums.hpp"
#include "./FileReader/FileReader.hpp"
#include "./MemoryManager/PartitionMemoryManager/PartitionMemoryManager.hpp"
  
using namespace std;

string GetContent(string cmd) {
  size_t start = cmd.find('(') + 1;
  size_t end   = cmd.find(')');

  return cmd.substr(start, end - start);
}

Process* GetCommandIN(string cmd) {
  string content   = GetContent(cmd);
  size_t comma_pos = content.find(',');
  
  Process* p = new Process;

  p->ProcessName = content.substr(0, comma_pos);
  p->MemorySize  = stoi(content.substr(comma_pos + 1));

  return p;
}

int main(){
  int  nMemorySize;
  char cMemManagement, cVarPartitions;
  PartitionMemoryManager* manager;

  // Le arquivo de process
  FileReader* file = new FileReader();
  vector<string> ListProcess = file->GetLines(); 
  
  cout << "Digite o tamanho da memoria:" << endl;
  cin  >> nMemorySize;
  
  cout << "Qual sera o algortimo de gerenciamento de memoria:" << endl;
  cout << "(1) - Particoes variaveis" << endl;
  cout << "(2) - Sistema Buddy" << endl;
  cin  >> cMemManagement;

  if (cMemManagement == '1'){
    cout << "Qual sera a politica de alocacao de memoria:" << endl; 
    cout << "(1) - Circular-Fit" << endl;
    cout << "(2) - Worst-Fit" << endl;
    cin  >> cVarPartitions;

    if (cVarPartitions == '1') {
      manager = new PartitionMemoryManager(nMemorySize, CIRCULAR_FIT);
    }
    else if (cVarPartitions == '2') {
      manager = new PartitionMemoryManager(nMemorySize, WORST_FIT);
    }
    else {
      cout << "Error, numero invalido: " << cVarPartitions << endl;
    }
  }
  else if (cMemManagement == '2'){
    
  }
  else{
    cout << "Error, numero invalido: " << cMemManagement << endl;
  }
  
  if (manager != nullptr) {
    for (string process : ListProcess) {
      std::cout << process << endl;

      if (process.substr(0, 2) == "IN") {
        Process* p = GetCommandIN(process);
       
        if (p != nullptr)
          manager->Alloc(p->ProcessName, p->MemorySize);
      } 
      else if (process.substr(0, 3) == "OUT") {
        string ProcessName = GetContent(process);
        manager->Dealloc(ProcessName);
      }
    }
  }

  return 0;
}
