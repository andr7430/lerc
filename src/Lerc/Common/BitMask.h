/*
Copyright 2015 Esri

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

A local copy of the license and additional notices are located with the
source distribution at:

http://github.com/Esri/lerc/

Contributors:  Thomas Maurer
*/

#pragma once

#include <vector>

#define LERCDLL_API __declspec(dllexport)

typedef unsigned char Byte;

/** BitMask - Convenient and fast access to binary mask bits
*
*/

namespace LercNS
{
  class LERCDLL_API BitMask
  {
  public:
    BitMask();
    BitMask(int nCols, int nRows);
    BitMask(const BitMask& src);
    virtual ~BitMask()                        { Clear(); }

    BitMask& operator= (const BitMask& src);

    // 1: valid, 0: not valid
    Byte IsValid(int k) const                 { return (m_pBits[k >> 3] & Bit(k)) > 0; }
    Byte IsValid(int row, int col) const      { return IsValid(row * m_nCols + col); }

    void SetValid(int k) const                { m_pBits[k >> 3] |= Bit(k); }
    void SetValid(int row, int col) const     { SetValid(row * m_nCols + col); }

    void SetInvalid(int k) const              { m_pBits[k >> 3] &= ~Bit(k); }
    void SetInvalid(int row, int col) const   { SetInvalid(row * m_nCols + col); }

    void SetAllValid() const                  { memset(m_pBits, 255, Size()); }
    void SetAllInvalid() const                { memset(m_pBits, 0, Size()); }

    bool SetSize(int nCols, int nRows);

    int GetWidth() const                      { return m_nCols; }
    int GetHeight() const                     { return m_nRows; }
    int Size() const                          { return (m_nCols * m_nRows + 7) >> 3; }
    const Byte* Bits() const                  { return m_pBits; }
    Byte* Bits()                              { return m_pBits; }
    Byte Bit(int k) const                     { return (1 << 7) >> (k & 7); }

    int CountValidBits() const;
    void Clear();

  private:
    Byte*  m_pBits;
    int    m_nCols,
           m_nRows;
  };
}
