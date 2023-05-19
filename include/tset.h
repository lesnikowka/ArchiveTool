#pragma once

#include <sstream>
#include "tbitfield.h"

class TSet
{
private:
  int MaxPower;       
  TBitField BitField; 
public:
  TSet(int mp);
  TSet(const TSet &s);       
  TSet(const TBitField &bf); 
  operator TBitField();      
  // доступ к битам
  int GetMaxPower(void) const noexcept;
  void InsElem(const int Elem);       
  void DelElem(const int Elem);       
  int IsMember(const int Elem) const; 
  // теоретико-множественные операции
  int operator== (const TSet &s) const;
  int operator!= (const TSet &s) const;
  TSet& operator=(const TSet &s);  
  TSet operator+ (const int Elem); 
                                   
  TSet operator- (const int Elem); 
                                   
  TSet operator+ (const TSet &s);  
  TSet operator* (const TSet &s);  
  TSet operator~ (void);           

  friend istream &operator>>(istream &istr, TSet &bf);
  friend ostream &operator<<(ostream &ostr, const TSet &bf);
};

