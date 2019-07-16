//-----------------------------------------------------------------------------------------------//
// xbw32 for Windows (generate of numeric combinations for bingo or lotery) (generate of numeric combinations for bingo or lotery)
//
// Created by wilsonsouza 2012, 2013, 2014, 2015, 2016, 2017, 2018
// For Olavo Co.
//
// WR Devinfo
// (c) 2012, 2014, 2015, 2018
// update of qt 5.01 to 5.11
//-----------------------------------------------------------------------------------------------//
#pragma once
#include <bb.defs.hpp>

namespace bb
{
   //std::multimap<group_name, std::multimap<page_id, std::multimap<numbers_id, availables_total>>>
   //

   struct available_numbers_controller : public std::multimap<int, int>
   {
      using pointer = std::shared_ptr<available_numbers_controller>;
      using available_numbers_type = std::multimap<int, int>;
      std::unicodestring group_id{};
      /**/
      available_numbers_controller(std::unicodestring const & group_id) :
         available_numbers_type{}
      {
         this->group_id = group_id;
      }
      value_type const & lookup(int const key)
      {
         return *find(key);
      }
      friend bool operator<(value_type const & left, value_type const & right)
      {
         return (left.first < right.first);
      }
      available_numbers_controller *  update(value_type const & value_pair)
      {
         auto founded = find(value_pair.first);
         //
         if (founded != end())
         {
            founded->second = std::move(value_pair.second);
         }
         return this;
      }
   };
   struct pages_controller;
   using groups_controller_queue = std::list<pages_controller *>;
   struct groups_controller : public groups_controller_queue, public task_group
   {
      using pointer = std::shared_ptr<groups_controller>;
      std::shared_ptr<available_numbers_controller> availables_queue{ nullptr };
      std::unicodestring group_id{};

      explicit groups_controller(std::unicodestring const & group_id);
      virtual ~groups_controller();
      virtual groups_controller::pointer clone();
      virtual pages_controller * search_page(int const page);
      virtual void  insert(pages_controller const * pages, int value);
      virtual bool  is_available(int value);
      virtual void   create_availables(int begin, int max);
   };
}