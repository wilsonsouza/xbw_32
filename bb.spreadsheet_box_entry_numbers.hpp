//-----------------------------------------------------------------------------------------------//
// xbw32 for Windows (generate of numeric combinations for bingo or lotery)
//
// Created by wilsonsouza 2013, 2018
//
// WR Devinfo
// (c) 2012, 2013, 2014, 2015, 2016, 2017, 2018
//-----------------------------------------------------------------------------------------------//
#pragma once
#include <std.widget.hpp>
#include <std.layouts.hpp>
#include <std.lineedit.hpp>
#include <std.button.hpp>
/**/
namespace bb
{
   class mdichildwindow_special_combination;
   struct controller::pages;
   class spreadsheet_box_entry_numbers : public std::widget_impl<std::vertical_box>
   {
      //Q_OBJECT
   public:
      spreadsheet_box_entry_numbers(mdichildwindow_special_combination * child);
      virtual ~spreadsheet_box_entry_numbers() override = default;
      /**/
      virtual QWidget * create() override;
      virtual std::vector<int> get_numbers();
      virtual bool on_validate(std::lineedit * page, int value_id);
      virtual bool on_get_data_edit_list();
      void clear_edit_list();
      void enable_edit_list(bool const & value = true);
      void add_numbers_on_data_grid_impl(std::shared_ptr<std::vector<std::lineedit *>> const & list_ptr);
      void delete_numbers_on_data_grid_impl(std::shared_ptr<std::vector<std::lineedit *>> const & list_ptr);
      void put_numbers_for_edition(std::vector<bb::controller::pages> & pages);
      //DECLARE_OPERATOR(spreadsheet_box_entry_numbers);
   protected:
      std::lineedit * m_page{ nullptr };
      std::button * m_ok{ nullptr };
      std::button * m_cancel{ nullptr };
      std::shared_ptr<std::vector<std::lineedit *>> m_data_list{ new std::vector<std::lineedit *>{} };
      bb::mdichildwindow_special_combination * m_child{ nullptr };
   };
}
