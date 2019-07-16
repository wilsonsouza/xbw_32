//-----------------------------------------------------------------------------------------------//
// xbw32 for Windows (generate of numeric combinations for bingo or lotery)
//
// Created by wilsonsouza 2013, 2014, 2015, 2016, 2017, 2018
//
// WR Devinfo
// (c) 2012, 2013, 2014, 2015, 2016, 2017, 2018, 2016, 2017, 2018
//-----------------------------------------------------------------------------------------------//
#include <bb.mdichildwindow.hpp>
#include <sql.table.hpp>
#include <sql.query.hpp>
#include <bb.table_interface.hpp>

namespace bb
{
   table_information::table_information(bb::mdichildwindow * frame) : table_interface{ frame }
   {
      m_table_id = TABLE_ID::INFORMATION;
   }
   //-----------------------------------------------------------------------------------------------//
   table_interface & table_information::write(std::unicodestring const & group, int const & page)
   {
      return *this;
   }
   //-----------------------------------------------------------------------------------------------//
   table_interface & table_information::read(std::unicodestring const & group, int const & page)
   {
      return *this;
   }
   //-----------------------------------------------------------------------------------------------//
   table_interface & table_information::erase(std::unicodestring const & group,
                                              int const & page,
                                              int const & number)
   {
      auto sql_cmd = prepare_query(MODE::ERASE, group, page, number);
      m_successed = m_query->execute_non_query(sql_cmd);
      return *this;
   }
   //-----------------------------------------------------------------------------------------------//
   table_interface & table_information::lookup(std::unicodestring const & group,
                                               int const & page,
                                               int const & number)
   {
      auto sql_cmd = prepare_query(MODE::SELECT, group, page, number);
      m_successed = m_table->open(sql_cmd);
      fill_data();
      return *this;
   }
   //-----------------------------------------------------------------------------------------------//
   table_interface & table_information::update(std::unicodestring const & group,
                                               int const & page,
                                               int const & number)
   {
      return *this;
   }
   //-----------------------------------------------------------------------------------------------//
   std::unicodestring table_information::prepare_query(table_interface::MODE const & mode,
                                                       std::unicodestring const & group,
                                                       int const & page,
                                                       int const & number)
   {
      using namespace bb::defs::db;
      auto sql_data = std::unicodestring{ " %1 %2 " };
      auto table_name = m_tables_names.at(int(m_table_id)).first;
      auto fields = m_tables_names.at(int(m_table_id)).second;
      auto catalog_name = m_catalog_schema.bind(base->catalog_name).bind(table_name);
      auto sql_cmd = std::unicodestring{ "%1 %2" };
      /* key */
      if (!group.empty())
      {
         sql_data.bind(datasource{}.SQL_CMD_WHERE.
                       bind(fields.at(int(datasource::SQL_INFORMATION_ID::GROUPNAME)).second)).
            bind(std::unicodestring{ " = '%1' " }.bind(group));
      }
      /* mount sql command via table_interface::MODE enum */
      switch (mode)
      {
      case MODE::INSERT:
         sql_cmd.bind(datasource{}.SQL_CMD_INSERT.bind(catalog_name).
                      bind(decode_fields()).bind(format_fields_values())).bind(sql_data);
         break;
      case MODE::SELECT:
         sql_cmd.bind(datasource{}.SQL_CMD_SELECT.bind(decode_fields()).bind(catalog_name)).bind(sql_data);
         break;
      case MODE::ERASE:
         sql_cmd.bind(datasource{}.SQL_CMD_DELETE.bind(catalog_name)).bind(sql_data);
         break;
      case MODE::UPDATE:
         sql_cmd.bind(datasource{}.SQL_CMD_UPDATE.bind(catalog_name).bind(format_fields_values(true))).
            bind(sql_data);
         break;
      }
      return sql_cmd;
   }
   //-----------------------------------------------------------------------------------------------//
   void const table_information::fill_data()
   {
      using namespace bb::defs::db;
      auto info = base->information;
      /**/
      info->by_username = m_table->get_field(datasource{}.FLD_INF_BYUSERNAME)->to_string();
      info->comments = m_table->get_field(datasource{}.FLD_INF_COMMENTS)->to_string();
      info->created = QDate{};
      info->groups_id = m_table->get_field(datasource{}.FLD_INF_GROUPID)->to_char();
      info->group_name = m_table->get_field(datasource{}.FLD_INF_GROUPNAME)->to_string();
      info->is_allowed_zero = m_table->get_field(datasource{}.FLD_INF_ISALLOWEDZERO)->to_bool();
      info->is_completed = m_table->get_field(datasource{}.FLD_INF_ISCOMPLETED)->to_bool();
      info->is_create_all_groups = m_table->get_field(datasource{}.FLD_INF_ISCREATEALLGROUPS)->to_bool();
      info->last_access = QDate{};
      info->last_updated = QDate{};
      info->numbers = m_table->get_field(datasource{}.FLD_INF_NUMBERS)->to_int();
      info->numbers_to_group = m_table->get_field(datasource{}.FLD_INF_NUMBERSBYGROUP)->to_int();
      info->numbers_to_page = m_table->get_field(datasource{}.FLD_INF_NUMBERSBYPAGE)->to_int();
      info->pages_to_group = m_table->get_field(datasource{}.FLD_INF_PAGESBYGROUP)->to_int();
      info->version_id = m_table->get_field(datasource{}.FLD_INF_VERSIONID)->to_double();
   }
}