//-----------------------------------------------------------------------------------------------//
// xbw32 for Windows (generate of numeric combinations for bingo or lotery)
//
// Created by wilsonsouza 2013, 2018
//
// WR Devinfo
// (c) 2012, 2013, 2014, 2015, 2016, 2017, 2018
//-----------------------------------------------------------------------------------------------//
#include <std.checkbox.hpp>
#include <std.display_progressbar.hpp>
#include <std.lineedit.hpp>
#include <std.waitcursor.hpp>
#include <bb.data_queue_controller.hpp>
#include <bb.groups_controller.hpp>
#include <bb.pages_controller.hpp>
#include <bb.lookup_numbers.hpp>
#include <bb.lookup_list.hpp>
#include <bb.spreadsheet_edit_finder.hpp>
#include <bb.data_queue_controller.hpp>
#include <bb.spreadsheet_edit_finder.hpp>
#include <bb.spreadsheet_edit_finder_numbers.hpp>
#include <bb.mdichildwindow.hpp>
#include <bb.mdichildwindow_special_combination.hpp>

namespace bb
{
   //-----------------------------------------------------------------------------------------------//
   spreadsheet_edit_finder_numbers::spreadsheet_edit_finder_numbers(spreadsheet_edit_finder * edit_finder) :
      m_edit_finder{ edit_finder }
   {
      m_lookup = std::shared_ptr<bb::lookup_list>(new bb::lookup_list{});
   }
   //-----------------------------------------------------------------------------------------------//
   spreadsheet_edit_finder_numbers * spreadsheet_edit_finder_numbers::create()
   {
      try
      {
         if (m_edit_finder->m_what_finder->text().indexOf(",") == -1)
         {
            m_list->append(m_edit_finder->m_what_finder->text());
         }
         else
         {
            m_list->append(m_edit_finder->m_what_finder->text().split(","));
         }
         //start process
         prepare_groups_controller();
         //fill table
         m_edit_finder->fill_table(m_lookup);
      }
      catch (...)
      {
         QMessageBox::warning(nullptr, std::captions::errors{}.CRITICAL, "INTERNAL ERROR DETECTED!");
      }
      return this;
   }
   //-----------------------------------------------------------------------------------------------//
   void spreadsheet_edit_finder_numbers::prepare_groups_controller()
   {
      std::shared_ptr<std::display_progressbar> pDisplay
      {
         new std::display_progressbar
         {
            m_edit_finder->m_child->get_frame(), m_edit_finder->m_child
         }
      };
      /**/
      auto pWait(new std::waitcursor{ m_edit_finder });
      //
      pDisplay->create(m_edit_finder->m_child->groups->size(), "Aguarde, pesquisando...");
      //
      auto & d = m_edit_finder->m_child->groups;
      /**/
      std::for_each(d->begin(), d->end(), [&](controller::groups const & p)
      {
         //this->groups = p.second;
         update_display_progressbar(pDisplay);
         prepare_pages_controller();

      });
   }
   //-----------------------------------------------------------------------------------------------//
   void spreadsheet_edit_finder_numbers::prepare_pages_controller()
   {
      std::for_each(m_groups->begin(), m_groups->end(), [&](pages_controller * p)
      {
         m_pages = p;
         get_pages_controller_numbers();
      });
   }
   //-----------------------------------------------------------------------------------------------//
   void spreadsheet_edit_finder_numbers::get_pages_controller_numbers()
   {
      //clear to fill
      m_integer_list_to_stringlist->clear();
      //fill again
      std::for_each(m_pages->begin(), m_pages->end(), [&](int n)
      {
         m_integer_list_to_stringlist->push_back(std::unicodestring{ "%1" }.arg(n));
      });
      /**/
      is_not_partial_finder();
      is_partial_finder();
   }
   //-----------------------------------------------------------------------------------------------//
   void spreadsheet_edit_finder_numbers::is_not_partial_finder()
   {
      if (!m_edit_finder->m_is_partial_finder->isChecked())
      {
         auto int_to_string = m_integer_list_to_stringlist->join(",");
         auto result_list = m_list->join(",");
         //
         if (result_list.compare(int_to_string) == 0)
         {
            m_lookup->push_back(new bb::lookup_numbers(m_pages, m_groups->group_id));
         }
      }
   }
   //-----------------------------------------------------------------------------------------------//
   void spreadsheet_edit_finder_numbers::is_partial_finder()
   {
      if (m_edit_finder->m_is_partial_finder->isChecked())
      {
         std::for_each(m_list->begin(), m_list->end(), [&](std::unicodestring n)
         {
            if (m_integer_list_to_stringlist->indexOf(n) != -1)
            {
               m_lookup->push_back(new bb::lookup_numbers(m_pages, m_groups->group_id));
            }
         });
      }
   }
   //-----------------------------------------------------------------------------------------------//
   void spreadsheet_edit_finder_numbers::update_display_progressbar(
      std::shared_ptr<std::display_progressbar> const & display)
   {
      display->update(std::unicodestring{ "Aguarde, total %1 de registros encontrados" }.
                       arg(m_lookup->size()));
      display->get_sub_caption()->setText(std::unicodestring{ "Pesquisando grupo %1" }.
                                           arg(m_groups->group_id));
   }
   //-----------------------------------------------------------------------------------------------//
}