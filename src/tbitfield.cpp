#include "tbitfield.h"

TBitField::TBitField(int len)
{
    if (len < 0) 
        throw std::length_error("Size cannot be less than 0");

    else {
        BitLen = len;
        MemLen = len & (sizeof(TELEM)*8 - 1) ? len / (sizeof(TELEM) * 8) + 1 : len / (sizeof(TELEM) * 8);

        pMem = new TELEM[MemLen];

        for (int i = 0; i < MemLen; i++)
            pMem[i] = 0;
    }
}

TBitField::TBitField(const TBitField &bf) 
{
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;

    pMem = new TELEM[MemLen];

    memcpy(pMem, bf.pMem, MemLen * sizeof(TELEM));
}

TBitField::TBitField(TBitField&& bf)
{
    BitLen = MemLen = 0;
    pMem = nullptr;

    std::swap(BitLen, bf.BitLen);
    std::swap(MemLen, bf.MemLen);
    std::swap(pMem, bf.pMem);
}

TBitField::~TBitField()
{
    delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const noexcept 
{
    return n / (sizeof(TELEM) * 8);
}

TELEM TBitField::GetMemMask(const int n) const noexcept 
{
    return ((TELEM)1) << (n & (sizeof(TELEM) * 8 - 1));
}



int TBitField::GetLength(void) const noexcept 
{
  return BitLen;
}

void TBitField::SetBit(const int n) 
{
    if (n < 0 || n >= BitLen) 
        throw std::out_of_range("index out of the bounds");
    
    else 
        pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] | GetMemMask(n);
}

void TBitField::ClrBit(const int n) 
{
    if (n < 0 || n >= BitLen) 
        throw std::out_of_range("index out of the bounds");
    
    else 
        pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] & (~GetMemMask(n));
}

int TBitField::GetBit(const int n) const 
{
    if (n < 0 || n >= BitLen) {
        throw std::exception("index out of the bounds");

        return 0;
    }

    if ((~GetMemMask(n)) == ((~GetMemMask(n)) | pMem[GetMemIndex(n)]))
        return 0;
    else
        return 1;

}



TBitField& TBitField::operator=(const TBitField& bf) 
{
    if (this == &bf) return *this;

    if (MemLen != bf.MemLen){
        delete[] pMem;
        pMem = new TELEM[bf.MemLen];
        MemLen = bf.MemLen;
    }

    BitLen = bf.BitLen;

    memcpy(pMem, bf.pMem, MemLen * sizeof(TELEM));

    return *this;
}

TBitField& TBitField::operator=(TBitField&& bf)
{
    std::swap(BitLen, bf.BitLen);
    std::swap(MemLen, bf.MemLen);
    std::swap(pMem, bf.pMem);

    return *this;
}

int TBitField::operator==(const TBitField &bf) const 
{
    if (BitLen == bf.BitLen) {
        for (int i = 0; i < MemLen; i++)
            if (pMem[i] != bf.pMem[i]) return 0;

        return 1;
    }

    return 0;
}

int TBitField::operator!=(const TBitField &bf) const 
{
    return !operator==(bf);
}

TBitField TBitField::operator|(const TBitField &bf) 
{
    TBitField result(0);

    if (BitLen > bf.BitLen) result = *this;
    else result = bf;

    for (int i = 0; i < std::min(MemLen, bf.MemLen); i++) 
        result.pMem[i] = pMem[i] | bf.pMem[i];
    
    return result;
}

TBitField TBitField::operator&(const TBitField &bf) 
{
    TBitField result(std::max(BitLen, bf.BitLen));

    for (int i = 0; i < std::min(MemLen, bf.MemLen); i++) 
        result.pMem[i] = pMem[i] & bf.pMem[i];

    return result;
}

TBitField TBitField::operator~(void) 
{
    TBitField result(BitLen);

    for (int i = 0; i < MemLen - 1; i++) 
        result.pMem[i] = (~pMem[i]);

    for (int i = (MemLen - 1) * sizeof(TELEM) * 8; i < BitLen; i++) 
        if (!GetBit(i))
            result.SetBit(i);
    
    return result;
}



istream &operator>>(istream &istr, TBitField &bf) 
{
    int bit;

    for (int i = 0; i < bf.BitLen; i++) {
        istr >> bit;
        bf.SetBit(bit);
    }

    return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) 
{
    for (int i = 0; i < bf.BitLen; i++) 
        ostr << bf.GetBit(i);

    return ostr;
}