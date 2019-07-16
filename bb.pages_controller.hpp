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
#include <bb.defs.hpp>

namespace bb
{
   /* struct controller_pages: public std::list<std::pair<int, int>>, public task_group{}*/
   /* struct interface_controller_pages{}*/
   /* struct abstract_controller_pages{}*/
   /* class multiple_document_interface_child_window{}*/
   using pages_controller_queue = std::set<int>;
   using pages_controller_to_stringlist_pointer = std::shared_ptr<std::stringlist>;
   struct pages_controller: public pages_controller_queue, public task_group
   {
      using pointer = std::shared_ptr<pages_controller_queue>;

      explicit pages_controller ( );
      explicit pages_controller ( pages_controller const & page );
      explicit pages_controller ( int const & page_id );
      virtual ~pages_controller ( );
      virtual pointer  clone(int const & page_id = 0);
      virtual bool  search_number(int const & page_id);
      virtual void  sort();
      virtual pages_controller_to_stringlist_pointer to_stringlist() noexcept; /*to_string_list*/
      /**/
      int page_id{ 0 };
   };
}