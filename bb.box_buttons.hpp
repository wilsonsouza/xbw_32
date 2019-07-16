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
#include <std.layouts.hpp>
/**/
namespace std
{
   class button;
}
/**/
namespace bb
{
   class mdichildwindow;
   class box_buttons: public std::horizontal_box
   {
   public:
      box_buttons(bb::mdichildwindow * child);
      box_buttons * create();
      std::stringlist  get_list_of_current_edited_numbers();
      std::unicodestring  prepare_query_complement(std::stringlist const & queue);
      void  next_page();
      bool  is_allowed_duplicate_groups();
      bool  is_allowed_duplicate_page();
      //
   public:
      std::button * m_ok{ nullptr };
      std::button * m_cancel{ nullptr };
      std::button * m_help{ nullptr };
      std::button * m_close{ nullptr };
      mdichildwindow * m_child{ nullptr };
   };
}
