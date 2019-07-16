//-----------------------------------------------------------------------------------------------//
// xbw32 for Windows (generate of numeric combinations for bingo or lotery)
//
// Created by wilsonsouza 2013, 2018
//
// WR Devinfo
// (c) 2012, 2013, 2014, 2015, 2016, 2017, 2018
//-----------------------------------------------------------------------------------------------//
#include <std.waitcursor.hpp>
#include <bb.data_queue_controller.hpp>
#include <bb.groups_controller.hpp>
#include <bb.pages_controller.hpp>
#include <bb.mdiframewindow.hpp>
#include <bb.group_manager.hpp>
#include <bb.mdichildwindow.hpp>
#include <bb.table_interface.hpp>
#include <bb.spreadsheet_advanced.hpp>
#include <bb.spreadsheet_delete.hpp>
#include <bb.spreadsheet_edit_finder.hpp>
#include <bb.spreadsheet_view.hpp>
#include <bb.spreadsheet_initialize_distribution.hpp>
#include <bb.spreadsheet_insert.hpp>
#include <bb.spreadsheet_insert_by.hpp>
#include <bb.spreadsheet_manual_insert.hpp>
#include <bb.spreadsheet_select_other_group.hpp>
#include <bb.spreadsheet_box_entry_numbers.hpp>
#include <bb.box_numbers.hpp>
#include <bb.box_page_numbers.hpp>
#include <bb.box_search.hpp>
#include <bb.mdichildwindow_special_combination.hpp>
#include <std.table.hpp>
//-----------------------------------------------------------------------------------------------//
namespace bb
{
   //-----------------------------------------------------------------------------------------------//
   mdichildwindow_special_combination::mdichildwindow_special_combination(bb::mdiframewindow * frame,
                                                                          bb::group_manager::pointer const & manager,
                                                                          std::unicodestring const & caption) :
      bb::mdichildwindow(frame, manager, caption)
   {
      /**/
      m_advanced = new spreadsheet_advanced{ this };
      m_delete = new spreadsheet_delete{ this };
      m_edit_finder = new spreadsheet_edit_finder{ this };
      m_view = new spreadsheet_view{ this };
      m_initialize_distribution = new spreadsheet_initialize_distribution{ this };
      m_insert = new spreadsheet_insert{ this };
      m_insert_by = new spreadsheet_insert_by{ this };
      m_manual_insert = new spreadsheet_manual_insert{ this };
      m_select_other_group = new spreadsheet_select_other_group{ this };
      m_entry_numbers = new spreadsheet_box_entry_numbers{ this };
      m_tabbed_view = new std::tabbed{ this };
      m_tabbed_action = new std::tabbed{ this };
      m_table_width = 250;
      /**/
      m_tabbed_action->setTabPosition(QTabWidget::South);
      m_tabbed_view->setTabPosition(QTabWidget::South);
      m_tabbed_action->setMaximumHeight(m_table_width);
      /**/
      set_widget(this->m_gbox);
   }
   //-----------------------------------------------------------------------------------------------//
   bool mdichildwindow_special_combination::create(std::mdichildwindow * child)
   {
      m_gbox->box()->addWidget(m_tabbed_view, 0, 0);
      m_gbox->box()->addWidget(m_tabbed_action, 1, 0);
      m_tabbed_view->addTab(m_view->create(),
                            std::icons::common{}.DBSTATUS,
                            std::unicodestring{ "Grupos e Cartelas" });
      //
      auto pNumbers = new std::widget_impl<std::vertical_box>{ this, std::unicodestring{} };
      {
         pNumbers->box()->addWidget(m_box_numbers->create());
         pNumbers->box()->addWidget(m_box_page_numbers->create());
         m_tabbed_view->addTab(pNumbers, std::icons::common{}.INFORMATION, std::unicodestring{ "Informações" });
      }
      //
      m_tabbed_action->addTab(m_initialize_distribution->create(), std::unicodestring{ "Inicialização" });
      m_tabbed_action->addTab(m_entry_numbers->create(), 
                              std::icons::edit{}.PASTE, 
                              std::unicodestring{ "Edição de cartela" });
      m_tabbed_action->addTab(m_advanced->create(), std::unicodestring{ "Selecionar Edição" });
      m_tabbed_action->addTab(m_delete->create(), 
                              std::icons::edit{}.REMOVE, 
                              std::unicodestring{ "Deletar dados" });
      m_tabbed_action->addTab(m_edit_finder->create(), 
                              std::icons::edit{}.FIND_REPLACE, 
                              std::unicodestring{ "Pesquisa" });
      m_tabbed_action->addTab(m_insert->create(), std::icons::file{}.NEW, "Inserir");
      m_tabbed_action->addTab(m_insert_by->create(), "Inserir por");
      m_tabbed_action->addTab(m_manual_insert->create(), std::unicodestring{ "Insersão manual" });
      m_tabbed_action->addTab(m_select_other_group->create(), std::unicodestring{ "Seleção de grupos" });
      /**/
      on_close = [&](std::mdichildwindow * child)
      {
         if (base->is_modified)
         {
            if (QMessageBox::question(this, std::captions::errors{}.QUESTION,
                std::unicodestring{ "Dado(s) não foram salvos! Você deseja salvar agora?" },
                QMessageBox::Ok | QMessageBox::Cancel) == QMessageBox::Ok)
            {
               emit get_frame()->find_menu_item(std::captions::file{}.SAVE)->triggered();
            }
            /* disconnect all */
            this->disconnect_actions_when_deactivated_window();
         }
         return base->is_modified;
      };
      /**/
      on_notify = [&](QObject * sender, QObject * child, void * msg, void * data)
      {
         switch (*(bb::interface_messages *)msg)
         {
         case bb::interface_messages::ON_UPDATE_LISTVIEW:
            m_view->update_listview(this->actived_group_id);
            break;
         case bb::interface_messages::ON_WRITE_DATA_ON_DATABASE:
            break;
         case bb::interface_messages::ON_UPDATE_LISTVIEW_ROWS:
            m_view->create_rows();
            m_view->update_listview(this->actived_group_id);
            break;
         }
         /**/
         if (*(long *)msg == WM_TIMER)
         {
            on_timer(this, *(uint*)msg, data);
         }
         return true;
      };
      return true;
   }
   //-----------------------------------------------------------------------------------------------//
   void const  mdichildwindow_special_combination::set_default_table_width_height(std::table * tbl)
   {
      for (auto row = 0; row <= tbl->rowCount(); row++)
      {
         tbl->setRowHeight(row, 0x14);
         /***/
         for (auto col = 0; col <= tbl->columnCount(); col++)
         {
            tbl->setColumnWidth(col, 0x14);
            tbl->resizeColumnToContents(col);
            tbl->setItem(row, col, new QTableWidgetItem(std::unicodestring{}));
         }
      }
   }
   //-----------------------------------------------------------------------------------------------//
   std::shared_ptr<table_numbers> mdichildwindow_special_combination::get_field_editions(
      std::unicodestring const & prefix_name)
   {
      auto display = std::shared_ptr<std::display_progressbar>{ new std::display_progressbar(get_frame(), this) };
      auto wc = std::shared_ptr<std::waitcursor>{ new std::waitcursor{get_frame()} };
      //
      get_frame()->find_menu_item(std::captions::file{}.SAVE_AS)->setEnabled(false);
      display->create(groups->size(), std::unicodestring{});
      //
      //for (auto g = m_DataQueue->begin(); g != m_DataQueue->end(); g++)
      //{
      //   std::shared_ptr<bb::DataSourceInformation> pData = std::shared_ptr<bb::DataSourceInformation>(
      //      new bb::DataSourceInformation());
      //   bb::groups_controller * pgroups_controller = g.operator*();
      //   //
      //   pData->SetGroup(pgroups_controller->GetGroup());
      //   pDisplay->Update(std::unicodestring
      //   {
      //      "Aguarde, efetuando leitura do grupo %1"
      //   }.arg(pgroups_controller->GetGroup()));
      //   //
      //   for (auto p = m_ListDataOfGrid->begin(); p != m_ListDataOfGrid->end(); p++)
      //   {
      //      std::shared_ptr<bb::DataGrid> & pDataGrid = p.operator*();
      //      //
      //      pData->SetPage(pDataGrid->Page);
      //      pData->SetGroup(pDataGrid->Group);
      //      //
      //      if(pDataGrid->IsUpdated)
      //      {
      //         //put current number in buffer
      //         pData->operator[](pDataGrid->Value) = pDataGrid->Availables;
      //         //insert on database
      //         m_DataSource->Insert(pData);
      //         //clear buffer
      //         pData->clear();
      //         //mark with reader
      //         pDataGrid->IsUpdated = false;
      //      }
      //   }
      //   //free used memory
      //   pData.reset();
      //}
      return nullptr;
   }
   //-----------------------------------------------------------------------------------------------//
   bool mdichildwindow_special_combination::connect_actions_when_activated_window()
   {
      this->on_save();
      this->on_delete();
      this->on_refresh();
      return true;
   }
   //-----------------------------------------------------------------------------------------------//
   bool mdichildwindow_special_combination::disconnect_actions_when_deactivated_window()
   {
      this->on_save(false);
      this->on_delete(false);
      this->on_refresh(false);
      return true;
   }
   //-----------------------------------------------------------------------------------------------//
   void mdichildwindow_special_combination::on_delete(bool enabled)
   {
      static auto old_action_delete = get_frame()->find_menu_item(std::captions::edit{}.REMOVE)->on_command;
      auto action_delete = get_frame()->find_menu_item(std::captions::edit{}.REMOVE)->on_command;
      /**/
      if (action_delete && enabled)
      {
         action_delete = [&](bool const & checked, std::action * sender)
         {
            m_view->remove_current_item();
            return true;
         };
         return;
      }
      /**/
      if (action_delete && !enabled)
      {
         action_delete = old_action_delete;
      }
   }
   //-----------------------------------------------------------------------------------------------//
   void mdichildwindow_special_combination::on_save(bool enabled)
   {
      static auto old_action_save = get_frame()->find_menu_item(std::captions::file{}.SAVE)->on_command;
      auto action_save = get_frame()->find_menu_item(std::captions::file{}.SAVE)->on_command;
      /**/
      if (action_save && enabled)
      {
         action_save = [&](bool const &, std::action * sender)
         {
            this->get_field_editions(std::unicodestring{});
            return true;
         };
         return;
      }
      /***/
      if (action_save && !enabled)
      {
         action_save = old_action_save;
      }
   }
   //-----------------------------------------------------------------------------------------------//
   void mdichildwindow_special_combination::on_refresh(bool enabled)
   {
      static auto old_action_updated = get_frame()->find_menu_item(std::captions::window{}.REFRESH)->on_command;
      auto action_updated = get_frame()->find_menu_item(std::captions::window{}.REFRESH)->on_command;
      /***/
      if (action_updated && enabled)
      {
         action_updated = [&](bool const &, std::action * sender)
         {
            std::dispatch_event(on_notify,
                                this,
                                this,
                                (void *)bb::interface_messages::ON_UPDATE_LISTVIEW,
                                nullptr);
            return true;
         };
         return;
      }
      /***/
      if (action_updated && !enabled)
      {
         action_updated = old_action_updated;
      }
   }
   //-----------------------------------------------------------------------------------------------//
   void mdichildwindow_special_combination::on_timer(std::mdichildwindow * child,
                                                     unsigned int id,
                                                     void const * data)
   {
      auto action_save = get_frame()->find_menu_item(std::captions::file{}.SAVE);
      auto action_del = get_frame()->find_menu_item(std::captions::edit{}.REMOVE);
      auto action_update = get_frame()->find_menu_item(std::captions::window{}.REFRESH);
      /***/
      if (action_save)
      {
         action_save->setEnabled(base->is_modified);
      }
      /***/
      if (action_del && m_view)
      {
         auto item = m_view->m_table_pages->currentItem();
         /***/
         action_del->setEnabled(item ? !item->text().isEmpty() : false);
      }
      /***/
      if (action_update)
      {
         action_update->setEnabled(is_modified);
      }
   }
   //-----------------------------------------------------------------------------------------------//
}