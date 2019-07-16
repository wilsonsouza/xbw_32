//-----------------------------------------------------------------------------------------------//
// xbw32 for Windows (generate of numeric combinations for bingo or lotery)
//
// Created by Wilson.Souza 2012
//
// WR Devinfo
// (c) 2012, 2013, 2014, 2015
//
// Last updated by wilson.souza 5-11-2015
//-----------------------------------------------------------------------------------------------//
#include <bb.defs.hpp>
#include <sql.table.hpp>
#include <sql.query.hpp>
#include <std.checkbox.hpp>
#include <std.linedate.hpp>
#include <std.textedit.hpp>
#include <std.label.hpp>
#include <std.groupbox_impl.hpp>
#include <std.display_progressbar.hpp>
#include <std.mdiframewindowarea.hpp>
#include <std.treewidget.hpp>
#include <bb.group_manager.hpp>
#include <bb.mdiframewindow.hpp>
#include <bb.mdichildwindow_open_paper.hpp>
#include <bb.create_database_data.hpp>
#include <bb.mdichildwindow_special_combination.hpp>
#include <bb.dialog_open_list_papers.hpp>
#include <bb.assign.hpp>
//-----------------------------------------------------------------------------------------------//
namespace bb
{
   //-----------------------------------------------------------------------------------------------//
   dialog_open_list_papers::dialog_open_list_papers(QWidget * parent) :
      std::dialog{ parent, Qt::Dialog, std::captions::file{}.OPEN }
   {
      auto caption = std::unicodestring{ std::captions::file{}.OPEN }.replace("&", std::unicodestring{});
      auto frame = dynamic_cast<mdiframewindow *>(parent);
      /**/
      frame->setCursor(Qt::WaitCursor);
      setWindowTitle(caption);
      setWindowIcon(std::icons::file{}.OPEN);
      /* disable OK button */
      m_ok->setEnabled(false);
      /* load catalogs */
      m_list_catalogs = new std::treewidget(this, "IDD_LISTCATALOGS");
      /**/
      m_delete = new std::button
      {
         this,
         std::captions::common{}.ERASE,
         std::icons::common{}.DENIED,
         "IDD_DELETE"
      };
      m_delete_all = new std::button
      {
         this,
         "Remover todos",
         std::icons::common{}.EXCLAMATION,
         "IDD_DELETE_ALL"
      };
      m_is_special_combination = new std::checkbox
      {
         this,
         "Abrir cartelas em forma de planilha",
         "IDD_IS_SPECIAL_COMBINATION",
         true
      };
      m_property_db = new std::groupbox_impl<std::vertical_box>
      {
         this,
         bb::defs::labels{}.IDS_PROPERTYS,
         std::unicodestring{}
      };
      /**/
   }
   //-----------------------------------------------------------------------------------------------//
   bool dialog_open_list_papers::create(std::dialog * dlg)
   {
      auto frame = dynamic_cast<mdiframewindow *>(parent());
      auto hbox = new std::horizontal_box{};
      /* call super class method */
      std::dialog::create(dlg);
      /*prepare editions*/
      {
         using namespace defs::db;
         auto pleGroupID = new std::lineedit(datasource{}.FLD_INF_GROUPID, 0x6, 0x64);
         auto pleGroupName = new std::lineedit(datasource{}.FLD_INF_GROUPNAME, 0x6, 0x64);
         auto plePagesByGroup = new std::lineedit(datasource{}.FLD_INF_PAGESBYGROUP, 0x3, 0x64);
         auto pleNumbersByGroup = new std::lineedit(datasource{}.FLD_INF_NUMBERSBYGROUP, 0x3, 0x64);
         auto pleNumbersByPage = new std::lineedit(datasource{}.FLD_INF_NUMBERSBYPAGE, 0x3, 0x64);
         auto pleNumbers = new std::lineedit(datasource{}.FLD_INF_NUMBERS, 0x3, 0x64);
         /**/
         auto fbBox = new std::formbox{};
         {
            using namespace bb::defs;
            fbBox->addRow(new std::label{ this, labels{}.IDS_GROUPID }, pleGroupID);
            fbBox->addRow(new std::label{ this, labels{}.IDS_GROUPNAME }, pleGroupName);
            fbBox->addRow(new std::label{ this, labels{}.IDS_PAGESBYGROUP }, plePagesByGroup);
            fbBox->addRow(new std::label{ this, labels{}.IDS_NUMBERSBYGROUP }, pleNumbersByGroup);
            fbBox->addRow(new std::label{ this, labels{}.IDS_NUMBERSBYPAGE }, pleNumbersByPage);
            fbBox->addRow(new std::label{ this, labels{}.IDS_NUMBERS }, pleNumbers);
            m_property_db->box()->addLayout(fbBox);
         }
      }
      /**/
      auto pgbOptions = new std::groupbox_impl<std::vertical_box>{ this, bb::defs::labels{}.IDS_OPTIONS };
      {
         using namespace bb::defs;
         using namespace bb::defs::db;
         pgbOptions->box()->addWidget(new std::checkbox{ this,
                                      labels{}.IDS_ISALLOWEDZERO,
                                      datasource{}.FLD_INF_ISALLOWEDZERO });
         pgbOptions->box()->addWidget(new std::checkbox{ this,
                                      labels{}.IDS_ISCREATEALLGROUPS,
                                      datasource{}.FLD_INF_ISCREATEALLGROUPS });
         m_property_db->box()->addWidget(pgbOptions);
      }
      /**/
      {
         using namespace bb::defs;
         using namespace bb::defs::db;
         auto pcbIsCompleted = new std::checkbox{ this, labels{}.IDS_ISCOMPLETED, datasource{}.FLD_INF_ISCOMPLETED };
         auto pleCreated = new std::linedate{ QDate{}, this, std::IDSDATEMASK, datasource{}.FLD_INF_CREATED };
         auto pleLastUpdated = new std::linedate{ QDate{}, this, std::IDSDATEMASK, datasource{}.FLD_INF_LASTUPDATED };
         auto pleByUserName = new std::lineedit{ this, std::unicodestring{}, 0xff, 0xff, datasource{}.FLD_INF_BYUSERNAME };
         auto pleVersionID = new std::lineedit{ this, std::unicodestring{}, 3, 0x64, datasource{}.FLD_INF_VERSIONID };
         auto pleLastAccess = new std::linedate{ QDate{}, this, std::IDSDATEMASK, datasource{}.FLD_INF_LASTACCESS };
         auto pteComments = new std::textedit{ this, std::unicodestring{}, datasource{}.FLD_INF_COMMENTS };
         /**/
         auto fbDown = new std::formbox{};
         {
            using namespace bb::defs;
            fbDown->addWidget(pcbIsCompleted);
            fbDown->addRow(new std::label{ this, labels{}.IDS_CREATED }, pleCreated);
            fbDown->addRow(new std::label{ this, labels{}.IDS_LASTUPDATE }, pleLastUpdated);
            fbDown->addRow(new std::label{ this, labels{}.IDS_BYUSERNAME }, pleByUserName);
            fbDown->addRow(new std::label{ this, labels{}.IDS_VERSIONID }, pleVersionID);
            fbDown->addRow(new std::label{ this, labels{}.IDS_LASTACCESS }, pleLastAccess);
            fbDown->addRow(new std::label{ this, labels{}.IDS_COMMENTS }, pteComments);
            m_property_db->box()->addLayout(fbDown);
         }
      }
      /* set width and height of dialog */
      auto area = frame->get_desktop()->geometry();
      auto size_area = QSize{ area.width() - 50, area.height() - 100 };
      {
         setFixedSize(size_area);
      }
      /**/
      auto pgbListDb = new std::groupbox_impl<std::vertical_box>{ this, "Composição de grupo(s)" };
      {
         m_list_catalogs->setHeaderLabels(bb::defs::labels{}.STACK_OPENLISTPAPERLABELS);
         pgbListDb->setMinimumWidth(size_area.width() - 410);
         /**/
         pgbListDb->box()->addWidget(m_list_catalogs);
         pgbListDb->box()->addWidget(m_is_special_combination);
         //
         m_list_catalogs->on_item_clicked = [&](QTreeWidgetItem * item, int const & column, std::treewidget * sender)
         {
            this->on_list_catalogs_item_click(item, column, sender);
            return true;
         };
      }
      /**/
      {
         this->hbuttons()->insertWidget(3, m_delete);
         m_delete->setToolTip("Apaga banco o selecionado.");
         /**/
         m_delete->on_clicked = [&](bool const & checked, std::button * sender)
         {
            this->on_delete_clicked(checked, sender);
            return true;
         };
         /**/
         hbuttons()->insertWidget(3, m_delete_all);
         m_delete_all->setToolTip("Remove todas as tabelas do banco");
         /**/
         m_delete_all->on_clicked = [&](bool const & checked, std::button * sender)
         {
            this->on_delete_all_clicked(checked, sender);
            return true;
         };
      }
      /**/
      hbox->addWidget(pgbListDb);
      hbox->addStretch();
      hbox->addWidget(m_property_db);
      vbox()->addLayout(hbox);
      vbox()->addLayout(hbuttons());
      /* */
      m_ok->setToolTip(std::unicodestring("Abre um ou vários grupo(s)\n, para modificação."));
      m_cancel->setToolTip(std::unicodestring("Cancela operação e fecha esta janela!"));
      /* run in ppl mode */
      set_disable_all_defined_controls();
      load_catalogs(m_list_catalogs);
      frame->unsetCursor();
      /**/
      on_command = [&](std::dialog * dlg, long const & cmd, QObject * sender)
      {
         if (sender == m_ok)
         {
            load_datasource();
            return close();
         }
         else if (sender == m_cancel)
         {
            return close();
         }
         return true;
      };
      return true;
   }
   //-----------------------------------------------------------------------------------------------//
   QWidget *  dialog_open_list_papers::create_box_datainfo()
   {
      using namespace bb::defs;
      using namespace bb::defs::db;
      auto pgbPropertyDb = new std::groupbox_impl<std::horizontal_box>{ this, labels{}.IDS_PROPERTYS };
      {
         auto pleGroupID = new std::lineedit(datasource{}.FLD_INF_GROUPID, 0x6, 0x64);
         auto pleGroupName = new std::lineedit(datasource{}.FLD_INF_GROUPNAME, 0x6, 0x64);
         auto plePagesByGroup = new std::lineedit(datasource{}.FLD_INF_PAGESBYGROUP, 0x3, 0x64);
         auto pleNumbersByGroup = new std::lineedit(datasource{}.FLD_INF_NUMBERSBYGROUP, 0x3, 0x64);
         auto pleNumbersByPage = new std::lineedit(datasource{}.FLD_INF_NUMBERSBYPAGE, 0x3, 0x64);
         auto pleNumbers = new std::lineedit(datasource{}.FLD_INF_NUMBERS, 0x3, 0x64);

         auto fbBox = new std::formbox{};
         {
            fbBox->addRow(new std::label{ this, labels{}.IDS_GROUPID }, pleGroupID);
            fbBox->addRow(new std::label{ this, labels{}.IDS_GROUPNAME }, pleGroupName);
            fbBox->addRow(new std::label{ this, labels{}.IDS_PAGESBYGROUP }, plePagesByGroup);
            fbBox->addRow(new std::label{ this, labels{}.IDS_NUMBERSBYGROUP }, pleNumbersByGroup);
            fbBox->addRow(new std::label{ this, labels{}.IDS_NUMBERSBYPAGE }, pleNumbersByPage);
            fbBox->addRow(new std::label{ this, labels{}.IDS_NUMBERS }, pleNumbers);
            pgbPropertyDb->box()->addLayout(fbBox);
            pgbPropertyDb->box()->addStretch();
         }
      }
      auto pgbOptions = new std::groupbox_impl<std::vertical_box>{ this, labels{}.IDS_OPTIONS };
      {
         auto pvbOptions = new std::vertical_box{};
         /**/
         pvbOptions->addWidget(pgbOptions);
         pgbOptions->box()->addWidget(new std::checkbox{ this,
                                      labels{}.IDS_ISALLOWEDZERO,
                                      datasource{}.FLD_INF_ISALLOWEDZERO });
         pgbOptions->box()->addWidget(new std::checkbox{ this,
                                      labels{}.IDS_ISCREATEALLGROUPS,
                                      datasource{}.FLD_INF_ISCREATEALLGROUPS });
         pvbOptions->addStretch();
         pgbPropertyDb->box()->addLayout(pvbOptions);
      }
      return pgbPropertyDb;
   }
   //-----------------------------------------------------------------------------------------------//
   void const  dialog_open_list_papers::load_catalogs(std::treewidget * source)
   {
      try
      {
         using namespace defs::db;
         auto frame = dynamic_cast<mdiframewindow *>(parent());
         auto display = std::display_progressbar::pointer{ new std::display_progressbar{frame, nullptr} };
         auto tbl = frame->get_sql_handle()->get_catalogs();
         auto & connection_id = frame->get_sql_handle()->get_connection_parameters();
         /**/
         std::shared_ptr<std::waitcursor>(new std::waitcursor{ this });
         display->create(0, "Aguarde, carregando catalog(s)...");
         display->set_maximum(tbl->reccount());
         /**/
         while (!tbl->eof())
         {
            auto catalog_name = tbl->get_field(std::sql::database_internal_captions{}.catalog_name);
            /**/
            display->get_sub_caption()->setText(std::unicodestring{ "Catalog %1." }.arg(catalog_name->to_string()));
            frame->dispatch_eventlooper(false);
            /**/
            if (catalog_name->to_string().left(datasource{}.TBL_GROUP_NAME.length()) == datasource{}.TBL_GROUP_NAME)
            {
               auto sql_cmd = datasource{}.SQL_CMD_SELECT.
                  bind("*").
                  bind(defs::db::datasource{}.CATALOG_SCHEMA.
                       bind(catalog_name->to_string()).bind(datasource{}.TBL_INFORMATION_NAME));
               auto item = new QTreeWidgetItem{};
               auto catalog_ptr = std::sql::table::pointer{ new std::sql::table{connection_id} };
               /**/
               catalog_ptr->open(sql_cmd);
               item->setData(0, Qt::UserRole, catalog_name->to_string());
               /**/
               while (!catalog_ptr->eof())
               {
                  auto i = 0;
                  auto stack = defs::labels{}.STACK_OPENLISTPAPERLABELS;
                  /**/
                  for (auto p = stack.begin(); p != stack.end(); p++, ++i)
                  {
                     auto f = catalog_ptr->get_field(*p);

                     if (f->to_type() == std::sql::field_type::SQL_FIELD_BOOL)
                     {
                        auto caption = "Sim";
                        /**/
                        if (f->to_bool())
                        {
                           item->setIcon(i, std::icons::common{}.OK);
                           item->setText(i, caption);
                        }
                        else
                        {
                           item->setIcon(i, std::icons::common{}.CANCEL);
                           item->setText(i, std::unicodestring{ "Não" });
                        }
                     }
                     else
                     {
                        item->setText(i, f->to_string());
                     }
                  }
                  /**/
                  catalog_ptr->next();
                  frame->dispatch_eventlooper(true);
               }
               /**/
               source->addTopLevelItem(item);
               /**/
               if (!m_is_update_columns)
               {
                  /* resize all columns */
                  source->updatecolumns(defs::labels{}.STACK_OPENLISTPAPERLABELS);
                  m_is_update_columns = !m_is_update_columns;

                  /* disable all controls */
                  assign::pointer{ new assign{catalog_ptr, this} }->set_enabled<false>();
               }
               /* close dataset and free memory */
               catalog_ptr->close();
            }
            /* process events */
            tbl->next();
            display->update(display->get_caption()->text());
            frame->dispatch_eventlooper(true);
         }
      }
      catch (std::exception const & e)
      {
         /**/
         QMessageBox::critical(this, std::captions::errors{}.CRITICAL, e.what());
         std::dispatch_event_by_pplx(this, m_cancel->on_clicked, true, m_cancel);
      }
   }
   //-----------------------------------------------------------------------------------------------//
   void const  dialog_open_list_papers::load_datasource()
   {
      try
      {
         using namespace bb::defs::db;
         auto frame = dynamic_cast<mdiframewindow *>(parent());
         auto wait = std::make_shared<std::waitcursor>(std::waitcursor{ this });
         auto catalog_name = m_list_catalogs->currentItem()->data(0, Qt::UserRole).toString();
         auto sql_cmd = defs::db::datasource{}.SQL_CMD_SELECT.bind("*").
            bind(defs::db::datasource{}.CATALOG_SCHEMA.bind(catalog_name).
                 bind(defs::db::datasource{}.TBL_INFORMATION_NAME));
         auto & connection_id = frame->get_sql_handle()->get_connection_parameters();
         auto tbl = std::sql::table::pointer{ new std::sql::table{ connection_id } };
         auto & information = frame->base->information;
         /**/
         tbl->open(sql_cmd);
         /**/
         frame->base->catalog_name = catalog_name;
         frame->base->table_name = defs::db::datasource{}.TBL_INFORMATION_NAME;
         information->is_allowed_zero = tbl->get_field(datasource{}.FLD_INF_ISALLOWEDZERO)->to_bool();
         information->is_create_all_groups = tbl->get_field(datasource{}.FLD_INF_ISCREATEALLGROUPS)->to_bool();
         information->numbers = tbl->get_field(datasource{}.FLD_INF_NUMBERS)->to_int();
         information->numbers_to_group = tbl->get_field(datasource{}.FLD_INF_NUMBERSBYGROUP)->to_int();
         information->numbers_to_page = tbl->get_field(datasource{}.FLD_INF_NUMBERSBYPAGE)->to_int();
         information->pages_to_group = tbl->get_field(datasource{}.FLD_INF_NUMBERSBYPAGE)->to_int();
         information->is_completed = tbl->get_field(datasource{}.FLD_INF_ISCOMPLETED)->to_bool();
         information->groups_id = tbl->get_field(datasource{}.FLD_INF_GROUPID)->to_char();
         frame->base->last_group_id = information->is_create_all_groups ? Qt::Key_Z : information->groups_id;
         /**/
         verify_table_numbers();
         /**/
         auto create_db = bb::create_database_data::pointer{ new bb::create_database_data{ frame } };
         frame->base->is_modified = true;
         /* copy data */
         create_db->update_tables();
         create_db.reset();
         /* open selected window */
         if (m_is_special_combination->isChecked())
         {
            new bb::mdichildwindow_special_combination{ frame, std::shared_ptr<group_manager>(frame), std::captions::file{}.OPEN };
         }
         else
         {
            new bb::mdichildwindow_open_paper{ frame, std::shared_ptr<group_manager>(frame) };
         }
         /***/
      }
      catch (std::exception const & e)
      {
         QMessageBox::critical(this, std::captions::errors{}.CRITICAL, e.what());
         {
            /* disable OK button */
            std::dispatch_event_by_pplx(this, m_list_catalogs->on_item_clicked, nullptr, 0, m_list_catalogs);
         }
      }
   }
   //-----------------------------------------------------------------------------------------------//
   void dialog_open_list_papers::on_update_controls(QTreeWidgetItem * item_source)
   {
      try
      {
         auto frame = dynamic_cast<mdiframewindow *>(parent());
         auto catalog_name = item_source->data(0, Qt::UserRole).toString();
         auto sql_cmd = defs::db::datasource{}.SQL_CMD_SELECT.bind("*").
            bind(defs::db::datasource{}.CATALOG_SCHEMA.bind(catalog_name).
                 bind(defs::db::datasource{}.TBL_INFORMATION_NAME));
         auto & connection_id = frame->get_sql_handle()->get_connection_parameters();
         auto tbl = std::sql::table::pointer{ new std::sql::table{connection_id} };
         /**/
         tbl->open(sql_cmd);
         /**/
         assign::pointer{ new assign{tbl, this} }->update<false>();
         /**/
         if (item_source != nullptr)
         {
            auto catalogs = m_list_catalogs->itemWidget(item_source->child(0), 0);
            assign::pointer{ new assign{tbl, catalogs} }->update<false>();
         }
         /* enable combination option */
         m_is_special_combination->setEnabled(true);
      }
      catch (std::exception const & e)
      {
         QMessageBox::warning(this, std::captions::errors{}.WARNING, e.what());
         {
            std::dispatch_event_by_pplx(this, m_list_catalogs->on_item_clicked, nullptr, 0, m_list_catalogs);
         }
      }
   }
   //-----------------------------------------------------------------------------------------------//
   void  dialog_open_list_papers::verify_table_numbers()
   {
      try
      {
         auto frame = dynamic_cast<mdiframewindow *>(parent());
         auto catalog_name = m_list_catalogs->currentItem()->data(0, Qt::UserRole).toString();
         auto sql_cmd = defs::db::datasource{}.SQL_CMD_SELECT.bind("*").
            bind(defs::db::datasource{}.CATALOG_SCHEMA.bind(catalog_name).
                 bind(defs::db::datasource{}.TBL_NUMBERS_NAME));
         auto & connection_id = frame->get_sql_handle()->get_connection_parameters();
         auto tbl = std::sql::table::pointer{ new std::sql::table{connection_id} };
         /**/
         tbl->open(sql_cmd);
         frame->dispatch_eventlooper(true);
         //
         if (tbl->reccount() > 0)
         {
            if (tbl->get_field(defs::db::datasource{}.FLD_NUM_USEDS) == nullptr)
            {
               frame->get_sql_handle()->execute_non_query(defs::db::datasource{}.SQL_CMD_ALTER_FIELD_NAME_ON_TABLE.
                                                          arg(catalog_name).
                                                          arg(defs::db::datasource{}.TBL_NUMBERS_NAME).
                                                          arg("useds int default 0"));
            }
            if (tbl->get_field(defs::db::datasource{}.FLD_NUM_AVAILABLES) == nullptr)
            {
               frame->get_sql_handle()->execute_non_query(defs::db::datasource{}.SQL_CMD_ALTER_FIELD_NAME_ON_TABLE.
                                                          arg(catalog_name).
                                                          arg(defs::db::datasource{}.TBL_NUMBERS_NAME).
                                                          arg("availables int default 0"));
            }
            if (tbl->get_field(defs::db::datasource{}.FLD_INF_ISCOMPLETED) == nullptr)
            {
               frame->get_sql_handle()->execute_non_query(defs::db::datasource{}.SQL_CMD_ALTER_FIELD_NAME_ON_TABLE.
                                                          arg(catalog_name).
                                                          arg(defs::db::datasource{}.TBL_NUMBERS_NAME).
                                                          arg("iscompleted int default 0"));
            }
         }
         /**/
         sql_cmd = defs::db::datasource{}.SQL_CMD_SELECT.bind("top 1 *").
            bind(defs::db::datasource{}.CATALOG_SCHEMA.bind(catalog_name).
                 bind(defs::db::datasource{}.TBL_CONTROLLER_NAME));
         /**/
         tbl->open(sql_cmd);
         //
         if (tbl->reccount() > 0)
         {
            if (tbl->get_field(defs::db::datasource{}.FLD_CTRL_PAGENAME) == nullptr)
            {
               frame->get_sql_handle()->execute_non_query(defs::db::datasource{}.SQL_CMD_ALTER_FIELD_NAME_ON_TABLE.
                                                          arg(catalog_name).
                                                          arg(defs::db::datasource{}.TBL_CONTROLLER_NAME).
                                                          arg("pagename int default 0"));
            }
         }
      }
      catch (std::exception const & e)
      {
         QMessageBox::warning(this, std::captions::errors{}.WARNING, e.what());
      }
   }
   //-----------------------------------------------------------------------------------------------//
   void const dialog_open_list_papers::set_disable_all_defined_controls()
   {
      auto q_list = findChildren<QWidget *>();
      /**/
      std::for_each(q_list.begin(), q_list.end(), [&](auto const & p)
      {
         if (p != nullptr)
         {
            if (p->inherits("std::lineedit") ||
                p->inherits("std::textedit") ||
                p->inherits("std::checkbox"))
            {
               p->setEnabled(false);
            }
         }
      });
   }
   //-----------------------------------------------------------------------------------------------//
   void dialog_open_list_papers::on_list_catalogs_item_click(QTreeWidgetItem * item_source,
                                                             int const & column,
                                                             QTreeWidget * source)
   {
      m_property_db->setVisible(true);
      /**/
      m_delete->setEnabled(true);
      /**/
      m_delete_all->setEnabled(true);
      /**/
      m_current_item = item_source;
      /**/
      if (item_source != nullptr)
      {
         /**/
         if (source->itemWidget(item_source->child(0), 0) == nullptr)
         {
            auto ptwItem = new QTreeWidgetItem{};
            auto pwCatalogs = create_box_datainfo();
            auto r = source->geometry();
            auto s = QSize{ r.width() - 0x64, (r.height() / 2) - 30 };
            /**/
            pwCatalogs->setFixedSize(s);
            item_source->addChild(ptwItem);
            source->setItemWidget(ptwItem, 0, pwCatalogs);
            pwCatalogs->show();
            source->expand(source->currentIndex());
         }
         /**/
         m_ok->setEnabled(true);
         on_update_controls(item_source);
      }
      else
      {
         m_ok->setEnabled(false);
         /**/
         m_delete->setEnabled(false);
         /**/
         m_delete_all->setEnabled(false);
      }
   }
   //-----------------------------------------------------------------------------------------------//
   void dialog_open_list_papers::on_delete_clicked(bool const & checked, std::button * sender)
   {
      auto frame = dynamic_cast<mdiframewindow *>(parent());
      auto & conn_id = frame->get_sql_handle()->get_connection_parameters();
      auto db = std::sql::database::pointer{ new std::sql::database{conn_id} };
      auto catalog_name = m_current_item->data(0, Qt::UserRole).toString();
      /**/
      db->set_initial_catalog(std::unicodestring{});
      db->set_active_connection(true);
      /**/
      if (QMessageBox::question(this, std::captions::errors{}.QUESTION,
          std::unicodestring("Você tem certeza que deseja remover este\n catalogo %1?").arg(catalog_name),
          QMessageBox::Ok | QMessageBox::Cancel) == QMessageBox::Cancel)
      {
         return;
      }
      /**/
      try
      {
         auto current_item_index = m_list_catalogs->indexOfTopLevelItem(m_current_item);
         /**/
         db->execute_non_query(defs::db::datasource{}.SQL_CMD_DROP_DATABASE.bind(catalog_name));
         m_list_catalogs->takeTopLevelItem(current_item_index);
         m_current_item = nullptr;
         /* Notify tree */
         std::dispatch_event_by_pplx(this, m_list_catalogs->on_item_clicked, m_current_item, 0, m_list_catalogs);
      }
      catch (std::exception const & e)
      {
         QMessageBox::warning(this, std::captions::errors{}.WARNING, e.what());
      }
   }
   //-----------------------------------------------------------------------------------------------//
   void dialog_open_list_papers::on_delete_all_clicked(bool const & checked, std::button * sender)
   {
      try
      {
         auto frame = dynamic_cast<mdiframewindow *>(parent());
         auto & conn_id = frame->get_sql_handle()->get_connection_parameters();
         auto db = std::sql::database::pointer{ new std::sql::database{conn_id} };
         auto catalog_name = m_current_item->data(0, Qt::UserRole).toString();
         /**/
         db->set_initial_catalog(std::unicodestring{});
         db->set_active_connection(true);
         /**/
         if (QMessageBox::question(this, std::captions::errors{}.QUESTION,
             std::unicodestring("Você tem certeza que deseja remover todos os catalogos?"),
             QMessageBox::Ok | QMessageBox::Cancel) == QMessageBox::Cancel)
         {
            return;
         }
         /**/
         auto display = std::display_progressbar::pointer{ new std::display_progressbar{frame, nullptr} };
         {
            display->create(m_list_catalogs->topLevelItemCount(), "Aguarde, removendo todos os catalogs...");
            /**/
            while (m_list_catalogs->topLevelItemCount() > 0)
            {
               m_current_item = m_list_catalogs->takeTopLevelItem(0);
               catalog_name = m_current_item->data(0, Qt::UserRole).toString();
               display->update(display->get_caption()->text());
               display->get_sub_caption()->setText(std::unicodestring{ "Catalog %1" }.arg(catalog_name));
               /**/
               try
               {
                  int current_item_index = m_list_catalogs->indexOfTopLevelItem(m_current_item);
                  {
                     db->drop_database(catalog_name);
                     m_list_catalogs->takeTopLevelItem(current_item_index);
                     m_current_item = nullptr;
                     frame->dispatch_eventlooper();
                     /* Notify tree */
                     this->m_list_catalogs->on_item_clicked(m_current_item, 0, m_list_catalogs);
                  }
               }
               catch (std::exception const & e)
               {
                  QMessageBox::warning(this, std::captions::errors{}.WARNING, e.what());
               }
            }
         }
      }
      catch (std::exception const & e)
      {
         QMessageBox::warning(this, std::captions::errors{}.WARNING, e.what());
      }
   }
   //-----------------------------------------------------------------------------------------------//
}