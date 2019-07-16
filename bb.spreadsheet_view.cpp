//-----------------------------------------------------------------------------------------------//
// xbw32 for Windows (generate of numeric combinations for bingo or lotery)
//
// Created by wilsonsouza 2013, 2018
//
// WR Devinfo
// (c) 2012, 2013, 2014, 2015, 2016, 2017, 2018
//-----------------------------------------------------------------------------------------------//
#include <std.waitcursor.hpp>
#include <std.widget.hpp>
#include <std.layouts.hpp>
#include <std.display_progressbar.hpp>
#include <bb.table_interface.hpp>
#include <bb.pages_controller.hpp>
#include <bb.groups_controller.hpp>
#include <bb.data_queue_controller.hpp>
#include <bb.mdichildwindow_special_combination.hpp>
#include <bb.group_manager.hpp>
#include <bb.table_ex.hpp>
#include <bb.spreadsheet_view.hpp>
#include <bb.table_item_delegate.hpp>

namespace bb
{
   //-----------------------------------------------------------------------------------------------//
   spreadsheet_view::spreadsheet_view(bb::mdichildwindow_special_combination * child) :
      std::widget_impl<std::vertical_box>{ this, "IDD_SPREADSHEET_VIEW" },
      m_child{ child }
   {
      /**/
      m_table_pages = new std::table{ this };
      m_table_pages->setItemDelegate(new bb::table_item_delegate{ m_table_pages, child });
   }
   //-----------------------------------------------------------------------------------------------//
   QWidget *  spreadsheet_view::create()
   {
      /* add widget on queue */
      this->box()->addWidget(m_table_pages);
      /* call all functions by parallel thread method and fill all data structure */
      this->update_data_queue();
      /* set default active group */
      this->set_active_group(std::unicodestring{});
      /* create columns */
      this->create_columns();
      /* create rows */
      this->create_rows();
      /**/
      this->update_listview(m_child->actived_group_id);
      return this;
   }
   //-----------------------------------------------------------------------------------------------//
   void  spreadsheet_view::set_active_group(std::unicodestring const & group)
   {
      if (group.empty())
      {
         m_child->actived_group_id = m_child->groups->begin()->group_id;
      }
      else
      {
         m_child->actived_group_id = group;
      }
   }
   //-----------------------------------------------------------------------------------------------//
   void  spreadsheet_view::create_columns()
   {
      m_child->run_and_wait([&]
      {
         m_table_pages->setColumnCount(m_child->base->information->numbers_to_page);
         /* put columns */
         for (auto i = 0; i <= m_table_pages->columnCount(); i++)
         {
            auto item = new QTableWidgetItem(std::unicodestring{ "%1" }.arg(i + 1));
            //
            item->setData(Qt::UserRole, i);
            item->setToolTip(std::unicodestring{ "Grupo %1 Coluna %1" }.arg(m_child->actived_group_id).arg(i + 1));
            m_table_pages->setHorizontalHeaderItem(i, item);
         }
      });
   }
   //-----------------------------------------------------------------------------------------------//
   void  spreadsheet_view::create_rows()
   {
      m_child->run_and_wait([&]
      {
         m_table_pages->setRowCount(m_child->base->information->pages_to_group);
         /* put columns */
         for (int i = 0; i <= m_table_pages->rowCount(); i++)
         {
            auto fmt = std::unicodestring{ "%1-%2" }.arg(m_child->actived_group_id).arg(i + 1);
            auto pItem = new QTableWidgetItem(fmt);
            /**/
            pItem->setData(Qt::UserRole, i);
            pItem->setToolTip(std::unicodestring{ "Grupo %1 cartela %2" }.arg(fmt).arg(i + 1));
            m_table_pages->setVerticalHeaderItem(i, pItem);
         }
         /**/
         m_child->set_default_table_width_height(m_table_pages);
      });
   }
   //-----------------------------------------------------------------------------------------------//
   void  spreadsheet_view::update_data_queue()
   {
      m_child->run_and_wait([&]
      {
         auto c_start_group = m_child->base->information->groups_id;
         auto c_last_group = m_child->base->last_group_id;
         auto n_start_is = m_child->base->information->is_allowed_zero;
         std::shared_ptr<std::waitcursor>{new std::waitcursor{ m_child }};
         /**/
         for (auto c_letter = c_start_group; c_start_group <= c_last_group; c_start_group++)
         {
            auto n_max_pg = m_child->base->information->pages_to_group;
            /***/
            for (int n_counter = n_start_is; n_counter <= n_max_pg; n_counter++)
            {
               auto fmt = std::unicodestring{}.sprintf("%c%03d", c_letter, n_counter);
               /**/
               //ChildWnd->DataQueue->SetGroups( szFmt,
               //   nCounter,
               //   GetChildWnd()->Numbers,
               //   GetChildWnd()->NumbersByGroup );
            }
         }
         /* fill grid */
         if (m_child->objectName() == std::captions::file{}.OPEN)
         {
            load_data_queue();
         }
      });
   }
   //-----------------------------------------------------------------------------------------------//
   __declspec(safebuffers) void  spreadsheet_view::load_data_queue()
   {
      m_child->run_and_wait([&]
      {
         auto display_pg = std::shared_ptr<std::display_progressbar>{
            new std::display_progressbar{m_child->get_frame(), m_child} };
         std::shared_ptr<std::waitcursor>{new std::waitcursor{ m_child }};
         /***/
         display_pg->create(0, "Aguarde selecionado grupos...");
         /**/
         //std::shared_ptr<sql::Table> pExecSQL = GetChildWnd()->DataSource->Select(
         //   bb::TBL_NUMBERS_NAME, nullptr,
         //   std::unicodestring( "groupname = groupname ORDER BY groupname" ) );
         ///**/
         //GetChildWnd()->LoadTable( pExecSQL );
         //pDisplay->SetMax( GetChildWnd()->DataList->size() );
         ///***/
         //for ( auto & pData = GetChildWnd()->DataList->begin(); pData != GetChildWnd()->DataList->end(); pData++ )
         //{
         //   std::shared_ptr<bb::DataNumber> & pDataNumber = pData.operator*( );
         //   /**/
         //   if ( pDataNumber->Group.length() == 3 )
         //   {
         //      pDataNumber->Group = pDataNumber->Group.insert( 1, "0" );
         //   }
         //   /**/
         //   bb::groups_controller * pgroups_controller =
         //      GetChildWnd()->DataQueue->search_group( pDataNumber->Group );
         //   //
         //   pDisplay->Update();
         //   pDisplay->SubCaption->Text = std::unicodestring
         //   {
         //      "Carregando grupo %1" 
         //   }.arg( pDataNumber->Group );
         //   /**/
         //   if ( pgroups_controller )
         //   {
         //      bb::pages_controller * ppages_controller = 
         //         pgroups_controller->SearchPage( pDataNumber->Page );
         //      /**/
         //      if ( ppages_controller )
         //      {
         //         pDisplay->SubCaption->Text = std::unicodestring( "Carregando cartela %1" ).
         //            arg( ppages_controller->Page );
         //         this->UpdateNumbersOnPages( pgroups_controller, ppages_controller, pDataNumber );
         //      }
         //   }
         //}
      });
   }
   //-----------------------------------------------------------------------------------------------//
   void  spreadsheet_view::update_numbers_on_pages(/*bb::groups_controller * pgroups_controller,
                                                   bb::pages_controller * ppages_controller,
                                                   std::shared_ptr<bb::datanumber> const & pDataNumbers*/)
   {
      //create new thread to process
      m_child->run_and_wait([&]
      {
         //auto & p = pDataNumbers->Numbers;
         ///**/
         //for ( auto n = p->begin();  n != p->end(); n++ )
         //{
         //   int nValue = n.operator*( );
         //   /**/
         //   if ( ppages_controller->size() == ChildWnd->NumbersByPage )
         //   {
         //      return;
         //   }
         //   //put page in group
         //   pgroups_controller->Insert( ppages_controller, nValue );
         //}
      });
   }
   //-----------------------------------------------------------------------------------------------//
   void  spreadsheet_view::update_listview(std::unicodestring const & group)
   {
      m_child->run_and_wait([&]
      {
         std::shared_ptr<std::waitcursor>{new std::waitcursor{ m_child }};
         auto & groups = std::find_if(m_child->groups->begin(), m_child->groups->end(), controller::groups{ group });
         /* clear all cells before redraw */
         this->empty_cells();
         this->create_columns();
         this->create_rows();
         /* refresh all cells */
         //for ( auto & p = pGroup->begin(); p != pGroup->end(); p++ )
         std::for_each(groups->pages.begin(), groups->pages.end(), [&](controller::pages & page)
         {
            int i = 0;
            int n_row = m_child->base->information->is_allowed_zero;
            int n_col = 0;

            //for ( auto &  n = pPage->begin(); n != pPage->end(); n++ )
            std::for_each(page.numbers.begin(), page.numbers.end(), [&](controller::page_numbers & num_id)
            {
               auto item = new QTableWidgetItem{ std::unicodestring{"%1"}.arg(num_id.number_id) };
               int n_line = page.page_id - n_row;
               auto avail_n = std::find_if(groups->availables.begin(),
                                           groups->availables.end(), controller::available_numbers{ num_id.number_id });
               /**/
               m_table_pages->setItem(n_line, n_col++, item);
               item->setToolTip(std::unicodestring
                                {
                                   "Disponivíes %1 do número %2"
                                }.arg(avail_n->availables).arg(avail_n->number_id));
               /**/
               m_table_pages->update();
            });
         });
      });
   }
   //-----------------------------------------------------------------------------------------------//
   void  spreadsheet_view::empty_cells()
   {
      m_child->run_and_wait([&]
      {
         m_table_pages->clear();
         /* recreate all qtablewidgetitem */
         m_child->set_default_table_width_height(m_table_pages);
      });
   }
   //-----------------------------------------------------------------------------------------------//
   bool  spreadsheet_view::validity_cell_value(QTableWidgetItem const * item)
   {
      auto success = false;
      /**/
      //try
      //{
      //   ChildWnd->run_and_wait([&]
      //   {
      //      /* get current item changed three */
      //      bb::groups_controller * g = GetChildWnd()->DataQueue->search_group( GetChildWnd()->ActivedGroupID );
      //      int nValue = pItem->text().toInt();
      //      int nStarted = GetChildWnd()->IsCountByZero();
      //      int nRow = pItem->row();
      //      int nCol = pItem->column();
      //      //
      //      //
      //      if ( g )
      //      {
      //         int nSelectedRow = TablePages->currentRow() + nStarted;
      //         bb::pages_controller * p = g->SearchPage( nSelectedRow );
      //         //
      //         if ( p )
      //         {
      //            std::shared_ptr<bb::DataGrid> & pOldValue = GetChildWnd()->ListDataOfGrid->Search( pItem, p->Page, g->Group );
      //            /**/
      //            if ( p->SearchNumber( nValue ) )
      //            {
      //               throw std::exception( std::unicodestring
      //               {
      //                  std::unicodestring( "Número %1 já existe!" ).arg( nValue )
      //               }.c_str() );
      //               return;
      //            }
      //            else
      //            {
      //               if ( !g->IsAvailable( nValue ) )
      //               {
      //                  throw std::exception( std::unicodestring
      //                  {
      //                     std::unicodestring
      //                     { 
      //                        "Números disponíveis para este número %1 esgotados!" 
      //                     }.arg( nValue )
      //                  }.c_str() );
      //                  return;
      //               }
      //               //
      //               if ( nValue > GetChildWnd()->Numbers )
      //               {
      //                  throw std::exception( std::unicodestring
      //                  {
      //                     std::unicodestring( "Número %1 não permitido!" ).arg( nValue )
      //                  }.c_str() );
      //                  return;
      //               }
      //               //
      //               if ( !GetChildWnd()->IsCountByZero() )
      //               {
      //                  if ( nValue == 0 )
      //                  {
      //                     throw std::exception( std::unicodestring
      //                     {
      //                        std::unicodestring( "Número %1 não permitido!" ).arg( nValue )
      //                     }.c_str() );
      //                     return;
      //                  }
      //               }
      //               /* verify if number already exists in table */
      //               std::shared_ptr<bb::DataGrid> & pData = GetChildWnd()->ListDataOfGrid->Search( nRow, nCol, p->Page, g->Group );
      //               //
      //               if ( pData )
      //               {
      //                  if ( pData->Value >= 0 && pData->Value != nValue && pData->Page == p->Page )
      //                  {
      //                     GetChildWnd()->DataSource->Delete( g->Group, p->Page, pData->Value );
      //                     GetChildWnd()->DataQueue->delete_number( g->Group, p->Page, pData->Value );
      //                     GetChildWnd()->ListDataOfGrid->removeOne( pData );
      //                  }
      //               }
      //               /* insert new number */
      //               g->Insert( p, nValue );
      //               int nAvailables = g->SearchAvailables( nValue );
      //               /* insert new number to feature research */
      //               GetChildWnd()->ListDataOfGrid->append( std::shared_ptr < DataGrid >
      //               {
      //                  new bb::DataGrid( nRow, nCol, nValue, p->Page, g->Group, nAvailables, true )
      //               } );
      //               /* set old number */
      //               ChildWnd->CurrentTableItem = nullptr;
      //               bSuccess = true;
      //            }
      //         }
      //      }
      //   } );
      //}
      //catch ( std::exception const & e )
      //{
      //   QMessageBox::warning( ChildWnd, std::Errors::WARNING, e.what() );
      //}
      return success;
   }
   //-----------------------------------------------------------------------------------------------//
   QTableWidgetItem *  spreadsheet_view::get_vertical_header_value()
   {
      return m_table_pages->verticalHeaderItem(m_table_pages->currentRow()/*m_child->m_current_table_widget_item->row()*/);
   }
   //-----------------------------------------------------------------------------------------------//
   void spreadsheet_view::remove_current_item()
   {
      m_child->run_and_wait([&]
      {
         try
         {
            if (m_table_pages->currentItem() == nullptr)
            {
               throw std::exception{ "Primeiro selecione um número para excluir!" };
            }
            /**/
            auto current_item = m_table_pages->currentItem();
            /**/
            if (QMessageBox::question(m_child, std::captions::errors{}.QUESTION,
                std::unicodestring
                {
                   "Você tem certeza de que deseja remover este %1 número?"
                }.arg(current_item->text().toInt()), QMessageBox::Ok | QMessageBox::Cancel) == QMessageBox::Ok)
            {
               auto n_page = m_child->base->information->is_allowed_zero + m_table_pages->currentRow();
               auto n_value = current_item->text().toInt();
               auto del = std::shared_ptr<table_numbers>{ new table_numbers { m_child } };
               /**/
               auto g = std::find_if(m_child->groups->begin(), m_child->groups->end(),
                                     controller::groups{ m_child->actived_group_id });
               auto p = std::find_if(g->pages.begin(), g->pages.end(), controller::pages{ n_page });
               auto n = std::find_if(p->numbers.begin(), p->numbers.end(), controller::page_numbers{ n_value });
               auto avail_n = std::find_if(g->availables.begin(), g->availables.end(),
                                           controller::available_numbers{ n_value });
               /**/
               if (del->erase(m_child->actived_group_id, n_page, n_value).m_successed)
               {
                  avail_n->availables++;
                  p->numbers.erase(n);
                  current_item->setText(std::unicodestring{});
               }
               /***/
               m_child->get_frame()->find_menu_item(std::captions::window{}.REFRESH)->triggered();
            }
         }
         catch (std::exception const & e)
         {
            QMessageBox::warning(m_child, std::captions::errors{}.WARNING, e.what());
         }
      });
   }
   //-----------------------------------------------------------------------------------------------//
}