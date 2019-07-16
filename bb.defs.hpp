//-----------------------------------------------------------------------------------------------//
// xbw32 for Windows (generate of numeric combinations for bingo or lotery) 
//
// Created by wilsonsouza 2012, 2013, 2014, 2015, 2016, 2017, 2018
// For Olavo Co.
//
// WR Devinfo
// (c) 2012, 2013, 2014, 2015, 2016, 2017, 2018
// update of qt 5.01 to 5.11
//-----------------------------------------------------------------------------------------------//
#pragma once
#pragma warning(disable:4275)
#pragma warning(disable:4251)
//QT headers
#include <qtcore/qtcore>
#include <qtgui/qtgui>
#include <qtwidgets/qtwidgets>
#include <QtPrintSupport\qtprintsupport>
//STL headers
#include <typeinfo>
#include <functional>
#include <ppl.h>
#include <exception>
#include <string>
#include <map>
#include <list>
#include <set>
#include <string>
#include <algorithm>
#include <std.unicodestring.hpp>
#include <std.layouts.hpp>
//-----------------------------------------------------------------------------------------------//
namespace bb
{
   template <class layout_t = std::vertical_box, class widget_t = QWidget>
   class define_layout_control : public layout_t
   {
   public:
      explicit define_layout_control(widget_t * control_owner) : layout_t{}
      {
         addWidget(control_owner);
         addStretch();
      }
      void add(widget_t * control_owner)
      {
         addWidget(control_owner);
      }
      void add(layout_t * layout_owner)
      {
         addLayout(layout_owner);
      }
   };
   //-----------------------------------------------------------------------------------------------//
   namespace defs
   {
      struct masks
      {
         const char * grouppageformat{ "%s%03d" };
         const char * pageformat{ "%03d" };
         /**/
         const std::unicodestring yes{ "Sim" };
         const std::unicodestring no{ "Não" };
         const std::unicodestring undefined{ "Indefinido" };
         masks() = default;
      };
      //-----------------------------------------------------------------------------------------------//
      namespace sql
      {
         struct database_access_security
         {
            std::unicodestring const instancename{ "sqlexpress" };
            std::unicodestring const hostname{ "idea-pc" };
            std::unicodestring const username{ "sa" };
            std::unicodestring const password{ "123456" };
            std::unicodestring const integratesecurity{};
            std::unicodestring const provider{ "sqlncli10.1" };
            database_access_security() = default;
         };

         struct database_key
         {
            std::unicodestring const instancename{ "sql_instance_name" };
            std::unicodestring const hostname{ "sql_host_name" };
            std::unicodestring const username{ "sql_user_name" };
            std::unicodestring const password{ "sql_password" };
            std::unicodestring const integratesecurity{ "sql_integrate_security" };
            std::unicodestring const provider{ "sql_provider" };
            database_key() = default;
         };
      }
      //-----------------------------------------------------------------------------------------------//
      namespace env
      {
         struct author
         {
            std::unicodestring const username{ "WILSON.SOUZA" };
            author() = default;
         };

         struct key
         {
            char const  * username{ "USERNAME" };
            key() = default;
         };

         //-----------------------------------------------------------------------------------------------//
         struct groups
         {
            const std::unicodestring Config{ "GroupManagerConfig%1" };
            const std::unicodestring Styles{ "ApplicationStyleMode%1" };
            const std::unicodestring Common{ "SharedCommond%1" };
            groups() = default;
         };
      }
      //-----------------------------------------------------------------------------------------------//
      namespace db
      {
         struct datasource
         {
            std::unicodestring const TBL_GROUP_NAME{ "Group" };
            std::unicodestring const TBL_INFORMATION_NAME{ "Information" };
            std::unicodestring const TBL_RESOURCES_NAME{ "Resources" };
            std::unicodestring const TBL_NUMBERS_NAME{ "Numbers" };
            std::unicodestring const TBL_CONTROLLER_NAME{ "Controller" };
            std::stringlist const DBN_GLOBALDATABASENAME
            {
               "Group_",
               "PagesByGroup_",
               "NumbersByGroup_",
               "NumbersByPage_",
               "Numbers_",
               "IsZero_"
            };
            //-----------------------------------------------------------------------------------------------//
            int const FIELD_VARCHAR_TYPE{ 0 };
            int const FIELD_INT_TYPE{ 0x2 };
            int const FIELD_DATETIME_TYPE{ 0x4 };
            int const FIELD_BIT_TYPE{ 0x8 };
            int const FIELD_FLOAT_TYPE{ 0x10 };
            //-----------------------------------------------------------------------------------------------//
            std::stringlist const TBL_CONTROLLERLISTFIELDS
            {
               "groupname varchar(10)",
               "pagename int default 0",
               "iscompleted int default 0"
            };
            std::unicodestring const FLD_CTRL_GROUPNAME{ "groupname" };
            std::unicodestring const FLD_CTRL_PAGENAME{ "pagename" };
            std::unicodestring const FLD_CTRL_ISCOMPLETED{ "iscompleted" };
            //
            enum class SQL_CONTROLLER_ID : int
            {
               GROUPNAME, PAGENAME, ISCOMPLETED
            };
            std::vector<std::pair<int, std::unicodestring>> const SQL_FIELDS_CONTROLLER
            {
               std::make_pair(int(SQL_CONTROLLER_ID::GROUPNAME), FLD_CTRL_GROUPNAME),
               std::make_pair(int(SQL_CONTROLLER_ID::PAGENAME), FLD_CTRL_PAGENAME),
               std::make_pair(int(SQL_CONTROLLER_ID::ISCOMPLETED), FLD_CTRL_ISCOMPLETED)
            };
            //
            struct table_controller
            {
               using pointer = std::shared_ptr<table_controller>;
               std::unicodestring group_name{};
               int page_name{ 0 };
               bool is_completed{ false };
            };
            //-----------------------------------------------------------------------------------------------//
            std::stringlist const TBL_NUMBERSLISTFIELDS
            {
              "groupname varchar(10)",
              "pagename int default 0",
              "numbers int default 0",
              "useds int default 0",
              "availables int default 0",
              "iscompleted int default 0"
            };
            /**/
            std::unicodestring const FLD_NUM_GROUPNAME{ "groupname" };
            std::unicodestring const FLD_NUM_PAGENAME{ "pagename" };
            std::unicodestring const FLD_NUM_NUMBERS{ "numbers" };
            std::unicodestring const FLD_NUM_USEDS{ "useds" };
            std::unicodestring const FLD_NUM_AVAILABLES{ "availables" };
            std::unicodestring const FLD_NUM_ISCOMPLETED{ "iscompleted" };
            //
            enum class SQL_NUMBERS_ID : int
            {
               GROUPNAME, PAGENAME, NUMBERS, USEDS, AVAILABLES, ISCOMPLETED
            };
            std::vector<std::pair<int, std::unicodestring>> const SQL_FIELD_NUMBERS
            {
               std::make_pair(int(SQL_NUMBERS_ID::GROUPNAME), FLD_NUM_GROUPNAME),
               std::make_pair(int(SQL_NUMBERS_ID::PAGENAME), FLD_NUM_PAGENAME),
               std::make_pair(int(SQL_NUMBERS_ID::NUMBERS), FLD_NUM_NUMBERS),
               std::make_pair(int(SQL_NUMBERS_ID::USEDS), FLD_NUM_USEDS),
               std::make_pair(int(SQL_NUMBERS_ID::AVAILABLES), FLD_NUM_AVAILABLES),
               std::make_pair(int(SQL_NUMBERS_ID::ISCOMPLETED), FLD_NUM_ISCOMPLETED)
            };
            //
            struct table_numbers
            {
               using pointer = std::shared_ptr<table_numbers>;
               std::unicodestring group_name{};
               int page_id{ 0 };
               int numbers{ 0 };
               int useds{ 0 };
               int availables{ 0 };
               bool is_completed{ false };
            };
            //
            //-----------------------------------------------------------------------------------------------//
            std::stringlist const TBL_RESOURCESLISTFIELDS
            {
               "groupname varchar(10)",
               "numbers int default 0",
               "useds int default 0",
               "availables int default 0"
            };
            //
            std::unicodestring const FLD_RES_GROUPNAME{ "groupname" };
            std::unicodestring const FLD_RES_NUMBERS{ "numbers" };
            std::unicodestring const FLD_RES_USEDS{ "useds" };
            std::unicodestring const FLD_RES_AVAILABLES{ "availables" };
            //
            enum class SQL_RESOURCES_ID : int
            {
               GROUPNAME, NUMBERS, USEDS, AVAILABLES
            };
            std::vector<std::pair<int, std::unicodestring>> const SQL_FIELD_RESOURCES
            {
               std::make_pair(int(SQL_RESOURCES_ID::GROUPNAME), FLD_RES_GROUPNAME),
               std::make_pair(int(SQL_RESOURCES_ID::NUMBERS), FLD_RES_NUMBERS),
               std::make_pair(int(SQL_RESOURCES_ID::USEDS), FLD_RES_USEDS),
               std::make_pair(int(SQL_RESOURCES_ID::AVAILABLES), FLD_RES_AVAILABLES)
            };
            //
            struct table_resources
            {
               using pointer = std::shared_ptr<table_resources>;
               std::unicodestring group_name{};
               int numbers{ 0 };
               int useds{ 0 };
               int availables{ 0 };
            };
            //
            //-----------------------------------------------------------------------------------------------//
            std::stringlist const TBL_INFORMATIONLISTFIELDS
            {
              "groupsid varchar(1)",
              "groupname varchar(10)",
              "pagesbygroup int default 0",
              "numbersbygroup int default 0",
              "numbersbypage int default 0",
              "numbers int default 0",
              "iscreateallgroups bit default 0",
              "isallowedzero bit default 0",
              "iscompleted bit default 0",
              "created datetime default getdate()",
              "lastupdated datetime default getdate()",
              "byusername varchar(255)",
              "versionid float",
              "lastaccess datetime",
              "comments varchar(255)"
            };
            //-----------------------------------------------------------------------------------------------//
            std::unicodestring const FLD_INF_GROUPID{ "groupsid" };
            std::unicodestring const FLD_INF_GROUPNAME{ "groupname" };
            std::unicodestring const FLD_INF_PAGESBYGROUP{ "pagesbygroup" };
            std::unicodestring const FLD_INF_NUMBERSBYGROUP{ "numbersbygroup" };
            std::unicodestring const FLD_INF_NUMBERSBYPAGE{ "numbersbypage" };
            std::unicodestring const FLD_INF_NUMBERS{ "numbers" };
            std::unicodestring const FLD_INF_ISCREATEALLGROUPS{ "iscreateallgroups" };
            std::unicodestring const FLD_INF_ISALLOWEDZERO{ "isallowedzero" };
            std::unicodestring const FLD_INF_ISCOMPLETED{ "iscompleted" };
            std::unicodestring const FLD_INF_CREATED{ "created" };
            std::unicodestring const FLD_INF_LASTUPDATED{ "lastupdated" };
            std::unicodestring const FLD_INF_BYUSERNAME{ "byusername" };
            std::unicodestring const FLD_INF_VERSIONID{ "versionid" };
            std::unicodestring const FLD_INF_LASTACCESS{ "lastaccess" };
            std::unicodestring const FLD_INF_COMMENTS{ "comments" };
            /**/
            enum class SQL_INFORMATION_ID : int
            {
               GROUPID, GROUPNAME, PAGESBYGROUP, NUMBERSBYGROUP, NUMBERSBYPAGE, NUMBERS, ISCREATEALLGROUPS,
               ISALLOWEDZERO, ISCOMPLETED, CREATED, LASTUPDATED, BYUSERNAME, VERSIONID, LASTACCESS, COMMENTS
            };
            //
            std::vector<std::pair<int, std::unicodestring>> const SQL_FIELD_INFORMATION
            {
               std::make_pair(int(SQL_INFORMATION_ID::GROUPID), FLD_INF_GROUPID),
               std::make_pair(int(SQL_INFORMATION_ID::GROUPNAME), FLD_INF_GROUPNAME),
               std::make_pair(int(SQL_INFORMATION_ID::PAGESBYGROUP), FLD_INF_PAGESBYGROUP),
               std::make_pair(int(SQL_INFORMATION_ID::NUMBERSBYGROUP), FLD_INF_NUMBERSBYGROUP),
               std::make_pair(int(SQL_INFORMATION_ID::NUMBERSBYPAGE), FLD_INF_NUMBERSBYPAGE),
               std::make_pair(int(SQL_INFORMATION_ID::NUMBERS), FLD_INF_NUMBERS),
               std::make_pair(int(SQL_INFORMATION_ID::ISCREATEALLGROUPS), FLD_INF_ISCREATEALLGROUPS),
               std::make_pair(int(SQL_INFORMATION_ID::ISALLOWEDZERO), FLD_INF_ISALLOWEDZERO),
               std::make_pair(int(SQL_INFORMATION_ID::ISCOMPLETED), FLD_INF_ISCOMPLETED),
               std::make_pair(int(SQL_INFORMATION_ID::CREATED), FLD_INF_CREATED),
               std::make_pair(int(SQL_INFORMATION_ID::LASTUPDATED), FLD_INF_LASTUPDATED),
               std::make_pair(int(SQL_INFORMATION_ID::BYUSERNAME), FLD_INF_BYUSERNAME),
               std::make_pair(int(SQL_INFORMATION_ID::VERSIONID), FLD_INF_VERSIONID),
               std::make_pair(int(SQL_INFORMATION_ID::LASTACCESS), FLD_INF_LASTACCESS),
               std::make_pair(int(SQL_INFORMATION_ID::COMMENTS), FLD_INF_COMMENTS)
            };
            //
            struct table_information
            {
               using pointer = std::shared_ptr<table_information>;
               char groups_id{ Qt::Key_A };
               std::unicodestring group_name{};
               int pages_to_group{ 0 };
               int numbers_to_group{ 0 };
               int numbers_to_page{ 0 };
               int numbers{ 0 };
               bool is_create_all_groups{ false };
               bool is_allowed_zero{ false };
               bool is_completed{ false };
               QDate created{};
               QDate last_updated{};
               std::unicodestring by_username{};
               double version_id{ 0.0 };
               QDate last_access{};
               std::unicodestring comments{};
            };
            //-----------------------------------------------------------------------------------------------//
            std::unicodestring const SQL_CMD_ALTER_FIELD_NAME_ON_TABLE{ "ALTER TABLE %1.dbo.%2 ADD %3" };
            std::unicodestring const SQL_CMD_AND{ " AND %1 " };
            std::unicodestring const SQL_CMD_OR{ " OR %1 " };
            std::unicodestring const SQL_CMD_NOT{ " NOT %1 " };
            std::unicodestring const SQL_CMD_INSERT{ "INSERT INTO %1(%2) VALUES(%3) " };
            std::unicodestring const SQL_CMD_UPDATE{ "UPDATE %1 SET %2 " };
            std::unicodestring const SQL_CMD_DELETE{ "DELETE FROM %1 " };
            std::unicodestring const SQL_CMD_SELECT{ "SELECT %1 FROM %2 " };
            std::unicodestring const SQL_CMD_WHERE{ " WHERE %1 " };
            std::unicodestring const SQL_CMD_ORDERBY{ " ORDER BY %1 " };
            std::unicodestring const SQL_CMD_DROP_DATABASE{ "DROP DATABASE %1 " };
            std::unicodestring const CATALOG_SCHEMA{ "%1.dbo.%2 " };
            /**/
            datasource()
            {
            }
            std::shared_ptr<datasource> alloc()
            {
               return std::make_shared<datasource>(datasource{});
            }
            std::shared_ptr<table_controller> alloc_controller()
            {
               return std::make_shared<table_controller>(table_controller{});
            }
            std::shared_ptr<table_information> alloc_information()
            {
               return std::make_shared<table_information>(table_information{});
            }
            std::shared_ptr<table_resources> alloc_resources()
            {
               return std::make_shared<table_resources>(table_resources{});
            }
            std::shared_ptr<table_numbers> alloc_numbers()
            {
               return std::make_shared<table_numbers>(table_numbers{});
            }
         };
      }
      //-----------------------------------------------------------------------------------------------//
      struct labels
      {
         std::unicodestring const IDS_GROUPID{ "Grupo" };
         std::unicodestring const IDS_GROUPNAME{ "Nome do grupo" };
         std::unicodestring const IDS_PAGESBYGROUP{ "Pagina(s) por grupo" };
         std::unicodestring const IDS_NUMBERSBYGROUP{ "Número(s) por grupo" };
         std::unicodestring const IDS_NUMBERSBYPAGE{ "Número(s) por pagina" };
         std::unicodestring const IDS_NUMBERS{ "Números" };
         std::unicodestring const IDS_ISCREATEALLGROUPS{ "Permitir criar todos os grupos automaticamente..." };
         std::unicodestring const IDS_ISALLOWEDZERO{ "Permitir inicialização de contagem apartir de zero..." };
         std::unicodestring const IDS_ISCOMPLETED{ "Completo" };
         std::unicodestring const IDS_CREATED{ "Criado em" };
         std::unicodestring const IDS_LASTUPDATE{ "Última atualização em" };
         std::unicodestring const IDS_BYUSERNAME{ "Usuário" };
         std::unicodestring const IDS_VERSIONID{ "Versão" };
         std::unicodestring const IDS_LASTACCESS{ "Último acesso" };
         std::unicodestring const IDS_COMMENTS{ "Comentários" };
         std::unicodestring const IDS_OPTIONS{ "Opções" };
         std::unicodestring const IDS_PROPERTYS{ "Propriedade(s)" };
         std::stringlist /*g_strListOpenListPapersLabels*/ const STACK_OPENLISTPAPERLABELS
         {
           "Grupo chave",
           "Sequencia",
           "Cartela(s) por grupo",
           "Números por grupo",
           "Números por cartela(s)",
           "Números",
           "Todo(s) grupo(s)",
           "Permite Zero",
           "Completo(s)",
           "Criado",
           "Última atualização",
           "Versão",
           "Último acesso",
           "Comentário(s)"
         };
         labels() = default;
      };
      //-----------------------------------------------------------------------------------------------//
      namespace app
      {
         struct details
         {
            std::unicodestring const NAME{ "xbingo windows64" };
            std::unicodestring const CAPTION{ "Control Number 2013, 2015, 2018" };
            std::unicodestring const COMPANY{ "WR Developer" };
            std::unicodestring const ORGANIZATION_NAME{ "Copyright (C) 2012, 2013, 2014, 2015, 2018 WR DevInfo" };
            std::unicodestring const AUTHOR_NAME{ "Developed by Wilson.Souza (c) 2012, 2013, 2014, 2015, 2018" };
            double const APPLICATION_VERSION{ 2.00 };

            std::unicodestring const MS_NAME{ "Microsoft" };
            std::unicodestring const MS_OSNAME{ "Windows" };
            std::unicodestring const MS_FOLDERS{ "CurrentVersion/Explorer/Shell Folders" };
            std::unicodestring const MS_DOCUMENTS_FOLDER{ "Personal" };

            std::unicodestring const MSG_WARNING{ "Atenção!!!" };
            std::unicodestring const MSG_ERROR{ "Erro!!!" };
            std::unicodestring const MSG_QUESTION{ "Confirma Operação?" };

            std::unicodestring const AutomaticReload{ "AutomaticReload" };
            details() = default;
         };

         struct error
         {
            std::unicodestring const WRITE{ "Falha de gravação do arquivo %1!" };
            error() = default;
         };

         struct dialog_config
         {
            std::unicodestring const NUMBERS{ bb::defs::env::groups{}.Config.bind("/Numbers") };
            std::unicodestring const NUMBERSBYGROUP{ bb::defs::env::groups{}.Config.bind("/NumbersByGroup") };
            std::unicodestring const NUMBERSBYPAGE{ bb::defs::env::groups{}.Config.bind("/NumbersByPage") };
            std::unicodestring const PAGESBYGROUP{ bb::defs::env::groups{}.Config.bind("/PagesByGroup") };
            std::unicodestring const ISALLOWEDZERO{ bb::defs::env::groups{}.Config.bind("/IsAllowed") };
            std::unicodestring const ISCREATEALLGROUPS{ bb::defs::env::groups{}.Config.bind("/IsCreate") };
            dialog_config() = default;
         };
      }
      //-----------------------------------------------------------------------------------------------//
      namespace icons
      {
         struct local
         {
            using pointer = std::shared_ptr<local>;
            //
            QIcon APP{ "App-atlantik.ico" }; //App-atlantik
            QIcon HELPBOX{ "App-black-box.ico" }; // App-black-box
            QIcon DBSTATUS{ "Action-db-status.ico" };//Action-db-status
            QIcon DBADD{ "Action-db-add.ico" }; //Action-db-add
            QIcon DBCOMMIT{ "Action-db-commit.ico" }; //Action-db-commit
            QIcon DBREMOVE{ "Action-db-remove.ico" }; //Action-db-remove
            QIcon DBUPDATE{ "Action-db-update.ico" }; //Action-db-update
            QIcon EDITADD{ "Action-edit-add.ico" }; //Action-edit-add
            local() = default;
         };
      }
      //-----------------------------------------------------------------------------------------------//
      enum class find_idd : unsigned int
      {
         FINDGROUP = 0xff,
         FINDPAGE,
         FINDNUMBERS,
         FINDCOMPLETEPAGE
      };
      //-----------------------------------------------------------------------------------------------//
      namespace old_doc_format
      {
         int const IDDMAXTITLE = 0x1E;
         int const IDDMAXKEY = 0x0A;
         int const IDDMAXLINE = /*(0x64 * 4);*/ (0x64 << 2);
         int const IDDMAXID = 0x4;
         int const IDDMAXFILLER = 0x2;
         int const IDDMAXRESERVED = 0x9;
         int const IDDMAXGROUPNAME = 0x6;
         int const IDDMAXDATA = 0x64;
         int const IDDMAXFILENAME = 0x64;
         int const IDDMAXQUEUE = 0x64;
         int const IDDMAXLIST = /*(0x64 * 0x64);*/ (0x64 << 1);
         /* struct document_header */
         struct document_header
         {
            std::shared_ptr<char> id{ new char[0xA] };
            long size{ 0 };
            long offset{ 0 };
            int cols{ 0 };
            int rows{ 0 };
            int version{ 0 };
            int year{ 0 };
            char filler{ 0 };
            long reserved{ 0 };
            document_header() = default;
         };
         /* struct document_data */
         struct document_data
         {
            std::shared_ptr<char> title{ nullptr };
            std::shared_ptr<char> key{ nullptr };
            std::shared_ptr<char> arrayline{ nullptr };
            long canditions{ 0 };
            document_data() = default;
         };

         /* struct document_queue */
         struct document_queue
         {
            unsigned char groupid{ 0 };
            std::shared_ptr<char> groupname{ nullptr };
            std::shared_ptr<document_data> arraydata{ new document_data{} };
            long conditions{ 0 };
         };
         /* struct document_sheet */
         struct document_sheet
         {
            bool isnonzero{ false };
            int pagesgroup{ 0 };
            int numbersgroup{ 0 };
            int numberspage{ 0 };
            int numbers{ 0 };
            bool iscreateallgroups{ false };
            std::shared_ptr<long> reserved_data{ nullptr };
         };
         /* struct document_manager */
         struct document_manager
         {
            int groups{ 0 };
            int actived{ 0 };
            int groupactived{ 0 };
            std::shared_ptr<char> filename{ nullptr };
            std::shared_ptr<document_header> header{ new document_header{} };
            std::shared_ptr<document_sheet> sheet{ new document_sheet{} };
            std::shared_ptr<document_queue> queue{ new document_queue{} };
            std::shared_ptr<int> arraylist{ nullptr };
            document_manager() = default;
         };
      }
      //-----------------------------------------------------------------------------------------------//
   #if(0)
      template<class string_t>
      inline string_t const to_ansi(std::wstring const & value)
      {
         auto data = std::wstring(in_value.begin(), in_value.end());
         auto out_value = string_t{};
         //
         std::for_each(data.begin(), data.end(), [&](auto const & byte_value)
         {
            auto n = 0;
            auto out_type_t = 0;
            /**/
            wctomb_s(&n, &out_type_t, 1, byte_value);
            out_value += char{ out_type_t };
         });
         return out_value;
      }
   #endif
   }
}
