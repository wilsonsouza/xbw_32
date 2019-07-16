//-----------------------------------------------------------------------------------------------//
// xbw32 for Windows (generate of numeric combinations for bingo or lotery) (generate of numeric combinations for bingo or lotery)
//
// Created by wilsonsouza 2012, 2013, 2014, 2015, 2016, 2017, 2018
// For Olavo Co.
//
// WR Devinfo
// (c) 2012, 2013, 2014, 2015, 2016, 2017, 2018
// update of qt 5.01 to 5.11
//-----------------------------------------------------------------------------------------------//
#pragma once
#include <bb.defs.hpp>
#include <bb.local_settings.hpp>
#include <std.mdiframewindow.hpp>
#include <std.menu.hpp>
#include <std.menubar.hpp>
#include <std.toolbar.hpp>
#include <std.timer.hpp>
#include <std.application.hpp>
#include <std.mdichildwindow.hpp>
#include <std.statusbar.hpp>
#include <bb.Application.hpp>
#include <sql.query.hpp>
#include <bb.group_manager.hpp>
//-----------------------------------------------------------------------------------------------//
namespace bb
{
   namespace captions
   {
      struct file
      {
         std::unicodestring const SpecialCombination{ "Combinação especial" };
         std::unicodestring const PREFERENCES{ "Preferências" };
         file() = default;
      };
      //-----------------------------------------------------------------------------------------------//
      struct view
      {
         std::unicodestring const ViewBoxListItems{ "Lista de grupos" };
         std::unicodestring const ViewBoxInformation{ "Caixa de informação" };
         std::unicodestring const ViewBoxEdition{ "Caixa de edição" };
         std::unicodestring const ViewBoxNumbers{ "Caixa de números" };
         view() = default;
      };
      //-----------------------------------------------------------------------------------------------//
      struct tools
      {
         std::unicodestring const VerifyPagesCompleted{ "Verifica cartelas completas" };
         std::unicodestring const UpdatePagesCounter{ "Atualizar contador de paginas" };
         tools() = default;
      };
   }
   //-----------------------------------------------------------------------------------------------//
   struct fileitems : public std::fileitems
   {
      fileitems() :std::fileitems{}
      {
         this->separator().
            operator+(new std::menuitemdata{ bb::captions::file{}.SpecialCombination }).
            operator+(new std::menuitemdata{ bb::captions::file{}.PREFERENCES });
      }
   };
   //-----------------------------------------------------------------------------------------------//
   struct viewitems : public std::viewitems
   {
      viewitems() :std::viewitems{}
      {
         separator().
         operator+(new std::menuitemdata{ bb::captions::view{}.ViewBoxEdition }).
            operator+(new std::menuitemdata{ bb::captions::view{}.ViewBoxInformation }).
            operator+(new std::menuitemdata{ bb::captions::view{}.ViewBoxListItems }).
            operator+(new std::menuitemdata{ bb::captions::view{}.ViewBoxNumbers });
      }
   };
   //-----------------------------------------------------------------------------------------------//
   struct toolsitems : public std::toolsitems
   {
      toolsitems() :std::toolsitems{}
      {
         separator().
         operator+(new std::menuitemdata{ bb::captions::tools{}.VerifyPagesCompleted }).
            operator+(new std::menuitemdata{ bb::captions::tools{}.UpdatePagesCounter });
      }
   };
   //-----------------------------------------------------------------------------------------------//
   class mdiframewindow : public std::mdiframewindow, public local_settings, public group_manager
   {
   public:
      explicit mdiframewindow(QWidget * owner,
                              bb::application * handle,
                              std::unicodestring const & name = std::unicodestring{},
                              Qt::WindowFlags wfflags = 0);
      ~mdiframewindow() override = default;
      bool create(std::mainwindow * sender);
      std::basic_string<wchar_t> const get_computer_username();
      virtual double const get_control_version_id();
      virtual std::unicodestring const get_control_comments();
      bb::local_settings::pointer get_config();
      virtual std::sql::query::pointer get_sql_handle();
      static bb::mdiframewindow * get_frame()
      {
         return dynamic_cast<bb::mdiframewindow *>(std::application::get_mainwindow());
      }
      //
   protected:
      std::action * m_delegate{ nullptr };
      std::sql::query::pointer m_sql_handle{ nullptr };
   };
}