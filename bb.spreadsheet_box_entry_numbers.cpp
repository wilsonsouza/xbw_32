//-----------------------------------------------------------------------------------------------//
// xbw32 for Windows (generate of numeric combinations for bingo or lotery)
//
// Created by wilsonsouza 2013, 2018
//
// WR Devinfo
// (c) 2012, 2013, 2014, 2015, 2016, 2017, 2018
//-----------------------------------------------------------------------------------------------//
#include <std.button.hpp>
#include <std.label.hpp>
#include <std.lineedit.hpp>
#include <std.groupbox_impl.hpp>
#include <std.layouts.hpp>
#include <bb.data_queue_controller.hpp>
#include <bb.groups_controller.hpp>
#include <bb.pages_controller.hpp>
#include <bb.mdichildwindow_special_combination.hpp>
#include <bb.group_manager.hpp>
#include <bb.spreadsheet_box_entry_numbers.hpp>
//-----------------------------------------------------------------------------------------------//
namespace bb
{
   //-----------------------------------------------------------------------------------------------//
   spreadsheet_box_entry_numbers::spreadsheet_box_entry_numbers(bb::mdichildwindow_special_combination * child) :
      std::widget_impl<std::vertical_box>{ this, "IDD_SPREADSHEET_BOX_ENTRY_NUMBERS" },
      m_child{ child },
      m_ok{ new std::button{ this, std::captions::common{}.OK, std::icons::common{}.OK } },
      m_cancel{ new std::button{ this,
      std::captions::common{}.CANCEL, std::icons::common{}.CANCEL, std::unicodestring{}, true } }
   {
      this->enable_edit_list(false);
      this->clear_edit_list();
   }
   //-----------------------------------------------------------------------------------------------//
   QWidget * spreadsheet_box_entry_numbers::create()
   {
      int nMaxLines = m_child->base->information->numbers_to_page;
      int nMaxCols = m_child->get_frame()->width() / 0x35;
      auto pActivePageBox = new std::groupbox_impl<std::formbox>{ this, "Cartela", std::unicodestring{} };
      {
         auto d = m_child;
         auto label_id = new std::label{ this, std::unicodestring{"Entre com a identificação"} };
         /**/
         m_page = new std::lineedit{ std::unicodestring{}, 2, 0x14 };
         pActivePageBox->box()->addRow(label_id, m_page);
         m_page->set_validator(new QIntValidator(0x1, d->base->information->pages_to_group, m_page));
         m_page->setToolTip(std::unicodestring("Entre com o número da <b>cartela</b> deseja."));
         m_page->setWhatsThis(std::unicodestring("Define qual <b>cartela</b> editar."));
         //
         m_page->on_return_pressed = [&](std::lineedit * sender)
         {
            auto g = std::find_if(m_child->groups->begin(),
                                  m_child->groups->end(),
                                  controller::groups{ m_child->actived_group_id });
            //
            if (g != m_child->groups->end())
            {
               auto page = std::find_if(g->pages.begin(),
                                        g->pages.end(),
                                        controller::pages{ sender->text().toInt() });
               //
               if (page == g->pages.end() || sender->text().toInt() == 0)
               {
                  QMessageBox::warning(m_child, std::captions::errors{}.WARNING,
                                       std::unicodestring{ "Cartela %1 não encontrado ou não e valida!" }.
                                       arg(sender->text().toInt()));
                  sender->setFocus();
                  return false;
               }
               //
               this->put_numbers_for_edition(g->pages);
               this->clear_edit_list();
               this->enable_edit_list();
               //jump next control
               sender->set_focus_next_child();
            }
            return true;
         };
      }
      /**/
      auto pNumbersBox = new std::groupbox_impl<std::vertical_box>{ this, "Edição", std::unicodestring{ } };
      {
         for (auto nRow = 0; nRow < nMaxLines;)
         {
            auto pLine = new std::horizontal_box{};
            /**/
            for (auto nCols = 0; nCols <= nMaxCols && nRow < nMaxLines; nCols++, nRow++)
            {
               std::lineedit * pEdit = nullptr;
               auto nMinValue = m_child->base->information->is_allowed_zero;
               auto nMaxValue = m_child->base->information->numbers;
               {
                  pLine->addWidget(pEdit = new std::lineedit{ std::unicodestring{}, 2, 0x27 });
                  m_data_list->push_back(pEdit);
                  pEdit->set_validator(new QIntValidator(nMinValue, nMaxValue, pEdit));
               }
               //
               pEdit->on_return_pressed = [&](std::lineedit * sender)
               {
                  if (on_validate(m_page, sender->text().toInt()))
                  {   /* jump next control */
                     sender->set_focus_next_child();
                  }
                  else
                  {
                     sender->setFocus();
                  }
                  return true;
               };
            }
            /* append on main layout box */
            pLine->addStretch();
            pNumbersBox->box()->addLayout(pLine);
         }
      }
      /**/
      auto pBoxButtons = new std::horizontal_box{};
      {
         pBoxButtons->addWidget(m_ok);
         pBoxButtons->addWidget(m_cancel);
         pBoxButtons->addStretch();
      };
      /* mount*/
      auto pBody = new std::horizontal_box{};
      {
         pBody->addLayout(new define_layout_control<>(pActivePageBox));
         pBody->addStretch();
         pBody->addLayout(new define_layout_control<>(pNumbersBox));
         pBody->addStretch();
      }
      //
      this->box()->addLayout(pBody);
      this->box()->addLayout(pBoxButtons);
      /**/
      m_ok->on_clicked = [&](bool const &, std::button * sender)
      {
         add_numbers_on_data_grid_impl(m_data_list);
         std::dispatch_event_by_pplx(m_child,
                                     m_child->on_notify,
                                     this,
                                     this,
                                     (void *)bb::interface_messages::ON_UPDATE_LISTVIEW,
                                     nullptr);
         auto next_page = m_page->text().toInt();
         /**/
         if (++next_page < m_child->base->information->pages_to_group)
         {
            m_page->setText(std::unicodestring{ "%1" }.arg(next_page));
            m_page->setFocus();
         }
         return next_page;
      };
      /**/
      m_cancel->on_clicked = [&](bool const &, std::button * sender)
      {
         delete_numbers_on_data_grid_impl(m_data_list);
         clear_edit_list();
         enable_edit_list(false);
         m_ok->setEnabled(false);
         return true;
      };
      /**/
      clear_edit_list();
      enable_edit_list();
      return this;
   }
   //-----------------------------------------------------------------------------------------------//
   std::vector<int> spreadsheet_box_entry_numbers::get_numbers()
   {
      auto out_values = std::vector<int>{};
      /**/
      std::for_each(m_data_list->begin(), m_data_list->end(), [&](std::lineedit * p)
      {
         if (!p->text().isEmpty())
         {
            out_values.push_back(p->text().toInt());
         }
      });
      return out_values;
   }
   //-----------------------------------------------------------------------------------------------//
   void spreadsheet_box_entry_numbers::clear_edit_list()
   {
      std::for_each(m_data_list->begin(), m_data_list->end(), [&](std::lineedit * p)
      {
         p->setText(std::unicodestring());
      });
   }
   //-----------------------------------------------------------------------------------------------//
   void spreadsheet_box_entry_numbers::enable_edit_list(bool const & enable)
   {
      std::for_each(m_data_list->begin(), m_data_list->end(), [&](std::lineedit * p)
      {
         p->setEnabled(enable);
      });
   }
   //-----------------------------------------------------------------------------------------------//
   bool spreadsheet_box_entry_numbers::on_validate(std::lineedit * page, int value_id)
   {
      int n_page = page->text().toInt();
      auto g = std::find_if(m_child->groups->begin(),
                            m_child->groups->end(),
                            controller::groups{ m_child->actived_group_id });
      //
      if (g != m_child->groups->end())
      {
         auto p = std::find_if(g->pages.begin(),
                               g->pages.end(),
                               controller::pages{ n_page });
         //
         if (p != g->pages.end())
         {
            if (std::find_if(p->numbers.begin(), 
                p->numbers.end(), controller::page_numbers{ value_id }) != p->numbers.end())
            {
               QMessageBox::warning(m_child, 
                                    std::captions::errors{}.WARNING,
                                    std::unicodestring{ "Número %1 já existe!" }.arg(value_id));
               return false;
            }
            //
            auto aval_n = std::find_if(g->availables.begin(),
                                       g->availables.end(),
                                       controller::available_numbers{ value_id });
            /**/
            if(aval_n->availables == 0)
            {
               QMessageBox::warning(m_child, 
                                    std::captions::errors{}.WARNING,
                                    std::unicodestring{ "Números disponíveis para este número %1 esgotado!" }.
                                    arg(value_id));
               return false;
            }
            //
            if (value_id > m_child->base->information->numbers)
            {
               QMessageBox::warning(m_child, 
                                    std::captions::errors{}.WARNING,
                                    std::unicodestring{ "Número %1 não permitido!" }.arg(value_id));
               return false;
            }
            //
            if (!m_child->base->information->is_allowed_zero)
            {
               if (value_id == 0)
               {
                  QMessageBox::warning(m_child, 
                                       std::captions::errors{}.WARNING,
                                       std::unicodestring{ "Número %1 não permitido!" }.arg(value_id));
                  return false;
               }
            }
            /**/
            p->numbers.push_back(controller::page_numbers{ value_id, false });
            aval_n->availables--;
            //check all fields if this filled
            on_get_data_edit_list();
            return true;
         }
      }
      return false;
   }
   //-----------------------------------------------------------------------------------------------//
   bool spreadsheet_box_entry_numbers::on_get_data_edit_list()
   {
      auto success = 0u;
      //
      std::for_each(m_data_list->begin(), m_data_list->end(), [&](std::lineedit * p)
      {
         if (!p->text().trimmed().isEmpty())
         {
            success |= 1;
         }
         else
         {
            success &= ~1;
         }
      });
      //
      m_ok->setEnabled(success);
      //
      if (success)
      {
         m_ok->setFocus();
      }
      //
      return success;
   }
   //-----------------------------------------------------------------------------------------------//
   void spreadsheet_box_entry_numbers::add_numbers_on_data_grid_impl(
      std::shared_ptr<std::vector<std::lineedit *>> const & list_ptr)
   {
      //int nCol = 0;
      //int nRow = m_page->text().toInt();
      //int nPage = nRow;
      //auto * lpWnd = dynamic_cast<bb::mdichildwindow_special_combination *>(std::vertical_box::parent());
      ////
      //for(auto i = pList->begin(); i != pList->end(); i++, nCol++)
      //{
      //   std::shared_ptr<bb::DataGrid> & pExists = 
      //      lpWnd->GetListDataOfGrid()->Search(nRow, nCol, nPage, lpWnd->GetActivedGroupID());
      //   std::lineedit * pEdit = dynamic_cast<std::lineedit *>(i.operator*());
      //   int nValue = pEdit->text().toInt();
      //   //
      //   if(!pExists)
      //   {
      //      int nAvailables = lpWnd->DataQueue->search_group( lpWnd->ActivedGroupID )->SearchAvailables(nValue);
      //      /**/
      //      lpWnd->ListDataOfGrid->append( std::shared_ptr<DataGrid>( new bb::DataGrid
      //      {
      //         nRow,
      //         nCol,
      //         nValue,
      //         nPage,
      //         lpWnd->GetActivedGroupID(),
      //         nAvailables,
      //         true
      //      } ) );
      //   }
      //}
   }
   //-----------------------------------------------------------------------------------------------//
   void spreadsheet_box_entry_numbers::delete_numbers_on_data_grid_impl(
      std::shared_ptr<std::vector<std::lineedit *>> const & list_ptr)
   {
      //int nRow = m_page->text().toInt();
      //int nPage = nRow;
      //int nCol = 0;
      ////
      //for(auto i = pList->begin(); i != pList->end(); i++)
      //{
      //   auto * lpWnd = dynamic_cast<bb::mdichildwindow_special_combination *>(std::vertical_box::parent());
      //   std::shared_ptr<bb::DataGrid> & pData = lpWnd->GetListDataOfGrid()->
      //      Search(nRow, nCol, nPage, lpWnd->GetActivedGroupID());
      //   //
      //   lpWnd->GetDataQueue()->delete_number(lpWnd->GetActivedGroupID(), nPage, pData->Value);
      //   lpWnd->GetListDataOfGrid()->removeOne(pData);
      //}
   }
   //-----------------------------------------------------------------------------------------------//
   void spreadsheet_box_entry_numbers::put_numbers_for_edition(std::vector<bb::controller::pages> & pages)
   {
      auto n_pos = 0;
      //
      std::for_each(pages.begin(), pages.end(), [&](controller::pages const & page)
      {
         m_data_list->at(n_pos++)->setText(std::unicodestring{ "%1" }.arg(page.page_id));
      });
      //remove all numbers
      pages.clear();
   }
   //-----------------------------------------------------------------------------------------------//
}