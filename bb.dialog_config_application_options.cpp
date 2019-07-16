//-----------------------------------------------------------------------------------------------//
// xbw32 for Windows (generate of numeric combinations for bingo or lotery)
//
// Created by Wilson.Souza 2012
// For Libbs Farma
//
// WR Devinfo
// (c) 2012
//-----------------------------------------------------------------------------------------------//
#include <std.lineedit.hpp>
#include <std.button.hpp>
#include <std.tabbed.hpp>
#include <std.widget_impl.hpp>
#include <bb.dialog_config_application_options.hpp>
//-----------------------------------------------------------------------------------------------//
namespace bb
{
   //-----------------------------------------------------------------------------------------------//
   dialog_config_application_options::dialog_config_application_options(std::widget * parent) :
      std::dialog{ parent, 0, "IDD_DIALOG_CONFIG_APPLICATION_OPTIONS" }
   {
      setWindowTitle(std::unicodestring{ std::captions::tools{}.PREFERENCES }.replace("&", std::unicodestring{}));
      m_tabbed = new std::tabbed{ this, "IDD_TABBED" };
      m_apply = new std::button{ this, "&Aplicar", std::icons::common{}.OK, "IDD_OK" };
   }
   //-----------------------------------------------------------------------------------------------//
   bool dialog_config_application_options::create(std::dialog * dlg)
   {
      std::dialog::create(dlg);
      /**/
      this->hbuttons()->insertWidget(hbuttons()->count() - 2, m_apply);
      /**/
      vbox()->addWidget(m_tabbed);
      vbox()->addLayout(hbuttons());
      /**/
      return true;
   }
}