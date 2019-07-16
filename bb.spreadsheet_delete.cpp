//-----------------------------------------------------------------------------------------------//
// xbw32 for Windows (generate of numeric combinations for bingo or lotery)
//
// Created by wilsonsouza 2013, 2018
//
// WR Devinfo
// (c) 2012, 2013, 2014, 2015, 2016, 2017, 2018
//-----------------------------------------------------------------------------------------------//
#include <bb.spreadsheet_delete.hpp>
#include <bb.mdichildwindow_special_combination.hpp>

namespace bb
{
   //-----------------------------------------------------------------------------------------------//
   spreadsheet_delete::spreadsheet_delete(bb::mdichildwindow_special_combination * child) :
      std::widget{ this, "IDD_SPREADSHEET_DELETE" },
      m_child{ child }
   {
   }
   //-----------------------------------------------------------------------------------------------//
   QWidget *  spreadsheet_delete::create()
   {
      return this;
   }
   //-----------------------------------------------------------------------------------------------//
}