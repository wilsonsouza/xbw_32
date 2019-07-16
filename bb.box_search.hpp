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
#include <bb.table_interface.hpp>
/***/
namespace std
{
   class Q_DECL_EXPORT button;
   class Q_DECL_EXPORT lineedit;
   class Q_DECL_EXPORT treewidget;
   class Q_DECL_EXPORT label;
   class Q_DECL_EXPORT radiobutton;
}
//
namespace bb
{
   class mdichildwindow;
   class box_search: public std::tabbed
   {
      //Q_OBJECT
   public:
      explicit box_search(bb::mdichildwindow * child);
      virtual box_search *  create();
      /**/
      bool on_search();
      void append_items_on_search_result(std::vector<controller::groups> const & groups);
      //DECLARE_OPERATOR(box_search);
      std::widget_impl<std::horizontal_box> * m_hbox{ nullptr };
      std::button * m_ok{ nullptr };
      std::button * m_cancel{ nullptr };
      std::button * m_help{ nullptr };
      std::lineedit * m_what_find{ nullptr };
      std::widget_impl<std::vertical_box> * m_vbox{ nullptr };
      std::treewidget * m_search_result{ nullptr };
      std::widget_impl<std::vertical_box> * m_vbox_search_result{ nullptr };
      std::label * m_information{ nullptr };
      std::radiobutton * m_is_group{ nullptr };
      std::radiobutton * m_is_page{ nullptr };
      std::radiobutton * m_is_sequence_numbers{ nullptr };
      std::radiobutton * m_is_only_complete_pages{ nullptr };
      std::radiobutton * m_is_only_incomplete_pages{ nullptr };
      std::radiobutton * m_is_only_duplicate_pages_group{ nullptr };
      std::radiobutton * m_is_all_duplicate_pages{ nullptr };
      std::radiobutton * m_is_partial_sequence_numbers{ nullptr };
      /**/
      enum class OPTIONS: uint
      {
         IDD_GROUP,
         IDD_PAGE,
         IDD_SEQUENCE_NUMBERS,
         IDD_ONLY_COMPLETE_PAGES,
         IDD_PARTIAL_SEQUENCE_NUMBERS,
         IDD_ONLY_INCOMPLETE_PAGES,
         IDD_ONLY_DUPLICATES_PAGES_ON_GROUP,
         IDD_ALL_DUPLICATES_PAGES
      };
      /**/
      OPTIONS m_search_options{ OPTIONS::IDD_GROUP };
      uint m_counter_rows{ 0 };
      /**/
   protected:
      bb::mdichildwindow * m_child{ nullptr };
   };
}