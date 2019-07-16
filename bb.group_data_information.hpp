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
   struct group_list_information
   {
      int availables{ 0 };
      std::unicodestring group_id{};
      group_list_information() = default;
   };
   //
   struct group_data_information_interface
   {
      int pages_to_group{ 0 };
      int numbers_to_group{ 0 };
      int numbers_to_page{ 0 };
      int numbers{ 0 };
      char group_id{ Qt::Key_A };
      char last_group_id{ Qt::Key_Z };
      bool is_count_to_zero{ false };
      bool is_create_all_groups{ true };
      bool is_completed{ false };
      std::unicodestring catalog_name{};
      std::unicodestring table_name{};
      bool is_modified{ false };
      std::unicodestring title_group{};
      int interval_groups{ 1 };
      //
      group_data_information_interface() : 
         title_group{ std::unicodestring{ "%1 à %2" }.bind(group_id, last_group_id) }
      {
      }
   };
   //
   struct group_data_information: public group_data_information_interface
   {
      group_data_information() = default;
      virtual ~group_data_information() = default;
      virtual int calculate()
      {
         return(calcule_letters(), interval_groups * pages_to_group * numbers_to_page);
      }
      virtual void calcule_letters()
      {
         interval_groups = ((last_group_id - group_id) == 0 ? 1 : last_group_id - group_id);
      }
   };
}

