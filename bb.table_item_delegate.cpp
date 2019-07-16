//-----------------------------------------------------------------------------------------------//
// xbw32 for Windows (generate of numeric combinations for bingo or lotery)
//
// Created by wilsonsouza 2013, 2018
//
// WR Devinfo
// (c) 2012, 2013, 2014, 2015, 2016, 2017, 2018, 2015
//-----------------------------------------------------------------------------------------------//
#include <std.lineedit.hpp>
#include <bb.group_manager.hpp>
#include <bb.table_interface.hpp>
#include <bb.table_item_delegate.hpp>
#include <bb.spreadsheet_view.hpp>
#include <bb.mdichildwindow_special_combination.hpp>

namespace bb
{
   //-----------------------------------------------------------------------------------------------//
   table_item_delegate::table_item_delegate(std::table * table,
                                            bb::mdichildwindow_special_combination * child) :
      QStyledItemDelegate{ table },
      m_child{ child }
   {
   }
   //-----------------------------------------------------------------------------------------------//
   QWidget * table_item_delegate::createEditor(QWidget * owner,
                                               QStyleOptionViewItem const & option_view_item,
                                               QModelIndex const & Index) const
   {
      auto edit = new std::lineedit{ owner, 2 };
      {
         edit->set_validator(new QIntValidator{ m_child->base->information->is_allowed_zero,
                             m_child->base->information->numbers, edit });
      }
      return edit;
   }
   //-----------------------------------------------------------------------------------------------//
   void table_item_delegate::destroyEditor(QWidget * owner, QModelIndex const & model_index) const
   {
   }
   //-----------------------------------------------------------------------------------------------//
   bool table_item_delegate::editorEvent(QEvent * event,
                                         QAbstractItemView * item_view,
                                         QStyleOptionViewItem const & option_view_item,
                                         QModelIndex const & model_index)
   {
      return true;
   }
   //-----------------------------------------------------------------------------------------------//
   void table_item_delegate::setEditorData(QWidget * owner, QModelIndex const & model_index) const
   {
      auto n_value = model_index.model()->data(model_index, Qt::UserRole).toInt();
      auto edit = static_cast<std::lineedit *>(owner);
      //
      //validate values then put
      edit->setText(std::unicodestring{ "%1" }.arg(n_value));
   }
   //-----------------------------------------------------------------------------------------------//
   void table_item_delegate::setModelData(QWidget * owner,
                                          QAbstractItemModel * item_model,
                                          QModelIndex const & model_index) const
   {
      auto edit = static_cast<std::lineedit *>(owner);
      auto n_value = edit->text().toInt();
      //
      //set value to model
      //vality before of update the data queue
      QTableWidgetItem * nc_items = m_child->m_view->m_table_pages->currentItem();
      //
      if (nc_items)
      {
         auto x = nc_items->row();
         auto y = nc_items->column();
         auto old_value = nc_items->text();
         //
         nc_items->setText(edit->text());
         //
         if (m_child->m_view->validity_cell_value(nc_items))
         {
            item_model->setData(model_index, n_value, Qt::EditRole);
         }
         else
         {
            m_child->m_view->m_table_pages->setItem(x, y, new QTableWidgetItem{ old_value });
         }
      }
   }
   //-----------------------------------------------------------------------------------------------//
   QSize table_item_delegate::sizeHint(QStyleOptionViewItem const & option_view_item,
                                       QModelIndex const & model_index) const
   {
      auto r = QRect{ option_view_item.rect };
      return QSize{ r.height(), r.width() };
   }
   //-----------------------------------------------------------------------------------------------//
   void table_item_delegate::updateEditorGeometry(QWidget * owner,
                                                  QStyleOptionViewItem const & option_view_item,
                                                  QModelIndex const & model_index) const
   {
      owner->setGeometry(option_view_item.rect);
   }
   //-----------------------------------------------------------------------------------------------//
   void table_item_delegate::paint(QPainter * painter,
                                   QStyleOptionViewItem const & option_view_item,
                                   QModelIndex const & model_index) const
   {
      //call super method
      QStyledItemDelegate::paint(painter, option_view_item, model_index);
   }
   //-----------------------------------------------------------------------------------------------//
}