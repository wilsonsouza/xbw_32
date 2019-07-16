//-----------------------------------------------------------------------------------------------//
// xbw32 for Windows (generate of numeric combinations for bingo or lotery)
//
// Created by Wilson.Souza 2012
// For 
//
// WR Devinfo
// (c) 2012, 2013 2014
//-----------------------------------------------------------------------------------------------//
#include <bb.group_manager.hpp>
#include <bb.mdichildwindow.hpp>
#include <std.display_progressbar.hpp>
#include <bb.box_menu_tools.hpp>
#include <sql.table.hpp>
#include <bb.table_interface.hpp>
#include <bb.MDIFrameWindow.hpp>

namespace bb
{
   //-----------------------------------------------------------------------------------------------//
   box_menu_tools::box_menu_tools(bb::mdichildwindow * child) :
      std::display_progressbar{ child->get_frame(), child },
      m_child{ child }
   {
   }
   //-----------------------------------------------------------------------------------------------//
   bool const box_menu_tools::verify_complete_pages()
   {
      auto records = table_numbers::pointer{ new table_numbers { m_child } };
      /**/
      create(records->groups->size(), "Aguarde, verificando cartela(s)...");
      /**/
      records->orderby = std::unicodestring{ " %1 %2 " }.
         bind(defs::db::datasource{}.FLD_NUM_GROUPNAME).
         bind(defs::db::datasource{}.FLD_NUM_PAGENAME);
      records->read(std::unicodestring{}, -1);
      /**/
      std::for_each(records->groups->begin(),
                    records->groups->end(),
                    [&](controller::groups & record)
      {
         for (auto & page : record.pages)
         {
            if (!page.is_completed)
            {
               if (page.numbers.size() == records->base->information->numbers_to_page)
               {
                  auto iscompleted_update = table_numbers::pointer{ new table_numbers { m_child } };
                  /**/
                  page.is_completed = true;
                  iscompleted_update->update(record.group_id, page.page_id, -1);
               }
            }
            /**/
            //while(!pRecords->Eof)
            //{
            //   sql::Field * pIsCompleted = pRecords->operator[](std::unicodestring("iscompleted"));
            //   sql::Field * pGroup = pRecords->operator[](std::unicodestring("groupname"));
            //   sql::Field * pPage = pRecords->operator[](std::unicodestring("pagename"));
            //   std::shared_ptr<bb::DataNumber> pData(new bb::DataNumber());
            //   /**/
            //   pWnd->LoadRecord(pGroup->Text, pPage->Integer, pData);
            //   /**/
            //   if(pIsCompleted->Integer == 0)
            //   {
            //      if(pData->Numbers->size() == pWnd->NumbersByPage)
            //      {
            //         std::unicodestring szSql = std::unicodestring
            //         {
            //            "update %1.dbo.%2 set iscompleted = %3 where groupname = '%4' and pagename = %5"
            //         }.arg(pWnd->CatalogName).
            //         arg(szDbName).
            //         arg(1).
            //         arg(std::unicodestring(pGroup->Text)).
            //         arg(pPage->Integer);
            //            /**/
            //         m_FrameWindow->GetSingleQueryLanguageHandle()->ExecutenonQuery(szSql);
            //      }
            //   }
            //   /**/
            //   pRecords->Next();
            update("Verificando cartela(s)....");
            get_sub_caption()->setText(std::unicodestring{ "Grupo %1 cartela %2..." }.
                                       arg(record.group_id).
                                       arg(page.page_id));
         }
      });
      /**/
      return false;
   }
   //-----------------------------------------------------------------------------------------------//
}