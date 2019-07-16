//-----------------------------------------------------------------------------------------------//
// xbw32 for Windows (generate of numeric combinations for bingo or lotery)
//
// Created by wilsonsouza 2013, 2018
//
// WR Devinfo
// (c) 2013
//-----------------------------------------------------------------------------------------------//
#include <bb.mdichildwindow.hpp>
#include <bb.mdichildwindow_open_paper.hpp>
#include <bb.box_buttons.hpp>
#include <bb.box_editions.hpp>
#include <bb.box_information.hpp>
#include <bb.box_list_items.hpp>
#include <bb.box_numbers.hpp>
#include <bb.box_page_numbers.hpp>
#include <bb.box_search.hpp>
#include <bb.box_select_group_page.hpp>
#include <bb.MDIFrameWindow.hpp>
//-----------------------------------------------------------------------------------------------//
namespace bb
{
   //-----------------------------------------------------------------------------------------------//
   mdichildwindow_open_paper::mdichildwindow_open_paper(bb::mdiframewindow * frame,
                                                        bb::group_manager::pointer const & manager) :
      mdichildwindow(frame, manager, std::captions::file{}.OPEN)
   {
      /**/
      set_widget(m_hbox);
   }
   //-----------------------------------------------------------------------------------------------//
   bool mdichildwindow_open_paper::create(std::mdichildwindow * pWnd)
   {
      /**/
      m_vbox_r->addWidget(m_box_page_numbers->create());
      m_vbox_r->addWidget(m_box_numbers->create());
      m_vbox_r->addWidget(m_box_search->create());
      m_vbox_l->addWidget(m_box_list_items->create());
      m_vbox_l->addWidget(m_box_select_group_page->create()); /* problem to fix */
      /**/
      on_close = [&](std::mdichildwindow * sender)
      {
         if (QMessageBox::question(this, std::captions::errors{}.QUESTION, std::unicodestring
             {
                "Existem dados não salvos! Você deseja salva-los agora?"
             }, QMessageBox::Ok | QMessageBox::Cancel | QMessageBox::Abort) == QMessageBox::Ok)
         {
            /* emit signal to save document */
            get_frame()->find_menu_item(std::captions::file{}.SAVE)->triggered();
            std::dispatch_event_by_pplx(this, on_deactivate, this);
            return true;
         }
         return false;
      };
      return true;
   }
}