//-----------------------------------------------------------------------------------------------//
// xbw32 for Windows (generate of numeric combinations for bingo or lotery)
//
// Created by wilsonsouza 2013, 2018
//
// WR Devinfo
// (c) 2012, 2013, 2014, 2015, 2016, 2017, 2018
//-----------------------------------------------------------------------------------------------//
#pragma once
#include <std.tabbed.hpp>
#include <std.widget_impl.hpp>
#include <std.treewidget.hpp>
#include <std.treewidgetitem.hpp>
#include <std.checkbox.hpp>
#include <std.lineedit.hpp>
/**/
namespace bb
{
   namespace captions
   {
      struct box_list_items
      {
         const std::unicodestring HEADERLISTNAMES{ "Grupo,Cartela,Número(s),Ordem,Disponíveis,Completa" };
         const std::unicodestring LISTFIELDNAMES{ "groupname, pagename, numbers, useds, availables, iscompleted" };
         const std::unicodestring TOKENSEPARATOR{ "," };
         box_list_items() = default;
      };
   }
   //
   class mdichildwindow;
   class box_list_items: public std::tabbed, public task_group
   {
      //Q_OBJECT
   public:
      enum class HEADERINDEX : uint
      {
         IDD_GROUP,
         IDD_PAGE,
         IDD_NUMBER,
         IDD_USED,
         IDD_AVAILABLE,
         IDD_COMPLETE
      };
      //
   public:
      box_list_items(bb::mdichildwindow * pchildwnd);
      box_list_items * create();
      void const  load_table_numbers();
      void const  update_items(std::stringlist const * plistitems);
      //
      //declare_operator(box_list_items);
   public:
      std::treewidget * m_list_items{ nullptr };
      std::treewidgetitem * m_current_item{ nullptr };
      std::checkbox * m_is_display_box_select_group_page{ nullptr };
      std::unicodestring m_actual_group{ };
      std::checkbox * m_is_auto_reload{ nullptr };
      std::lineedit * m_actual_edit{ nullptr };
      //
   protected:
      std::widget_impl<std::vertical_box> * m_vbox{ nullptr };
      bb::mdichildwindow * m_child{ nullptr };
   };
}