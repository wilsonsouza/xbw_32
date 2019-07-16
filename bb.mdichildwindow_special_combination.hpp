//-----------------------------------------------------------------------------------------------//
// xbw32 for Windows (generate of numeric combinations for bingo or lotery)
//
// Created by wilsonsouza 2013, 2018
//
// WR Devinfo
// (c) 2012, 2013, 2014, 2015, 2016, 2017, 2018
//-----------------------------------------------------------------------------------------------//
#pragma once
#include <std.tabbed.hpp>
#include <std.table.hpp>
#include <bb.mdichildwindow.hpp>
/**/
namespace bb
{
   enum class interface_messages : uint
   {
      ON_UPDATE_LISTVIEW,
      ON_WRITE_DATA_ON_DATABASE,
      ON_UPDATE_LISTVIEW_ROWS
   };
   /**/
   class group_manager;
   class mdiframewindow;
   class spreadsheet_advanced;
   class spreadsheet_delete;
   class spreadsheet_edit_finder;
   class spreadsheet_view;
   class spreadsheet_initialize_distribution;
   class spreadsheet_insert;
   class spreadsheet_insert_by;
   class spreadsheet_manual_insert;
   class spreadsheet_select_other_group;
   class spreadsheet_box_entry_numbers;
   class mdichildwindow_special_combination : public mdichildwindow
   {
      //Q_OBJECT
   public:
      explicit mdichildwindow_special_combination(bb::mdiframewindow * child,
                                                  bb::group_manager::pointer const & manager,
                                                  std::unicodestring const & caption);
      virtual ~mdichildwindow_special_combination() override = default;
      virtual bool create(std::mdichildwindow * child) override;
      virtual void const  set_default_table_width_height(std::table * tbl);
      virtual std::shared_ptr<table_numbers> get_field_editions(std::unicodestring const & prefix_name) override;
      //DECLARE_OPERATOR(mdichildwindow_special_combination);
   protected:
      virtual bool  connect_actions_when_activated_window() override;
      virtual bool  disconnect_actions_when_deactivated_window() override;

   private:
      //events
      void on_delete(bool enabled = true);
      void on_save(bool enabled = true);
      void on_refresh(bool enabled = true);
      void on_timer(std::mdichildwindow * child, unsigned int id, void const * data = nullptr);

   public:
      std::tabbed * m_tabbed_view{ nullptr };
      std::tabbed * m_tabbed_action{ nullptr };
      bb::spreadsheet_advanced * m_advanced{ nullptr };
      bb::spreadsheet_delete * m_delete{ nullptr };
      bb::spreadsheet_edit_finder * m_edit_finder{ nullptr };
      bb::spreadsheet_view * m_view{ nullptr };
      bb::spreadsheet_initialize_distribution * m_initialize_distribution{ nullptr };
      bb::spreadsheet_insert * m_insert{ nullptr };
      bb::spreadsheet_insert_by * m_insert_by{ nullptr };
      bb::spreadsheet_manual_insert * m_manual_insert{ nullptr };
      bb::spreadsheet_select_other_group * m_select_other_group{ nullptr };
      int m_table_width{ 0 };
      bb::spreadsheet_box_entry_numbers * m_entry_numbers{ nullptr };
   };
}
