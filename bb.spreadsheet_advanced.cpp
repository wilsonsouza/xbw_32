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
#include <std.table.hpp>
#include <bb.mdichildwindow.hpp>
#include <bb.mdichildwindow_special_combination.hpp>
#include <std.button.hpp>
#include <bb.group_manager.hpp>
#include <bb.spreadsheet_advanced.hpp>
#include <bb.data_queue_controller.hpp>
#include <bb.groups_controller.hpp>
#include <bb.pages_controller.hpp>
#include <std.groupbox_impl.hpp>

namespace bb
{
   //-----------------------------------------------------------------------------------------------//
   spreadsheet_advanced::spreadsheet_advanced(bb::mdichildwindow_special_combination * child) :
      std::widget_impl<std::gridbox>{ this, "IDD_SPREADSHEET_ADVANCED" },
      m_child{ child }
   {
      m_ok = new std::button{ nullptr, std::captions::common{}.OK, std::icons::common{}.OK, "", false };
      m_cancel = new std::button{ nullptr, std::captions::common{}.CANCEL, std::icons::common{}.CANCEL, "", true };
      m_table_actived_group = new std::table{ nullptr, 0, 0, "IDD_SPREADSHEET_ADVANCED_ACTIVED_TABLE_GROUP" };
   }
   //-----------------------------------------------------------------------------------------------//
   QWidget * spreadsheet_advanced::create()
   {
      auto selected_group = new std::groupbox_impl<std::vertical_box>(this, "Selecione o grupo");
      {
         auto row = 0;
         /**/
         selected_group->box()->addWidget(m_table_actived_group);
         //fill table
         m_table_actived_group->setColumnCount(2);
         m_table_actived_group->setRowCount(1); //m_ChildWnd->GetDataQueue()->size());
         //
         auto header_list = std::shared_ptr<std::stringlist>{ new std::stringlist{} };
         auto label_list = std::shared_ptr<std::stringlist>{ new std::stringlist{} };
         //
         header_list.operator*() << "Grupos" << "Selecionado";
         m_table_actived_group->setHorizontalHeaderLabels(*header_list);
         //set default row column with and height
         m_child->set_default_table_width_height(m_table_actived_group);
         //
         std::for_each(m_child->groups->begin(), 
                       m_child->groups->end(), [&](controller::groups & group)
         {
            auto actived = this->create_object_list(&group, row);
            //
            actived->on_clicked = [&](bool const & clicked, std::radiobutton * sender)
            {
               m_ok->setEnabled(m_table_item && !m_old_actived_group.empty());
               return true;
            };
            //next row
            row++;
         });
         //
         m_table_actived_group->on_cell_clicked = [&](int row, int col, std::table * sender)
         {
            auto control = m_table_actived_group->cellWidget(row, col);
            /**/
            if ((m_table_item = m_table_actived_group->item(row, col)))
            {
               m_old_actived_group = m_table_item->data(Qt::UserRole).toString();
            }
            /**/
            if (control && m_table_item)
            {
               auto ctrl = reinterpret_cast<std::radiobutton *>(control);
               //
               m_ok->setEnabled(ctrl->isChecked());
               std::dispatch_event_by_pplx(m_child, ctrl->on_clicked, true, ctrl);
               std::dispatch_event_by_pplx(m_child, m_ok->on_clicked, true, m_ok);
            }
            return true;
         };
      }
      //
      auto buttons = new std::widget_impl<std::horizontal_box>{ this, std::unicodestring{} };
      {
         buttons->box()->addWidget(m_ok);
         buttons->box()->addWidget(m_cancel);
         buttons->box()->addStretch();
         //
         m_ok->on_clicked = [&](bool const & checked, std::button * sender)
         {
            //m_child->SetActivedGroupID(m_OldActivedGroup);
            //m_ChildWnd->OnNotify(m_ChildWnd, ON_UPDATE_LISTVIEW_ROWS, nullptr);
            m_child->actived_group_id = m_old_actived_group;
            std::dispatch_event_by_pplx(m_child,
                                        m_child->on_notify,
                                        m_child,
                                        this,
                                        (void *)bb::interface_messages::ON_UPDATE_LISTVIEW_ROWS,
                                        nullptr);
            sender->setEnabled(!sender->isEnabled());
            m_table_item = nullptr;
            return true;
         };
         //
         m_cancel->on_clicked = [&](bool const & checked, std::button * sender)
         {
            m_table_item = nullptr;
            m_ok->setEnabled(false);
            return true;
         };
      }
      //
      this->box()->addWidget(selected_group, 0, 0);
      this->box()->addWidget(buttons, 1, 0);
      return this;
   }
   //-----------------------------------------------------------------------------------------------//
   std::radiobutton *  spreadsheet_advanced::create_object_list(controller::groups * groups,
                                                                int & row)
   {
      int n = m_child->base->information->is_allowed_zero;
      auto item = new QTableWidgetItem{ groups->group_id };
      auto actived = new std::radiobutton{ this, "Ativo", "IDD_ACTIVED", true, false };
      //
      item->setToolTip(std::unicodestring("Selecione primeiro o grupo,\npara depois ativo-lo!"));
      actived->setToolTip(item->toolTip());
      item->setData(Qt::UserRole, groups->group_id);
      item->setTextAlignment(Qt::AlignCenter);
      m_table_actived_group->setItem(row, 0, item);
      m_table_actived_group->setCellWidget(row, 1, actived);
      //
      actived->setChecked(m_child->actived_group_id.compare(groups->group_id));
      /**/
      return actived;
   }
   //-----------------------------------------------------------------------------------------------//
}