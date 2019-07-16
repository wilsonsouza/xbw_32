//-----------------------------------------------------------------------------------------------//
// xbw32 for Windows (generate of numeric combinations for bingo or lotery)
//
// Created by wilsonsouza 2013, 2018
//
// WR Devinfo
// (c) 2012, 2013, 2014, 2015, 2016, 2017, 2018
//-----------------------------------------------------------------------------------------------//
#pragma once
#include <bb.defs.hpp>
#include <std.widget.hpp>
#include <std.layouts.hpp>

namespace std
{
   class Q_DECL_EXPORT LineEdit;
   class Q_DECL_EXPORT Table;
   class Q_DECL_EXPORT TreeWidget;
   class Q_DECL_EXPORT RadioButton;
   class Q_DECL_EXPORT GroupBox;
   class Q_DECL_EXPORT Button;
};

namespace bb
{
   namespace captions
   {
      struct insert_by
      {
         const std::stringlist Header
         {
            std::unicodestring{"Números"},
            std::unicodestring{"Grupos"},
            std::unicodestring{"Posições"},
            std::unicodestring{"Cartelas"}
         };
         insert_by() = default;
      };
   }
   //
   class mdichildwindow;
   class mdichildwindow_special_combination;
   class spreadsheet_insert_by : public std::widget_impl<std::gridbox>
   {
      //Q_OBJECT
   public:
      spreadsheet_insert_by(bb::mdichildwindow_special_combination * child);
      virtual ~spreadsheet_insert_by() override = default;
      virtual QWidget * create() override;

      //DECLARE_OPERATOR(spreadsheet_insert_by);
      std::table * m_table_numbers{ nullptr };
      std::table * m_table_groups{ nullptr };
      std::table * m_table_position{ nullptr };
      std::table * m_table_pages{ nullptr };
      std::radiobutton * m_insert_in_all_groups{ nullptr };
      std::radiobutton * m_select_groups_and_pages{ nullptr };
      std::radiobutton * m_insert_in_all_groups_by_position{ nullptr };
      std::radiobutton * m_select_group_and_position{ nullptr };
      std::button * m_ok{ nullptr };
      std::button * m_cancel{ nullptr };
   protected:
      bb::mdichildwindow_special_combination * m_child{ nullptr };
   };
}