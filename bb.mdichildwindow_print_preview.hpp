//-----------------------------------------------------------------------------------------------//
// xbw32 for Windows (generate of numeric combinations for bingo or lotery)
//
// Created by wilsonsouza 2013, 2018
//
// WR Devinfo
// (c) 2013
//-----------------------------------------------------------------------------------------------//
#pragma once
#include <bb.defs.hpp>
#include <std.mdichildwindow.hpp>
//-----------------------------------------------------------------------------------------------//
namespace std
{
   class Button;
   template <typename = QVBoxLayout> class WidgetImpl;
   class vertical_box;
   class HorizontalBox;
};
/**/
namespace bb
{
   class mdichildwindow;
   class group_manager;
   class mdichildwindow_print_preview : public std::mdichildwindow
   {
      //Q_OBJECT
   public:
      explicit mdichildwindow_print_preview(std::mdiframewindow * frame,
                                            std::unicodestring const & caption);
      virtual ~mdichildwindow_print_preview() override = default;
      virtual void const  create_pages();
      virtual bool create(std::mdichildwindow * child) override;

      //DECLARE_OPERATOR(mdichildwindow_print_preview)
      std::widget_impl<std::horizontal_box> * m_options{ nullptr };
      QScrollArea * m_scroll_area{ nullptr };
      std::widget * m_body{ nullptr };
      std::shared_ptr<bb::group_manager> m_manager{ nullptr };
      bb::mdichildwindow * m_active_childwindow{ nullptr };
      std::widget_impl<std::vertical_box> * m_rows{ nullptr };
      //items on report form
      typedef std::shared_ptr<std::map<std::unicodestring, std::widget *>> mapped_widgets;
      mapped_widgets m_items_list{};
      std::button * m_close{ nullptr };
      std::button * m_print{ nullptr };
   };
}

