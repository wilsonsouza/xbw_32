//-----------------------------------------------------------------------------------------------//
// xbw32 for Windows (generate of numeric combinations for bingo or lotery)
//
// Created by wilsonsouza 2013, 2018
//
// WR Devinfo
// (c) 2012, 2013, 2014, 2015, 2016, 2017, 2018
//-----------------------------------------------------------------------------------------------//
#pragma once
#include <std.lineedit.hpp>
#include <std.tablewidgetitem.hpp>
#include <std.widget.hpp>

namespace bb
{
   class table_widgetitem_lineedit : public std::lineedit
   {
      //Q_OBJECT
   public:
      explicit table_widgetitem_lineedit(int const & length, //table_widgetitem_lineedit
                                         int const & fixed_width) :
         std::lineedit{ nullptr, std::unicodestring{}, length, fixed_width }
      {
      }
      explicit table_widgetitem_lineedit(int const & length,
                                         int const & fixed_width,
                                         int const & min,
                                         int const & max) :
         std::lineedit{ nullptr, std::unicodestring{}, length, fixed_width }
      {
         this->set_validator(new QIntValidator{ min, max, this });
      }

      //DECLARE_OPERATOR(table_widgetitem_lineedit);
   protected:
      int m_minimum_value{ 0 };
      int m_maximum_value{ 0 };
      QIntValidator * m_validator{ nullptr };
   };
}
