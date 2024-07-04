#include "./Segment.hpp"

Segment::Segment(std::string pName, int start, int size, bool isFree, Segment* next){
  this->m_IsFree  = isFree;
  this->m_Process = pName;
  this->m_Size    = size;
  this->m_Start   = start;

  this->m_Next    = next;
}

void Segment::Fragment(std::string processName, int size){
  Segment* fragment = new Segment("", this->m_Start + size, this->m_Size - size, true, this->m_Next); 
  
  this->m_Process = processName;
  this->m_IsFree  = false;
  this->m_Next    = fragment;
  this->m_Size    = size;
}

// Faz uma uniao com o segmento atual e o proximo
void Segment::Union() {
  // Utilizado o mesmo Segmento para não alterar o ponteiro e perder a referencia
  this->m_IsFree  = true;
  this->m_Process = "";
  this->m_Size    = this->m_Size + this->m_Next->Size();
  this->m_Start   = this->m_Start;

  this->m_Next    = this->m_Next->Next();
}

void Segment::Free() {
  this->m_IsFree  = true;
  this->m_Process = "";
}

bool Segment::IsFree(){
  return this->m_IsFree;
}

Segment* Segment::Next(){
  return this->m_Next;
}

int Segment::Size(){
  return this->m_Size;
}

std::string Segment::ProcessName(){
  return this->m_Process;
}

