//-----------------------------------------------------------------------------------------------//
// xbw32 for Windows (generate of numeric combinations for bingo or lotery)
//
// Created by wilsonsouza 2013, 2018
//
// WR Devinfo
// (c) 2012, 2013, 2014, 2015, 2016, 2017, 2018
//-----------------------------------------------------------------------------------------------//
#pragma once
#include <std.button.hpp>
#include <std.lineedit.hpp>
#include <std.treewidget.hpp>
#include <std.treewidgetitem.hpp>
#include <bb.mdichildwindow.hpp>
#include <bb.box_buttons.hpp>
#include <bb.box_information.hpp>
#include <bb.box_select_group_page.hpp>
#include <bb.box_editions.hpp>
#include <bb.box_list_items.hpp>
#include <bb.box_numbers.hpp>
#include <bb.table_interface.hpp>
//-----------------------------------------------------------------------------------------------//
namespace bb
{
   box_buttons::box_buttons(bb::mdichildwindow * child) :
      std::horizontal_box{ child, "IDD_BOX_BUTTONS" }, 
      m_child{ child }
   {
      /**/
      m_ok = new std::button{ nullptr, std::captions::common{}.OK, std::icons::common{}.OK, "IDD_OK" };
      m_cancel = new std::button{ nullptr, std::captions::common{}.CANCEL, std::icons::common{}.CANCEL, "IDD_CANCEL" };
      m_help = new std::button{ nullptr, std::captions::common{}.HELP, std::icons::common{}.HELPINDEX, "IDD_HELP" };
   }
   //-----------------------------------------------------------------------------------------------//
   box_buttons *  box_buttons::create()
   {
      addWidget(m_ok);
      addWidget(m_cancel);
      addWidget(m_help);
      addStretch();
      //
      m_ok->on_clicked = [&](bool const & checked, std::button * sender)->auto
      {
         auto data = m_child->get_field_editions(bb::captions::internal_editions{}.NUMBERS);
         //
         if (!is_allowed_duplicate_groups())
         {
            return false;
         }
         //
         if (!is_allowed_duplicate_page())
         {
            return false;
         }
         //
         if (data->write(m_child->actived_group_id, m_child->actived_page_id).m_successed)
         {
            m_child->m_box_editions->set_clear_editions();
            m_child->m_box_editions->set_enable_editions(true);
            this->next_page();
            m_ok->setEnabled(false);
            /**/
            if (m_child->m_box_list_items->m_is_auto_reload->isChecked())
            {
               m_child->m_box_list_items->load_table_numbers();
            }
         }
         return true;
      };
      //
      m_cancel->on_clicked = [&](bool const &, std::button * sender)
      {
         m_child->m_box_editions->set_clear_editions();
         m_child->m_box_editions->set_enable_editions(false);
         /**/
         m_child->m_box_select_group_page->m_group_id->setEnabled(true);
         m_child->m_box_select_group_page->m_page_id->setEnabled(true);
         m_child->m_box_select_group_page->m_group_id->setFocus();
         /**/
         m_ok->setEnabled(false);
         return true;
      };
      //
      m_help->on_clicked = [&](bool const &, std::button * sender)
      {
         return true;
      };
      return this;
   }
   //-----------------------------------------------------------------------------------------------//
   std::stringlist  box_buttons::get_list_of_current_edited_numbers()
   {
      auto s = std::stringlist{};
      {
         for (auto & e : m_child->m_box_editions->m_edit_queue)
         {
            s.push_back(e->text().trimmed());
         }
      }
      /**/
      return s;
   }
   //-----------------------------------------------------------------------------------------------//
   std::unicodestring  box_buttons::prepare_query_complement(std::stringlist const & queue)
   {
      return std::unicodestring
      {
         " numbers in(%1) order by groupname, pagename "
      }.arg(queue.join(","));
   }
   //-----------------------------------------------------------------------------------------------//
   void  box_buttons::next_page()
   {
      auto n = m_child->m_box_select_group_page->m_page_id->text().toInt();
      auto box_numbers = m_child->m_box_numbers;
      auto box_select_page = m_child->m_box_select_group_page;
      //
      if (n < m_child->base->information->pages_to_group)
      {
         auto next_value = box_select_page->m_group_id->text().trimmed();
         /**/
         n++;
         box_numbers->update_lcdnumber_all(next_value.toUpper());
         box_select_page->m_page_id->setText(std::unicodestring{}.sprintf("%02d", n));
         box_select_page->m_page_id->setEnabled(true);
         /**/
         box_select_page->m_page_id->on_return_pressed(box_select_page->m_page_id);
         box_select_page->m_page_id->setFocus();
      }
   }
   //-----------------------------------------------------------------------------------------------//
   bool  box_buttons::is_allowed_duplicate_groups()
   {
      using namespace std;
      //duplicate on group
      //if(!ChildWnd->BoxInformation->IsAllowedDuplicateNumbersOnGroups->Checked)
      //{
      //   std::unicodestring szQuery = std::unicodestring("groupname like '%1' and ").arg(ChildWnd->BoxSelectGrouppage->GroupId->Text.right(1));
      //   //
      //   szQuery += PrepareQueryComplement(GetListOfCurrentEditedNumbers());
      //   //
      //   std::shared_ptr<sql::Table> pResult = ChildWnd->DataSource->Select(bb::TBL_NUMBERS_NAME, nullptr, szQuery);
      //   //
      //   if(pResult != nullptr)
      //   {
      //      if(!pResult->Eof)
      //      {
      //         QMessageBox::warning(ChildWnd, 
      //            std::Errors::WARNING, 
      //            ustring("Sequencia de números %1 ja existe!").arg(GetListOfCurrentEditedNumbers().join(",")));
      //         return false;
      //      }
      //   }
      //}
      return true;
   }
   //-----------------------------------------------------------------------------------------------//
   bool  box_buttons::is_allowed_duplicate_page()
   {
      using namespace std;
      bool success = true;
      //duplicate pages
      //if (!ChildWnd->GetBoxInformation()->GetIsAllowedDuplicatePages()->isChecked())
      //{
      //   ustring szQuery = PrepareQueryComplement(GetListOfCurrentEditedNumbers());
      //   shared_ptr<sql::Table> pResult = ChildWnd->DataSource->Select(bb::TBL_NUMBERS_NAME, nullptr, szQuery);
      //   //
      //   if(pResult != nullptr)
      //   {
      //      auto pData = ChildWnd->GetFieldEditions(std::unicodestring());
      //      {
      //         ChildWnd->LoadTable(pResult);
      //      }
      //      /**/
      //      if (ChildWnd->GetDataList()->size() > 0)
      //      {
      //         auto d = ChildWnd->GetDataList();
      //         /**/
      //         std::for_each(d->begin(), d->end(), [&](std::shared_ptr<DataNumber> p)
      //         {
      //            int nCount = 0;
      //            auto pKeys = std::shared_ptr<QList<int>>(new QList<int>(pData->keys()));
      //            /**/
      //            std::for_each( pKeys->begin(), pKeys->end(), [&]( int nValue )
      //            {
      //               std::find_if( p->Numbers->begin(), p->Numbers->end(), [&] ( int nNum )
      //               {
      //                  if ( nNum == nValue )
      //                  {
      //                     nCount++;
      //                  }
      //                  return( nNum == nValue );
      //               } );
      //            } );
      //            /**/
      //            if(nCount == pData->count())
      //            {
      //               auto pFmt = std::shared_ptr<std::stringlist>(new std::stringlist());
      //               /**/
      //               std::for_each( pKeys->begin(), pKeys->end(), [&] ( int n )
      //               {
      //                  pFmt->append( std::unicodestring { "%1" }.arg(n) );
      //               } );
      //               /**/
      //               QMessageBox::warning(ChildWnd, std::Errors::WARNING,
      //                  std::unicodestring
      //               {
      //                  "Cartela %1 do grupo %2, já existe!\nSequencia de números [%3]!" 
      //               }.
      //               arg(p->Page).
      //               arg(p->Group).
      //               arg(pFmt->join(",")));
      //               /**/
      //               bSuccess = false;
      //               return;
      //            }
      //         });
      //      }
      //   }
      //}
      return success;
   }
}