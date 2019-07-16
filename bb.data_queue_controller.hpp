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
#include <bb.defs.hpp>
/**/
namespace std
{
   class display_progressbar;
   class mdiframewindow;
};
/**/
namespace bb
{
   struct groups_controller;
   struct pages_controller;
   class group_manager;
   struct result_controller
   {
      using pointer = std::shared_ptr<result_controller>;
      groups_controller * groups{ nullptr };
      pages_controller * pages{ nullptr };
      std::pair<int, int> availables{ -1, -1 };
      result_controller() :groups(nullptr), pages(nullptr)
      {
      }
   };
   //
   using data_queue_controller_queue = std::multimap<std::unicodestring, groups_controller *>;
   struct data_queue_controller : public data_queue_controller_queue, public task_group
   {
   public:
      using pointer = std::shared_ptr<data_queue_controller>;
      //
   public:
      data_queue_controller() noexcept;
      explicit data_queue_controller(std::mdiframewindow * frame) noexcept;
      virtual ~data_queue_controller();
      virtual data_queue_controller *  clone(bb::data_queue_controller_queue const & data = bb::data_queue_controller_queue{});
      virtual void create(std::shared_ptr<group_manager> const & manager);
      virtual groups_controller *  search_group(std::unicodestring const & group_id);
      virtual result_controller::pointer lookup(std::unicodestring const & group_id,
                                                int const & page_id, int const & number);
      virtual bool  is_filled(std::unicodestring const & group_id);
      virtual void  delete_number(std::unicodestring const & group_id,
                                  int const & page_id,
                                  int const & value);
      virtual bb::groups_controller *  lookup(std::size_t const & index);
      /**/
   private:
      std::shared_ptr<std::display_progressbar>  create_progressbar();
      std::mdiframewindow * m_framewindow;
   };
}