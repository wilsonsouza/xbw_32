//-----------------------------------------------------------------------------------------------//
// xbw32 for Windows (generate of numeric combinations for bingo or lotery)
//
// Created by wilsonsouza 2013, 2018
//
// WR Devinfo
// (c) 2013
//-----------------------------------------------------------------------------------------------//
#pragma once
#include <bb.defs.hpp>
//-----------------------------------------------------------------------------------------------//
namespace bb
{
   class integral_validator : public QIntValidator
   {
   public:
      explicit integral_validator(int start, int end, QObject * owner) :QIntValidator(start, end, owner)
      {
         setRange(start, end);
      }
      virtual QValidator::State validate(QString & value, int & pos)
      {
         if (value.toInt() < bottom() || value.toInt() > top())
         {
            QMessageBox::warning(nullptr,
                                 std::captions::errors{}.WARNING,
                                 std::unicodestring{ "Número fora do intervalo!" });
            return Invalid;
         }
         return Acceptable;
      }
   };
}