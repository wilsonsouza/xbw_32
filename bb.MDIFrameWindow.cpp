//-----------------------------------------------------------------------------------------------//
// xbw32 for Windows (generate of numeric combinations for bingo or lotery) (generate of numeric combinations for bingo or lotery)
//
// Created by wilsonsouza 2012, 2013, 2014, 2015, 2016, 2017, 2018
// For Olavo Co.
//
// WR Devinfo
// (c) 2012, 2013, 2014, 2015, 2016, 2017, 2018
// update of qt 5.01 to 5.11
//-----------------------------------------------------------------------------------------------//
#include <std.toolbar.hpp>
#include <std.mdiframewindowarea.hpp>
#include <bb.application.hpp>
#include <bb.mdiframewindow.hpp>
//-----------------------------------------------------------------------------------------------//
namespace bb
{
   //-----------------------------------------------------------------------------------------------//
   mdiframewindow::mdiframewindow(QWidget * owner,
                                  bb::application * handle,
                                  std::unicodestring const & name,
                                  Qt::WindowFlags wfflags) :
      std::mdiframewindow{ nullptr, handle, name, wfflags },
      local_settings{ defs::app::details{}.COMPANY, defs::app::details{}.CAPTION, std::mdiframewindow::parent() },
      group_manager{}
   {
      setWindowIcon(handle->windowIcon());
      setWindowTitle(handle->applicationName());
      //alloc settings
   }
   //-----------------------------------------------------------------------------------------------//
   bool mdiframewindow::create(std::mainwindow * sender)
   {
      /* mrnu mount */
      get_popup()->operator+(new bb::fileitems{}).
         operator+(new std::edititems{}).
         operator+(new std::useritems{}).
         operator+(new bb::viewitems{}).
         operator+(new bb::toolsitems{}).
         operator+(new std::styleitems{}).
         operator+(new std::windowitems{}).
         operator+(new std::helpwrdeveloperinfoitems{});

      //alloc delegate response
      //SetDelegate(std::shared_ptr<mdiframewindowDelegate>(new mdiframewindowDelegate(this)));
      //SetConfig(std::shared_ptr<local_settings>(new local_settings
      //          {
      //             App::COMPANY, App::CAPTION, this
      //          }));
      /**/
      //CreateMenuBar(*pp, *GetDelegate());
      //CreateToolBar(*pp);
      //statusBar();
      //create mainmenu
      create_menubar(get_popup().operator->(), nullptr, defs::app::details{}.CAPTION);
      /**/
      //std::stringlist strListMenuItems = std::stringlist()
      //   << std::captions::File::NEW
      //   << std::captions::File::OPEN
      //   << std::captions::Tools::PREFERENCES;
      //EnableMenuItem(strListMenuItems, true);
      set_enable_menuitem(std::stringlist{ std::captions::file{}.NEW,
                          std::captions::file{}.OPEN,
                          bb::captions::file{}.PREFERENCES },
                          true);
      /**/
      //operator[](std::captions::File::NEW)->setShortcut(QKeySequence("Alt+N"));
      //operator[](std::captions::File::OPEN)->setShortcut(QKeySequence("Alt+O"));
      find_menu_item(std::captions::file{}.NEW)->setShortcut(QKeySequence("Alt+N"));
      find_menu_item(std::captions::file{}.OPEN)->setShortcut(QKeySequence("Alt+O"));
      /**/
      /* start sql server connection */
      //ActiveSQLConnection();
      //return std::mdiframewindow::OnCreate(pWnd);
      //process events
      on_close = [&](QWidget * sender)->auto
      {
         return true;
      };
      on_command = [&](std::action * sender, bool const &)->auto
      {
         return(std::captions::file{}.EXIT.compare(sender->objectName()) ? close() : false);
      };
      return true;
   }
   //-----------------------------------------------------------------------------------------------//
   std::basic_string<wchar_t> const mdiframewindow::get_computer_username()
   {
   #if defined(UNICODE)
      auto out_username = std::basic_string<wchar_t>{};
   #else
      auto out_username = std::basic_string<char>{};
   #endif
      {
         out_username.reserve(MAX_PATH);
         /**/
         auto out_offset = out_username.length();
      #if defined(UNICODE)
         GetUserName(const_cast<wchar_t *>(out_username.c_str()), LPDWORD(&out_offset));
      #else
         GetUserName(const_cast<char *>(out_username.c_str()), const_cast<DWORD *>(addressof(out_offset)));
      #endif
      }
      return out_username;
   }
   //-----------------------------------------------------------------------------------------------//
   double const  mdiframewindow::get_control_version_id()
   {
      return bb::defs::app::details{}.APPLICATION_VERSION;
   }
   //-----------------------------------------------------------------------------------------------//
   std::unicodestring const mdiframewindow::get_control_comments()
   {
      return defs::app::details{}.AUTHOR_NAME; //"Developed by Wilson.Souza (c) 2012, 2013, 2014, 2015, 2018";
   }
   //-----------------------------------------------------------------------------------------------//
#if(0)
   void  mdiframewindow::ActiveSQLConnection()
   {
      try
      {
         QByteArray byUserName = qgetenv(Env::Key::UserName);
         std::unicodestring strDataSource = Config->value(Sql::Key::InstanceName, Sql::InstanceName).toString();
         std::unicodestring strEnvironmentID = Config->value(Env::Key::UserName, Env::UserName).toString();

         /**/
         SetSQL(std::shared_ptr<sql::Query>(new sql::Query()));

         if (byUserName.toUpper() == strEnvironmentID.toUpper().toUtf8())
         {
            std::wstring computername = std::wstring{ };
            unsigned long offset = 0;
            /**/
            computername.reserve(MAX_PATH);
            GetComputerNameW(const_cast<wchar_t *>(computername.c_str()), &offset);
            /**/
            std::unicodestring szDataSource = std::unicodestring
            {
               "%1\\%2"
            }.bind(computername).arg(strDataSource);
            /**/
            //SQL->SetDataSource(szDataSource);
            SQL->SetDataSource(computername);
         }
         else
         {
            std::unicodestring strHostName = Config->value(Sql::Key::HostName, Sql::HostName).toString();
            std::unicodestring strUserName = Config->value(Sql::Key::UserName, Sql::UserName).toString();
            std::unicodestring strPassword = Config->value(Sql::Key::Password, Sql::Password).toString();
            std::unicodestring strIntegratedSecurity = Config->value(Sql::Key::IntegrateSecurity, Sql::IntegrateSecurity).toString();

            SQL->SetDataSource(std::unicodestring
                               {
                                  std::unicodestring
                                  {
                                     "%1\\%2"
                                  }.arg(strHostName).arg(strDataSource)
                               });
            /*
            sql->set_user_id(str_user_name);
            sql->set_password(str_password);
            sql->set_integrated_security(str_integrated_security);
            */
            SQL->SetUserID(strUserName);
            SQL->SetPassword(strPassword);
            SQL->SetIntegratedSecurity(strIntegratedSecurity);
         }
         /**/
         SQL->SetProvider(std::unicodestring
                          {
                             //config->value(sql::key::provider, sql::provider).to_string();
                             Config->value(Sql::Key::Provider, Sql::Provider).toString()
                          });
         SQL->SetConnection(SQL.operator*());
         SQL->SetActiveConnection(true);
      }
      catch (std::exception & e)
      {
         QMessageBox::critical(this, App::MSG_ERROR, e.what());
         GetapplicationHandle()->exit(1);
      }
   }
#endif
   //-----------------------------------------------------------------------------------------------//
#if(0)
   bool const  mdiframewindow::OnCommand(bool const & bChecked, std::Action * pAc)
   {
      std::unicodestring szName = pAc->text();

      if (szName == std::captions::File::NEW)
      {
         std::shared_ptr<bb::dialog_new_papers> pDlg(new bb::dialog_new_papers(this));
         /**/
         pDlg->DoModal();
      }
      else if (szName == std::captions::File::OPEN)
      {
         std::shared_ptr<bb::dialog_open_list_papers> pDlg(new bb::dialog_open_list_papers(this));
         /**/
         pDlg->DoModal();
      }
      else if (szName == std::captions::Tools::PREFERENCES)
      {
         QMessageBox::warning(this, std::Errors::WARNING, std::unicodestring
                              {
                                 "Opção não disponível no momento, \nem desenvolvimento para proxíma atualização!"
                              });
      }
      else if (szName == std::captions::File::EXIT)
      {
         Close();
      }
      else if (szName == std::captions::File::PRINT)
      {
         std::shared_ptr<QPrintDialog> pDlg(new QPrintDialog
                                            {
                                               Printer, this
                                            });
         /**/
         if (pDlg->exec() == QDialog::Accepted)
         {
         }
      }
      else if (szName == std::captions::File::PRINT_PAGE_SETUP)
      {
         std::shared_ptr<QPageSetupDialog> pDlg(new QPageSetupDialog(Printer, this));
         /**/
         if (pDlg->exec() == QDialog::Accepted)
         {
         }
      }
      else if (szName == std::captions::File::PRINT_SETUP)
      {
         std::shared_ptr<QPrintDialog> pDlg(new QPrintDialog(Printer, this));
         /**/
         if (pDlg->exec() == QDialog::Accepted)
         {
         }
      }
      else if (szName == std::captions::File::PRINT_VIEW)
      {
         new bb::mdichildwindow_print_preview
         {
            this,
            std::unicodestring("Visualição de %1").
            arg(Desktop->GetActiveMDIChildWindow()->windowTitle())
         };
      }
      return std::mdiframewindow::OnCommand(bChecked, pAc);
   }
#endif
   //-----------------------------------------------------------------------------------------------//
   local_settings::pointer mdiframewindow::get_config()
   {
      return std::shared_ptr<bb::local_settings>(this);
   }
   //-----------------------------------------------------------------------------------------------//
   std::sql::query::pointer mdiframewindow::get_sql_handle()
   {
      return std::sql::query::pointer{ new std::sql::query{} };
   }
   //-----------------------------------------------------------------------------------------------//
}