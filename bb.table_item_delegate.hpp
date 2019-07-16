//-----------------------------------------------------------------------------------------------//
// xbw32 for Windows (generate of numeric combinations for bingo or lotery)
//
// Created by wilsonsouza 2013, 2018
//
// WR Devinfo
// (c) 2012, 2013, 2014, 2015, 2016, 2017, 2018, 2015
//-----------------------------------------------------------------------------------------------//
#pragma once
#include <bb.defs.hpp>
#include <std.table.hpp>

namespace bb
{
   class mdichildwindow_special_combination;
   class table_item_delegate : public QStyledItemDelegate
   {
      //Q_OBJECT
   public:
      explicit table_item_delegate(std::table * table, bb::mdichildwindow_special_combination * child);
      virtual ~table_item_delegate() override = default;
      virtual QWidget * createEditor(QWidget * owner, 
                                     QStyleOptionViewItem const & style_option_view_item,
                                     QModelIndex const & model_index) const;
      virtual void destroyEditor(QWidget * owner, QModelIndex const & model_index) const;
      virtual bool editorEvent(QEvent * event, 
                               QAbstractItemView * item_view,
                               QStyleOptionViewItem const & style_option_view_item, 
                               QModelIndex const & model_index);
      virtual void setEditorData(QWidget * owner, QModelIndex const & model_index) const;
      virtual void setModelData(QWidget * owner, 
                                QAbstractItemModel * item_model,
                                QModelIndex const & model_index) const;
      virtual QSize sizeHint(QStyleOptionViewItem const & option_view_item, 
                             QModelIndex const & model_index) const;
      virtual void updateEditorGeometry(QWidget * owner, 
                                        QStyleOptionViewItem const & option_view_item,
                                        QModelIndex const & model_index) const;
      virtual void paint(QPainter * painter, 
                         QStyleOptionViewItem const & option_view_item,
                         QModelIndex const & model_index) const;
      //
      //DECLARE_OPERATOR(table_item_delegate);
      bb::mdichildwindow_special_combination * m_child{ nullptr };
   };
}
