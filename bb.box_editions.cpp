//-----------------------------------------------------------------------------------------------//
// xbw32 for Windows (generate of numeric combinations for bingo or lotery)
//
// Created by wilsonsouza 2013, 2018
//
// WR Devinfo
// (c) 2012, 2013, 2014, 2015, 2016, 2017, 2018
//-----------------------------------------------------------------------------------------------//
#include <std.lineedit.hpp>
#include <std.button.hpp>
#include <bb.mdichildwindow.hpp>
#include <bb.box_editions.hpp>
#include <bb.group_manager.hpp>
#include <bb.box_select_group_page.hpp>
#include <bb.box_buttons.hpp>
#include <bb.box_numbers.hpp>
#include <bb.box_list_items.hpp>
#include <bb.data_queue_controller.hpp>
#include <bb.groups_controller.hpp>

namespace bb
{
   //-----------------------------------------------------------------------------------------------//
   box_editions::box_editions(bb::mdichildwindow * child) :
      std::groupbox_impl<std::vertical_box>{ this, name{}.caption, "IDD_BOX_EDITIONS" },
      m_child{ child }
   {
   }
   //-----------------------------------------------------------------------------------------------//
   QWidget * box_editions::create()
   {
      auto start = int{ m_child->base->information->is_allowed_zero };
      auto max_np = m_child->base->information->numbers_to_page;
      /**/
      for (auto lines = start; lines <= max_np; )
      {
         auto hbox_cols = new std::horizontal_box{ this, std::unicodestring{} };
         auto start_cols = 0x11;
         //
         for (auto n = start; n < start_cols && lines <= max_np; n++, lines++)
         {
            auto name_id = bb::captions::internal_editions{}.NUMBERS.bind(lines);
            auto edit = new std::lineedit{ name_id, 2, 0x14 };
            /**/
            edit->set_validator(new QIntValidator{ start, m_child->base->information->numbers, edit });
            edit->setText(std::unicodestring{});
            /**/
            m_edit_queue.push_back(edit);
            /**/
            edit->on_return_pressed = std::bind(&bb::box_editions::validate_entry, this, std::placeholders::_1);
            edit->on_text_changed = [&](std::unicodestring const & value, std::lineedit * sender)->auto
            {
               m_actual_edit = sender;
               return true;
            };
            /**/
            edit->setEnabled(false);
            hbox_cols->addWidget(edit);
            hbox_cols->addStretch();
         }
         //
         hbox_cols->addStretch();
         box()->addLayout(hbox_cols);
      }
      //
      box()->addStretch();
      set_enable_editions(false);
      return this;
   }
   //-----------------------------------------------------------------------------------------------//
   bool box_editions::validate_entry(std::lineedit * sender)
   {
      try
      {
         auto select_group_page_box = m_child->m_box_select_group_page;
         auto value = sender->text().toInt();
         auto group_id = select_group_page_box->m_group_id->text().trimmed();
         auto page_id = select_group_page_box->m_page_id->text().toInt();
         auto group = std::find_if(m_child->groups->begin(),
                                   m_child->groups->end(), controller::groups{ group_id });
         /**/
         if (group != m_child->groups->end())
         {
            auto & page = std::find_if(group->pages.begin(), group->pages.end(), controller::pages{ page_id });
            auto & available = std::find_if(group->availables.begin(),
                                            group->availables.end(), controller::available_numbers{ value });
            /**/
            if (page != group->pages.end())
            {
               auto number_id = std::find_if(page->numbers.begin(),
                                             page->numbers.end(), controller::page_numbers{ value });
               /**/
               if (value == 0 || number_id != page->numbers.end())
               {
                  throw std::unicodestring{ "Número %1 não permitido!" }.arg(value);
               }
               /**/
               if (available->availables == 0)
               {
                  throw std::unicodestring{ "Número %1 com quantidade esgotada!" }.arg(value);
               }
               available->availables--;
               page->numbers.push_back(controller::page_numbers{ value });
               /**/
               sender->set_focus_next_child();
               verify_all_editions();
               return true;
            }
         }
      }
      catch (std::unicodestring & e)
      {
         QMessageBox::warning(this, std::captions::errors{}.WARNING, e);
         sender->setFocus();
      }
      return false;
   }
   //-----------------------------------------------------------------------------------------------//
   void  box_editions::verify_all_editions()
   {
      auto success = 0u;
      auto lines = std::shared_ptr<std::stringlist>{ new std::stringlist{} };
      auto child = dynamic_cast<mdichildwindow *>(parent());
      /**/
      std::for_each(m_edit_queue.begin(), m_edit_queue.end(), [&](std::lineedit * p)
      {
         if (!p->text().trimmed().isEmpty())
         {
            lines->append(p->text().trimmed());
         }
         if (!p->text().trimmed().isEmpty())
         {
            success |= 1;
         }
         else
         {
            success &= ~1;
         }
      });
      //enable save
      child->m_box_buttons->m_ok->setEnabled(success);
      child->base->is_modified = success;
      child->m_box_list_items->update_items(lines.operator->());
      /**/
      if (success)
      {
         child->m_box_buttons->m_ok->setFocus();
      }
   }
   //-----------------------------------------------------------------------------------------------//
   box_editions *  box_editions::set_enable_editions(bool const & enabled)
   {
      std::for_each(m_edit_queue.begin(), m_edit_queue.end(), [&](std::lineedit * e)
      {
         e->setEnabled(enabled);
      });
      /**/
      if (enabled)
      {
         std::for_each(m_edit_queue.begin(), m_edit_queue.end(), [&](std::lineedit * e)
         {
            e->setFocus();
            return;
         });
      }
      return this;
   }
   //-----------------------------------------------------------------------------------------------//
   box_editions *  box_editions::set_clear_editions()
   {
      std::for_each(m_edit_queue.begin(), m_edit_queue.end(), [&](std::lineedit * e)
      {
         e->setText(std::unicodestring{ });
      });
      return this;
   }
}