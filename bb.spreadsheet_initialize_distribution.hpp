//-----------------------------------------------------------------------------------------------//
// xbw32 for Windows (generate of numeric combinations for bingo or lotery)
//
// Created by wilsonsouza 2013, 2018
//
// WR Devinfo
// (c) 2012, 2013, 2014, 2015, 2016, 2017, 2018
//-----------------------------------------------------------------------------------------------//
#pragma once
#include <std.widget.hpp>
#include <std.layouts.hpp>
#include <std.lineedit.hpp>
#include <std.radiobutton.hpp>
#include <std.combobox.hpp>
#include <std.button.hpp>
/**/
namespace bb
{
   class mdichildwindow_special_combination;
   class spreadsheet_initialize_distribution : public std::widget_impl<std::vertical_box>
   {
      //Q_OBJECT
   public:
      spreadsheet_initialize_distribution(mdichildwindow_special_combination * child);
      virtual ~spreadsheet_initialize_distribution() override = default;
      virtual QWidget * create() override;

      void fill_select_group();
      void set_number_to_queue();
      void on_initialize_all_groups();
      void on_distribution_in_all_groups();
      void on_select_distributions_by_groups();
      void on_distribution_randon_in_all_groups();

      //DECLARE_OPERATOR(spreadsheet_initialize_distribution);
      std::lineedit * m_number_id{ nullptr };
      std::radiobutton * m_initialize_all_groups{ nullptr };
      std::radiobutton * m_distribution_in_all_groups{ nullptr };
      std::radiobutton * m_select_distribution_by_groups{ nullptr };
      std::radiobutton * m_distribution_randon_in_all_groups{ nullptr };
      std::combobox * m_select_group{ nullptr };
      bb::mdichildwindow_special_combination * m_child{ nullptr };
      std::button * m_ok{ nullptr };
      std::button * m_cancel{ nullptr };
      std::button * m_apply{ nullptr };
   };
}