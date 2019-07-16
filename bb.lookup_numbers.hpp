//-----------------------------------------------------------------------------------------------//
// xbw32 for Windows (generate of numeric combinations for bingo or lotery)
//
// Created by wilsonsouza 2013, 2018
//
// WR Devinfo
// (c) 2012, 2013, 2014, 2015, 2016, 2017, 2018, 2015
//-----------------------------------------------------------------------------------------------//
#pragma once
#include <bb.defs.hpp>

namespace bb
{
   struct pages_controller;
   struct lookup_numbers
   {
      std::unicodestring group;
      bb::pages_controller * page;
      explicit lookup_numbers(bb::pages_controller * pages, std::unicodestring const & group_id) :
         group{ group_id },
         page{ pages }
      {
      }
   };
}