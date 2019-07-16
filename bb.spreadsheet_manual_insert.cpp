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
#include <std.lineedit.hpp>
#include <std.label.hpp>
#include <bb.mdichildwindow_special_combination.hpp>
#include <bb.spreadsheet_manual_insert.hpp>
#include <std.groupbox_impl.hpp>

namespace bb
{
   //-----------------------------------------------------------------------------------------------//
   spreadsheet_manual_insert::spreadsheet_manual_insert(bb::mdichildwindow_special_combination * child) :
      std::widget_impl < std::gridbox>{ this, "IDD_SPREADSHEET_MANUAL_INSERT" },
      m_child{ child }
   {
      m_apply = new std::button{ this, "Aplicar", std::icons::common{}.VALID };
      m_cancel = new std::button{ this,std::captions::common{}.CANCEL, std::icons::common{}.CANCEL };
      m_ok = new std::button{this, std::captions::common{}.OK, std::icons::common{}.OK };
      m_number_id = new std::lineedit{ "NumberID", 2, 0x32 };
      m_table_groups = new std::table{ this };
      m_table_pages = new std::table{ this };
   }
   //-----------------------------------------------------------------------------------------------//
   QWidget *  spreadsheet_manual_insert::create()
   {
      /**/
      auto pNumber = new std::groupbox_impl<std::formbox>{ this, std::unicodestring("Número") };
      {
         pNumber->box()->addRow(new std::label{ this, std::unicodestring{"Digite o número"} }, m_number_id);
         pNumber->adjustSize();
      }
      //
      auto pGroup = new std::groupbox_impl<std::vertical_box>{ this, "Grupos" };
      {
         pGroup->box()->addWidget(m_table_groups);
      }
      //
      auto pPages = new std::groupbox_impl<std::vertical_box>{ this,"Cartelas" };
      {
         pPages->box()->addWidget(m_table_pages);
      }
      //
      auto pButtons = new std::widget_impl<std::horizontal_box>{ this, std::unicodestring{} };
      {
         pButtons->box()->addWidget(m_ok);
         pButtons->box()->addWidget(m_cancel);
         pButtons->box()->addWidget(m_apply);
         pButtons->box()->addStretch();
      }
      //
      this->box()->addLayout(new define_layout_control<>(pNumber), 0, 0, 1, 1);
      this->box()->addWidget(pGroup, 0, 1, 1, 1);
      this->box()->addWidget(pPages, 0, 2, 1, 1);
      this->box()->addWidget(pButtons, 1, 0, 1, 1);
      this->adjustSize();
      return this;
   }
   //-----------------------------------------------------------------------------------------------//
}