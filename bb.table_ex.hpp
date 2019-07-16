//-----------------------------------------------------------------------------------------------//
// xbw32 for Windows (generate of numeric combinations for bingo or lotery)
//
// Created by wilsonsouza 2013, 2018
//
// WR Devinfo
// (c) 2012, 2013, 2014, 2015, 2016, 2017, 2018, 2015
//-----------------------------------------------------------------------------------------------//
#pragma once
#include <bb.defs.hpp>
#include <std.table.hpp>
//
namespace bb
{
   class mdichildwindow_special_combination;
   class table_ex: public std::table
   {
      //Q_OBJECT
   public:
      table_ex(mdichildwindow_special_combination * child);
      virtual ~table_ex(){}
      //
      //DECLARE_OPERATOR(table_ex);
   };
}
