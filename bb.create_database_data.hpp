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
#include <std.waitcursor.hpp>
#include <std.display_progressbar.hpp>
//-----------------------------------------------------------------------------------------------//
namespace bb
{
   class mdiframewindow;
   class create_database_data : public std::display_progressbar
   {
   public:
      using pointer = std::shared_ptr<create_database_data>;
      /**/
   public:
      explicit create_database_data(bb::mdiframewindow * frame);
      virtual ~create_database_data();
      virtual bool const create(bool const & );
      virtual bool const update_tables();
      virtual void drop_database(std::unicodestring const & catalog_name);
      virtual void update_information_table();
      virtual void update_resources_table(std::unicodestring const & group);
      virtual void update_controller_table(std::unicodestring const & group);
      virtual void update_numbers_table(std::unicodestring const & group);
      virtual void process();
      /**/
   protected:
      std::shared_ptr<std::waitcursor> m_wait_cursor{ nullptr };
      bb::mdiframewindow * m_frame{ nullptr };
   };
}
//-----------------------------------------------------------------------------------------------//
