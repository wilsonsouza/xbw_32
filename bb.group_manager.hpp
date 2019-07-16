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
//-----------------------------------------------------------------------------------------------//
namespace bb
{
   namespace controller
   {
      struct available_numbers
      {
         int number_id{ 0 };
         int availables{ 0 };
         int useds{ 0 };
         bool operator()(available_numbers const & available_id)
         {
            return available_id.number_id == number_id;
         }
      };
      //
      struct page_numbers
      {
         int number_id{ 0 };
         bool is_deleted{ false };
         bool operator()(page_numbers const & value_id)
         {
            return number_id == value_id.number_id;
         }
      };
      //
      struct pages
      {
         int page_id{ 0 };
         bool is_deleted{ false };
         bool is_completed{ false };
         std::vector<page_numbers> numbers{};
         /**/
         std::shared_ptr<std::stringlist> numbers_to_stringlist() const
         {
            auto queue = std::stringlist{};
            std::for_each(numbers.begin(), numbers.end(), [&](controller::page_numbers const & value)
            {
               queue.push_back(std::unicodestring{ "%1" }.bind(value.number_id));
            });
            return std::make_shared<std::stringlist>(queue);
         }
         bool operator()(pages const & page)
         {
            return page.page_id == page_id;
         }
      };
      //
      struct groups
      {
         std::unicodestring group_id{};
         std::vector<pages> pages{};
         std::vector<available_numbers> availables{};
         /**/
         bool operator()(groups const & group)
         {
            return group.group_id.compare(group_id);
         }
         int calculate_available_numbers() const
         {
            auto sum = 0;
            std::for_each(availables.begin(), availables.end(), [&](available_numbers const & value)
            {
               sum += value.availables;
            });
            return sum;
         }
      };
      //
      struct base_impl
      {
         using pointer = std::shared_ptr<base_impl>;
         /**/
         defs::db::datasource::table_information::pointer information{};
         defs::db::datasource::table_resources::pointer resources{};
         defs::db::datasource::table_numbers::pointer numbers{};
         defs::db::datasource::table_controller::pointer controller{};
         char last_group_id{ Qt::Key_Z };
         std::unicodestring catalog_name{};
         std::unicodestring table_name{};
         bool is_modified{ false };
         std::unicodestring title_group{};
         int interval_groups{ 1 };
         uint groups_sum{ 0 };
         uint pages_sum{ 0 };
         //
         base_impl() :
            information{ new defs::db::datasource::table_information{} },
            resources{ new defs::db::datasource::table_resources{} },
            numbers{ new defs::db::datasource::table_numbers{} },
            controller{ new defs::db::datasource::table_controller{} },
            title_group{ std::unicodestring{ "%1 à %2" }.bind(information->groups_id, last_group_id) }
         {
         }
         void calculate_letters()
         {
            interval_groups = ((last_group_id - information->groups_id) == 0 ? 1 :
                               last_group_id - information->groups_id);
         }
         uint calculate()
         {
            title_group = std::unicodestring{ "%1 à %2" }.bind(information->groups_id, last_group_id);
            calculate_letters();
            groups_sum = (interval_groups * information->pages_to_group);
            pages_sum = groups_sum * information->pages_to_group;
            return(interval_groups * information->pages_to_group * information->numbers_to_page);
         }
         void set_group_name(std::unicodestring const & group_name)
         {
            information->group_name = group_name;
            resources->group_name = group_name;
            numbers->group_name = group_name;
            resources->group_name = group_name;
         }
      };
   }
   //
   struct group_manager
   {
      using pointer = std::shared_ptr<group_manager>;
      /**/
      std::unicodestring actived_group_id{};
      int actived_page_id{ -1 };
      std::shared_ptr<std::vector<controller::groups>> groups{ new std::vector<controller::groups>{} };
      controller::base_impl::pointer base{ new controller::base_impl{} };
      //
      group_manager() = default;
      explicit group_manager(group_manager::pointer const & in)
      {
         copy(in);
      }
      group_manager & copy(group_manager::pointer const & in)
      {
         groups->swap(*const_cast<group_manager::pointer &>(in)->groups);
         std::swap(base, in->base);
         actived_group_id = in->actived_group_id;
         actived_page_id = in->actived_page_id;
         return *this;
      }
      group_manager::pointer clone()
      {
         return std::make_shared<group_manager>(*this);
      }
   };
}