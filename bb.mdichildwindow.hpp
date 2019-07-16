//-----------------------------------------------------------------------------------------------//
// xbw32 for Windows (generate of numeric combinations for bingo or lotery)
//
// Created by wilsonsouza 2013, 2018
//
// WR Devinfo
// (c) 2012, 2013, 2014, 2015, 2016, 2017, 2018
//-----------------------------------------------------------------------------------------------//
#pragma once
#include <std.mdiframewindow.hpp>
#include <std.mdichildwindow.hpp>
#include <bb.group_manager.hpp>
#include <bb.table_interface.hpp>
/**/
namespace std
{
   class lcdnumber;
   class treewidget;
   class button;
   class checkbox;
   class vertical_box;
   class horizontal_box;
   class display_progressbar;/*display_progress_bar*/
};
/**/
namespace bb
{
   namespace captions
   {
      struct internal_editions
      {
         std::unicodestring const NUMBERS{ "IDD_NUMBERS_%1" };
         std::unicodestring const LCD{ "IDD_LCD_%1" };
         std::unicodestring const GROUPNAME{ "IDD_GROUPNAME" };
         std::unicodestring const PAGENAME{ "IDD_PAGENAME" };
         internal_editions() = default;
      };
      /**/
   }
   /**/
   enum IDD : uint
   {
      IDD_MDIFRAMEWINDOW,
      IDD_LOCALTECONTROL,
      IDD_DISPLAYPROGRESSBAR,
      IDD_DATAQUEUE,
      IDD_TREELISTGROUPS,
      IDD_TREELISTRESULT,
      IDD_VBOXLEFT,
      IDD_VBOXRIGHT,
      IDD_BUTTONSBOX,
      IDD_EDITIONSBOX,
      IDD_INFORMATIONBOX,
      IDD_LISTITEMSBOX,
      IDD_NUMBERSBOX,
      IDD_SEARCHBOX,
      IDD_SELECTGROUPPAGEBOX,
      IDD_PAGENUMBERSBOX,
      IDD_CURRENTTABLEWIDGETITEM
   };
   //
   class mdiframewindow;
   class box_buttons;
   class box_editions;
   class box_information;
   class box_list_items;
   class box_numbers;
   class box_page_numbers;
   class box_print_preview;
   class box_search;
   class box_select_group_page;
   class mdichildwindow : public std::mdichildwindow, public group_manager
   {
      //Q_OBJECT
   public:
      explicit mdichildwindow(bb::mdiframewindow * frame,
                                     bb::group_manager::pointer const & manager,
                                     std::unicodestring const & caption);
      virtual ~mdichildwindow() override;
      virtual bool create(std::mdichildwindow * child) override;

      virtual std::shared_ptr<table_numbers> get_field_editions(std::unicodestring const & prefix_name);
      virtual std::shared_ptr<table_resources> update_table_resource_on_memory(std::unicodestring const & group);
      virtual void const rescue_page();
      virtual void const put_selected_on_editions();
      //
      std::shared_ptr<table_numbers> load_record(std::unicodestring const & group, int const & page);
      //
      virtual void  set_current_table_item_value(std::unicodestring const & value, QTableWidget * tbl);
      //
      virtual bool  connect_actions_when_activated_window();
      virtual bool  disconnect_actions_when_deactivated_window();
      /**/
      virtual std::display_progressbar::pointer create_display_progressbar();
      /**/
   public:
      bool is_modified{ false };
      std::treewidget * m_list_groups{ nullptr };
      std::treewidget * m_list_result{ nullptr };
      std::vertical_box * m_vbox_l{ nullptr };
      std::vertical_box * m_vbox_r{ nullptr };
      bb::box_buttons * m_box_buttons{ nullptr };
      bb::box_editions * m_box_editions{ nullptr };
      bb::box_information * m_box_information{ nullptr };
      bb::box_list_items * m_box_list_items{ nullptr };
      bb::box_numbers * m_box_numbers{ nullptr };
      bb::box_page_numbers * m_box_page_numbers{ nullptr };
      bb::box_search * m_box_search{ nullptr };
      bb::box_select_group_page * m_box_select_group_page{ nullptr };
      QTableWidgetItem * m_current_table_widget_item{ nullptr };
   };
}