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
#pragma once
#include <bb.pages_controller.hpp>
#include <bb.groups_controller.hpp>
//-----------------------------------------------------------------------------------------------//
namespace bb
{
   groups_controller::groups_controller(std::unicodestring const & group_id) :
      groups_controller_queue{},
      task_group{},
      m_group{ group_id },
      m_availables_queue{ new available_numbers_controller{m_group} }
   {
   }
   //-----------------------------------------------------------------------------------------------//
   groups_controller::~groups_controller()
   {
      /* clear internal list */
      clear();
      /* emit cancel all task in running */
      cancel();
   }
   //-----------------------------------------------------------------------------------------------//
   groups_controller::pointer  groups_controller::clone()
   {
      return pointer{ new groups_controller{m_group} };
   }
   //-----------------------------------------------------------------------------------------------//
   pages_controller *  groups_controller::search_page(int const page)
   {
      auto out_value = nullptr;
      /**/
      run_and_wait([&]
      {
         std::find_if(begin(), end(), [&](auto const & pages)->auto
         {
            if (pages->m_page == page)
            {
               out_value = pages;
            }
            return out_value != nullptr;
         });
      });
      return out_value;
   }
   //-----------------------------------------------------------------------------------------------//
   void  groups_controller::insert(pages_controller const * page, int value)
   {
      auto available = m_availables_queue->lookup(value);
      //
      std::static_exception(page->search_number(value),
                            std::unicodestring{ "Número %1 já existe nesta cartela!" }.bind(value));
      /**/
      std::static_exception(available.second == 0,
                            std::unicodestring{ "Número %1 com quantidade esgotada, quantidade %2 disponível!" }.
                            bind(available.first).bind(available.second));
      /**/
      page->emplace(std::make_pair(available.first, --available.second));
      m_availables_queue->update(available);
   }
   //-----------------------------------------------------------------------------------------------//
   bool  groups_controller::is_available(int const value)
   {
      return m_availables_queue->lookup(value).second > 0;
   }
   //-----------------------------------------------------------------------------------------------//
   void  groups_controller::create_availables(int begin, int max)
   {
      std::for_integral_positive(begin, max, [&](auto const & value)
      {
         m_availables_queue->emplace(std::make_pair(value, max));
      });
   }
}