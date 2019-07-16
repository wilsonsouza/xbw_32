//-----------------------------------------------------------------------------------------------//
// xbw32 for Windows (generate of numeric combinations for bingo or lotery)
//
// Created by wilsonsouza 2013, 2014, 2015, 2016, 2017, 2018
//
// WR Devinfo
// (c) 2012, 2013, 2014, 2015, 2016, 2017, 2018, 2016, 2017, 2018
//-----------------------------------------------------------------------------------------------//
#include <bb.table_interface.hpp>
#include <bb.mdichildwindow.hpp>
#include <sql.table.hpp>
#include <sql.query.hpp>

namespace bb
{
   table_resources::table_resources(mdichildwindow * frame) : table_interface{ frame }
   {
      m_table_id = TABLE_ID::RESOURCES;
   }
   //-----------------------------------------------------------------------------------------------//
   table_interface & table_resources::write(std::unicodestring const & group, int const & page)
   {
      return *this;
   }
   //-----------------------------------------------------------------------------------------------//
   table_interface & table_resources::read(std::unicodestring const & group, int const & page)
   {
      return *this;
   }
   //-----------------------------------------------------------------------------------------------//
   table_interface & table_resources::erase(std::unicodestring const & group, int const & page, int const & number)
   {
      return *this;
   }
   //-----------------------------------------------------------------------------------------------//
   table_interface & table_resources::lookup(std::unicodestring const & group, int const & page, int const & number)
   {
      return *this;
   }
   //-----------------------------------------------------------------------------------------------//
   table_interface & table_resources::update(std::unicodestring const & group, int const & page, int const & number)
   {
      return *this;
   }
   //-----------------------------------------------------------------------------------------------//
   std::unicodestring table_resources::prepare_query(table_interface::MODE const & mode,
                                                   std::unicodestring const & group,
                                                   int const & page,
                                                   int const & number)
   {
      return std::unicodestring{};
   }
}