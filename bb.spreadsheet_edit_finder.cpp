//-----------------------------------------------------------------------------------------------//
// xbw32 for Windows (generate of numeric combinations for bingo or lotery)
//
// Created by wilsonsouza 2013, 2018
//
// WR Devinfo
// (c) 2012, 2013, 2014, 2015, 2016, 2017, 2018
// only support vc++ 2013
//-----------------------------------------------------------------------------------------------//
#include <std.checkbox.hpp>
#include <std.groupbox.hpp>
#include <std.button.hpp>
#include <std.lineedit.hpp>
#include <std.table.hpp>
#include <std.display_progressbar.hpp>
#include <std.groupbox_impl.hpp>
#include <std.layouts.hpp>
#include <std.tabbed.hpp>
#include <bb.mdichildwindow_special_combination.hpp>
#include <bb.spreadsheet_view.hpp>
#include <bb.spreadsheet_edit_finder_numbers.hpp>
#include <bb.spreadsheet_edit_finder.hpp>
#include <bb.lookup_list.hpp>
#include <bb.lookup_numbers.hpp>
#include <bb.data_queue_controller.hpp>
#include <bb.groups_controller.hpp>
#include <bb.pages_controller.hpp>

namespace bb
{
   //-----------------------------------------------------------------------------------------------//
   spreadsheet_edit_finder::spreadsheet_edit_finder(bb::mdichildwindow_special_combination * child) :
      std::widget_impl<std::gridbox>{ this, "IDD_SPREADSHEET_EDIT_FINDER" }
   {
      m_cancel = new std::button{ this, std::captions::common{}.CANCEL,
         std::icons::common{}.CANCEL, std::unicodestring(), true };
      m_is_partial_finder = new std::checkbox{ this, "Pesquisa parcial", "IDD_IS_PARTIAL_FINDER", true };
      m_ok = new std::button{ this,  std::captions::common{}.OK, std::icons::common{}.OK };
      m_table_list = new std::table{ this };
      m_what_finder = new std::lineedit{ this };
   }
   //-----------------------------------------------------------------------------------------------//
   QWidget *  spreadsheet_edit_finder::create()
   {
      box()->addWidget(create_search_group(), 0, 0);
      box()->addWidget(this->create_data_group(), 0, 1);
      box()->addWidget(this->create_buttons(), 1, 0);
      return this;
   }
   //-----------------------------------------------------------------------------------------------//
   void  spreadsheet_edit_finder::fill_table(std::shared_ptr<lookup_list> & lookup_list)
   {
      try
      {
         int nRow = 0;
         int nCol = 0;
         auto display = std::shared_ptr<std::display_progressbar>
         {
            new std::display_progressbar{m_child->get_frame(), m_child}
         };
         //
         if (lookup_list->empty())
         {
            throw std::exception{ "Nenhum registro foi encontrado!!!" };
         }
         //
         m_table_list->setRowCount(lookup_list->size());
         m_child->set_default_table_width_height(m_table_list);
         display->create(lookup_list->size(),
                         std::unicodestring{ "%1 registros encontrados..." }.
                         arg(lookup_list->size()));
         //
         this->m_display_total_records->setTitle(std::unicodestring
                                                 {
                                                    "Total %1 de registro(s) encontrado(s)...."
                                                 }.arg(lookup_list->size()));

         this->m_display_total_records->update();
         //
         std::for_each(lookup_list->begin(), lookup_list->end(), [&](bb::lookup_numbers * p)
         {
            auto data = p->page->to_stringlist();
            std::button * button_view = nullptr;
            //
            m_table_list->setItem(nRow, nCol++, new QTableWidgetItem(p->group));
            m_table_list->setItem(nRow, nCol++, new QTableWidgetItem(std::unicodestring{ "%1" }.arg(p->page->page_id)));
            //
            m_table_list->setItem(nRow, nCol++, new QTableWidgetItem(data->join(",")));
            m_table_list->setCellWidget(nRow,
                                        nCol,
                                        button_view = new std::button{ this,
                                        std::captions::view{}.NAME,
                                        std::icons::common{}.VIEW,
                                        std::unicodestring{},
                                        true });
            /**/
            button_view->on_clicked = [&](bool const & checked, std::button * sender)
            {
               m_child->actived_group_id = m_table_list->item(m_table_list->currentRow(), 0)->text();
               return std::dispatch_event_by_pplx(m_child,
                                                  m_child->on_notify,
                                                  m_child,
                                                  this,
                                                  (void *)interface_messages::ON_UPDATE_LISTVIEW_ROWS,
                                                  nullptr);
            };
            /**/
            //OnTableListViewButton(pView);
            display->update(std::unicodestring{});
            display->get_sub_caption()->setText(std::unicodestring{ "Carregando grupo %1 cartela %2" }.
                                                arg(p->group).arg(p->page->page_id));
            button_view->setEnabled(false);
            //
            nRow++;
            nCol = 0;
            //
            m_table_list->update();
         });
         //
         m_table_list->resizeColumnsToContents();
      }
      catch (std::exception & e)
      {
         QMessageBox::warning(m_child, std::captions::errors{}.WARNING, e.what());
      }
   }
   //-----------------------------------------------------------------------------------------------//
   QWidget * spreadsheet_edit_finder::create_search_group()
   {
      auto pData = new std::groupbox_impl<std::formbox>{ this,"Pesquisa", std::unicodestring{} };
      {
         pData->box()->addRow(std::unicodestring{ "Digite os números separados por virgula" }, m_what_finder);
         pData->box()->addRow(m_is_partial_finder);
         //
         //OnWhatFinder();
         m_what_finder->on_text_changed = [&](std::unicodestring const & data, std::lineedit * sender)
         {
            m_ok->setEnabled(!data.empty());
            return true;
         };
         //
         auto pIsFullScreen = new std::checkbox{ this, "Tela cheia", std::unicodestring(), true };
         {
            pData->box()->addRow(pIsFullScreen);
            //OnFullScreen(pIsFullScreen);
            pIsFullScreen->on_state_changed = [&](uint state, std::checkbox * sender)
            {
               static int nOldHeight = m_child->m_table_width;
               //
               if (m_child->m_tabbed_view->isVisible())
               {
                  m_child->m_tabbed_view->setVisible(!sender->isChecked());
                  m_child->m_tabbed_action->setMaximumHeight(m_child->maximumHeight());
               }
               else
               {
                  m_child->m_tabbed_view->setVisible(!sender->isChecked());
                  m_child->m_tabbed_action->setMaximumHeight(nOldHeight);
               }
               //
               m_child->update();
               return true;
            };
         }
      }
      return pData;
   }
   //-----------------------------------------------------------------------------------------------//
   QWidget * spreadsheet_edit_finder::create_data_group()
   {
      auto pDataTable = new std::groupbox_impl<std::horizontal_box>{ this, "Dados...", "IDD_TABLEDATA" };
      {
         on_table_list();
         pDataTable->box()->addWidget(m_table_list);
         this->m_display_total_records = pDataTable;
      }
      return pDataTable;
   }
   //-----------------------------------------------------------------------------------------------//
   QWidget * spreadsheet_edit_finder::create_buttons()
   {
      auto pButtons = new std::widget_impl<std::horizontal_box>{ this, std::unicodestring{}, 0 };
      {
         pButtons->box()->addWidget(m_ok);
         pButtons->box()->addWidget(m_cancel);
         pButtons->box()->addStretch();
         //
         m_ok->on_clicked = [&](bool const &, std::button * sender)
         {
            auto pFinder = new bb::spreadsheet_edit_finder_numbers{ this };
            //
            on_table_list();
            pFinder->create();
            return true;
         };
         m_cancel->on_clicked = [&](bool const &, std::button * sender)
         {
            m_what_finder->setText(std::unicodestring{});
            m_what_finder->setFocus();
            return true;
         };
      }
      return pButtons;
   }
   //-----------------------------------------------------------------------------------------------//
   void spreadsheet_edit_finder::on_table_list()
   {
      auto lookup_list = std::shared_ptr<std::stringlist>{
         new std::stringlist
      {
         "Grupo",
         "Cartela",
         std::unicodestring{"Números"},
         std::unicodestring{"Ação"}
      } };
      //
      m_table_list->clear();
      m_table_list->setColumnCount(lookup_list->size());
      m_table_list->setHorizontalHeaderLabels(lookup_list.operator*());
      m_table_list->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
      //
      auto flags = m_table_list->editTriggers();
      {
         flags &= ~QAbstractItemView::AnyKeyPressed;
         flags &= ~QAbstractItemView::EditKeyPressed;
         m_table_list->setEditTriggers(flags);
      }
   }
   //-----------------------------------------------------------------------------------------------//
}