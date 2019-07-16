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

namespace bb
{
   class spreadsheet_edit_finder;
   struct lookup_list;
   struct groups_controller;
   struct pages_controller;
   class spreadsheet_edit_finder_numbers : public QObject
   {
   public:
      spreadsheet_edit_finder_numbers(bb::spreadsheet_edit_finder * edit_finder);
      virtual ~spreadsheet_edit_finder_numbers() override = default;
      virtual spreadsheet_edit_finder_numbers * create();
      //
      //DECLARE_OPERATOR(spreadsheet_edit_finder_numbers);
   protected:
      void prepare_groups_controller();
      void prepare_pages_controller();
      void get_pages_controller_numbers();
      void is_not_partial_finder();
      void is_partial_finder();
      void update_display_progressbar(std::shared_ptr<std::display_progressbar> const & display);
      //
   protected:
      std::shared_ptr<std::stringlist> m_list{ new std::stringlist{} };
      std::shared_ptr<bb::lookup_list> m_lookup{ nullptr };
      bb::groups_controller * m_groups{ nullptr };
      bb::pages_controller * m_pages{ nullptr };
      std::shared_ptr<std::stringlist> m_integer_list_to_stringlist{ new std::stringlist{} };
      bb::spreadsheet_edit_finder * m_edit_finder{ nullptr };
   };
}