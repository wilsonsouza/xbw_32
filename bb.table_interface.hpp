//-----------------------------------------------------------------------------------------------//
// xbw32 for Windows (generate of numeric combinations for bingo or lotery)
//
// Created by wilsonsouza 2013, 2014, 2015, 2016, 2017, 2018
//
// WR Devinfo
// (c) 2012, 2013, 2014, 2015, 2016, 2017, 2018, 2016, 2017, 2018
//-----------------------------------------------------------------------------------------------//
#pragma once
#include <bb.defs.hpp>
#include <std.display_progressbar.hpp>
#include <bb.group_manager.hpp>
/* classes protype */
namespace std
{
   namespace sql
   {
      class query;
      class table;
   }
}
//
namespace bb
{
   class mdichildwindow;
   class mdiframewindow;
   class table_interface : public task_group, public group_manager, public QObject
   {
   public:
      using pointer = std::shared_ptr<table_interface>;
      //
   public:
      enum class MODE : uint
      {
         SELECT,
         ERASE,
         INSERT,
         UPDATE
      };
      //
      enum class RUN_MODE : uint
      {
         FAIL = 1,
         OK = 2,
         LOOKUP_LOADDATA = 4,
         LOOKUP_NO_LOADDATA = 8
      };
      //
      enum class TABLE_ID : uint
      {
         CONTROLLER,
         INFORMATION,
         NUMBERS,
         RESOURCES
      };
      //
   public:
      explicit table_interface(mdichildwindow * frame);
      virtual ~table_interface();
      virtual table_interface & write(std::unicodestring const & group, int const & page) = 0;
      virtual table_interface & read(std::unicodestring const & group, int const & page) = 0;
      virtual table_interface & erase(std::unicodestring const & group, int const & page, int const & number) = 0;
      virtual table_interface & lookup(std::unicodestring const & group, int const & page, int const & number) = 0;
      virtual table_interface & update(std::unicodestring const & group, int const & page, int const & number) = 0;
      virtual std::unicodestring prepare_query(table_interface::MODE const & mode,
                                               std::unicodestring const & group,
                                               int const & page,
                                               int const & number) = 0;
      virtual std::display_progressbar::pointer create_display_progressbar();
      virtual table_interface & set_table_identification(table_interface::TABLE_ID const & table_id);
      virtual std::unicodestring decode_fields();
      virtual std::unicodestring format_fields_values(bool const & is_with_field_name = true);
      virtual table_interface & update_data();
      /**/
   public:
      std::shared_ptr<std::sql::table> m_table{ nullptr };
      std::shared_ptr<std::sql::query> m_query{ nullptr };
      MODE m_fill_mode{ MODE::SELECT };
      RUN_MODE m_run_mode{ RUN_MODE::FAIL };
      TABLE_ID m_table_id{ TABLE_ID::NUMBERS };
      bool m_successed{ false };
      std::unicodestring m_catalog_schema{ ".dbo." };
      std::unicodestring constrain{};
      std::unicodestring orderby{};
      /**/
   protected:
      std::vector<std::pair<std::unicodestring, std::vector<std::pair<int, std::unicodestring>>>> m_tables_names
      {
         make_pair(defs::db::datasource{}.TBL_CONTROLLER_NAME, defs::db::datasource{}.SQL_FIELDS_CONTROLLER),
         make_pair(defs::db::datasource{}.TBL_INFORMATION_NAME, defs::db::datasource{}.SQL_FIELD_INFORMATION),
         make_pair(defs::db::datasource{}.TBL_NUMBERS_NAME, defs::db::datasource{}.SQL_FIELD_NUMBERS),
         make_pair(defs::db::datasource{}.TBL_RESOURCES_NAME, defs::db::datasource{}.SQL_FIELD_RESOURCES)
      };
      std::vector<std::pair<int, std::stringlist>> m_tables_field_types
      {
         std::make_pair(int(TABLE_ID::CONTROLLER), defs::db::datasource{}.TBL_CONTROLLERLISTFIELDS),
         std::make_pair(int(TABLE_ID::INFORMATION), defs::db::datasource{}.TBL_INFORMATIONLISTFIELDS),
         std::make_pair(int(TABLE_ID::NUMBERS), defs::db::datasource{}.TBL_NUMBERSLISTFIELDS),
         std::make_pair(int(TABLE_ID::RESOURCES), defs::db::datasource{}.TBL_RESOURCESLISTFIELDS)
      };
      std::vector<std::tuple<std::unicodestring, int const, QVariant>> m_controller_data{};
      std::vector<std::tuple<std::unicodestring, int const, QVariant>> m_information_data{};
      std::vector<std::tuple<std::unicodestring, int const, QVariant>> m_numbers_data{};
      std::vector<std::tuple<std::unicodestring, int const, QVariant>> m_resources_data{};
      /**/
   private:
      void decode_variant_and_push_back_value(std::stringlist & out_value,
                                              std::unicodestring const & field_composite,
                                              QVariant const & value_out);
   };
   //-----------------------------------------------------------------------------------------------//
   class table_numbers : public table_interface
   {
   public:
      using pointer = std::shared_ptr<table_numbers>;
      //
   public:
      explicit table_numbers(mdichildwindow * frame);
      virtual ~table_numbers() override = default;
      virtual table_interface & write(std::unicodestring const & group, int const & page);
      virtual table_interface & read(std::unicodestring const & group, int const & page);
      virtual table_interface & erase(std::unicodestring const & group, int const & page, int const & number);
      virtual table_interface & lookup(std::unicodestring const & group, int const & page, int const & number);
      virtual table_interface & update(std::unicodestring const & group, int const & page, int const & number);
      virtual std::unicodestring prepare_query(table_interface::MODE const & mode,
                                               std::unicodestring const & group,
                                               int const & page,
                                               int const & number);
      void load_records();
      defs::db::datasource::table_numbers fill_data();
   };
   //-----------------------------------------------------------------------------------------------//
   class table_resources : public table_interface
   {
   public:
      using pointer = std::shared_ptr<table_resources>;
      //
   public:
      explicit table_resources(mdichildwindow * frame);
      virtual ~table_resources() override = default;
      virtual table_interface & write(std::unicodestring const & group, int const & page);
      virtual table_interface & read(std::unicodestring const & group, int const & page);
      virtual table_interface & erase(std::unicodestring const & group, int const & page, int const & number);
      virtual table_interface & lookup(std::unicodestring const & group, int const & page, int const & number);
      virtual table_interface & update(std::unicodestring const & group, int const & page, int const & number);
      virtual std::unicodestring prepare_query(table_interface::MODE const & mode,
                                               std::unicodestring const & group,
                                               int const & page,
                                               int const & number);
   };
   //-----------------------------------------------------------------------------------------------//
   class table_controller : public table_interface
   {
   public:
      using pointer = std::shared_ptr<table_controller>;
      //
   public:
      explicit table_controller(mdichildwindow * frame);
      virtual ~table_controller() override = default;
      virtual table_interface & write(std::unicodestring const & group, int const & page);
      virtual table_interface & read(std::unicodestring const & group, int const & page);
      virtual table_interface & erase(std::unicodestring const & group, int const & page, int const & number);
      virtual table_interface & lookup(std::unicodestring const & group, int const & page, int const & number);
      virtual table_interface & update(std::unicodestring const & group, int const & page, int const & number);
      virtual std::unicodestring prepare_query(table_interface::MODE const & mode,
                                               std::unicodestring const & group,
                                               int const & page,
                                               int const & number);
   };
   //-----------------------------------------------------------------------------------------------//
   class table_information : public table_interface
   {
   public:
      using pointer = std::shared_ptr<table_information>;
      //
   public:
      explicit table_information(mdichildwindow * frame);
      virtual ~table_information() override = default;
      virtual table_interface & write(std::unicodestring const & group, int const & page);
      virtual table_interface & read(std::unicodestring const & group, int const & page);
      virtual table_interface & erase(std::unicodestring const & group, int const & page, int const & number);
      virtual table_interface & lookup(std::unicodestring const & group, int const & page, int const & number);
      virtual table_interface & update(std::unicodestring const & group, int const & page, int const & number);
      virtual std::unicodestring prepare_query(table_interface::MODE const & mode,
                                               std::unicodestring const & group,
                                               int const & page,
                                               int const & number);
      /**/
      void const fill_data();
   };
}