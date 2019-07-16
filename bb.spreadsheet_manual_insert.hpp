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
#include <std.lineedit.hpp>
#include <std.table.hpp>
#include <std.button.hpp>
//
namespace bb
{
   class mdichildwindow_special_combination;
   class spreadsheet_manual_insert : public std::widget_impl<std::gridbox>
   {
      //Q_OBJECT
   public:
      spreadsheet_manual_insert(bb::mdichildwindow_special_combination * child);
      virtual ~spreadsheet_manual_insert() override = default;
      virtual QWidget * create() override;

      //DECLARE_OPERATOR(spreadsheet_manual_insert);
      std::lineedit * m_number_id{ nullptr };
      std::table * m_table_groups{ nullptr };
      std::table * m_table_pages{ nullptr };
      std::button * m_ok{ nullptr };
      std::button * m_cancel{ nullptr };
      std::button * m_apply{ nullptr };
      /**/
   protected:
      bb::mdichildwindow_special_combination * m_child{ nullptr };
   };
}