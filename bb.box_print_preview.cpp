//-----------------------------------------------------------------------------------------------//
// xbw32 for Windows (generate of numeric combinations for bingo or lotery)
//
// Created by wilsonsouza 2013, 2018
//
// WR Devinfo
// (c) 2013
//-----------------------------------------------------------------------------------------------//
#pragma once
#include <bb.box_print_preview.hpp>
#include <bb.mdichildwindow.hpp>
#include <bb.MDIFrameWindow.hpp>

namespace bb
{
   //-----------------------------------------------------------------------------------------------//
   box_print_preview::box_print_preview(bb::mdichildwindow * child):
      std::widget{child, "IDD_CUSTOM_PRINT_PREVIEW"}
   {
   }
   //-----------------------------------------------------------------------------------------------//
   QWidget * box_print_preview::create()
   {
      auto * p = dynamic_cast<mdichildwindow *>(parent());
      {
         /* set default printer options 
         p->setOutputFormat(QPrinter::PdfFormat);
         p->setOutputFileName("cn_report.pdf");
         p->setPaperSize(QPrinter::A4);
         p->setFullPage(true);
         p->setResolution(0x12c);
         */
      }
      return this;
   }
}