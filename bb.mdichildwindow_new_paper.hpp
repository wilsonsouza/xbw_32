//-----------------------------------------------------------------------------------------------//
// xbw32 for Windows (generate of numeric combinations for bingo or lotery)
//
// Created by wilsonsouza 2013, 2018
//
// WR Devinfo
// (c) 2012, 2013, 2014, 2015, 2016, 2017, 2018
//-----------------------------------------------------------------------------------------------//
#pragma once
#include <bb.mdichildwindow.hpp>
//-----------------------------------------------------------------------------------------------//
namespace bb
{
   class mdiframewindow;
   class mdichildwindow_new_paper: public mdichildwindow
   {
      //Q_OBJECT
   public:
      mdichildwindow_new_paper(bb::mdiframewindow * frame, bb::group_manager::pointer const & manager);
      virtual ~mdichildwindow_new_paper();
      virtual bool create(std::mdichildwindow * child) override;
   };
}