#include "./PartitionMemoryManager.hpp"
#include <iostream>

PartitionMemoryManager::PartitionMemoryManager(int size, Policy policy) {
  this->m_Policy = policy;
  this->m_nSize  = size;

  this->m_MemorySpace = new Segment("", 0, size, true, nullptr);
  this->m_LastAlloc   = nullptr;
}

bool PartitionMemoryManager::Alloc(std::string label, int size){
  this->PrintResults();

  if (this->m_Policy == WORST_FIT){
    return this->AllocWorstFit(label, size);
  }
  else if (this->m_Policy == CIRCULAR_FIT){
    return this->AllocCircularFit(label, size);
  }
  else
    return false;
}

bool PartitionMemoryManager::AllocWorstFit(std::string label, int size){
  Segment* biggest = GetBiggestFreeSegment();

  if (biggest != nullptr) {
    if (biggest->Size() > size) {
      biggest->Fragment(label, size);
      
      this->PrintResults();
      return true;
    }
    else {
      std::cout << "Espaco insuficiente para alocar esse processo" << std::endl;
      return false;
    }
  } 
  else {
    std::cout << "Error: Segmento invalido" << std::endl;
    return false;
  }
}

bool PartitionMemoryManager::AllocCircularFit(std::string label, int size){
  Segment* seg = GetNextFreeSegment(size);

  if (seg != nullptr) {
    // Já sabemos que ele é grande o bastante
    seg->Fragment(label, size);

    this->PrintResults();
    this->m_LastAlloc = seg;

    return true;
  }
  std::cout << "Espaco insuficiente para alocar esse processo" << std::endl;
  return true;
}

Segment* PartitionMemoryManager::GetBiggestFreeSegment(){
  Segment* seg     = this->m_MemorySpace;
  Segment* biggest = nullptr; 

  while (seg != nullptr) {
    if ((biggest == nullptr) and (seg->IsFree())) {
      biggest = seg;
    }
    else {
      if ((seg->IsFree()) and (biggest->Size() < seg->Size())) 
        biggest = seg;
    }

    seg = seg->Next();
  }

  return biggest;
}

Segment*  PartitionMemoryManager::GetNextFreeSegment(int size) {
  if (this->m_LastAlloc == nullptr) {
    return this->m_MemorySpace;
  }
  else {
    Segment* seg = this->m_LastAlloc->Next();

    // Roda até chegar no LastAlloc, ou seja deu a volta
    while (seg != this->m_LastAlloc) {
      // Chegou ao fim da linha, volta para o inicio
      if (seg == nullptr) {
        seg = this->m_MemorySpace;

        // Resolve o bug de LastAlloc for na primeira pos
        // entrava em um loop quando tinha apenas dois process na tabela
        // Pois ele nunca Verificava se this->m_MemorySpace == this->m_LastAlloc
        if (seg == this->m_LastAlloc)
          break;
      }

      if (seg->IsFree() and seg->Size() >= size)
        return seg;

      seg = seg->Next();
    }
    
    // Não encotramos, retorna vazio
    return nullptr;
  }
}

bool PartitionMemoryManager::Dealloc(std::string label) {
  this->PrintResults();

  Segment* seg = this->m_MemorySpace;
  bool bFound  = false;

  while (seg != nullptr) {
    if (!seg->IsFree() and seg->ProcessName() == label) {
      // Processo encontrado e não esta livre vamos liberar
      if (seg->Next() != nullptr) {
        if (!seg->Next()->IsFree()) {
          // Se o proximo segmento não for vazio, apenas precisa liberar o atual
          std::cout << "Liberando" << std::endl;
          seg->Free();
        } 
        else {
          // Se o proximo segmento for vazio, precisamos criar um segmento que junte os dois
          seg->Union();
          std::cout << "Unindo" << std::endl;
        }
      }
      bFound = true;
      break;
    }
    seg = seg->Next();
  }

  // Pode acontecer da espaço de memoria anterior esteja livre, e quando eu comecei a fazer
  // não me toquei que precisavamos da referencia do nodo anterior, e agora o desenvolvimento esta muito avancado para 
  // voltar atras, para contornar sera feito outro while verificando se tem espacos de memorias livres em sequencia
  // Essa implementacao nao eh a mais otimizada, por percorrer a lista duas vezes
  //
  // Faz isso apenas se teve alteracoes no while de cima
  if (bFound) {
    Segment* seg = this->m_MemorySpace;
    while (seg != nullptr) {
      // Verifica se o segmento e o proximo são validos e vazios
      if (seg->IsFree() and seg->Next() != nullptr and seg->Next()->IsFree()) {
        seg->Union();
      } 

      seg = seg->Next();
    }
    return true;
  }
  else {
    std::cout << "O Segmento informado nao foi encontrado!" << std::endl;
    return false;
  }
}

void PartitionMemoryManager::PrintResults(){
  Segment* seg = this->m_MemorySpace;
  while (seg != nullptr) {
    std::cout << "|" << seg->Size(); 

    if (seg->IsFree())
      std::cout << "*";

    seg = seg->Next();
  }
  std::cout << "|" << std::endl;
}
