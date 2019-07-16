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
#include <std.application.hpp>
//-----------------------------------------------------------------------------------------------//
namespace bb
{
   class application: public std::application
   {
   public:
      explicit application ( int & argc, char ** aargv );
      //
   protected:
      defs::icons::local::pointer m_icons{ new defs::icons::local{} };
   };
}
//-----------------------------------------------------------------------------------------------//
