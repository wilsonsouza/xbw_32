//-----------------------------------------------------------------------------------------------//
// xbw32 for Windows (generate of numeric combinations for bingo or lotery)
//
// Created by wilsonsouza 2013, 2018
//
// WR Devinfo
// (c) 2012, 2013, 2014, 2015, 2016, 2017, 2018
//-----------------------------------------------------------------------------------------------//
#pragma once
#include <std.widget.hpp>
#include <std.layouts.hpp>

namespace bb
{
   class mdichildwindow;
   class mdichildwindow_special_combination;
   class spreadsheet_delete : public std::widget
   {
      //Q_OBJECT
   public:
      explicit spreadsheet_delete(bb::mdichildwindow_special_combination * child);
      virtual ~spreadsheet_delete() override = default;
      virtual QWidget * create() override;
      //DECLARE_OPERATOR(spreadsheet_delete);
   protected:
      mdichildwindow_special_combination * m_child{ nullptr };
   };
}
