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
#include <std.radiobutton.hpp>
#include <std.table.hpp>
#include <std.button.hpp>
//
namespace bb
{
   class mdichildwindow_special_combination;
   class spreadsheet_insert : public std::widget_impl<std::gridbox>
   {
   public:
      enum class MODE : uint
      {
         TBL_CREATE_HEADER_TO_GROUPS,
         TBL_CREATE_HEADER_TO_PAGES,
         TBL_ALL_GROUPS,
         TBL_SELECT_PAGES
      };
      //Q_OBJECT
   public:
      spreadsheet_insert(bb::mdichildwindow_special_combination * child);
      virtual ~spreadsheet_insert() override = default;
      virtual QWidget * create() override;
      virtual void fill_table_pages(MODE const & mode);
      virtual void create_header_table_pages(MODE const & mode);

      //DECLARE_OPERATOR(spreadsheet_insert);
      std::lineedit * m_number_id{ nullptr };
      std::radiobutton * m_insertin_all_pages_of_all_groups{ nullptr };
      std::radiobutton * m_selectin_that_pages_wish_inserted{ nullptr };
      std::table * m_table_pages{ nullptr };
      int m_enable_selected{ 0 };
      std::button * m_ok{ nullptr };
      std::button * m_cancel{ nullptr };
      /**/
   protected:
      bb::mdichildwindow_special_combination * m_child{ nullptr };
   };
}
