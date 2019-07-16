//-----------------------------------------------------------------------------------------------//
// xbw32 for Windows (generate of numeric combinations for bingo or lotery)
//
// Created by wilsonsouza 2013, 2018
//
// WR Devinfo
// (c) 2012, 2013, 2014, 2015, 2016, 2017, 2018
//-----------------------------------------------------------------------------------------------//
#include <std.radiobutton.hpp>
#include <std.button.hpp>
#include <std.table.hpp>
#include <bb.mdichildwindow.hpp>
#include <std.groupbox_impl.hpp>
#include <bb.spreadsheet_insert_by.hpp>

namespace bb
{
   //-----------------------------------------------------------------------------------------------//
   spreadsheet_insert_by::spreadsheet_insert_by(bb::mdichildwindow_special_combination * pWnd) :
      std::widget_impl<std::gridbox>{ this, "IDD_SPREADSHEET_INSERT_BY" }
   {
      m_cancel = new std::button{ this, std::captions::common{}.CANCEL, std::icons::common{}.CANCEL };
      m_ok = new std::button{ this, std::captions::common{}.OK, std::icons::common{}.OK };
      m_insert_in_all_groups = new std::radiobutton{ this, "Inserir em todos os grupos", "", true, false };
      m_insert_in_all_groups_by_position =
         new std::radiobutton{ this, "Inserir em todos os grupos por posição", "", true, false };
      m_select_group_and_position =
         new std::radiobutton{ this, "Selecionar grupo e posição", "", true, false };
      m_select_groups_and_pages = new std::radiobutton{ this, "Selecionar grupos e cartelas", "", true, false };
      m_table_groups = new std::table{ this };
      m_table_numbers = new std::table{ this };
      m_table_pages = new std::table{ this };
      m_table_position = new std::table{ this };
   }
   //-----------------------------------------------------------------------------------------------//
   QWidget *  spreadsheet_insert_by::create()
   {
      auto pNumbers = new std::groupbox_impl<std::vertical_box>{ this, std::unicodestring{"Números"} };
      {
         pNumbers->box()->addWidget(m_table_numbers);
      }
      //
      auto pOptions = new std::groupbox_impl<std::vertical_box>{ this, std::unicodestring{"Opções"} };
      {
         pOptions->box()->addWidget(m_insert_in_all_groups);
         pOptions->box()->addWidget(m_select_groups_and_pages);
         pOptions->box()->addWidget(m_select_group_and_position);
         pOptions->box()->addWidget(m_insert_in_all_groups_by_position);
      }
      //
      auto pGroups = new std::groupbox_impl<std::vertical_box>{ this,"Grupos" };
      {
         pGroups->box()->addWidget(m_table_groups);
      }
      //
      auto pPosition = new std::groupbox_impl<std::vertical_box>{ this, std::unicodestring{"Posição"} };
      {
         pPosition->box()->addWidget(m_table_position);
      }
      //
      auto pPages = new std::groupbox_impl<std::vertical_box>{ this, "Cartelas" };
      {
         pPages->box()->addWidget(m_table_pages);
      }
      //
      auto pButtons = new std::widget_impl<std::horizontal_box>{ this, "" };
      {
         pButtons->box()->addStretch();
         pButtons->box()->addWidget(m_ok);
         pButtons->box()->addWidget(m_cancel);
      }
      //
      auto lay = box();
      {
         lay->addWidget(pNumbers, 0, 0);
         lay->addLayout(new define_layout_control<>(pOptions), 0, 1);
         lay->addWidget(pGroups, 0, 2);
         lay->addWidget(pPosition, 0, 3);
         lay->addWidget(pPages, 0, 4);
         lay->addWidget(pButtons, 1, 0);
      }
      return this;
   }
   //-----------------------------------------------------------------------------------------------//
}
