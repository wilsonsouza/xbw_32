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
#include <std.groupbox.hpp>
#include <std.lineedit.hpp>
#include <std.treewidget.hpp>
/**/
namespace bb
{
   class mdichildwindow;
   class box_select_group_page: public std::tabbed
   {
      //Q_OBJECT
   public:
      explicit box_select_group_page(bb::mdichildwindow * child);
      box_select_group_page *  create();
      /**/
      //DECLARE_OPERATOR(box_select_group_page);
      std::lineedit * m_group_id{ nullptr };
      std::lineedit * m_page_id{ nullptr };
      std::groupbox * m_groupbox_edit_selected_page{ nullptr };
      std::unicodestring m_actual_group_id{};
      //
   protected:
      std::widget_impl<std::vertical_box> * m_vbox{ nullptr };
      bb::mdichildwindow * m_child{ nullptr };
   };
}