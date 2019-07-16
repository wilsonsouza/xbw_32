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
#pragma once
#include <std.groupbox_impl.hpp>
/**/
/* custom_box_editions custom_mdi_child_window group_box*/
namespace std
{
   class Q_DECL_EXPORT vertical_box;
   class Q_DECL_EXPORT lineedit;
}
namespace bb
{
   class mdichildwindow;
   class box_editions : public std::groupbox_impl<std::vertical_box>
   {
      //Q_OBJECT
   public:
      struct name
      {
         std::unicodestring caption{ "Edição da cartela..." };
      };
      //
   public:
      explicit box_editions(bb::mdichildwindow * child);
      QWidget * create();
      void verify_all_editions();
      box_editions *  set_enable_editions(bool const & value = false);
      box_editions *  set_clear_editions();
      //
   public:
      std::vector<std::lineedit *> m_edit_queue{};
      std::lineedit * m_actual_edit{ nullptr };
      bb::mdichildwindow * m_child{ nullptr };
      //
   protected:
      bool validate_entry(std::lineedit * sender);
   };
}
