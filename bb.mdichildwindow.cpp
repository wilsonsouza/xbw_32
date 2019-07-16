//-----------------------------------------------------------------------------------------------//
// xbw32 for Windows (generate of numeric combinations for bingo or lotery)
//
// Created by wilsonsouza 2013, 2018
//
// WR Devinfo
// (c) 2012, 2013, 2014, 2015, 2016, 2017, 2018
//-----------------------------------------------------------------------------------------------//
#include <std.timer.hpp>
#include <std.display_progressbar.hpp>
#include <std.waitcursor.hpp>
#include <std.layouts.hpp>
#include <std.lineedit.hpp>
#include <std.treewidget.hpp>
#include <std.treewidgetitem.hpp>
#include <bb.mdiframewindow.hpp>
#include <bb.box_buttons.hpp>
#include <bb.box_editions.hpp>
#include <bb.box_information.hpp>
#include <bb.box_list_items.hpp>
#include <bb.box_numbers.hpp>
#include <bb.box_page_numbers.hpp>
#include <bb.box_search.hpp>
#include <bb.box_select_group_page.hpp>
#include <bb.mdichildwindow.hpp>
#include <sql.table.hpp>
/**/
namespace bb
{
   mdichildwindow::mdichildwindow(bb::mdiframewindow * frame,
                                  bb::group_manager::pointer const & manager,
                                  std::unicodestring const & caption) :
      std::mdichildwindow{ frame, caption, 0 },
      bb::group_manager{ manager }
   {
      //set caption of window and icon
      setWindowTitle(std::unicodestring{ "Grupo de %1 total de cartelas %2" }.
                     bind(base->title_group).
                     bind(base->calculate()));
      //
      m_vbox_l = new std::vertical_box{};
      m_vbox_r = new std::vertical_box{};
      m_box_buttons = new bb::box_buttons{ this };
      m_box_editions = new bb::box_editions{ this };
      m_box_information = new bb::box_information{ this };
      m_box_numbers = new bb::box_numbers{ this };
      m_box_search = new bb::box_search{ this };
      m_box_select_group_page = new bb::box_select_group_page{ this };
      m_box_list_items = new bb::box_list_items{ this };
      m_box_page_numbers = new bb::box_page_numbers{ this };
   }
   //-----------------------------------------------------------------------------------------------//
   mdichildwindow::~mdichildwindow()
   {
      cancel(); /* cancel all task_group task */
   }
   //-----------------------------------------------------------------------------------------------//
   bool mdichildwindow::create(std::mdichildwindow * child)
   {
      m_box_buttons->create();
      m_box_editions->create();
      m_box_information->create();
      m_box_list_items->create();
      m_box_numbers->create();
      m_box_page_numbers->create();
      m_box_search->create();
      /* close event */
      this->on_close = [&](std::mdichildwindow * child)->auto
      {
         auto frame = bb::mdiframewindow::get_frame();
         frame->get_config()->setValue(bb::defs::app::details{}.AutomaticReload,
                                       m_box_list_items->m_is_auto_reload->isChecked());
         return true;
      };
      /* activate */
      this->on_activate = [&](std::mdichildwindow * child)->auto
      {
         return connect_actions_when_activated_window();
      };
      /* deactivate */
      this->on_deactivate = [&](std::mdichildwindow * child)->auto
      {
         return disconnect_actions_when_deactivated_window();
      };
      /* notify */
      this->on_notify = [&](QObject * sender, QObject * child, void * message, void * data)->auto
      {
         if (*reinterpret_cast<long *>(message) == WM_TIMER)
         {
            auto frame = bb::mdiframewindow::get_frame();
            auto items = m_box_list_items;
            //
            frame->set_enable_menuitem(std::captions::file{}.SAVE, is_modified);
            //
            if (items)
            {
               frame->set_enable_menuitem(std::captions::edit{}.REMOVE, items->m_current_item != nullptr);
               frame->set_enable_menuitem(std::captions::window{}.REFRESH, items->m_is_auto_reload->isChecked());
               frame->set_enable_menuitem(std::captions::edit{}.FIND_REPLACE,
                                          items->m_list_items->topLevelItemCount() > 0);
               frame->set_enable_menuitem(std::captions::edit{}.UNDO, items->m_actual_edit != nullptr);
               frame->set_enable_menuitem(std::captions::edit{}.REDO, items->m_actual_edit != nullptr);
               return true;
            }
         }
         return false;
      };
      return true;
   }
   //-----------------------------------------------------------------------------------------------//
   table_numbers::pointer mdichildwindow::get_field_editions(std::unicodestring const & prefix_name)
   {
      auto tbl = table_numbers::pointer{ new table_numbers{this} };
      //auto box_select_group_page = get<bb::box_select_group_page, IDD_SELECTGROUPPAGEBOX>();
      //auto box_editions = get<bb::box_editions, IDD_EDITIONSBOX>();
      //{
      //   tbl->table_data->group = box_select_group_page->group_id->text().toUpper();
      //   tbl->table_data->page = box_select_group_page->page_id->text().toInt();
      //   /**/
      //   for (auto e = box_editions->edit_queue->begin(); e != box_editions->edit_queue->end(); e++)
      //   {
      //      tbl->table_data->number = e->text().toInt();
      //      /**/
      //      auto & g = data_queue->lookup(tbl->table_data->group, tbl->table_data->page, tbl->table_data->number);
      //      /**/
      //      if (g->availables.first != -1)
      //      {
      //         tbl->table_data->availables = g->availables.second;
      //      }
      //      /**/
      //      tbl->table_queue->push_back(table_numbers::pointer{ new table_numbers{ tbl } });
      //   }
      //}
      return tbl;
   }
   //-----------------------------------------------------------------------------------------------//
   table_resources::pointer mdichildwindow::update_table_resource_on_memory(
      std::unicodestring const & group)
   {
      try
      {
         auto resource = table_resources::pointer{ new table_resources{this} };
         /**/
         run_and_wait([&]
         {
            resource->orderby = bb::defs::db::datasource{}.FLD_NUM_NUMBERS;
            resource->lookup(group.toUpper(), -1, -1);
         });
         return resource;
      }
      catch (std::exception const & e)
      {
         QMessageBox::warning(this, std::captions::errors{}.WARNING, e.what());
      }
      return nullptr;
   }
   //-----------------------------------------------------------------------------------------------//
   void const mdichildwindow::rescue_page()
   {
      try
      {
      }
      catch (std::exception const & e)
      {
         QMessageBox::warning(this, std::captions::errors{}.WARNING, e.what());
      }
   }
   //-----------------------------------------------------------------------------------------------//
   void const mdichildwindow::put_selected_on_editions()
   {
      try
      {
         auto n = table_numbers::pointer{ new table_numbers { this } };
         auto box_list_items = m_box_list_items;
         /**/
         n->lookup(box_list_items->m_current_item->text(0).trimmed(),
                   box_list_items->m_current_item->text(1).toInt(),
                   -1);
         /**/
         if (n->groups->size() > 0)
         {
            //box_list_items->set_clear_editions();
            /* add process query result method */
            //box_list_items-> ListLineEdit->begin().operator*()->setFocus();
         }
         //std::unicodestring szQuery = std::unicodestring
         //{
         //   "groupname in('%1') and pagename in(%2)"
         //}.
         //arg(m_BoxListItems->GetCurrentItem()->text(0).trimmed()).
         //arg(m_BoxListItems->GetCurrentItem()->text(1).toInt());
         //auto pQuery = m_DataSource->Select(bb::TBL_NUMBERS_NAME, nullptr, szQuery);
         //      
         //if(!pQuery->Eof)
         //{
         //   LoadTable(pQuery);
         //   SetClearEditions();
         //   /**/
         //   auto & p = DataList->begin().operator*( );
         //   {
         //      p->ProcessResultQuery( this );
         //   }
         //   m_BoxEditions->GetListLineEdit()->first()->setFocus();
         //}
      }
      catch (std::exception const & e)
      {
         QMessageBox::warning(this, std::captions::errors{}.WARNING, e.what());
      }
   }
   //-----------------------------------------------------------------------------------------------//
   void  mdichildwindow::set_current_table_item_value(std::unicodestring const & value,
                                                      QTableWidget * table)
   {
      auto item = m_current_table_widget_item;
      {
         item->setText(value);
         table->setItem(table->currentRow(), table->currentColumn(), item);
         item = nullptr;
      }
   }
   //-----------------------------------------------------------------------------------------------//
   bool mdichildwindow::connect_actions_when_activated_window()
   {
      auto frame = bb::mdiframewindow::get_frame();
      auto box_list_items = m_box_list_items;
      //
      frame->set_enable_menuitem(std::stringlist
                                 {
                                    std::captions::file{}.PRINT,
                                    std::captions::file{}.PRINT_PAGE_SETUP,
                                    std::captions::file{}.PRINT_VIEW,
                                    std::captions::file{}.PRINT_SETUP
                                 }, true);
      /**/
      auto c = frame->get_config();
      auto bool_value = c->value(bb::defs::app::details{}.AutomaticReload, false).toBool();
      box_list_items->m_is_auto_reload->setChecked(bool_value);
      /**/
      auto refresh = frame->find_menu_item(std::captions::window{}.REFRESH);
      auto remove = frame->find_menu_item(std::captions::edit{}.REMOVE);
      auto undo = frame->find_menu_item(std::captions::edit{}.UNDO);
      auto redo = frame->find_menu_item(std::captions::edit{}.REDO);
      auto save = frame->find_menu_item(std::captions::file{}.SAVE);
      auto find_replace = frame->find_menu_item(std::captions::edit{}.FIND_REPLACE);
      //
      refresh->setText("Recarregar");
      refresh->setToolTip("Recarrega lista de cartelas");
      refresh->on_command = [&](bool const &, std::action * sender)->auto
      {
         box_list_items->load_table_numbers();
         return true;
      };
      /**/
      remove->setText("Remover");
      remove->setToolTip("Remove à cartela");
      remove->on_command = [&](bool const &, std::action * sender)->auto
      {
         if (QMessageBox::question(this, std::captions::errors{}.QUESTION,
             std::unicodestring("Você tem certeza de que deseja remover este cartela %1.%2?").
             arg(box_list_items->m_current_item->text(0)).
             arg(box_list_items->m_current_item->text(1)),
             QMessageBox::Ok | QMessageBox::Cancel) == QMessageBox::Ok)
         {
            auto pos = box_list_items->m_list_items->indexOfTopLevelItem(box_list_items->m_current_item);
            box_list_items->m_list_items->takeTopLevelItem(pos);
            rescue_page();
         }
         //
         box_list_items->m_current_item = nullptr;
         return true;
      };
      //
      find_replace->setText("Pesquisar");
      find_replace->setToolTip("Ativa pesquisa com multiplas escolhas");
      find_replace->on_command = [&](bool const &, std::action * sender)->auto
      {
         m_box_search->setVisible(!m_box_search->isVisible());
         return true;
      };
      //
      save->setToolTip(std::unicodestring{ "Save a cartela corrente em edição" });
      save->on_command = [&](bool const &, std::action * sender)->auto
      {
         return std::dispatch_event_by_pplx(this, m_box_buttons->m_ok->on_clicked, false, m_box_buttons->m_ok);
      };
      //
      redo->setToolTip("Defaz uma edição");
      redo->on_command = [&](bool const &, std::action * sender)->auto
      {
         if (m_box_editions->m_actual_edit)
         {
            m_box_editions->m_actual_edit->redo();
         }
         return true;
      };
      //
      undo->on_command = [&](bool const &, std::action * sender)->auto
      {
         return true;
      };
      return true;
   }
   //-----------------------------------------------------------------------------------------------//
   bool mdichildwindow::disconnect_actions_when_deactivated_window()
   {
      auto frame = bb::mdiframewindow::get_frame();
      //enable menu items
      frame->set_enable_menuitem(std::stringlist
                                 {
                                     std::captions::file{}.PRINT,
                                     std::captions::file{}.PRINT_PAGE_SETUP,
                                     std::captions::file{}.PRINT_VIEW,
                                     std::captions::file{}.PRINT_SETUP
                                 }, false);
      //
      auto refresh = frame->find_menu_item(std::captions::window{}.REFRESH);
      auto remove = frame->find_menu_item(std::captions::edit{}.REMOVE);
      auto undo = frame->find_menu_item(std::captions::edit{}.UNDO);
      auto redo = frame->find_menu_item(std::captions::edit{}.REDO);
      auto save = frame->find_menu_item(std::captions::file{}.SAVE);
      auto find_replace = frame->find_menu_item(std::captions::edit{}.FIND_REPLACE);
      //
      refresh->setEnabled(false);
      remove->setEnabled(false);
      undo->setEnabled(false);
      redo->setEnabled(false);
      save->setEnabled(false);
      find_replace->setEnabled(false);
      return true;
   }
   //-----------------------------------------------------------------------------------------------//
   std::display_progressbar::pointer mdichildwindow::create_display_progressbar()
   {
      return std::display_progressbar::pointer
      {
         new std::display_progressbar{bb::mdiframewindow::get_frame(), this}
      };
   }
   //-----------------------------------------------------------------------------------------------//
}