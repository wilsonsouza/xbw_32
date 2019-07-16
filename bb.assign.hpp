//-----------------------------------------------------------------------------------------------//
// xbw32 for Windows (generate of numeric combinations for bingo or lotery) 
//
// Created by wilsonsouza 2012, 2013, 2014, 2015, 2016, 2017, 2018
// For Olavo Co.
//
// WR Devinfo
// (c) 2012, 2013, 2014, 2015, 2016, 2017, 2018
// update of qt 5.01 to 5.11
//-----------------------------------------------------------------------------------------------//
#include <bb.defs.hpp>
#include <std.widget.hpp>
#include <sql.table.hpp>
#include <sql.query.hpp>
/**/
namespace bb
{
   class assign : public QWidget, public std::multimap<std::unicodestring, std::widget *>
   {
   protected:
      struct compare_key
      {
         std::unicodestring key{};
         bool operator()(std::unicodestring const & key_name)
         {
            return (key == key_name);
         }
      };
      /**/
   public:
      using pointer = std::shared_ptr<assign>;
      /**/
   public:
      explicit assign(std::sql::table::pointer const & table, QWidget * owner);
      template<bool enabled> void update();
      template<bool enabled> void set_enabled();
      bool operator()(std::unicodestring const & key);
      /**/
   protected:
      std::sql::table::pointer m_table{ nullptr };
   };
}