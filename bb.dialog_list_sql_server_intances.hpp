//-----------------------------------------------------------------------------------------------//
// xbw32 for Windows (generate of numeric combinations for bingo or lotery)
//
// Created by wilsonsouza 2013, 2018
//
// WR Devinfo
// (c) 2012, 2013, 2014, 2015, 2016, 2017, 2018
//	Display dialog with list of sql server instances on the network
//-----------------------------------------------------------------------------------------------//
#pragma once
#include <bb.defs.hpp>
#include <std.dialog.hpp>

namespace std
{
	class CheckBox;
   class ComboBox;
   class LineEdit;
};

namespace bb
{
	class dialog_list_sql_server_intances: public std::dialog
	{
		//Q_OBJECT
	public:
		dialog_list_sql_server_intances(QWidget * pWnd, std::unicodestring const & szCaption);
		virtual ~dialog_list_sql_server_intances() override=default;
		//overwrite
      virtual bool create(dialog * dlg) override;
		//local methods
		virtual void const  get_sqlserver_instances_names();
      /* operators and propertys */
	};
}