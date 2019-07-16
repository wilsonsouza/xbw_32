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
#include <bb.assign.hpp>
#include <std.lineedit.hpp>
#include <std.linedate.hpp>
#include <std.checkbox.hpp>
#include <std.combobox.hpp>
#include <std.radiobutton.hpp>
/**/
namespace bb
{
   assign::assign(std::sql::table::pointer const & table, QWidget * owner) : 
      QWidget{ owner },
      std::multimap<std::unicodestring, std::widget *>{},
      m_table{ table }
   {
      auto queue = this->children();
      //
      std::for_each(queue.begin(), queue.end(), [&](QObject * obj)
      {
         this->emplace(obj->objectName(), static_cast<std::widget *>(obj));
      });
   }
   //-----------------------------------------------------------------------------------------------//
   template<bool enabled> void assign::update()
   {
      auto fields = m_table->get_field_list_map();
      /**/
      std::for_each(fields.begin(), fields.end(), [&](std::pair < std::unicodestring, std::sql::field *> f)
      {
         auto control = std::find_if(begin(), end(), compare_key{ f.first });
         /**/
         if (control != end())
         {
            if (control->second)
            {
               if (control->second->inherint("std::lineedit"))
               {
                  static_cast<std::lineedit *>(control->second)->setText(f.second->to_string());
                  control->second->setEnabled(enabled);
               }
            }
         }
      });
   }
   //-----------------------------------------------------------------------------------------------//
   template<bool enabled> void assign::set_enabled()
   {
      std::for_each(begin(), end(), [&](std::pair<std::unicodestring, std::widget> const & pair)
      {
         pair.second->setEnabled(enabled);
      });
   }
}