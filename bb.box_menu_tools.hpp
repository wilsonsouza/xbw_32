//-----------------------------------------------------------------------------------------------//
// xbw32 for Windows (generate of numeric combinations for bingo or lotery)
//
// Created by Wilson.Souza 2012
// For 
//
// WR Devinfo
// (c) 2012, 2013 2014
//-----------------------------------------------------------------------------------------------//
#pragma once
#include <std.display_progressbar.hpp>

namespace bb
{
   class mdichildwindow;
   class box_menu_tools : public std::display_progressbar
   {
   public:
      explicit box_menu_tools(bb::mdichildwindow * child);
      virtual ~box_menu_tools() override = default;
      //
      virtual bool const verify_complete_pages();
   protected:
      bb::mdichildwindow * m_child{ nullptr };
   };
}