//-----------------------------------------------------------------------------------------------//
// xbw32 for Windows (generate of numeric combinations for bingo or lotery)
//
// Created by wilsonsouza 2013, 2018
//
// WR Devinfo
// (c) 2012, 2013, 2014, 2015, 2016, 2017, 2018
//-----------------------------------------------------------------------------------------------//
#pragma once
#include <std.widget_impl.hpp>
#include <std.layouts.hpp>
#include <std.lineedit.hpp>
#include <std.table.hpp>
#include <std.groupbox.hpp>
#include <std.checkbox.hpp>
#include <std.button.hpp>

namespace bb
{
   class mdichildwindow;
   class mdichildwindow_special_combination;
   struct lookup_list;
   class spreadsheet_edit_finder: public std::widget_impl<std::gridbox>
   {
      //Q_OBJECT
   public:
      spreadsheet_edit_finder(bb::mdichildwindow_special_combination * child);
      virtual ~ spreadsheet_edit_finder();
      virtual QWidget * create() override;
      virtual void  OnFinderNumbers();
      virtual void  fill_table(std::shared_ptr<lookup_list> & lookup_list);
      //create
      QWidget * create_search_group();
      QWidget * create_data_group();
      QWidget * create_buttons();
      /*property*/
      std::lineedit * m_what_finder{ nullptr };
      std::table * m_table_list{ nullptr };
      std::checkbox * m_is_partial_finder{ nullptr };
      std::groupbox * m_display_total_records{ nullptr };
      std::button * m_ok{ nullptr };
      std::button * m_cancel{ nullptr };
      /**/
      //DECLARE_OPERATOR(spreadsheet_edit_finder);
      mdichildwindow_special_combination * m_child{ nullptr };

   protected:
      void on_table_list();
   };
}
