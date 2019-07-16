//-----------------------------------------------------------------------------------------------//
// xbw32 for Windows (generate of numeric combinations for bingo or lotery)
//
// Created by wilsonsouza 2013, 2018
//
// WR Devinfo
// (c) 2013
//-----------------------------------------------------------------------------------------------//
#include <bb.mdichildwindow.hpp>
#include <bb.mdichildwindow_new_paper.hpp>
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
   mdichildwindow_new_paper::mdichildwindow_new_paper(bb::mdiframewindow * frame,
                                                      bb::group_manager::pointer const & manager) :
      mdichildwindow{ frame, manager, std::captions::file{}.NEW }
   {
      /**/
      set_widget(m_hbox);
   }
   //-----------------------------------------------------------------------------------------------//
   mdichildwindow_new_paper::~mdichildwindow_new_paper()
   {
   }
   //-----------------------------------------------------------------------------------------------//
   bool mdichildwindow_new_paper::create(std::mdichildwindow * child)
   {
      /* tree list */
      m_vbox_l->addWidget(m_box_list_items->create());
      /* generate numbers */
      m_vbox_r->addWidget(m_box_numbers->create()); //pvbRight->addWidget(CreateBoxNumbers());
      /* label */
      m_vbox_r->addWidget(m_box_information->create()); //pvbRight->addWidget(CreateBoxLabelInfo());
      /* search */
      m_vbox_r->addWidget(m_box_search->create()); //pvbRight->addWidget(CreateBoxSearch());
      /* select group and page */
      m_vbox_l->addWidget(m_box_select_group_page->create()); //pvbLeft->addWidget(CreateBoxSelectGroupPage());
      /**/
      m_box_select_group_page->setVisible(true);
      on_close = [&](std::mdichildwindow * sender)
      {
         if (this->base->is_modified)
         {
            if (QMessageBox::question(this, std::captions::errors{}.QUESTION,
                std::unicodestring("Dado(s) não foram salvos! Você deseja salvar agora?"),
                QMessageBox::Ok | QMessageBox::Cancel) == QMessageBox::Ok)
            {
               child->get_frame()->find_menu_item(std::captions::file{}.SAVE)->triggered();
            }
            /**/
            std::dispatch_event_by_pplx(this, on_deactivate, this);
         }
         return true;
      };
      return true;
   }
}
