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
//
namespace std
{
   class Q_DECL_EXPORT label;
   class Q_DECL_EXPORT checkbox;
   class Q_DECL_EXPORT vertical_box;
}
//
namespace bb
{
   class mdichildwindow;
   class box_information: public std::tabbed
   {
      //Q_OBJECT
   public:
      box_information(bb::mdichildwindow * pChildWnd);
      box_information *  create();

      //DECLARE_OPERATOR(box_information);
   public:
      std::label * m_label_data{ nullptr };
      std::checkbox * m_is_allowed_duplicate_pages{ nullptr };
      std::checkbox * m_is_allowed_duplicate_numbers_on_groups{ nullptr };
      //
   protected:
      std::widget_impl<std::vertical_box> * m_vbox{ nullptr };
      bb::mdichildwindow * m_child{ nullptr };
   };
}