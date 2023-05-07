#include "tset.h"

TSet::TSet(int mp) : BitField(mp), MaxPower(mp)
{
}


TSet::TSet(const TSet &s) : BitField(s.BitField), MaxPower(s.MaxPower)
{
}


TSet::TSet(const TBitField &bf) : BitField(bf), MaxPower(bf.GetLength())
{
}

TSet::operator TBitField()
{
    return BitField;
}

int TSet::GetMaxPower(void) const noexcept
{
    return MaxPower;
}

int TSet::IsMember(const int Elem) const 
{
    if (Elem < 0 || Elem >= MaxPower) {
        throw std::out_of_range("Element not in universe");
        return 0;
    }

    if (BitField.GetBit(Elem)) return 1;

    return 0;
}

void TSet::InsElem(const int Elem) 
{
    if (Elem < 0 || Elem >= MaxPower) 
        throw std::out_of_range("Element not in universe");

    BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) 
{
    if (Elem < 0 || Elem >= MaxPower) 
        throw std::out_of_range("Element not in universe");

    BitField.ClrBit(Elem);
}



TSet& TSet::operator=(const TSet &s) 
{
    BitField = s.BitField;
    MaxPower = s.MaxPower;

    return *this;
}

int TSet::operator==(const TSet &s) const 
{
    if ((MaxPower == s.MaxPower) && (BitField == s.BitField)) return 1;
    return 0;
}

int TSet::operator!=(const TSet &s) const 
{
    return !operator==(s);
}

TSet TSet::operator+(const TSet &s) 
{
    TSet result(std::max(MaxPower, s.MaxPower));
    result = BitField | s.BitField;

    return result;
}

TSet TSet::operator+(const int Elem) 
{
    if (Elem < 0 || Elem >= MaxPower) {
        throw std::out_of_range("Element not in universe");
        return TSet(0);
    }

    TSet result(*this);
    result.InsElem(Elem);

    return result;
}

TSet TSet::operator-(const int Elem) 
{
    if (Elem < 0 || Elem >= MaxPower) {
        throw std::out_of_range("Element not in universe");
        return TSet(0);
    }

    TSet result(*this);
    result.DelElem(Elem);

    return result;
}

TSet TSet::operator*(const TSet &s) 
{
    TSet result(std::max(MaxPower, s.MaxPower));
    result = BitField & s.BitField;

    return result;
}

TSet TSet::operator~(void) 
{
    TSet result(MaxPower);
    result.BitField = (~BitField);

    return result;
}



istream &operator>>(istream &istr, TSet &s) 
{
    int elem;
    std::string str;
    getline(istr, str);

    std::istringstream iss(str);

    while (iss >> elem)
        s.InsElem(elem);
    
    return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) 
{
    bool isFirstElement = true;

    ostr << "{";

    for (int i = 0; i < s.MaxPower; i++) {
        if (s.BitField.GetBit(i)) {
            if (!isFirstElement) 
                ostr << ", ";

            isFirstElement = false;

            ostr << i;
        }
    }

    ostr << "}";

    return ostr;
}