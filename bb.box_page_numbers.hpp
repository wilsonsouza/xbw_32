//-----------------------------------------------------------------------------------------------//
// xbw32 for Windows (generate of numeric combinations for bingo or lotery)
//
// Created by wilsonsouza 2013, 2018
//
// WR Devinfo
// (c) 2012, 2013, 2014, 2015, 2016, 2017, 2018
//-----------------------------------------------------------------------------------------------//
#pragma once
#include <bb.box_numbers.hpp>

namespace bb
{
   class mdichildwindow;
   class box_page_numbers: public bb::box_numbers
   {
      //Q_OBJECT
   public:
      box_page_numbers(bb::mdichildwindow * child);
      box_page_numbers * create();
      virtual void update_lcdnumbers(std::stringlist const * queue);
   };
}