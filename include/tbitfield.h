#pragma once

#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

typedef unsigned char TELEM;

class TBitField													
{																
private:										
  size_t  BitLen;
  TELEM *pMem; 
  size_t MemLen;
												
  					
  int   GetMemIndex(const size_t n) const noexcept;
  TELEM GetMemMask (const size_t n) const noexcept;
public:											
  TBitField(size_t len);
  TBitField(const TBitField &bf);          
  TBitField(TBitField &&bf);          
  TBitField(const TELEM* mem, size_t MemLen, size_t BitLen);
  ~TBitField();
												
  				
  size_t GetLength(void) const noexcept;
  size_t GetCapacity(void) const noexcept;
  void SetBit(const size_t n);
  void ClrBit(const size_t n);
  int  GetBit(const size_t n) const;
								
  					
  int operator==(const TBitField &bf) const;
  int operator!=(const TBitField &bf) const;
  TBitField& operator=(const TBitField &bf);
  TBitField& operator=(TBitField &&bf);
  TBitField  operator|(const TBitField &bf);
  TBitField  operator&(const TBitField &bf);
  TBitField  operator~(void);

  const TELEM& operator[](size_t i) const;

  friend istream &operator>>(istream &istr, TBitField &bf);       
  friend ostream &operator<<(ostream &ostr, const TBitField &bf); 
};
