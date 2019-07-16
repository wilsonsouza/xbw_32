//-----------------------------------------------------------------------------------------------//
// xbw32 for Windows (generate of numeric combinations for bingo or lotery)
//
// Created by wilsonsouza 2013, 2018
//
// WR Devinfo
// (c) 2012, 2013, 2014, 2015, 2016, 2017, 2018
//-----------------------------------------------------------------------------------------------//
#include <std.checkbox.hpp>
#include <std.radiobutton.hpp>
#include <std.button.hpp>
#include <std.lineedit.hpp>
#include <std.table.hpp>
#include <std.label.hpp>
#include <bb.data_queue_controller.hpp>
#include <bb.groups_controller.hpp>
#include <bb.pages_controller.hpp>
#include <bb.mdichildwindow_special_combination.hpp>
#include <std.groupbox_impl.hpp>
#include <bb.group_manager.hpp>
#include <bb.spreadsheet_insert.hpp>

namespace bb
{
   //-----------------------------------------------------------------------------------------------//
   spreadsheet_insert::spreadsheet_insert(bb::mdichildwindow_special_combination * child) :
      std::widget_impl < std::gridbox >{ this, "IDD_SPREADSHEET_INSERT" }
   {
      m_cancel = new std::button{ this, std::captions::common{}.CANCEL, std::icons::common{}.CANCEL };
      m_insertin_all_pages_of_all_groups = new std::radiobutton{ this,
         "Inserir em todas as cartelas dos grupos", std::unicodestring{}, true, false };
      m_number_id = new std::lineedit{ "NumberID", 2, 0x32 };
      m_ok = new std::button{ this, std::captions::common{}.OK, std::icons::common{}.OK };
      m_selectin_that_pages_wish_inserted = new std::radiobutton{ this,
         "Selecionar em quais cartelas deseja inserir", std::unicodestring{}, true, false };
      m_table_pages = new std::table{ this };
   }
   //-----------------------------------------------------------------------------------------------//
   QWidget *  spreadsheet_insert::create()
   {
      auto pNumber = new std::groupbox_impl<std::formbox>{ this, "Número" };
      {
         pNumber->box()->addRow(new std::label{ this, "Digite o número à inserir" }, m_number_id);
         pNumber->adjustSize();
         /**/
         m_number_id->on_text_changed = [&](std::unicodestring const & data, std::lineedit * sender)
         {
            if (data.empty())
            {
               m_enable_selected |= 1;
            }
            else
            {
               m_enable_selected &= ~1;
            }
            return true;
         };
      }
      /**/
      auto pOptions = new std::groupbox_impl<std::vertical_box>{ this,"Opções" };
      {
         pOptions->box()->addWidget(this->m_insertin_all_pages_of_all_groups);
         pOptions->box()->addWidget(this->m_selectin_that_pages_wish_inserted);
         //
         m_insertin_all_pages_of_all_groups->on_clicked = [&](bool const &, std::radiobutton * sender)
         {
            this->create_header_table_pages(MODE::TBL_CREATE_HEADER_TO_GROUPS);
            this->fill_table_pages(MODE::TBL_ALL_GROUPS);
            m_enable_selected |= 1;
            return m_enable_selected;
         };
         //
         m_selectin_that_pages_wish_inserted->on_clicked = [&](bool const &, std::radiobutton * sender)
         {
            this->create_header_table_pages(MODE::TBL_CREATE_HEADER_TO_PAGES);
            this->fill_table_pages(MODE::TBL_SELECT_PAGES);
            m_enable_selected |= 1;
            return m_enable_selected;
         };
      }
      //
      auto pPages = new std::groupbox_impl<std::vertical_box>{ this, "Cartelas" };
      {
         this->create_header_table_pages(MODE::TBL_CREATE_HEADER_TO_PAGES);
         pPages->box()->addWidget(m_table_pages);
      }
      //
      auto pButtons = new std::widget_impl<std::horizontal_box>{ this, std::unicodestring{} };
      {
         pButtons->box()->addWidget(this->m_ok);
         pButtons->box()->addWidget(this->m_cancel);
         pButtons->box()->addStretch();
         //
         m_ok->on_clicked = [&](bool const &, std::button * sender)
         {
            return true;
         };
         //
         m_cancel->on_clicked = [&](bool const &, std::button * sender)
         {
            return true;
         };
      }
      //
      auto lay = box();
      {
         lay->addLayout(new define_layout_control<>(pNumber), 0, 0, 1, 1);
         lay->addLayout(new define_layout_control<>(pOptions), 0, 1, 1, 1);
         lay->addWidget(pPages, 0, 2, 1, 1);
         lay->addWidget(pButtons, 1, 0);
      }
      return this;
   }
   //-----------------------------------------------------------------------------------------------//
   void spreadsheet_insert::fill_table_pages(MODE const& mode)
   {
      auto n_line = 0;
      //
      if (mode == MODE::TBL_ALL_GROUPS)
      {
         m_table_pages->setRowCount(m_child->groups->size() * m_child->base->information->pages_to_group);
         //
         for (auto & groups : *m_child->groups)
         {
            auto top_group = groups.group_id;
            //
            std::for_each(groups.pages.begin(), groups.pages.end(), [&](controller::pages const & page)
            {
               auto checkbox_id = new std::checkbox{ this, top_group };
               auto page_name = std::unicodestring{ "%1" }.arg(page.page_id);
               //
               m_table_pages->setCellWidget(n_line, 0, checkbox_id);
               m_table_pages->setItem(n_line, 1, new QTableWidgetItem(page_name));
               m_table_pages->setItem(n_line, 2, new QTableWidgetItem("Nenhuma"));
               //
               ++n_line;
               //
               checkbox_id->on_state_changed = [=](uint state, std::checkbox * sender)
               {
                  m_ok->setEnabled(sender->isChecked() && m_enable_selected);
                  return true;
               };
            });
         }
      }
      else if (mode == MODE::TBL_SELECT_PAGES)
      {
         auto groups = std::find_if(m_child->groups->begin(),
                                    m_child->groups->end(), controller::groups{ m_child->actived_group_id });
         //
         m_table_pages->setRowCount(groups->pages.size());
         //
         std::for_each(groups->pages.begin(), groups->pages.end(), [&](controller::pages const & page)
         {
            auto page_name = std::unicodestring{ "%1" }.arg(page.page_id);
            std::checkbox * checkbox_id = new std::checkbox{ this, page_name };

            m_table_pages->setCellWidget(n_line, 0, checkbox_id);
            m_table_pages->setItem(n_line, 1, new QTableWidgetItem("Nenhuma"));
            /**/
            ++n_line;
            /**/
            checkbox_id->on_state_changed = [=](uint state, std::checkbox * sender)
            {
               m_ok->setEnabled(sender->isChecked() && m_enable_selected);
               return true;
            };
         });
         /**/
         m_child->set_default_table_width_height(m_table_pages);
      }
   }
   //-----------------------------------------------------------------------------------------------//
   void spreadsheet_insert::create_header_table_pages(MODE const & mode)
   {
      auto labels = std::stringlist{};
      //
      if (mode == MODE::TBL_CREATE_HEADER_TO_GROUPS)
      {
         labels = std::stringlist{ "Grupo", "Cartela", std::unicodestring { "Ação" } };
      }
      else if (mode == MODE::TBL_CREATE_HEADER_TO_PAGES)
      {
         labels = std::stringlist{ "Cartela", std::unicodestring { "Ação" } };
      }
      /**/
      m_table_pages->setColumnCount(labels.size());
      m_table_pages->setHorizontalHeaderLabels(labels);
   }
   //-----------------------------------------------------------------------------------------------//
}