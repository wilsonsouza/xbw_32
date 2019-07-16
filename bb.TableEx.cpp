//-----------------------------------------------------------------------------------------------//
// xbw32 for Windows (generate of numeric combinations for bingo or lotery)
//
// Created by wilsonsouza 2013, 2018
//
// WR Devinfo
// (c) 2012, 2013, 2014, 2015, 2016, 2017, 2018, 2015
//-----------------------------------------------------------------------------------------------//
#include <bb.table_ex.hpp>
#include <bb.spreadsheet_view.hpp>
#include <bb.custom_mdichildwindow.hpp>
#include <bb.table_item_delegate.hpp>

using namespace bb;
//-----------------------------------------------------------------------------------------------//
table_ex::table_ex(bb::mdichildwindow_special_combination * pWnd):Table()
{
   //set row and column delegate edit control
   setItemDelegate(new bb::table_item_delegate(this, pWnd));
}
//-----------------------------------------------------------------------------------------------//
void table_ex::OnItemClicked(QTableWidgetItem * pItem, std::table * Sender)
{
}
//-----------------------------------------------------------------------------------------------//
