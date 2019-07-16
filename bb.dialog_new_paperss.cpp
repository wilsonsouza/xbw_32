//-----------------------------------------------------------------------------------------------//
// xbw32 for Windows (generate of numeric combinations for bingo or lotery)
//
// Created by Wilson.Souza 2012
// For Libbs Farma
//
// WR Devinfo
// (c) 2012
//-----------------------------------------------------------------------------------------------//
#include <std.button.hpp>
#include <std.combobox.hpp>
#include <std.treewidget.hpp>
#include <std.checkbox.hpp>
#include <std.textedit.hpp>
#include <std.groupbox_impl.hpp>
#include <std.lineedit.hpp>
#include <bb.create_database_data.hpp>
#include <bb.mdichildwindow_new_paper.hpp>
#include <bb.mdichildwindow_special_combination.hpp>
#include <bb.integral_validator.hpp>
#include <bb.dialog_new_papers.hpp>
#include <bb.MDIFrameWindow.hpp>
//-----------------------------------------------------------------------------------------------//
namespace bb
{
   //-----------------------------------------------------------------------------------------------//
   dialog_new_papers::dialog_new_papers(QWidget * parent) :
      std::dialog{ parent, Qt::Dialog, std::captions::file{}.NEW }
   {
      auto caption = std::unicodestring{ "%1(s) Grupo(s)..." }.
         bind(std::unicodestring{ std::captions::file{}.NEW }.replace("&", std::unicodestring{}));
      dynamic_cast<mdiframewindow *>(parent)->setCursor(Qt::WaitCursor);
      /**/
      setWindowIcon(std::icons::file{}.NEW);
      setWindowTitle(caption);
      //set text
      m_ok->setToolTip(std::unicodestring{ "Inicia operação para criação de um novo grupo ou vários." });
      m_cancel->setToolTip(std::unicodestring{ "Finaliza operação!" });
      //
      this->m_pages_bygroup = new std::lineedit{ "IDD_PAGES_BYGROUP", 3, 0x64 };
      this->m_numbers_bygroup = new std::lineedit{ "IDD_NUMBERS_BYGROUP", 3, 0x64 };
      this->m_numbers_bypage = new std::lineedit{ "IDD_NUMBERS_BYPAGE", 3, 0x64 };
      this->m_numbers = new std::lineedit{ "IDD_NUMBERS", 3, 0x64 };
      this->m_list_ofgroups = new std::combobox{ this, "Grupo(s)", true, "IDD_LIST_OF_GROUPS" };
      this->m_is_allowed_zero = new std::checkbox{ this, "", "IDD_IS_ALLOWED_ZERO", false };
      this->m_is_create_allgroups = new std::checkbox{ this, "", "IDD_IS_CREATE_ALL_GROUPS", false };
      this->m_is_special_combination = new std::checkbox{ this, "", "IDD_IS_SPECIAL_COMBINATION", false };
   }
   //-----------------------------------------------------------------------------------------------//
   bool dialog_new_papers::create(std::dialog * dlg)
   {
      auto frame = dynamic_cast<mdiframewindow *>(parent());
      /* call super method */
      dialog::create(dlg);
      /**/
      auto selection = new std::groupbox_impl<std::vertical_box>{ this, "Selecionar", "IDD_SELECTION" };
      auto options = new std::groupbox_impl<std::horizontal_box>{ this, "Opçôes", "IDD_OPTIONS" };
      // set lineedit fields
      {
         m_pages_bygroup->set_validator(new bb::integral_validator{ 6, 0x63, m_pages_bygroup });
         m_pages_bygroup->setWhatsThis("Define a quantidade de cartela(s) por grupo");
         m_pages_bygroup->setToolTip(m_pages_bygroup->whatsThis());
         //
         m_numbers_bygroup->set_validator(new bb::integral_validator(6, 0x63, m_numbers_bygroup));
         m_numbers_bygroup->setWhatsThis("Define a quantidade de número(s) utilizado(s) por grupo");
         m_numbers_bygroup->setToolTip(m_numbers_bygroup->whatsThis());
         //
         m_numbers_bypage->set_validator(new bb::integral_validator(6, 0x63, m_numbers_bypage));
         m_numbers_bypage->setWhatsThis("Define a quantidade de número(s) por cartela(s)");
         m_numbers_bypage->setToolTip(m_numbers_bypage->whatsThis());
         //
         m_numbers->set_validator(new bb::integral_validator(9, 0x64, m_numbers));
         m_numbers->setToolTip("Quantidade de número(s) permitido não pode, ser maior que 100!");
         m_numbers->setWhatsThis("Define a quantidade de número(s) a ser utilizado(s)");
         //
         m_list_ofgroups->setToolTip("Seleciona o grupo a ser criado");
         /* create an list */
         for (auto c = frame->base->information->groups_id; c <= frame->base->last_group_id; c++)
         {
            m_list_ofgroups->addItem(std::icons::common{}.MYDOCUMENTS,
                                     std::unicodestring{ "Grupo %1" }.arg(c),
                                     c);
         }
         //
         m_is_allowed_zero->setText("Inicializa contagem apartir de zero");
         m_is_allowed_zero->setToolTip("Esta opção quando ativada, poderá afetar o\n"
                                       "desempenho e o bom funcionamento do sistema. \n"
                                       "Recomendamos não marcar esta opção!");
         m_is_allowed_zero->setWhatsThis("Define se grupo(s) sera permitido à inicialização, do número zero.");
         //
         m_is_create_allgroups->setText("Criar todos os grupos automaticamente de A à Z...");
         m_is_create_allgroups->setToolTip("Define a crição de todos os grupos de A à Z.");
         m_is_create_allgroups->setWhatsThis(m_is_create_allgroups->toolTip());
         m_is_create_allgroups->on_state_changed = [this](uint state, std::checkbox * sender)->bool
         {
            m_list_ofgroups->setEnabled(!sender->isChecked());
            return true;
         };
         //
         m_is_special_combination->setText("Criar combinação em forma de planilha");
         m_is_special_combination->setToolTip("Combinação em forma de planilha.");
         m_is_special_combination->setWhatsThis(m_is_special_combination->toolTip());
         //
         on_command = [this](std::dialog * dlg, long const & cmd, QObject * sender)->auto
         {
            if (sender == m_ok)
            {
               this->create_database_process();
            }
            else if (sender == m_cancel)
            {
               close();
            }
            return true;
         };
         //
         on_timer = [&](std::dialog * dlg, std::shared_ptr<std::timer> const & timer)->bool
         {
            auto success = this->m_numbers->text().toInt() > 0x8 &&
               m_numbers_bypage->text().toInt() > 0x5 &&
               m_numbers_bygroup->text().toInt() > 0x5 &&
               m_pages_bygroup->text().toInt() > 0x5;
            m_ok->setEnabled(success);
            return success;
         };
      }
      adjustSize();
      frame->setCursor(Qt::ArrowCursor);
      return true;
   }
   //-----------------------------------------------------------------------------------------------//
   void const  dialog_new_papers::create_database_process()
   {
      auto index = m_list_ofgroups->currentIndex();
      auto start_group = Qt::Key_A + (index == -1 ? 0 : index);
      auto last_group = m_is_create_allgroups->isChecked() ? Qt::Key_Z : start_group;
      auto frame = dynamic_cast<mdiframewindow *>(parent());
      {
         frame->base->information->groups_id = start_group;
         frame->base->last_group_id = last_group;
         frame->base->information->pages_to_group = m_pages_bygroup->text().toInt();
         frame->base->information->numbers = m_numbers->text().toInt();
         frame->base->information->numbers_to_group = m_numbers_bygroup->text().toInt();
         frame->base->information->numbers_to_page = m_numbers_bypage->text().toInt();
         frame->base->information->is_allowed_zero = m_is_allowed_zero->isChecked();
         frame->base->information->is_create_all_groups = m_is_create_allgroups->isChecked();
         //set catalog name
         create_catalog_name(std::shared_ptr<group_manager>{frame});
      }
      auto cdd = create_database_data::pointer{ new bb::create_database_data{frame} };
      std::waitcursor::pointer{ new std::waitcursor{this} };
      /* check groups */
      close();
      /* check combination */
      bool is_special_combination = m_is_special_combination->isChecked();
      bool is_created = cdd->create(true);
      /* free memory*/
      cdd.reset();
      /**/
      if (is_created && !is_special_combination)
      {
         new mdichildwindow_new_paper{ frame, std::shared_ptr<group_manager>{frame} };
      }
      /**/
      if (is_created && is_special_combination)
      {
         new mdichildwindow_special_combination{ frame, std::shared_ptr<group_manager>{frame}, std::captions::file{}.NEW };
      }
   }
   //-----------------------------------------------------------------------------------------------//
   void const dialog_new_papers::create_catalog_name(bb::group_manager::pointer & data)
   {
      auto szL = defs::db::datasource{}.DBN_GLOBALDATABASENAME;
      auto fmt = std::unicodestring{};
      /***/
      if (data->base->information->is_create_all_groups)
      {
         fmt = std::unicodestring
         {
            "%1%2_a_%3_"
         }.arg(szL.first()).arg(data->base->information->groups_id).arg(data->base->last_group_id);
      }
      else
      {
         fmt = std::unicodestring
         {
            "%1%2_"
         }.arg(szL.first()).arg(data->base->information->groups_id);
      }
      /**/
      fmt += std::unicodestring
      {
         std::unicodestring { "%1%2_" }.arg(szL[1].toLower()).arg(data->base->information->pages_to_group) +
         std::unicodestring { "%1%2_" }.arg(szL[2].toLower()).arg(data->base->information->numbers_to_group) +
         std::unicodestring { "%1%2_" }.arg(szL[3].toLower()).arg(data->base->information->numbers_to_page) +
         std::unicodestring { "%1%2_" }.arg(szL[4].toLower()).arg(data->base->information->numbers) +
         std::unicodestring { "%1%2" }.arg(szL[5].toLower()).arg(data->base->information->is_allowed_zero)
      };
      /*set catalog name*/
      data->base->catalog_name = fmt;
   }
   //-----------------------------------------------------------------------------------------------//
}