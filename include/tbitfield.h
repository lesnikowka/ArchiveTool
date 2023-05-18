#pragma once

#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

typedef unsigned char TELEM;

class TBitField													
{																
private:										
  int  BitLen; 
  TELEM *pMem; 
  int  MemLen; 
												
  					
  int   GetMemIndex(const int n) const noexcept;
  TELEM GetMemMask (const int n) const noexcept;
public:											
  TBitField(int len);                      
  TBitField(const TBitField &bf);          
  TBitField(TBitField &&bf);          
  ~TBitField();
												
  				
  int GetLength(void) const noexcept;  
  void SetBit(const int n);       
  void ClrBit(const int n);       
  int  GetBit(const int n) const; 
								
  					
  int operator==(const TBitField &bf) const;
  int operator!=(const TBitField &bf) const;
  TBitField& operator=(const TBitField &bf);
  TBitField& operator=(TBitField &&bf);
  TBitField  operator|(const TBitField &bf);
  TBitField  operator&(const TBitField &bf);
  TBitField  operator~(void);

  TELEM& operator[](size_t i) {
	  return pMem[i];
  }
													
  friend istream &operator>>(istream &istr, TBitField &bf);       
  friend ostream &operator<<(ostream &ostr, const TBitField &bf); 
};
