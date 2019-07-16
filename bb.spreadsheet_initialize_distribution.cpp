//-----------------------------------------------------------------------------------------------//
// xbw32 for Windows (generate of numeric combinations for bingo or lotery)
//
// Created by wilsonsouza 2013, 2018
//
// WR Devinfo
// (c) 2012, 2013, 2014, 2015, 2016, 2017, 2018
//-----------------------------------------------------------------------------------------------//
#include <std.radiobutton.hpp>
#include <std.combobox.hpp>
#include <std.button.hpp>
#include <std.lineedit.hpp>
#include <std.label.hpp>
#include <bb.mdichildwindow_special_combination.hpp>
#include <std.groupbox_impl.hpp>
#include <bb.group_manager.hpp>
#include <bb.spreadsheet_view.hpp>
#include <bb.spreadsheet_initialize_distribution.hpp>
#include <bb.data_queue_controller.hpp>
#include <bb.groups_controller.hpp>
#include <bb.pages_controller.hpp>
//-----------------------------------------------------------------------------------------------//
namespace bb
{
   //-----------------------------------------------------------------------------------------------//
   spreadsheet_initialize_distribution::spreadsheet_initialize_distribution(
      bb::mdichildwindow_special_combination * child) :
      std::widget_impl<std::vertical_box>{ this, "IDD_SPREADSHEET_INITIALIZE_DISTRIBUTION" },
      m_child{ child }
   {
      m_apply = new std::button{ this, "Aplicar", std::icons::common{}.VALID };
      m_cancel = new std::button{ this, std::captions::common{}.CANCEL, std::icons::common{}.CANCEL };
      m_distribution_in_all_groups = new std::radiobutton{ this,
         "Distribuir em todos os grupos", std::unicodestring{}, true, false };
      m_distribution_randon_in_all_groups = new std::radiobutton{ this,
         std::unicodestring{"Distribuição aleatória em todos os grupos"},
      std::unicodestring{}, true, false };
      m_initialize_all_groups = new std::radiobutton{ this,
         "Inicializar todos os grupos", std::unicodestring{}, true, false };
      m_number_id = new std::lineedit{ "NumberID", 2, 0x32 };
      m_ok = new std::button{ this, std::captions::common{}.OK, std::icons::common{}.OK };
      m_select_distribution_by_groups = new std::radiobutton{ this,
         std::unicodestring{"Selecionar a distribuição por grupos"}, std::unicodestring{}, true, false };
      m_select_group = new std::combobox{ this, std::unicodestring{} };
   }
   //-----------------------------------------------------------------------------------------------//
   QWidget * spreadsheet_initialize_distribution::create()
   {
      int n_start = m_child->base->information->is_allowed_zero;
      int n_end = m_child->base->information->numbers;
      //
      auto pNumber = new std::groupbox_impl<std::formbox>{ this, "Seleção" };
      {
         pNumber->box()->addRow(new std::label{ this, "Entre com o número desejado" }, m_number_id);
         m_number_id->set_validator(new QIntValidator{ n_start, n_end, m_number_id });
         pNumber->adjustSize();
         /**/
         m_number_id->on_text_changed = [&](std::unicodestring const & data, std::lineedit * sender)
         {
            if (!m_child->base->information->is_allowed_zero)
            {
               if (!data.isEmpty())
               {
                  if (data.toInt() == 0)
                  {
                     QMessageBox::warning(m_child,
                                          std::captions::errors{}.WARNING,
                                          "Valor invalido!");
                  }
               }
            }
            return true;
         };
      }
      /**/
      auto pOptions = new std::groupbox_impl<std::vertical_box>{ this, "Opções" };
      {
         pOptions->box()->addWidget(m_initialize_all_groups);
         pOptions->box()->addWidget(m_distribution_in_all_groups);
         pOptions->box()->addWidget(m_select_distribution_by_groups);
         pOptions->box()->addWidget(m_distribution_randon_in_all_groups);
         pOptions->adjustSize();
         //
         m_initialize_all_groups->on_clicked = [&](bool const &, std::radiobutton * sender)
         {
            m_select_group->setEnabled(false);
            m_ok->setEnabled(true);
            m_apply->setEnabled(m_ok->isEnabled());
            return true;
         };
         //
         m_distribution_in_all_groups->on_clicked = [&](bool const &, std::radiobutton * sender)
         {
            m_select_group->setEnabled(false);
            m_ok->setEnabled(!m_number_id->text().isEmpty());
            m_apply->setEnabled(m_ok->isEnabled());
            return true;
         };
         //
         m_select_distribution_by_groups->on_clicked = [&](bool const &, std::radiobutton * sender)
         {
            m_select_group->setEnabled(true);
            return true;
         };
         //
         m_distribution_randon_in_all_groups->on_clicked = [&](bool const &, std::radiobutton * sender)
         {
            m_select_group->setEnabled(false);
            m_ok->setEnabled(!m_number_id->text().isEmpty());
            m_apply->setEnabled(m_ok->isEnabled());
            return true;
         };
         //
      }
      //
      auto pSelect = new std::groupbox_impl<std::formbox>{ this, "Grupos" };
      {
         pSelect->box()->addRow(new std::label{ this, "Selecione o grupo desejado" }, m_select_group);
         pSelect->adjustSize();
         //
         m_select_group->setEnabled(false);
         //fill select group
         fill_select_group();
         //
         m_select_group->on_current_index_changed = [&](int const &, std::combobox * sender)
         {
            m_ok->setEnabled(!m_number_id->text().isEmpty() && m_select_distribution_by_groups->isChecked());
            m_apply->setEnabled(m_ok->isEnabled());
            return true;
         };
      }
      //
      auto pButtons = new std::widget_impl<std::horizontal_box>{ this, std::unicodestring{} };
      {
         pButtons->box()->addWidget(m_ok);
         pButtons->box()->addWidget(m_cancel);
         pButtons->box()->addWidget(m_apply);
         pButtons->box()->addStretch();
         //
         m_cancel->setEnabled(true);
         //
         m_ok->on_clicked = [&](bool const &, std::button * sender)
         {
            m_ok->setEnabled(false);
            m_apply->setEnabled(false);
            /**/
            set_number_to_queue();
            return std::dispatch_event_by_pplx(m_child,
                                               m_child->on_notify,
                                               this,
                                               this,
                                               (void *)bb::interface_messages::ON_UPDATE_LISTVIEW,
                                               nullptr);
         };
         //
         m_apply->on_clicked = m_ok->on_clicked;
         //
         m_cancel->on_clicked = [&](bool const &, std::button * sender)
         {
            m_number_id->setText(std::unicodestring{});
            m_number_id->setFocus();
            m_ok->setEnabled(false);
            m_apply->setEnabled(false);
            return true;
         };
      }
      //
      auto pBody = new std::horizontal_box{};
      {
         pBody->addLayout(new define_layout_control<>(pNumber));
         pBody->addLayout(new define_layout_control<>(pOptions));
         pBody->addLayout(new define_layout_control<>(pSelect));
         pBody->addStretch();
      }
      //
      box()->addLayout(pBody);
      box()->addWidget(pButtons);
      adjustSize();
      return this;
   }
   //-----------------------------------------------------------------------------------------------//
   void  spreadsheet_initialize_distribution::fill_select_group()
   {
      for (auto & value : *m_child->groups)
      {
         m_select_group->addItem(std::icons::common{}.INFORMATION, value.group_id);
      }
   }
   //-----------------------------------------------------------------------------------------------//
   void  spreadsheet_initialize_distribution::set_number_to_queue()
   {
      if (m_initialize_all_groups->isChecked())
      {
         on_initialize_all_groups();
      }
      if (m_distribution_in_all_groups->isChecked())
      {
         on_distribution_in_all_groups();
      }
      if (m_select_distribution_by_groups->isChecked())
      {
         on_select_distributions_by_groups();
      }
      if (m_distribution_randon_in_all_groups->isChecked())
      {
         on_distribution_randon_in_all_groups();
      }
   }
   //-----------------------------------------------------------------------------------------------//
   void spreadsheet_initialize_distribution::on_initialize_all_groups()
   {
      int n_value = m_child->base->information->is_allowed_zero;
      //
      for (auto & g : *m_child->groups)
      {
         for (auto & p : g.pages)
         {
            auto value_id = std::find_if(p.numbers.begin(), p.numbers.end(), controller::page_numbers{ n_value });
            /**/
            if (value_id != p.numbers.end())
            {
               auto avail_n = std::find_if(g.availables.begin(),
                                           g.availables.end(),
                                           controller::available_numbers{ n_value });
               /**/
               if (avail_n != g.availables.end())
               {
                  if (avail_n->availables > 0)
                  {
                     p.numbers.push_back(controller::page_numbers{ n_value, false });
                     n_value++;
                     avail_n->availables--;
                  }
               }
            }
         }
      }
   }
   //-----------------------------------------------------------------------------------------------//
   void spreadsheet_initialize_distribution::on_distribution_in_all_groups()
   {
      auto n_value = m_number_id->text().toInt();
      /**/
      for (auto & group : *m_child->groups)
      {
         for (auto & page : group.pages)
         {
            auto number_id = std::find_if(page.numbers.begin(),
                                          page.numbers.end(), controller::page_numbers{ n_value });
            auto avail_n = std::find_if(group.availables.begin(),
                                        group.availables.end(), controller::available_numbers{ n_value });
            /**/
            if (number_id == page.numbers.end())
            {
               if (avail_n->availables > 0)
               {
                  page.numbers.push_back(controller::page_numbers{ n_value, false });
                  avail_n->availables--;
               }
            }
         }
      }
   }
   //-----------------------------------------------------------------------------------------------//
   void spreadsheet_initialize_distribution::on_select_distributions_by_groups()
   {
      auto n_pos = m_select_group->currentIndex(); /* get current index*/
      auto group = std::find_if(m_child->groups->begin(),
                                m_child->groups->end(), controller::groups{ m_select_group->itemText(n_pos) });
      auto n_value = m_number_id->text().toInt();
      /* run all pages */
      for (auto & page : group->pages)
      {
         auto n_id = std::find_if(page.numbers.begin(), page.numbers.end(), controller::page_numbers{ n_value });
         auto avail_n = std::find_if(group->availables.begin(),
                                     group->availables.end(), controller::available_numbers{ n_value });
         /**/
         if (n_id != page.numbers.end())
         {
            if (avail_n->availables > 0)
            {
               page.numbers.push_back(controller::page_numbers{ n_value, false });
               avail_n->availables--;
            }
         }
      }
   }
   //-----------------------------------------------------------------------------------------------//
   void spreadsheet_initialize_distribution::on_distribution_randon_in_all_groups()
   {
      auto n_value = m_number_id->text().toInt();
      /* fill in randon mode*/
      for (auto n_acc = 0; n_acc < m_child->groups->size(); n_acc++)
      {
         auto n_pos_id = (n_acc % rand());
         auto & group_ad = m_child->groups->at(n_pos_id);
         /**/
         for (auto & page : group_ad.pages)
         {
            auto n_id = std::find_if(page.numbers.begin(),
                                     page.numbers.end(), controller::page_numbers{ n_value });
            /**/
            if (n_id == page.numbers.end())
            {
               auto avail_n = std::find_if(group_ad.availables.begin(),
                                           group_ad.availables.end(), controller::available_numbers{ n_value });
               /**/
               if (avail_n->availables > 0)
               {
                  page.numbers.push_back(controller::page_numbers{ n_value, false });
                  avail_n->availables--;
               }
            }
         }
      }
   }
   //-----------------------------------------------------------------------------------------------//
}