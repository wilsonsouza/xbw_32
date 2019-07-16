//-----------------------------------------------------------------------------------------------//
// xbw32 for Windows (generate of numeric combinations for bingo or lotery)
//
// Created by wilsonsouza 2013, 2018
//
// WR Devinfo
// (c) 2012, 2013, 2014, 2015, 2016, 2017, 2018
//-----------------------------------------------------------------------------------------------//
#include <bb.mdichildwindow.hpp>
#include <bb.box_information.hpp>
#include <std.label.hpp>
#include <std.checkbox.hpp>

namespace bb
{
   box_information::box_information(bb::mdichildwindow * child) :
      std::tabbed{ child, "IDD_INFORMATION" },
      m_vbox{ new std::widget_impl<std::vertical_box>{this, std::unicodestring{}} },
      m_child{ child }
   {
      m_label_data = new std::label{ this, std::unicodestring{} };
      m_is_allowed_duplicate_numbers_on_groups = new std::checkbox
      {
         this, "Permite sequencia de números duplicados no grupo", "IDD_DUPLICATENUMBERSONGROUPS"
      };
      m_is_allowed_duplicate_pages = new std::checkbox
      {
         this, "Permite cartelas duplicadas no grupo", "IDD_DUPLICATEPAGE"
      };
      addTab(m_vbox, std::unicodestring{ "Propriedades/Opçoes" });
   }
   //-----------------------------------------------------------------------------------------------//
   box_information *  box_information::create()
   {
      m_vbox->box()->addWidget(m_is_allowed_duplicate_numbers_on_groups);
      m_vbox->box()->addWidget(m_is_allowed_duplicate_pages);
      m_vbox->box()->addWidget(m_label_data);
      return this;
   }
}