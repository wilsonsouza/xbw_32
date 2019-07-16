//-----------------------------------------------------------------------------------------------//
// xbw32 for Windows (generate of numeric combinations for bingo or lotery)
//
// Created by wilsonsouza 2013, 2018
//
// WR Devinfo
// (c) 2013
//-----------------------------------------------------------------------------------------------//
#pragma once
#include <bb.defs.hpp>
#include <std.dialog.hpp>
//-----------------------------------------------------------------------------------------------//
namespace std
{
   class display_progressbar;
   class treewidget;
   class vertical_box;
   template <typename = vertical_box> class groupbox_impl;
};

namespace bb
{
   class group_manager;
   class mdiframewindow;
   class group_data_information;
   class dialog_open_list_papers : public std::dialog
   {
      //Q_OBJECT
   public:
      dialog_open_list_papers(QWidget * parent);
      virtual ~dialog_open_list_papers() override = default;
      virtual bool create(std::dialog * dlg) override;
      /**/
      void const load_catalogs(std::treewidget * tree);
      void const load_datasource();

      QWidget *  create_box_datainfo();
      void const set_disable_all_defined_controls();
      //
      void on_list_catalogs_item_click(QTreeWidgetItem * item_source, int const & column, QTreeWidget * source);
      void on_delete_clicked(bool const & checked, std::button * sender);
      void on_delete_all_clicked(bool const & checked, std::button * sender);
      void on_update_controls(QTreeWidgetItem * item_source);

      //
      //DECLARE_OPERATOR(dialog_open_list_papers);
   public:
      std::groupbox_impl<std::vertical_box> * m_property_db{ nullptr };
      QTreeWidgetItem * m_current_item{ nullptr };
      std::shared_ptr<bb::group_data_information> m_data{ nullptr };
      std::treewidget * m_list_catalogs{ nullptr };
      bool m_is_update_columns{ false };
      std::button * m_delete{ nullptr };
      std::button * m_delete_all{ nullptr };
      std::checkbox * m_is_special_combination{ nullptr };
      /**/
   protected:
      void  verify_table_numbers();
   };
}