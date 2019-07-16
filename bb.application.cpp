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
#include <std.unicodestring.hpp>
#include <bb.application.hpp>
#include <bb.mdiframewindow.hpp>
//-----------------------------------------------------------------------------------------------//
namespace bb
{
   application::application(int & argc, char ** argv) :std::application{ argc, argv }
   {
      auto directory_list = std::stringlist
      {
             "c:/xbw32/Resources/",
             "c:/xbw32/table/",
             "c:/xbw32/",
      };
      directory_list.append(this->libraryPaths());
      this->setLibraryPaths(directory_list);
      /**/
      setWindowIcon(m_icons->APP);
      setApplicationName("xbw32");
      setApplicationDisplayName(defs::app::details{}.CAPTION);
   #if(0)
      setapplicationVersion(std::unicodestring("Versão 1.2.7"));
   #else
      setApplicationVersion(std::unicodestring{ "Versão 2.0.0" });
   #endif
      setOrganizationName(bb::defs::app::details{}.ORGANIZATION_NAME);
      this->m_framewindow = new bb::mdiframewindow{ nullptr, this, bb::defs::app::details{}.CAPTION, 0 };
   }
}