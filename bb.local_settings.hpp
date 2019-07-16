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
//-----------------------------------------------------------------------------------------------//
namespace bb
{
   class local_settings : public std::settings
   {
   public:
      using pointer = std::shared_ptr<local_settings>;
      //
      explicit local_settings(const std::unicodestring &organization,
                              const std::unicodestring &application,
                              QObject *parent) :
         std::settings{ organization, application, parent }
      {
         beginGroup(bb::defs::app::details{}.MS_FOLDERS);
      }
      //-----------------------------------------------------------------------------------------------//
      std::unicodestring  get_documentpath() const
      {
         return value(bb::defs::app::details{}.MS_DOCUMENTS_FOLDER).toString();
      }
   };
}