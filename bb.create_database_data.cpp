//-----------------------------------------------------------------------------------------------//
// xbw32 for Windows (generate of numeric combinations for bingo or lotery) (generate of numeric combinations for bingo or lotery)
//
// Created by wilsonsouza 2012, 2013, 2014, 2015, 2016, 2017, 2018
// For Olavo Co.
//
// WR Devinfo
// (c) 2012, 2014, 2015, 2018
// update of qt 5.01 to 5.11
//-----------------------------------------------------------------------------------------------//
#include <bb.defs.hpp>
#include <sql.table.hpp>
#include <sql.query.hpp>
#include <std.waitcursor.hpp>
#include <std.mdichildwindow.hpp>
#include <std.mdiframewindow.hpp>
#include <bb.mdichildwindow.hpp>
#include <bb.mdiframewindow.hpp>
#include <bb.create_database_data.hpp>
//-----------------------------------------------------------------------------------------------//
namespace bb
{
   create_database_data::create_database_data(bb::mdiframewindow * frame) :
      std::display_progressbar{ frame, nullptr },
      m_frame{ frame },
      m_wait_cursor{ std::shared_ptr<std::waitcursor>{ new std::waitcursor{frame} } }
   {
   }
   //-----------------------------------------------------------------------------------------------//
   create_database_data::~create_database_data()
   {
      this->m_wait_cursor.reset();
      m_frame->cancel();
   }
   //-----------------------------------------------------------------------------------------------//
   bool const create_database_data::create(bool const &)
   {
      try
      {
         auto sql_handle = m_frame->get_sql_handle();
         auto base = m_frame->base;
         //Copy(manager);
         std::display_progressbar::create(base->interval_groups,
                                          "Aguarde, preparando grupos e cartelas...");
         /**/
         std::static_exception(sql_handle->is_catalog(base->catalog_name) == true,
                               std::unicodestring{ "Banco de dados %1 já existe!" }.bind(base->catalog_name));
         std::static_exception(sql_handle->create_database(base->catalog_name) == false,
                               std::unicodestring{ "Bando de dados %1 não pode ser criado!" }.
                               bind(base->catalog_name));
         //
         std::static_exception(sql_handle->create_table(bb::defs::db::datasource{}.TBL_INFORMATION_NAME,
                               bb::defs::db::datasource{}.TBL_INFORMATIONLISTFIELDS.join(",")) == false,
                               std::unicodestring{ "Tabela %1 de informações, não pode ser criada!" }.
                               bind(bb::defs::db::datasource{}.TBL_INFORMATION_NAME));
         //
         std::static_exception(sql_handle->create_table(bb::defs::db::datasource{}.TBL_RESOURCES_NAME,
                               bb::defs::db::datasource{}.TBL_RESOURCESLISTFIELDS.join(",")) == false,
                               std::unicodestring{ "Tabela %1 de recursos, não pode ser criada!" }.
                               bind(bb::defs::db::datasource{}.TBL_RESOURCES_NAME));
         //
         std::static_exception(sql_handle->create_table(bb::defs::db::datasource{}.TBL_NUMBERS_NAME,
                               bb::defs::db::datasource{}.TBL_NUMBERSLISTFIELDS.join(",")) == false,
                               std::unicodestring{ "Tabela %1 de recursos, não pode ser criada!" }.
                               bind(bb::defs::db::datasource{}.TBL_NUMBERS_NAME));
         /**/
         std::static_exception(sql_handle->create_table(bb::defs::db::datasource{}.TBL_CONTROLLER_NAME,
                               bb::defs::db::datasource{}.TBL_CONTROLLERLISTFIELDS.join(",")) == false,
                               std::unicodestring{ "Tabela %1 de controle de grupo, não pode ser criada!" }.
                               bind(bb::defs::db::datasource{}.TBL_CONTROLLER_NAME));
         /**/
         this->update_information_table();
         this->process();
         return true;
      }
      catch (std::exception const & e)
      {
         QMessageBox::critical(m_frame, std::captions::errors{}.CRITICAL, e.what());
      }
      return false;
   }
   //-----------------------------------------------------------------------------------------------//
   void create_database_data::process()
   {
      m_frame->run_and_wait([&]
      {
         auto base = m_frame->base;
         //
         for (auto c = base->information->groups_id; c <= base->last_group_id && !m_frame->is_canceling(); ++c)
         {
            for (auto i = 1; i < base->information->pages_to_group && !m_frame->is_canceling(); ++i)
            {
               auto fmt_group_id = std::unicodestring{}.sprintf("%c%03d", c, i);
               /**/
               get_caption()->setText(std::unicodestring("Criando grupo %1").arg(fmt_group_id));

               /* insert resources */
               update_resources_table(fmt_group_id);

               /* insert controller */
               update_controller_table(fmt_group_id);

               /* insert numbers */
               //UpdateNumbersTable(szGroup);
               m_frame->dispatch_eventlooper(true);
            }
            /**/
            update(get_caption()->text());
         }
      });
   }
   //-----------------------------------------------------------------------------------------------//
   bool const create_database_data::update_tables()
   {
      try
      {
         auto base = m_frame->base;
         //Copy(pManager);
         /**/
         std::display_progressbar::create(base->interval_groups,
                                          "Aguarde, carregando grupos para verificação...");
         /**/
         for (auto c = base->information->groups_id; c <= base->last_group_id && !m_frame->is_canceling(); ++c)
         {
            for (auto i = 1; i < base->information->pages_to_group && !m_frame->is_canceling(); ++i)
            {
               auto fmt_group_id = std::unicodestring().sprintf("%c%03d", c, i);

               get_caption()->setText(std::unicodestring{ "Verificando grupo %1" }.arg(fmt_group_id));

               /* insert resources */
               update_resources_table(fmt_group_id);

               /* insert controller */
               update_controller_table(fmt_group_id);

               /* insert numbers */
               //UpdateNumbersTable(szGroup);
               m_frame->dispatch_eventlooper(true);
            }
            /**/
            update(m_frame->QObject::objectName());
         }
         /**/
         return true;
      }
      catch (std::exception const & e)
      {
         QMessageBox::critical(m_frame, std::captions::errors{}.CRITICAL, e.what());
      }
      return false;
   }
   //-----------------------------------------------------------------------------------------------//
   void create_database_data::drop_database(std::unicodestring const & catalog_name)
   {
      try
      {
         m_frame->get_sql_handle()->clone()->drop_database(catalog_name);
      }
      catch (std::exception const & e)
      {
         QMessageBox::critical(m_frame, std::captions::errors{}.CRITICAL, e.what());
      }
   }
   //-----------------------------------------------------------------------------------------------//
   void create_database_data::update_information_table()
   {
      try
      {
         auto base = m_frame->base;
         /**/
         base->information->by_username = std::unicodestring::fromStdWString(m_frame->get_computer_username());
         base->information->comments = m_frame->get_control_comments();
         base->information->version_id = m_frame->get_control_version_id();
         /**/
         auto d = QDate::currentDate();
         {
            base->information->created.setDate(d.year(), d.month(), d.day());
            base->information->last_updated.setDate(d.year(), d.month(), d.day());
            base->information->last_access.setDate(d.year(), d.month(), d.day());
         }
         /* execute sql command */
         get_caption()->setText(std::unicodestring("Registrando informações..."));
      }
      catch (std::exception const & e)
      {
         throw e;
      }
      return;
   }
   //-----------------------------------------------------------------------------------------------//
   void create_database_data::update_controller_table(std::unicodestring const & group)
   {
      try
      {
         auto base = m_frame->base;
         auto controller = table_controller::pointer{ new table_controller{nullptr} };
         /**/
         controller->constrain = std::unicodestring{ " %1 %2 > 0" }.
            bind(bb::defs::db::datasource{}.SQL_CMD_AND).
            bind(bb::defs::db::datasource{}.FLD_CTRL_PAGENAME);
         controller->lookup(group, -1, -1);
         /**/
         if (controller->m_table->reccount() == 0)
         {
            return;
         }
         /* run in current pplx of controller object */
         get_caption()->setText(std::unicodestring{ "Removendo dados de controle do grupo %1" }.arg(group));
         controller->constrain = std::unicodestring{};
         controller->erase(group, -1, -1);
         get_caption()->setText("Aguarde...");
         /**/
         for (auto i = 1; i <= base->information->pages_to_group && !m_frame->is_canceling(); ++i)
         {
            controller->constrain = std::unicodestring{};
            controller->write(group, i);
            /**/
            get_caption()->setText(std::unicodestring{ "Registrando dados de controle do grupo %1" }.arg(group));
            /**/
            m_frame->dispatch_eventlooper(true);
         }
      }
      catch (std::exception const & e)
      {
         throw e;
      }
   }
   //-----------------------------------------------------------------------------------------------//
   void create_database_data::update_numbers_table(std::unicodestring const & group)
   {
      //std::unicodestring szGroup = szGroupId;
      //std::shared_ptr<sql::Table> pQuery(new sql::Table(FrameWindow->SQL->Handle));
      //std::unicodestring szQuery = std::unicodestring("select * from dbo.Numbers "
      //   " where groupname in('%1') and (availables is null or availables < 0)").
      //   arg(szGroupId);
      //std::shared_ptr<QList<std::shared_ptr<bb::DataNumber>>> pNumbers(new QList<std::shared_ptr<bb::DataNumber>>());
      ////
      //Display->SubCaption->Text = "Verificando cartelas prontas...";
      //FrameWindow->DispatchEventLooper();
      ////
      //pQuery->Open(szQuery);
      ////
      //if(!pQuery->Eof)
      //{
      //   Display->SubCaption->Text = std::unicodestring("Montando lista de fixação...");
      //   FrameWindow->DispatchEventLooper();
      //   //
      //   for(int n; n <= Manager->Data->Numbers; ++n)
      //   {
      //      std::shared_ptr<bb::DataNumber> p(new bb::DataNumber());
      //      //
      //      p->Availables = Manager->Data->NumbersByGroup;
      //      p->Useds      = 0;
      //      p->Group      = szGroup;
      //      pNumbers->append(p);
      //   }
      //   //
      //   while(!pQuery->Eof)
      //   {
      //      int nNumber = pQuery->GetFieldByName("numbers")->Integer;
      //      int nPage   = pQuery->GetFieldByName("pagename")->Integer;
      //      std::shared_ptr<bb::DataNumber> p = pNumbers->value(nNumber);
      //      //
      //      p->Availables--;
      //      p->Useds++;
      //      p->Page = nPage;
      //      //
      //      FrameWindow->SQL->ExecutenonQuery(std::unicodestring("update dbo.Numbers set availables = %1, useds = %2 "
      //         "where groupname in('%3') and pagename = %4 and numbers = %6").
      //         arg(p->Availables).arg(p->Useds).arg(szGroup).arg(nNumber).arg(p->Page));
      //      //
      //      FrameWindow->SQL->ExecutenonQuery(std::unicodestring("update dbo.Resources set useds = %1, availables = %2 "
      //         "where groupname in('%3') and numbers = %4").
      //         arg(p->Useds).arg(p->Availables).arg(szGroup).arg(nNumber));
      //      //
      //      pQuery->Next();
      //      Display->SubCaption->Text = std::unicodestring("Atualizando cartela %1 do grupo %2...").arg(p->Page).arg(szGroup);
      //      FrameWindow->DispatchEventLooper();
      //      pNumbers->replace(nNumber, p);
      //   }
      //}
   }
   //-----------------------------------------------------------------------------------------------//
   void create_database_data::update_resources_table(std::unicodestring const & group)
   {
      try
      {
         auto base = m_frame->base;
         auto resources = table_resources::pointer{ new table_resources{nullptr} };
         //
         resources->constrain = std::unicodestring{ " %1 is not null" }.
            bind(defs::db::datasource{}.SQL_CMD_AND.bind(defs::db::datasource{}.FLD_RES_AVAILABLES));
         resources->lookup(group, -1, -1);
         /**/
         if (resources->m_table->reccount() == long const(base->resources->numbers))
         {
            return;
         }
         /* run in pplx */
         get_caption()->setText(std::unicodestring{ "Removendo recursos invalidos do grupo %1" }.arg(group));
         /**/
         resources->constrain = std::unicodestring{};
         resources->erase(group, -1, -1);
         get_caption()->setText("Aguarde...");
         /**/
         for (auto i = 1; i <= base->resources->numbers && !m_frame->is_canceling(); ++i)
         {
            get_caption()->setText(std::unicodestring{ "Registrando recursos do grupo %1" }.arg(group));
            /**/
            resources->write(group, -1);
            /**/
            m_frame->dispatch_eventlooper(true);
         }
      }
      catch (std::exception const & e)
      {
         throw e;
      }
   }
}