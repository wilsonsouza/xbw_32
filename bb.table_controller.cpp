//-----------------------------------------------------------------------------------------------//
// xbw32 for Windows (generate of numeric combinations for bingo or lotery)
//
// Created by wilsonsouza 2013, 2014, 2015, 2016, 2017, 2018
//
// WR Devinfo
// (c) 2012, 2013, 2014, 2015, 2016, 2017, 2018, 2016, 2017, 2018
//-----------------------------------------------------------------------------------------------//
#include <bb.table_interface.hpp>
#include <sql.table.hpp>
#include <sql.query.hpp>
#include <bb.mdichildwindow.hpp>
#include <bb.MDIFrameWindow.hpp>

namespace bb
{
   table_controller::table_controller(mdichildwindow * frame) :
      table_interface{ frame }
   {
      set_table_identification(TABLE_ID::CONTROLLER);
   }
   //-----------------------------------------------------------------------------------------------//
   table_interface & table_controller::write(std::unicodestring const & group, int const & page)
   {
      auto sql_cmd = prepare_query(MODE::INSERT, group, page, -1) +
         std::unicodestring{ " %1 " }.bind(constrain);
      m_successed = m_query->execute_non_query(sql_cmd);
      return *this;
   }
   //-----------------------------------------------------------------------------------------------//
   table_interface & table_controller::read(std::unicodestring const & group, int const & page)
   {
      auto sql_cmd = prepare_query(MODE::SELECT, group, page, -1) +
         std::unicodestring{ " %1 %2 " }.bind(constrain).bind(orderby);
      m_table = m_query->execute(sql_cmd);
      return *this;
   }
   //-----------------------------------------------------------------------------------------------//
   table_interface & table_controller::erase(std::unicodestring const & group,
                                             int const & page,
                                             int const & number)
   {
      auto sql_cmd = prepare_query(MODE::ERASE, group, page, number) +
         std::unicodestring{ " %1 " }.bind(constrain);
      m_successed = m_query->execute_non_query(sql_cmd);
      return *this;
   }
   //-----------------------------------------------------------------------------------------------//
   table_interface & table_controller::lookup(std::unicodestring const & group,
                                              int const & page,
                                              int const & number)
   {
      auto sql_cmd = prepare_query(MODE::SELECT, group, page, number) +
         std::unicodestring{ " %1 %2 " }.bind(constrain).bind(orderby);
      m_table = m_query->execute(sql_cmd);
      return *this;
   }
   //-----------------------------------------------------------------------------------------------//
   table_interface & table_controller::update(std::unicodestring const & group,
                                              int const & page,
                                              int const & number)
   {
      auto sql_cmd = prepare_query(MODE::UPDATE, group, page, number) +
         std::unicodestring{ " %1 " }.bind(constrain);
      m_successed = m_query->execute_non_query(sql_cmd);
      return *this;
   }
   //-----------------------------------------------------------------------------------------------//
   std::unicodestring table_controller::prepare_query(table_interface::MODE const & mode,
                                                      std::unicodestring const & group,
                                                      int const & page,
                                                      int const & number)
   {
      using namespace bb::defs::db;
      auto sql_cmd = std::unicodestring{};
      auto table_name = m_tables_names.at(int(m_table_id)).first;
      auto catalog_name = m_catalog_schema.bind(base->catalog_name).bind(table_name);
      /**/
      if (!group.empty())
      {
         auto fmt = std::unicodestring{ " %1 = '%2'" }.bind(datasource{}.FLD_CTRL_GROUPNAME).bind(group);
         sql_cmd += datasource{}.SQL_CMD_WHERE.bind(fmt);
      }
      if (page != -1)
      {
         auto fmt = std::unicodestring{ " %1 = %2" }.bind(datasource{}.FLD_CTRL_PAGENAME).bind(page);
         sql_cmd += (fmt.empty() ? datasource{}.SQL_CMD_WHERE.bind(fmt) : datasource{}.SQL_CMD_AND.bind(fmt));
      }
      if (number != -1)
      {
         auto fmt = std::unicodestring{ " %1 = %2" }.bind(datasource{}.FLD_CTRL_ISCOMPLETED).bind(number);
         sql_cmd += (fmt.empty() ? datasource{}.SQL_CMD_WHERE.bind(fmt) : datasource{}.SQL_CMD_AND.bind(fmt));
      }
      /**/
      auto cmd = std::unicodestring{"%1 %2"};
      /**/
      switch (mode)
      {
      case MODE::SELECT:
         cmd.bind(datasource{}.SQL_CMD_SELECT.bind(decode_fields()).bind(catalog_name)).bind(sql_cmd);
         break;
      case MODE::INSERT:
         update_data();
         cmd.bind(datasource{}.SQL_CMD_INSERT.
                  bind(catalog_name).bind(decode_fields()).bind(format_fields_values(false))).bind(sql_cmd);
         break;
      case MODE::ERASE:
         cmd.bind(datasource{}.SQL_CMD_DELETE.bind(catalog_name)).bind(sql_cmd);
         break;
      case MODE::UPDATE:
         cmd.bind(datasource{}.SQL_CMD_UPDATE.bind(catalog_name).bind(format_fields_values(true))).bind(sql_cmd);
         break;
      }
      return cmd;
   }
}