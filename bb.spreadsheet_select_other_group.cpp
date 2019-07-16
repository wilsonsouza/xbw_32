//-----------------------------------------------------------------------------------------------//
// xbw32 for Windows (generate of numeric combinations for bingo or lotery)
//
// Created by wilsonsouza 2013, 2018
//
// WR Devinfo
// (c) 2012, 2013, 2014, 2015, 2016, 2017, 2018
//-----------------------------------------------------------------------------------------------//
#include <std.button.hpp>
#include <std.table.hpp>
#include <bb.mdichildwindow_special_combination.hpp>
#include <bb.spreadsheet_select_other_group.hpp>
#include <std.groupbox_impl.hpp>

namespace bb
{
   //-----------------------------------------------------------------------------------------------//
   spreadsheet_select_other_group::spreadsheet_select_other_group(bb::mdichildwindow_special_combination * child) :
      std::widget_impl<std::gridbox>{ this, "IDD_SPREADSHEET_SELECT_OTHER_GROUP" },
      m_child{ child }
   {
      m_cancel = new std::button{ this, std::captions::common{}.CANCEL, std::icons::common{}.CANCEL };
      m_ok = new std::button{ this, std::captions::common{}.OK, std::icons::common{}.OK };
      m_table_groups = new std::table{ this };
      m_table_numbers = new std::table{ this };
      m_table_pages = new std::table{ this };
   }
   //-----------------------------------------------------------------------------------------------//
   QWidget *  spreadsheet_select_other_group::create()
   {
      //
      auto pGroups = new std::groupbox_impl<std::vertical_box>{ this, "Grupos" };
      {
         pGroups->box()->addWidget(m_table_groups);
      }
      //
      auto pPages = new std::groupbox_impl<std::vertical_box>{ this, "Cartelas" };
      {
         pPages->box()->addWidget(m_table_pages);
      }
      //
      auto pNumbers = new std::groupbox_impl<std::vertical_box>{ this, std::unicodestring{"Números"} };
      {
         pNumbers->box()->addWidget(m_table_numbers);
      }
      //
      auto pButtons = new std::widget_impl<std::horizontal_box>{ this, std::unicodestring{} };
      {
         pButtons->box()->addWidget(this->m_ok);
         pButtons->box()->addWidget(this->m_cancel);
         pButtons->box()->addStretch();
      }
      //
      this->box()->addWidget(pGroups, 0, 0);
      this->box()->addWidget(pPages, 0, 1);
      this->box()->addWidget(pNumbers, 0, 2);
      this->box()->addWidget(pButtons, 1, 0);
      this->adjustSize();
      //
      return this;
   }
   //-----------------------------------------------------------------------------------------------//
}