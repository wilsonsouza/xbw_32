//-----------------------------------------------------------------------------------------------//
// xbw32 for Windows (generate of numeric combinations for bingo or lotery)
//
// Created by wilsonsouza 2013, 2018
//
// WR Devinfo
// (c) 2013
//-----------------------------------------------------------------------------------------------//
#pragma once
#include <bb.defs.hpp>
#include <std.dialog.hpp>
//-----------------------------------------------------------------------------------------------//
namespace std
{
   class lineedit;
   class checkbox;
   class tabbed;
   class button;
};
/**/
namespace bb
{
   class dialog_config_application_options : public std::dialog
   {
   public:
      explicit dialog_config_application_options(std::widget * parent);
      virtual ~dialog_config_application_options() override = default;
      virtual bool create(std::dialog * dlg) override;
      /**/
   protected:
      //DECLARE_OPERATOR(dialog_config_application_options)
      std::tabbed * m_tabbed{ nullptr };
      std::lineedit * m_pages_by_group{ nullptr };
      std::lineedit * m_numbers_by_page{ nullptr };
      std::lineedit * m_numbers_by_group{ nullptr };
      std::lineedit * m_numbers{ nullptr };
      std::checkbox * m_is_allowed_zero{ nullptr };
      std::checkbox * m_is_create_all_groups{ nullptr };
      std::button * m_apply{ nullptr };
   };
}
//-----------------------------------------------------------------------------------------------//
