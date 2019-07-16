//-----------------------------------------------------------------------------------------------//
// xbw32 for Windows (generate of numeric combinations for bingo or lotery)
//
// Created by wilsonsouza 2013, 2018
//
// WR Devinfo
// (c) 2012, 2013, 2014, 2015, 2016, 2017, 2018
//-----------------------------------------------------------------------------------------------//
#include <std.lcdnumber.hpp>
#include <std.widget_impl.hpp>
#include <std.layouts.hpp>
#include <bb.mdichildwindow.hpp>
#include <bb.box_numbers.hpp>
#include <bb.group_manager.hpp>
#include <bb.box_list_items.hpp>
#include <bb.box_select_group_page.hpp>
#include <bb.table_interface.hpp>
#include <bb.MDIFrameWindow.hpp>
//-----------------------------------------------------------------------------------------------//
namespace bb
{
   //-----------------------------------------------------------------------------------------------//
   box_numbers::box_numbers(bb::mdichildwindow * child) :
      std::tabbed{ child, "IDD_BOX_NUMBERS" },
      m_child{ child },
      m_vbox{ new std::widget_impl<std::vertical_box>{ this, std::unicodestring{} } }
   {
      m_numbers_queue = property_numbers_box::alloc_data();
      addTab(m_vbox, std::unicodestring("Números disponíveis..."));
      //
      setVisible(!(m_child->std::mdichildwindow::objectName() == std::captions::file{}.OPEN));
   }
   //-----------------------------------------------------------------------------------------------//
   box_numbers *  box_numbers::create()
   {
      auto child = m_child;
      auto n_start = child->base->information->is_allowed_zero;
      auto n_nums = child->base->information->numbers;
      //
      for (int i = n_start; i <= n_nums; )
      {
         auto row = new std::horizontal_box{};
         int n_max_columns = 0x11;
         //
         for (int x = n_start; x < n_max_columns && i <= n_nums; ++i, ++x)
         {
            auto lcd = new std::lcdnumber
            {
               nullptr, 2, bb::captions::internal_editions{}.LCD.arg(i)
            };
            //
            lcd->display(child->base->information->numbers_to_group);
            lcd->setFixedSize(0x20, 0x20);
            lcd->setPalette(Qt::blue);
            row->addWidget(lcd);
            row->addStretch();
            /**/
            QPalette oPalette;
            {
               oPalette.setColor(QPalette::Foreground, Qt::black);
               oPalette.setColor(QPalette::Background, Qt::blue);
               lcd->setPalette(oPalette);
            }
            /**/
            m_numbers_queue->emplace(i, lcd);
         }
         //
         row->addStretch();
         m_vbox->box()->addLayout(row);
      }
      //
      m_vbox->box()->addStretch();
      return this;
   }
   //-----------------------------------------------------------------------------------------------//
   std::lcdnumber * box_numbers::get_lcdnumber_by_id(int value)
   {
      auto result = m_numbers_queue->find(value);
      return (result != m_numbers_queue->end() ? result->second : nullptr);
   }
   //-----------------------------------------------------------------------------------------------//
   void box_numbers::update_lcdnumbers(std::stringlist const * queue)
   {
      std::for_each(queue->cbegin(), queue->cend(), [&](auto const & value)
      {
         auto lcd = get_lcdnumber_by_id(value.toInt());
         //
         if (lcd != nullptr)
         {
            lcd->display(value);
         }
      });
   }
   //-----------------------------------------------------------------------------------------------//
   void box_numbers::update_lcdnumber_available(int const & value)
   {
      //auto & l = ChildWnd->NumbersList;
      //auto pExists = std::find_if( l->begin(), l->end(), [&] ( std::shared_ptr<PropertyNumber> p )
      //{
      //   return ( p->Number == nValue );
      //} ).operator*( );
      ///**/
      //if(pExists)
      //{
      //   auto pBox = m_QueueNumber->value(pExists->Number);
      //   {
      //      if (pBox)
      //         pBox->Handle->display(pExists->Available);
      //   }
      //}
   }
   //-----------------------------------------------------------------------------------------------//
   void box_numbers::update_lcdnumber_all(std::unicodestring const & group)
   {
      auto child = dynamic_cast<bb::mdichildwindow *>(parentWidget());
      auto & d = child->update_table_resource_on_memory(group);
      auto n_start = child->base->information->is_allowed_zero;
      /**/
      //for (int n = nStart; n <= m_ChildWnd->Numbers; ++n)
      //{
      //   std::shared_ptr<PropertyNumber> pExists = nullptr;  
      //   auto & l = ChildWnd->NumbersList;
      //   std::find_if( l->begin(), l->end(), [&] ( std::shared_ptr<PropertyNumber> p )
      //   {
      //      if ( p->Number == n )
      //      {
      //         pExists = p;
      //      }
      //      return ( p->Number == n );
      //   } );
      //   /**/
      //   if(pExists)
      //   {
      //      auto pBox = m_QueueNumber->value(pExists->Number);
      //      {
      //         if (pBox)
      //            pBox->Handle->display(pExists->Available);
      //      }
      //   }
      //}
   }
   //-----------------------------------------------------------------------------------------------//
}



