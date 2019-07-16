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
#include <std.table.hpp>
#include <bb.group_manager.hpp>
/**/
namespace bb
{
   class mdichildwindow_special_combination;
   class spreadsheet_view : public std::widget_impl<std::vertical_box>
   {
      //Q_OBJECT
   public:
      explicit spreadsheet_view(bb::mdichildwindow_special_combination * child);
      virtual ~spreadsheet_view() override = default;
      //
      virtual QWidget * create() override;
      virtual void  create_rows();
      virtual void  create_columns();
      virtual void  update_data_queue();
      virtual __declspec(safebuffers) void  load_data_queue();
      virtual void  update_numbers_on_pages();
      virtual void  update_listview(std::unicodestring const & group_id);
      virtual void  empty_cells();
      virtual bool  validity_cell_value(QTableWidgetItem const * item);
      virtual QTableWidgetItem *  get_vertical_header_value();
      virtual void  remove_current_item();
      virtual void  set_active_group(std::unicodestring const & group);
      /* get handles*/
   public:
      std::table * m_table_pages{ nullptr };
      //
   protected:
      bb::mdichildwindow_special_combination * m_child{ nullptr };
   };
}
