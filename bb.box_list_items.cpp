//-----------------------------------------------------------------------------------------------//
// xbw32 for Windows (generate of numeric combinations for bingo or lotery)
//
// Created by wilsonsouza 2013, 2018
//
// WR Devinfo
// (c) 2012, 2013, 2014, 2015, 2016, 2017, 2018
//-----------------------------------------------------------------------------------------------//
#include <std.waitcursor.hpp>
#include <std.treewidget.hpp>
#include <std.checkbox.hpp>
#include <std.widget_impl.hpp>
#include <std.treewidgetitem.hpp>
#include <std.lineedit.hpp>
#include <bb.mdichildwindow.hpp>
#include <bb.box_list_items.hpp>
#include <bb.box_page_numbers.hpp>
#include <bb.box_select_group_page.hpp>
#include <bb.table_interface.hpp>
#include <bb.MDIFrameWindow.hpp>

namespace bb
{
   //-----------------------------------------------------------------------------------------------//
   box_list_items::box_list_items(bb::mdichildwindow * child) :
      std::tabbed{ this, "IDD_LIST_ITEMS" },
      task_group{},
      m_child{ child },
      m_vbox{ new std::widget_impl<std::vertical_box>{ this, std::unicodestring{} } },
      m_list_items{ new std::treewidget{ this } }
   {
      /**/
      m_list_items->setHeaderLabels(bb::captions::box_list_items{}.
                                    HEADERLISTNAMES.
                                    split(bb::captions::box_list_items{}.TOKENSEPARATOR));
      /**/
      m_is_display_box_select_group_page = new std::checkbox
      {
         this, std::unicodestring{"Apresentar tela para edição de cartelas"}, "IDD_DISPLAYBOXSELECTGROUPPAGE"
      };
      /**/
      m_is_auto_reload = new std::checkbox
      {
         this, std::unicodestring{"Recarregar a lista de cartelas automaticamente"}, "IDD_AUTOMATICRELOAD"
      };
      /**/
      addTab(m_vbox, "Grupo(s) completo(s)...");
   }
   //-----------------------------------------------------------------------------------------------//
   box_list_items *  box_list_items::create()
   {
      auto box_page_numbers = m_child->m_box_page_numbers;
      auto box_numbers = m_child->m_box_numbers;
      auto box_select_page = m_child->m_box_select_group_page;
      auto hbox = new std::horizontal_box{};
      {
         hbox->addWidget(m_is_display_box_select_group_page);
         hbox->addWidget(m_is_auto_reload);
      }

      m_vbox->box()->addWidget(m_list_items);
      m_vbox->box()->addLayout(hbox);
      //load records in pplx mode
      load_table_numbers();
      //
      m_list_items->on_item_clicked = [&](QTreeWidgetItem * item, int const & column, std::treewidget * sender)->auto
      {
         if (sender->parent()->parent()->objectName() == std::captions::file{}.OPEN)
         {
            auto queue = std::shared_ptr<std::stringlist>{ new std::stringlist(item->text(2).split(",")) };
            /**/
            if (queue->size() < m_child->base->information->numbers_to_page)
            {
               return false;
            }
            /**/
            if (queue->indexOf("-1") != -1)
            {
               return false;
            }
            /**/
            box_page_numbers->setVisible(true);
            box_page_numbers->update_lcdnumbers(queue.operator->());
            /***/
            m_current_item = static_cast<std::treewidgetitem *>(item);
            //
            if (m_current_item->text(0) != m_actual_group && m_is_display_box_select_group_page->isChecked())
            {
               box_numbers->update_lcdnumber_all(m_current_item->text(0).trimmed().toUpper());
               m_actual_group = m_current_item->text(0);
            }
         }
         return true;
      };
      //
      m_is_display_box_select_group_page->on_state_changed = [&](uint state, std::checkbox * sender)->auto
      {
         box_select_page->setVisible(state == Qt::Checked);
         box_numbers->setVisible(state == Qt::Checked);
         return true;
      };
      //
      m_is_auto_reload->on_state_changed = [&](uint state, std::checkbox * sender)->auto
      {
         sender->setChecked(state == Qt::Checked);
         return true;
      };
      //
      m_is_display_box_select_group_page->setChecked(box_select_page->isVisible());
      box_numbers->setVisible(box_select_page->isVisible());
      return this;
   }
   //-----------------------------------------------------------------------------------------------//
   void const  box_list_items::load_table_numbers()
   {
      try
      {
         auto cursor_wait = std::shared_ptr<std::waitcursor>{ new std::waitcursor{m_child} };
         auto completed_group = std::unicodestring{ };
         auto n_completed_group = 0;
         auto table = table_numbers::pointer{ new table_numbers{m_child} };
         auto display = m_child->create_display_progressbar();
         //create progress bar
         table->orderby = defs::db::datasource{}.SQL_CMD_ORDERBY.
            bind(std::unicodestring{ "%1, %2, %3" }.
                 bind(defs::db::datasource{}.FLD_NUM_GROUPNAME).
                 bind(defs::db::datasource{}.FLD_NUM_PAGENAME).
                 bind(defs::db::datasource{}.FLD_NUM_NUMBERS));
         table->read(std::unicodestring{}, -1);
         m_list_items->clear();
         /**/
         if (table->groups->size() > 0)
         {
            display->create(table->groups->size(), "Aguarde, indexando dados...");
         }
         else
         {
            return;
         }
         //set record count
         auto current_rows = 0;
         /* run by pplx */
         std::for_each(table->groups->begin(),
                       table->groups->end(), [&](bb::controller::groups const & groups)
         {
            std::for_each(groups.pages.begin(), groups.pages.end(), [&](controller::pages const & pages)
            {
               auto column = new QTreeWidgetItem{};
               /**/
               ++current_rows;
               /**/
               column->setText(0, groups.group_id);
               column->setText(1, std::unicodestring().sprintf("%03d", pages.page_id));
               column->setText(2, pages.numbers_to_stringlist()->join(","));
               column->setText(3, std::unicodestring("%1").arg(current_rows));
               column->setText(4, std::unicodestring("%1").arg(groups.calculate_available_numbers()));
               column->setText(5, pages.is_completed ? "Sim" : std::unicodestring("Não"));
               column->setIcon(5, pages.is_completed ? std::icons::common{}.OK : std::icons::common{}.DENIED);
               column->setData(0, Qt::UserRole, std::unicodestring{ "%1" }.
                               arg(groups.group_id).sprintf("%03d", pages.page_id));
               /**/
               if (completed_group.empty())
               {
                  completed_group = groups.group_id;
                  ++n_completed_group;
               }
               //
               if (completed_group != groups.group_id)
               {
                  ++n_completed_group;
                  completed_group = groups.group_id;
               }
               //
               m_list_items->addTopLevelItem(column);
               this->setTabText(0, std::unicodestring
                                {
                                   "Grupo(s) %1 e Cartela(s) %2 completa(s)..."
                                }.
                                bind(n_completed_group, 0));
               /**/
               display->get_sub_caption()->setText(std::unicodestring
                                                   {
                                                      "Grupo %1 cartela %2"
                                                   }.bind(groups.group_id, pages.page_id));
               /**/
               m_child->get_frame()->dispatch_eventlooper(true);
            });
            /**/
            display->update(display->objectName());
         });
      }
      catch (std::exception const & e)
      {
         QMessageBox::warning(parentWidget(), std::captions::errors{}.WARNING, e.what());
      }
   }
   //-----------------------------------------------------------------------------------------------//
   void const  box_list_items::update_items(std::stringlist const * string_items)
   {
      auto box_select_page = m_child->m_box_select_group_page;
      auto fmt = std::unicodestring{ "%1" }.
         arg(box_select_page->m_group_id->text().trimmed()).
         sprintf("%03d", box_select_page->m_page_id->text().toInt());
      QTreeWidgetItem * item_data = m_list_items->finddata(fmt, 0);
      /**/
      if (item_data)
      {
         auto f = font();
         {
            f.setBold(true);
            f.setItalic(true);
         }
         /**/
         item_data->setFont(0, f);
         item_data->setText(2, string_items->join(","));
      }
   }
}
