//-----------------------------------------------------------------------------------------------//
// xbw32 for Windows (generate of numeric combinations for bingo or lotery)
//
// Created by wilsonsouza 2013, 2018
//
// WR Devinfo
// (c) 2012, 2013, 2014, 2015, 2016, 2017, 2018
//-----------------------------------------------------------------------------------------------//
#include <bb.mdichildwindow.hpp>
#include <bb.box_page_numbers.hpp>
#include <bb.group_manager.hpp>
#include <std.lcdnumber.hpp>

namespace bb
{
   //-----------------------------------------------------------------------------------------------//
   box_page_numbers::box_page_numbers(bb::mdichildwindow * child) :
      box_numbers{ child }
   {
      setObjectName("IDD_BOX_PAGE_NUMBERS");
      this->setTabText(0, std::unicodestring{ "Números selecionados" });
   }
   //-----------------------------------------------------------------------------------------------//
   box_page_numbers *  box_page_numbers::create()
   {
      auto child = m_child;
      int n_start = child->base->information->is_allowed_zero;
      int n_max = child->base->information->numbers_to_page + n_start;
      /**/
      for (auto i = n_start; i < n_max;)
      {
         auto row = new std::horizontal_box{};
         int n_max_columns = 0x11;
         //
         for (auto x = n_start; x < n_max_columns && i < n_max; ++i, ++x)
         {
            auto lcd = new std::lcdnumber
            {
               nullptr, 2, bb::captions::internal_editions{}.LCD.arg(i)
            };
            /**/
            {
               lcd->display(0);
               lcd->setFixedSize(0x20, 0x20);
               lcd->setPalette(Qt::blue);
               row->addWidget(lcd);
               row->addStretch();
            }
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
         m_vbox->box()->addLayout(row);
      }
      //
      m_vbox->box()->addStretch();
      return this;
   }
   //-----------------------------------------------------------------------------------------------//
   void box_page_numbers::update_lcdnumbers(std::stringlist const * queue)
   {
      try
      {
         for(auto & value: *m_numbers_queue)
         {
            if (value.first <= queue->size())
            {
               value.second->display(queue->at(value.first - 1));
            }
         }
      }
      catch (...)
      {
         QMessageBox::warning(m_child, 
                              std::captions::errors{}.WARNING, 
                              std::unicodestring{ "Exception detected!!!" });
      }
   }
   //-----------------------------------------------------------------------------------------------//
}