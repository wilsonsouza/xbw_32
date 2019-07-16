//-----------------------------------------------------------------------------------------------//
// xbw32 for Windows (generate of numeric combinations for bingo or lotery)
//
// Created by wilsonsouza 2013, 2018
//
// WR Devinfo
// (c) 2013
//-----------------------------------------------------------------------------------------------//
#pragma once
#include <std.dialog.hpp>
#include <bb.group_manager.hpp>
#include <std.lineedit.hpp>
#include <std.combobox.hpp>
//-----------------------------------------------------------------------------------------------//
namespace bb
{
   class mdiframewindow;
   class dialog_new_papers: public std::dialog
   {
      //Q_OBJECT
   public:
      explicit dialog_new_papers(QWidget * parent);
      virtual bool create(std::dialog * dlg) override;
      virtual void const  create_database_process();
      //
      void const create_catalog_name(bb::group_manager::pointer & data);
      //
      //DECLARE_OPERATOR(dialog_new_papers)
   protected:
      std::lineedit * m_numbers_bypage{ nullptr };
      std::lineedit * m_numbers_bygroup{ nullptr };
      std::lineedit * m_pages_bygroup{ nullptr };
      std::lineedit * m_numbers{ nullptr };
      std::combobox * m_list_ofgroups{ nullptr };
      std::checkbox * m_is_allowed_zero{ nullptr };
      std::checkbox * m_is_create_allgroups{ nullptr };
      std::checkbox * m_is_special_combination{ nullptr };
   };
}
//-----------------------------------------------------------------------------------------------//
