//-----------------------------------------------------------------------------------------------//
// xbw32 for Windows (generate of numeric combinations for bingo or lotery)
//
// Created by wilsonsouza 2013, 2018
//
// WR Devinfo
// (c) 2013
//-----------------------------------------------------------------------------------------------//
#pragma once
#include <bb.defs.hpp>
#include <qprintpreviewwidget.h>
#include <std.widget.hpp>
/**/
namespace bb
{
   class mdichildwindow;
   class box_print_preview : public std::widget
   {
      //Q_OBJECT
   public:
      box_print_preview(bb::mdichildwindow * child);
      virtual ~box_print_preview() override = default;
      virtual QWidget * create() override;
      /**/
      //DECLARE_OPERATOR(box_print_preview);
   protected:
      QPrintPreviewWidget * m_preview{ nullptr };
   };
}
