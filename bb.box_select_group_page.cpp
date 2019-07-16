//-----------------------------------------------------------------------------------------------//
// xbw32 for Windows (generate of numeric combinations for bingo or lotery)
//
// Created by wilsonsouza 2013, 2018
//
// WR Devinfo
// (c) 2012, 2013, 2014, 2015, 2016, 2017, 2018
//-----------------------------------------------------------------------------------------------//
#include <std.label.hpp>
#include <std.lineedit.hpp>
#include <std.layouts.hpp>
#include <std.widget_impl.hpp>
#include <bb.box_select_group_page.hpp>
#include <bb.mdichildwindow.hpp>
#include <bb.box_buttons.hpp>
#include <bb.box_editions.hpp>
#include <bb.group_manager.hpp>
#include <bb.box_numbers.hpp>
#include <sql.table.hpp>
#include <bb.table_interface.hpp>
#include <bb.MDIFrameWindow.hpp>
#include <bb.integral_validator.hpp>
//-----------------------------------------------------------------------------------------------//
namespace bb
{
   //-----------------------------------------------------------------------------------------------//
   box_select_group_page::box_select_group_page(bb::mdichildwindow * child) :
      std::tabbed{ child, "IDD_BOX_SELECT_GROUP_PAGE" },
      m_child{ child }
   {
      m_vbox = new std::widget_impl<std::vertical_box>{ this, std::unicodestring{} };
      m_groupbox_edit_selected_page = new std::groupbox{ std::unicodestring{"Manutenção..."}, this };
      m_group_id = new std::lineedit
      {
         this, std::unicodestring{}, 4, 0x32, bb::captions::internal_editions{}.GROUPNAME
      };
      m_page_id = new std::lineedit
      {
         this, std::unicodestring{}, 2, 0x32, bb::captions::internal_editions{}.PAGENAME
      };
      //
      addTab(m_vbox, std::unicodestring{ "Selecione o grupo e cartela..." });
      m_group_id->set_input_mask("A999");
      m_page_id->set_validator(new bb::integral_validator{ 1,
                               child->base->information->pages_to_group, m_page_id });
      m_page_id->setEnabled(false);
   }
   //-----------------------------------------------------------------------------------------------//
   box_select_group_page *  box_select_group_page::create()
   {
      auto hbox = new std::horizontal_box{};
      {
         hbox->addWidget(new std::label{ this, "Nome do grupo" });
         hbox->addWidget(m_group_id);
         hbox->addWidget(new std::label{ this, "Nome da cartela" });
         hbox->addWidget(m_page_id);
         hbox->addStretch();
         //
         m_groupbox_edit_selected_page->setLayout(hbox);
      }
      /**/
      auto box_editions = m_child->m_box_editions;
      auto box_buttons = m_child->m_box_buttons;
      /**/
      box_editions->create();
      box_buttons->create();
      /**/
      m_group_id->setFocus();
      m_vbox->box()->addWidget(m_groupbox_edit_selected_page);
      m_vbox->box()->addWidget(box_editions);
      m_vbox->box()->addLayout(box_buttons);
      //
      setVisible(!(m_child->std::mdichildwindow::objectName() == std::captions::file{}.OPEN));
      /**/
      m_group_id->on_return_pressed = [&](std::lineedit * sender)->bool
      {
         try
         {
            if (sender == m_group_id)
            {
               if (m_group_id->text().isEmpty())
               {
                  throw std::unicodestring{ "Grupo invalido!" };
               }
               /**/
               sender->set_focus_next_child();
               return false;
            }
            /**/
            if (sender == m_page_id)
            {
               if (m_page_id->text().toInt() == 0)
               {
                  throw std::unicodestring{ "Cartela invalida!" };
               }
            }
            /**/
            auto resources = std::shared_ptr<table_resources>{ new table_resources{m_child} };
            /**/
            resources->m_run_mode = table_interface::RUN_MODE::LOOKUP_NO_LOADDATA;
            resources->lookup(m_group_id->text(), m_page_id->text().toInt(), -1);
            /**/
            if (!resources->m_successed)
            {
               throw std::unicodestring
               {
                  "Grupo %1 ou cartela %2 não encontrada!\nProcesso abortado!"
               }.arg(m_group_id->text()).arg(m_page_id->text().toInt());
            }
            /**/
            box_editions->set_clear_editions();
            box_editions->set_enable_editions(true);
            /**/
            m_group_id->setEnabled(false);
            m_page_id->setEnabled(false);
            /**/
         }
         catch (std::unicodestring const & e)
         {
            QMessageBox::warning(m_child, std::captions::errors{}.CRITICAL, e);
         }
         return true;
      };
      /**/
      m_group_id->on_text_changed = [&](std::unicodestring const & value, std::lineedit * sender)->bool
      {
         if (sender == m_group_id && m_group_id->text().length() == 0x4)
         {
            sender->setText(sender->text().toUpper().trimmed());
         }
         return true;
      };
      //
      m_page_id->on_return_pressed = m_group_id->on_return_pressed;
      m_page_id->on_text_changed = m_group_id->on_text_changed;
      return this;
   }
}