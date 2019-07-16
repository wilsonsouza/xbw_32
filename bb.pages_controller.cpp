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
#include <bb.pages_controller.hpp>
//-----------------------------------------------------------------------------------------------//
namespace bb
{
   pages_controller::pages_controller() : std::set<value_type>{}, task_group{}, m_page{ -1 }
   {
   }
   //-----------------------------------------------------------------------------------------------//
   pages_controller::pages_controller(pages_controller const & page) :
      std::set<int>{},
      task_group{},
      m_page{ page.m_page }
   {
      clear();
      swap(const_cast<pages_controller &>(page));
   }
   //-----------------------------------------------------------------------------------------------//
   pages_controller::pages_controller(int const & page_id) :
      std::set<value_type>{},
      task_group{},
      m_page{ page_id }
   {
   }
   //-----------------------------------------------------------------------------------------------//
   pages_controller::~pages_controller()
   {
      clear();
      cancel();
   }
   //-----------------------------------------------------------------------------------------------//
   pages_controller::pointer  pages_controller::clone(int const & page_id)
   {
      return pointer{ new pages_controller{page_id} };
   }
   //-----------------------------------------------------------------------------------------------//
   bool  pages_controller::search_number(int const & page_id)
   {
      auto success = false;
      /* run pplx */
      run_and_wait([&]
      {
         success = std::find_if(begin(), end(), [&](auto const & page)
         {
            return(page == page_id);
         }) != end() ? true : false;
      });
      return success;
   }
   //-----------------------------------------------------------------------------------------------//
   void  pages_controller::sort()
   {
   }
   //-----------------------------------------------------------------------------------------------//
   pages_controller_to_stringlist_pointer  pages_controller::to_stringlist() noexcept
   {
      auto queue = pages_controller_to_stringlist_pointer{ new std::stringlist { } };
      /**/
      std::static_exception(queue == nullptr, "Falha na alocão de memoria!");
      run_and_wait([&]
      {
         auto image = pages_controller_queue{};
         /**/
         std::for_each(begin(), end(), [&](auto const & page)
         {
            queue->push_back(std::unicodestring{ "%1" }.bind(page));
         });
      });
         return queue;
   }
}