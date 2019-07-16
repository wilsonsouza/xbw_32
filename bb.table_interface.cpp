//-----------------------------------------------------------------------------------------------//
// xbw32 for Windows (generate of numeric combinations for bingo or lotery)
//
// Created by wilsonsouza 2013, 2014, 2015, 2016, 2017, 2018
//
// WR Devinfo
// (c) 2012, 2013, 2014, 2015, 2016, 2017, 2018, 2016, 2017, 2018
//-----------------------------------------------------------------------------------------------//
#include <bb.table_interface.hpp>
#include <bb.MDIFrameWindow.hpp>
#include <bb.mdichildwindow.hpp>
#include <std.widget.hpp>
#include <sql.table.hpp>
#include <sql.query.hpp>

namespace bb
{
   table_interface::table_interface(bb::mdichildwindow * child) :
      task_group{},
      group_manager{ std::make_shared<group_manager>(*child) },
      QObject{ child }
   {
      auto frame = bb::mdiframewindow::get_frame();
      /**/
      m_query = std::shared_ptr<std::sql::query>
      {
         new std::sql::query{frame->get_sql_handle()->get_connection_parameters()}
      };
   }
   //-----------------------------------------------------------------------------------------------//
   table_interface::~table_interface()
   {
      cancel();
   }
   //-----------------------------------------------------------------------------------------------//
   std::display_progressbar::pointer table_interface::create_display_progressbar()
   {
      auto child = dynamic_cast<bb::mdichildwindow *>(parent());
      auto frame = bb::mdiframewindow::get_frame();
      return std::display_progressbar::pointer{ new std::display_progressbar{frame, child} };
   }
   //-----------------------------------------------------------------------------------------------//
   table_interface & table_interface::set_table_identification(table_interface::TABLE_ID const & table_id)
   {
      m_table_id = table_id;
      return *this;
   }
   //-----------------------------------------------------------------------------------------------//
   std::unicodestring table_interface::decode_fields()
   {
      auto out_value = std::stringlist{};
      /**/
      for (auto & value : m_tables_names.at(int(m_table_id)).second)
      {
         out_value.push_back(value.second);
      }
      return out_value.join(",");
   }
   //-----------------------------------------------------------------------------------------------//
   void table_interface::decode_variant_and_push_back_value(std::stringlist & out_value,
                                                            std::unicodestring const & field_composite,
                                                            QVariant const & value_out)
   {
      switch (value_out.type())
      {
      case value_out.Int:
         out_value.push_back(field_composite.bind(value_out.toInt()));
         return;
      case value_out.ByteArray:
         out_value.push_back(field_composite.bind(std::unicodestring{ value_out.toByteArray() }));
         return;
      case value_out.Date:
         out_value.push_back(field_composite.bind(std::unicodestring{}.sprintf("%02d/%02d/%04d",
                             value_out.toDate().day(),
                             value_out.toDate().month(),
                             value_out.toDate().year())));
         return;
      case value_out.Double:
         out_value.push_back(field_composite.bind(value_out.toDouble()));
         return;
      case value_out.Char:
         out_value.push_back(field_composite.bind(value_out.toChar()));
         return;
      case value_out.Bool:
         out_value.push_back(field_composite.bind(value_out.toBool()));
         return;
      case value_out.LongLong:
         out_value.push_back(field_composite.arg(value_out.toLongLong()));
         return;
      }
   }
   //-----------------------------------------------------------------------------------------------//
   std::unicodestring table_interface::format_fields_values(bool const & is_with_field_name)
   {
      auto out_value = std::stringlist{};
      /**/
      for (auto & value : m_tables_names.at(int(m_table_id)).second)
      {
         auto field_name = (is_with_field_name ? value.second + " = " : std::unicodestring{});
         auto field_fmt = std::unicodestring{};
         auto field_list = m_tables_field_types.at(int(m_table_id)).second;
         auto pos = 0;
         /* search by field type */
         for (auto fvalue = field_list.begin(); fvalue != field_list.end(); fvalue++, pos++)
         {
            if (fvalue->contains(value.second))
            {
               field_fmt = (fvalue->contains("varchar(") ? std::unicodestring{ "'%1'" } : std::unicodestring{ "%1" });
               //
               if (m_table_id == TABLE_ID::CONTROLLER)
               {
                  auto tuple_value = m_controller_data.at(pos);
                  auto value_out = std::get<2>(tuple_value);
                  decode_variant_and_push_back_value(out_value, field_name + field_fmt, value_out);
               }
               else if (m_table_id == TABLE_ID::INFORMATION)
               {
                  auto tuple_value = m_information_data.at(pos);
                  auto value_out = std::get<2>(tuple_value);
                  decode_variant_and_push_back_value(out_value, field_name + field_fmt, value_out);
               }
               else if (m_table_id == TABLE_ID::NUMBERS)
               {
                  auto tuple_value = m_numbers_data.at(pos);
                  auto value_out = std::get<2>(tuple_value);
                  decode_variant_and_push_back_value(out_value, field_name + field_fmt, value_out);
               }
               else if (m_table_id == TABLE_ID::RESOURCES)
               {
                  auto tuple_value = m_resources_data.at(pos);
                  auto value_out = std::get<2>(tuple_value);
                  decode_variant_and_push_back_value(out_value, field_name + field_fmt, value_out);
               }
               break;
            }
         }
      }
      return out_value.join(",");
   }
   //-----------------------------------------------------------------------------------------------//
   table_interface & table_interface::update_data()
   {
      if (m_table_id == TABLE_ID::CONTROLLER)
      {
         using namespace defs::db;
         auto ctrl = base->controller;
         /**/
         m_controller_data.clear();
         m_controller_data.push_back(std::make_tuple(datasource{}.FLD_CTRL_GROUPNAME,
                                     datasource{}.FIELD_VARCHAR_TYPE,
                                     QVariant{ ctrl->group_name }));
         m_controller_data.push_back(std::make_tuple(datasource{}.FLD_CTRL_PAGENAME,
                                     datasource{}.FIELD_INT_TYPE,
                                     QVariant{ ctrl->page_name }));
         m_controller_data.push_back(std::make_tuple(datasource{}.FLD_CTRL_ISCOMPLETED,
                                     datasource{}.FIELD_INT_TYPE,
                                     QVariant{ ctrl->is_completed }));
      }
      else if (m_table_id == TABLE_ID::INFORMATION)
      {
         using namespace defs::db;
         auto i = base->information;
         /**/
         m_information_data.clear();
         m_information_data.push_back(std::make_tuple(datasource{}.FLD_INF_GROUPID,
                                      datasource{}.FIELD_VARCHAR_TYPE,
                                      QVariant{ i->groups_id }));
         m_information_data.push_back(std::make_tuple(datasource{}.FLD_INF_GROUPNAME,
                                      datasource{}.FIELD_VARCHAR_TYPE,
                                      QVariant{ i->group_name }));
         m_information_data.push_back(std::make_tuple(datasource{}.FLD_INF_PAGESBYGROUP,
                                      datasource{}.FIELD_INT_TYPE,
                                      QVariant{ i->pages_to_group }));
         m_information_data.push_back(std::make_tuple(datasource{}.FLD_INF_NUMBERSBYGROUP,
                                      datasource{}.FIELD_INT_TYPE,
                                      QVariant{ i->numbers_to_group }));
         m_information_data.push_back(std::make_tuple(datasource{}.FLD_INF_NUMBERSBYPAGE,
                                      datasource{}.FIELD_INT_TYPE,
                                      QVariant{ i->numbers_to_page }));
         m_information_data.push_back(std::make_tuple(datasource{}.FLD_INF_NUMBERS,
                                      datasource{}.FIELD_INT_TYPE,
                                      QVariant{ i->numbers }));
         m_information_data.push_back(std::make_tuple(datasource{}.FLD_INF_ISCREATEALLGROUPS,
                                      datasource{}.FIELD_BIT_TYPE,
                                      QVariant{ i->is_create_all_groups }));
         m_information_data.push_back(std::make_tuple(datasource{}.FLD_INF_ISALLOWEDZERO,
                                      datasource{}.FIELD_BIT_TYPE,
                                      QVariant{ i->is_allowed_zero }));
         m_information_data.push_back(std::make_tuple(datasource{}.FLD_INF_ISCOMPLETED,
                                      datasource{}.FIELD_BIT_TYPE,
                                      QVariant{ i->is_completed }));
         m_information_data.push_back(std::make_tuple(datasource{}.FLD_INF_CREATED,
                                      datasource{}.FIELD_DATETIME_TYPE,
                                      QVariant{ i->created.toString("dd/mm/yyyy") }));
         m_information_data.push_back(std::make_tuple(datasource{}.FLD_INF_LASTUPDATED,
                                      datasource{}.FIELD_DATETIME_TYPE,
                                      QVariant{ i->last_updated.toString("dd/mm/yyyy") }));
         m_information_data.push_back(std::make_tuple(datasource{}.FLD_INF_BYUSERNAME,
                                      datasource{}.FIELD_VARCHAR_TYPE,
                                      QVariant{ i->by_username }));
         m_information_data.push_back(std::make_tuple(datasource{}.FLD_INF_VERSIONID,
                                      datasource{}.FIELD_FLOAT_TYPE,
                                      QVariant{ i->version_id }));
         m_information_data.push_back(std::make_tuple(datasource{}.FLD_INF_LASTACCESS,
                                      datasource{}.FIELD_DATETIME_TYPE,
                                      QVariant{ i->last_access.toString("dd/mm/yyyy") }));
         m_information_data.push_back(std::make_tuple(datasource{}.FLD_INF_COMMENTS,
                                      datasource{}.FIELD_VARCHAR_TYPE,
                                      QVariant{ i->comments }));
      }
      else if (m_table_id == TABLE_ID::NUMBERS)
      {
         using namespace defs::db;
         auto n = base->numbers;
         /**/
         m_numbers_data.clear();
         m_numbers_data.push_back(std::make_tuple(datasource{}.FLD_NUM_GROUPNAME,
                                  datasource{}.FIELD_VARCHAR_TYPE,
                                  QVariant{ n->group_name }));
         m_numbers_data.push_back(std::make_tuple(datasource{}.FLD_NUM_PAGENAME,
                                  datasource{}.FIELD_INT_TYPE,
                                  QVariant{ n->page_id }));
         m_numbers_data.push_back(std::make_tuple(datasource{}.FLD_NUM_NUMBERS,
                                  datasource{}.FIELD_INT_TYPE,
                                  QVariant{ n->numbers }));
         m_numbers_data.push_back(std::make_tuple(datasource{}.FLD_NUM_USEDS,
                                  datasource{}.FIELD_INT_TYPE,
                                  QVariant{ n->useds }));
         m_numbers_data.push_back(std::make_tuple(datasource{}.FLD_NUM_AVAILABLES,
                                  datasource{}.FIELD_INT_TYPE,
                                  QVariant{ n->availables }));
         m_numbers_data.push_back(std::make_tuple(datasource{}.FLD_NUM_ISCOMPLETED,
                                  datasource{}.FIELD_INT_TYPE,
                                  QVariant{ n->is_completed }));
      }
      else if (m_table_id == TABLE_ID::RESOURCES)
      {
         using namespace defs::db;
         auto r = base->resources;
         /**/
         m_resources_data.clear();
         m_resources_data.push_back(std::make_tuple(datasource{}.FLD_RES_GROUPNAME,
                                    datasource{}.FIELD_VARCHAR_TYPE,
                                    QVariant{ r->group_name }));
         m_resources_data.push_back(std::make_tuple(datasource{}.FLD_RES_NUMBERS,
                                    datasource{}.FIELD_INT_TYPE,
                                    QVariant{ r->numbers }));
         m_resources_data.push_back(std::make_tuple(datasource{}.FLD_RES_USEDS,
                                    datasource{}.FIELD_INT_TYPE,
                                    QVariant{ r->useds }));
         m_resources_data.push_back(std::make_tuple(datasource{}.FLD_RES_AVAILABLES,
                                    datasource{}.FIELD_INT_TYPE,
                                    QVariant{ r->availables }));
      }
      return *this;
   }
}