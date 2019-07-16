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
   table_numbers::table_numbers(mdichildwindow * child) : table_interface{ child }
   {
      m_table_id = TABLE_ID::NUMBERS;
   }
   //-----------------------------------------------------------------------------------------------//
   table_interface & table_numbers::write(std::unicodestring const & group, int const & page)
   {
      auto sql_cmd = prepare_query(MODE::INSERT, group, page, -1) +
         std::unicodestring{ " %1 " }.bind(constrain);
      m_successed = m_query->execute_non_query(sql_cmd);
      return *this;
   }
   //-----------------------------------------------------------------------------------------------//
   table_interface & table_numbers::read(std::unicodestring const & group, int const & page)
   {
      auto sql_cmd = prepare_query(MODE::SELECT, group, page, -1) +
         std::unicodestring{ " %1 %2 " }.bind(constrain).bind(orderby);
      m_table = m_query->execute(sql_cmd);
      load_records();
      return *this;
   }
   //-----------------------------------------------------------------------------------------------//
   table_interface & table_numbers::erase(std::unicodestring const & group,
                                          int const & page,
                                          int const & number)
   {
      auto sql_cmd = prepare_query(MODE::ERASE, group, page, number) +
         std::unicodestring{ " %1 " }.bind(constrain);
      m_successed = m_query->execute_non_query(sql_cmd);
      return *this;
   }
   //-----------------------------------------------------------------------------------------------//
   table_interface & table_numbers::lookup(std::unicodestring const & group,
                                           int const & page,
                                           int const & number)
   {
      auto sql_cmd = prepare_query(MODE::SELECT, group, page, number) +
         std::unicodestring{ " %1 %2 " }.bind(constrain).bind(orderby);
      m_table = m_query->execute(sql_cmd);
      load_records();
      return *this;
   }
   //-----------------------------------------------------------------------------------------------//
   table_interface & table_numbers::update(std::unicodestring const & group,
                                           int const & page,
                                           int const & number)
   {
      auto sql_cmd = prepare_query(MODE::UPDATE, group, page, number) +
         std::unicodestring{ " %1 " }.bind(constrain);
      m_successed = m_query->execute_non_query(sql_cmd);
      return *this;
   }
   //-----------------------------------------------------------------------------------------------//
   std::unicodestring table_numbers::prepare_query(table_interface::MODE const & mode,
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
         auto fmt = std::unicodestring{ " %1 = '%2' " }.bind(datasource{}.FLD_NUM_GROUPNAME).bind(group);
         sql_cmd += datasource{}.SQL_CMD_WHERE.bind(fmt);
      }
      if (page != -1)
      {
         auto fmt = std::unicodestring{ " %1 = %2 " }.bind(datasource{}.FLD_NUM_PAGENAME).bind(page);
         sql_cmd += (fmt.empty() ? datasource{}.SQL_CMD_WHERE.bind(fmt) : datasource{}.SQL_CMD_AND.bind(fmt));
      }
      if (number != -1)
      {
         auto fmt = std::unicodestring{ " %1 = %2 " }.bind(datasource{}.FLD_NUM_NUMBERS).bind(number);
         sql_cmd += (fmt.empty() ? datasource{}.SQL_CMD_WHERE.bind(fmt) : datasource{}.SQL_CMD_AND.bind(fmt));
      }
      /**/
      auto cmd = std::unicodestring{ "%1 %2" };
      /**/
      switch (mode)
      {
      case MODE::SELECT:
         cmd.bind(datasource{}.SQL_CMD_SELECT.bind(decode_fields()).bind(catalog_name)).bind(sql_cmd);
         break;
      case MODE::INSERT:
         update_data();
         cmd.bind(datasource{}.SQL_CMD_INSERT.bind(catalog_name).
                  bind(decode_fields()).bind(format_fields_values(false))).bind(sql_cmd);
         break;
      case MODE::ERASE:
         cmd.bind(datasource{}.SQL_CMD_DELETE.bind(catalog_name)).bind(sql_cmd);
         break;
      case MODE::UPDATE:
         cmd.bind(defs::db::datasource{}.SQL_CMD_UPDATE.
                  bind(catalog_name).bind(format_fields_values(true))).bind(sql_cmd);
         break;
      }
      /**/
      return cmd;
   }
   //-----------------------------------------------------------------------------------------------//
   void table_numbers::load_records()
   {
      groups->clear();
      /**/
      while (!m_table->eof())
      {
         auto data = fill_data();
         auto available_numbers = controller::available_numbers{ data.numbers, data.availables, data.useds };
         auto result = std::find_if(groups->begin(),
                                    groups->end(), controller::groups{ data.group_name });
         /**/
         if (result == groups->end())
         {
            auto group = controller::groups{};
            auto page = controller::pages{ data.page_id, false, data.is_completed };
            /**/
            group.group_id = data.group_name;
            page.numbers.push_back(controller::page_numbers{ data.numbers, false });
            group.pages.push_back(page);
            group.availables.push_back(available_numbers);
            groups->push_back(group);
         }
         else
         {
            auto pages = std::find_if(result->pages.begin(),
                                      result->pages.end(), controller::pages{ data.page_id });
            /**/
            if (pages != result->pages.end())
            {
               pages->numbers.push_back(controller::page_numbers{ data.numbers, false });
               result->availables.push_back(available_numbers);
            }
            else
            {
               auto pages = controller::pages{ data.page_id, false, data.is_completed };
               /**/
               pages.numbers.push_back(controller::page_numbers{ data.numbers, false });
               result->pages.push_back(pages);
               result->availables.push_back(available_numbers);
            }
         }
         /**/
         m_table->next();
         bb::mdiframewindow::get_frame()->dispatch_eventlooper(true);
      }
   }
   //-----------------------------------------------------------------------------------------------//
   defs::db::datasource::table_numbers table_numbers::fill_data()
   {
      auto data = defs::db::datasource::table_numbers{};
      /**/
      data.group_name = m_table->get_field(defs::db::datasource{}.FLD_NUM_GROUPNAME)->to_string();
      data.page_id = m_table->get_field(defs::db::datasource{}.FLD_NUM_PAGENAME)->to_int();
      data.numbers = m_table->get_field(defs::db::datasource{}.FLD_NUM_NUMBERS)->to_int();
      data.availables = m_table->get_field(defs::db::datasource{}.FLD_NUM_AVAILABLES)->to_int();
      data.useds = m_table->get_field(defs::db::datasource{}.FLD_NUM_USEDS)->to_int();
      data.is_completed = m_table->get_field(defs::db::datasource{}.FLD_NUM_ISCOMPLETED)->to_bool();
      /**/
      return data;
   }
   //-----------------------------------------------------------------------------------------------//
}