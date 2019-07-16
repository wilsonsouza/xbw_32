//-----------------------------------------------------------------------------------------------//
// xbw32 for Windows (generate of numeric combinations for bingo or lotery)
//
// Created by wilsonsouza 2013, 2018
//
// WR Devinfo
// (c) 2013
//-----------------------------------------------------------------------------------------------//
#pragma once
#include <bb.group_manager.hpp>
#include <bb.mdichildwindow.hpp>
//-----------------------------------------------------------------------------------------------//
namespace bb
{
   class mdiframewindow;
   class mdichildwindow_open_paper : public mdichildwindow
   {
      //Q_OBJECT
   public:
      mdichildwindow_open_paper(bb::mdiframewindow * child, bb::group_manager::pointer const & manager);
      virtual ~mdichildwindow_open_paper() override = default;
      virtual bool create(std::mdichildwindow * child) override;
   };
}