//-----------------------------------------------------------------------------------------------//
// xbw32 for Windows (generate of numeric combinations for bingo or lotery)
//
// Created by wilsonsouza 2013, 2018
//
// WR Devinfo
// (c) 2012, 2013, 2014, 2015, 2016, 2017, 2018
//-----------------------------------------------------------------------------------------------//
#include <std.radiobutton.hpp>
#include <std.label.hpp>
#include <std.button.hpp>
#include <std.lineedit.hpp>
#include <std.treewidget.hpp>
#include <std.groupbox_impl.hpp>
#include <std.waitcursor.hpp>
#include <bb.mdichildwindow.hpp>
#include <bb.box_list_items.hpp>
#include <bb.box_search.hpp>
#include <bb.MDIFrameWindow.hpp>
#include <bb.table_interface.hpp>
//-----------------------------------------------------------------------------------------------//
namespace bb
{
   //-----------------------------------------------------------------------------------------------//
   box_search::box_search(bb::mdichildwindow * child) :
      std::tabbed{ child, "IDD_CUSTOM_SEARCH_BOX" },
      m_child{ child }
   {
      m_ok = new std::button{ this, std::captions::common{}.OK, std::icons::common{}.OK, "IDD_OK" };
      m_cancel = new std::button{ this, std::captions::common{}.CANCEL, std::icons::common{}.CANCEL, "IDD_CANCEL", true };
      m_help = new std::button{ this, std::captions::common{}.HELP, std::icons::common{}.HELPINDEX, "IDD_HELP" };
      m_what_find = new std::lineedit{ "IDD_LINEEDIT_FINDWHAT" };
      m_vbox = new std::widget_impl<std::vertical_box>{ this, "IDD_WIDGET_IMPL_VBOX" };
      m_search_result = new std::treewidget{ this, "IDD_TREEWIDGET_SEARCH_RESULT" };
      m_vbox_search_result = new std::widget_impl<std::vertical_box>{ this, "IDD_WIDGET_IMPL_VBOX_SEARCH_RESULT" };
      m_information = new std::label{ this, std::unicodestring{}, "IDD_LABEL_INFORMATION" };
      //
      m_is_group = new std::radiobutton{ this, "Grupo", "IDD_GROUP", false, false };
      m_is_page = new std::radiobutton{ this, "Cartela", "IDD_PAGE", false, false };
      /**/
      m_is_sequence_numbers = new std::radiobutton
      {
         this, std::unicodestring{"Sequencia de números"}, "IDD_SEQUENCENUMBERS", false, false
      };
      m_is_only_complete_pages = new std::radiobutton
      {
         this, "Somente cartelas completas", "IDD_ONLYCOMPLETEPAGES", false, false
      };
      m_is_only_incomplete_pages = new std::radiobutton
      {
         this, "Somente cartelas incompletas", "IDD_ONLYINCOMPLETEPAGES", false, false
      };
      m_is_only_duplicate_pages_group = new std::radiobutton
      {
         this, "Somente cartelas duplicadas no grupo", "IDD_ONLYDUPLICATEPAGESGROUP", false, false
      };
      m_is_all_duplicate_pages = new std::radiobutton
      {
         this, "Todas cartelas duplicadas", "IDD_ALLDUPLICATEPAGES", false, false
      };
      m_is_partial_sequence_numbers = new std::radiobutton
      {
         this, std::unicodestring{ "Sequencia parcial de números" }, "IDD_PARTIAL_SEQUENCE_NUMBERS", false, false
      };
      //
      addTab(m_vbox, "Pesquisar...");
      addTab(m_vbox_search_result, "Resultado da pesquisa...");
      setTabIcon(0, std::icons::edit{}.FIND_REPLACE);
      m_search_result->setHeaderLabels(bb::captions::box_list_items{}.HEADERLISTNAMES.split(","));
      m_search_result->sortItems(0, Qt::DescendingOrder);
      //
      m_what_find->setParent(this);
      setVisible(false);
   }
   //-----------------------------------------------------------------------------------------------//
   box_search *  box_search::create()
   {
      auto hbody = new std::horizontal_box{};
      {
         auto vdata = new std::vertical_box{};
         {
            vdata->addWidget(new std::label{ this, "Texto", "IDD_LABEL_TEXTO" });
            vdata->addWidget(m_what_find);
            hbody->addLayout(vdata);
         }
         //
         auto hoptions = new std::groupbox_impl < std::horizontal_box >
         {
            this, std::unicodestring{"Opções"}, "IDD_OPTIONS"
         };
         {
            auto voptions = new std::vertical_box{};
            {
               voptions->addWidget(m_is_group);
               voptions->addWidget(m_is_page);
               voptions->addWidget(m_is_sequence_numbers);
               voptions->addWidget(m_is_only_complete_pages);
            }
            //
            auto svoptions = new std::vertical_box{};
            {
               svoptions->addWidget(m_is_partial_sequence_numbers);
               svoptions->addWidget(m_is_only_incomplete_pages);
               svoptions->addWidget(m_is_only_duplicate_pages_group);
               svoptions->addWidget(m_is_all_duplicate_pages);
            }
            //
            hoptions->box()->addLayout(voptions);
            hoptions->box()->addLayout(svoptions);
         }
         //
         m_vbox->box()->addLayout(hbody);
         m_vbox->box()->addWidget(hoptions);
      }
      //
      auto hbuttons = new std::horizontal_box{};
      {
         hbuttons->addWidget(m_ok);
         hbuttons->addWidget(m_cancel);
         hbuttons->addWidget(m_help);
         hbuttons->addStretch();
         /**/
         m_vbox->box()->addLayout(hbuttons);
      }
      //
      m_vbox_search_result->box()->addWidget(m_search_result);
      m_vbox_search_result->box()->addWidget(m_information, Qt::AlignBottom);
      m_vbox->box()->addWidget(m_information);
      m_vbox->box()->addStretch();
      //
      auto radio_list = std::shared_ptr < std::vector<std::radiobutton *>>{ new std::vector<std::radiobutton *>{} };
      {
         radio_list->push_back(m_is_group);
         radio_list->push_back(m_is_page);
         radio_list->push_back(m_is_sequence_numbers);
         radio_list->push_back(m_is_only_complete_pages);
         radio_list->push_back(m_is_only_incomplete_pages);
         radio_list->push_back(m_is_only_duplicate_pages_group);
         radio_list->push_back(m_is_all_duplicate_pages);
         radio_list->push_back(m_is_partial_sequence_numbers);
      }
      //
      m_what_find->on_text_changed = [=](std::unicodestring const & data, std::lineedit * sender)->auto
      {
         //refresh tabbed class
         m_ok->setEnabled(!sender->text().trimmed().isEmpty());
         update();
         return true;
      };
      //
      m_ok->on_clicked = [&](bool const &, std::button * sender)->auto
      {
         auto wait_cursor = new std::waitcursor{ this };
         //
         m_search_result->clear();
         return on_search();
      };
      //
      m_cancel->on_clicked = [=](bool const &, std::button * sender)->auto
      {
         m_ok->setEnabled(false);
         m_what_find->setText(std::unicodestring{});
         m_what_find->setFocus();
         return true;
      };
      //
      m_is_only_duplicate_pages_group->setEnabled(false);
      m_is_all_duplicate_pages->setEnabled(false);
      m_is_page->setEnabled(false);
      m_is_group->setChecked(true);
      //
      for (auto p = radio_list->begin(); p != radio_list->end(); p++)
      {
         auto b = p.operator*();
         /**/
         b->on_clicked = [&](bool const &, std::radiobutton * sender)->bool
         {
            auto name = sender->objectName();
            /**/
            if (name == "IDD_GROUP")
            {
               m_information->setText(std::unicodestring
                                      {
                                         "Utiliza seguinte forma para pesquisar.\n"
                                         "Exemplo:\n"
                                         "A0% -> irá pesquisar todos os grupos de A01 à A09\n"
                                         "A%  -> irá pesquisar todos os grupos de A01 à A99\n"
                                         "Ainda pode-se utilizar outras combinações como por exemplo\n"
                                         "A%1 -> pesquisa todos os grupos entre A01 à A91"
                                      });
               m_search_options = OPTIONS::IDD_GROUP;
            }
            //
            if (name == "IDD_ONLYCOMPLETEPAGES")
            {
               m_information->setText("Digite COMPLETA/completa");
               m_search_options = OPTIONS::IDD_ONLY_COMPLETE_PAGES;
            }
            //
            if (name == "IDD_ONLYINCOMPLETEPAGES")
            {
               m_information->setText("Digite INCOMPLETA/incompleta");
               m_search_options = OPTIONS::IDD_ONLY_INCOMPLETE_PAGES;
            }
            //
            if (name == "IDD_PARTIAL_SEQUENCE_NUMBERS")
            {
               m_information->setText(std::unicodestring
                                      {
                                         "Esta opção efetua pesquisa parcial ou seja\n"
                                         "ira pesquisar em todos os grupos de cartelas a seguencia\n"
                                         "parcial dos números digitas, qualquer cartela que contenha um dos números digitados\n"
                                         "será incluida na lista. Este modo não pesquisa a sequencia exata e sim parcial."
                                      });
               m_search_options = OPTIONS::IDD_PARTIAL_SEQUENCE_NUMBERS;
            }
            //
            if (name == "IDD_SEQUENCENUMBERS")
            {
               m_information->setText(std::unicodestring
                                      {
                                         "Utilizae a seguinte forma para pesquisar.\n"
                                         "Exemplo:\n"
                                         "1,2,3,41,52,83,99 e assim por diante, a comparação sera feita igualmente à\n"
                                         "sequencia de números digitados. Somente será retornado cartelas que contenha a\n"
                                         "sequencia exata digitada."
                                      });
               m_search_options = OPTIONS::IDD_SEQUENCE_NUMBERS;
            }
            //
            if (name == "IDD_ALLDUPLICATESPAGES")
            {
               QMessageBox::warning(m_child,
                                    std::captions::errors{}.WARNING,
                                    std::unicodestring{ "Opções não disponível no momento, em desenvolvimento!" });
               m_search_options = OPTIONS::IDD_ALL_DUPLICATES_PAGES;
               return false;
            }
            //
            if (name == "IDD_PAGE")
            {
               return false;
            }
            //
            if (name == "IDD_ONLYDUPLICATESPAGESGROUP")
            {
               QMessageBox::warning(m_child,
                                    std::captions::errors{}.WARNING,
                                    std::unicodestring{ "Opções não disponível no momento, em desenvolvimento!" });
               m_search_options = OPTIONS::IDD_ONLY_DUPLICATES_PAGES_ON_GROUP;
               return false;
            }
            //
            m_information->setVisible(true);
            return true;
         };
      }
      return this;
   }
   //-----------------------------------------------------------------------------------------------//
   bool  box_search::on_search()
   {
      try
      {
         auto table = table_numbers::pointer{ new table_numbers { m_child } };
         /**/
         switch (m_search_options)
         {
         case OPTIONS::IDD_GROUP:
            table->constrain = defs::db::datasource{}.SQL_CMD_WHERE.
               bind(std::unicodestring{ "groupname = '%1'" }.bind(m_what_find->text().toUpper()));
            table->orderby = defs::db::datasource{}.SQL_CMD_ORDERBY.bind("groupname, pagename");
            break;
         case OPTIONS::IDD_ONLY_COMPLETE_PAGES:
            //szQuery = std::unicodestring("iscompleted in(1) order by groupname, pagename");
            table->constrain = defs::db::datasource{}.SQL_CMD_WHERE.
               bind(std::unicodestring{ "iscomplete = %1" }.bind(true));
            table->orderby = defs::db::datasource{}.SQL_CMD_ORDERBY.bind("groupname, pagename");
            break;
         case OPTIONS::IDD_ONLY_INCOMPLETE_PAGES:
            //szQuery = std::unicodestring("iscompleted in(0) order by groupname, pagename");
            table->constrain = defs::db::datasource{}.SQL_CMD_WHERE.
               bind(std::unicodestring{ "iscomplete = %1" }.bind(false));
            table->orderby = defs::db::datasource{}.SQL_CMD_ORDERBY.bind("groupname, pagename");
            break;
         case OPTIONS::IDD_SEQUENCE_NUMBERS:
            //szQuery = std::unicodestring
            //{
            //   "numbers in(%1) order by groupname, pagename" 
            //}.arg(m_WhatFind->text());
            table->constrain = defs::db::datasource{}.SQL_CMD_WHERE.
               bind(std::unicodestring{ "numbers in(%1)" }.
                    bind(std::stringlist{ m_what_find->text().split(",") }.join(",")));
               table->orderby = defs::db::datasource{}.SQL_CMD_ORDERBY.bind("groupname, pagename");
            break;
         case OPTIONS::IDD_PARTIAL_SEQUENCE_NUMBERS:
         case OPTIONS::IDD_ALL_DUPLICATES_PAGES:
         case OPTIONS::IDD_PAGE:
         case OPTIONS::IDD_ONLY_DUPLICATES_PAGES_ON_GROUP:
            return false;
         }
         /* execute query and load result data*/
         table->read(std::unicodestring{}, -1);
         setCurrentIndex(1);
         m_counter_rows = 0;
         append_items_on_search_result(*table->groups);
         /**/
         m_information->setText(std::unicodestring
                                {
                                   "Registro(s) %1 encontrado(s)"
                                }.arg(table->groups->size()));
         setTabText(1, std::unicodestring
                    {
                       "Resultado da pesquisa, %1"
                    }.arg(table->groups->size() == 0 ?
                    std::unicodestring{ "nenhum registro foi encontrado!" } :
                    std::unicodestring{ "%1 registro(s) encontrado(s)..." }.
                    bind(table->groups->size())));
      }
      catch (std::exception const & e)
      {
         QMessageBox::warning(parentWidget(), std::captions::errors{}.WARNING, e.what());
      }
      return false;
   }
   //-----------------------------------------------------------------------------------------------//
   void  box_search::append_items_on_search_result(std::vector<controller::groups> const & records)
   {
      std::for_each(records.begin(), records.end(), [&](controller::groups const & groups)
      {
         std::for_each(groups.pages.begin(), groups.pages.end(), [&](controller::pages const & pages)
         {
            QTreeWidgetItem * item = new QTreeWidgetItem{};
            //
            item->setText(0, groups.group_id);
            item->setText(1, std::unicodestring{}.sprintf("%03d", pages.page_id));
            item->setText(2, pages.numbers_to_stringlist()->join(","));
            item->setText(3, std::unicodestring{}.sprintf("%d", m_counter_rows));
            item->setText(4, std::unicodestring{}.sprintf("%d", groups.calculate_available_numbers()));
            item->setText(5, std::unicodestring{ "%1" }.
                          arg(pages.is_completed ? "Sim" : std::unicodestring{ "Não" }));
            item->setIcon(5, pages.is_completed ? std::icons::common{}.OK : std::icons::common{}.DENIED);
            //
            m_search_result->addTopLevelItem(item);
            bb::mdiframewindow::get_frame()->dispatch_eventlooper(true);
         });
      });
   }
   //-----------------------------------------------------------------------------------------------//
}
