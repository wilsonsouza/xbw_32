//-----------------------------------------------------------------------------------------------//
// xbw32 for Windows (generate of numeric combinations for bingo or lotery)
//
// Created by wilsonsouza 2013, 2018
//
// WR Devinfo
// (c) 2012, 2013, 2014, 2015, 2016, 2017, 2018
//-----------------------------------------------------------------------------------------------//
#pragma once
#include <bb.defs.hpp>
#include <std.tabbed.hpp>
#include <std.widget_impl.hpp>
/**/
namespace std
{
   class Q_DECL_EXPORT lcdnumber;
}
//
namespace bb
{
   struct property_numbers_box : public std::multimap<int, std::lcdnumber *>
   {
      using pointer = std::shared_ptr<property_numbers_box>;
      int number{ -1 };
      std::lcdnumber * current{ nullptr };
      property_numbers_box() = default;
      /**/
      static property_numbers_box::pointer alloc_data()
      {
         return pointer{ new property_numbers_box{} };
      }
   };
   /**/
   class mdichildwindow;
   class box_numbers : public std::tabbed
   {
      //Q_OBJECT
   public:
      explicit box_numbers(bb::mdichildwindow * child);
      box_numbers *  create();
      virtual void update_lcdnumber_available(int const & value);
      virtual void update_lcdnumber_all(std::unicodestring const & group_id);
      virtual std::lcdnumber * get_lcdnumber_by_id(int value);
      virtual void update_lcdnumbers(std::stringlist const * list_ptr);
      //
   public:
      std::lcdnumber * m_current_lcdnumber{ nullptr };
      std::widget_impl<std::vertical_box> * m_vbox{ nullptr };
      int m_total{ 0 };
      property_numbers_box::pointer m_numbers_queue{ nullptr };
      /**/
   protected:
      bb::mdichildwindow * m_child{ nullptr };
   };
}