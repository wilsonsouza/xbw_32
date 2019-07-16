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
#include <std.table.hpp>
#include <std.radiobutton.hpp>
#include <std.button.hpp>
//
namespace bb
{
   class mdichildwindow;
   class mdichildwindow_special_combination;
   class spreadsheet_advanced : public std::widget_impl<std::gridbox>
   {
      //Q_OBJECT
   public:
      spreadsheet_advanced(bb::mdichildwindow_special_combination * child);
      virtual ~spreadsheet_advanced() override = default;
      virtual QWidget * create() override;

      //DECLARE_OPERATOR(spreadsheet_advanced);
      std::table * m_table_actived_group{ nullptr };
      std::unicodestring m_old_actived_group{ };
      QTableWidgetItem * m_table_item{ nullptr };
      std::button * m_ok{ nullptr };
      std::button * m_cancel{ nullptr };
      bb::mdichildwindow_special_combination * m_child{ nullptr };
      //
   protected:
      std::radiobutton *  create_object_list(controller::groups * groups, int & row);
   };
}