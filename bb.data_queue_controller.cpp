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
#include <bb.groups_controller.hpp>
#include <bb.pages_controller.hpp>
#include <bb.data_queue_controller.hpp>
#include <bb.group_manager.hpp>
#include <std.display_progressbar.hpp>
//-----------------------------------------------------------------------------------------------//
namespace bb
{
   data_queue_controller::data_queue_controller() noexcept :
      data_queue_controller_queue{},
      task_group{},
      m_framewindow{ nullptr }
   {}
   //-----------------------------------------------------------------------------------------------//
   data_queue_controller::data_queue_controller(std::mdiframewindow * frame) noexcept :
      data_queue_controller_queue{},
      task_group{},
      m_framewindow{ frame }
   {
   }
   //-----------------------------------------------------------------------------------------------//
   data_queue_controller::~data_queue_controller()
   {
      clear();
      cancel();
   }
   //-----------------------------------------------------------------------------------------------//
   data_queue_controller *  data_queue_controller::clone(bb::data_queue_controller_queue const & data)
   {
      auto temp = new data_queue_controller{ m_framewindow };
      this->swap(const_cast<data_queue_controller_queue &>(data));
      return temp;
   }
   //-----------------------------------------------------------------------------------------------//
   std::display_progressbar::pointer data_queue_controller::create_progressbar()
   {
      return std::display_progressbar::pointer{new std::display_progressbar{ m_framewindow, nullptr }};
   }
   //-----------------------------------------------------------------------------------------------//
   void data_queue_controller::create(group_manager::pointer const & manager)
   {
      run_and_wait([&]
      {
         auto m = manager;
         auto d = create_progressbar();
         /**/
         d->create(m->calculate(), "Aguarde, criando grupo(s)...");
         /**/
         for (auto c = m->group_id; c <= m->last_group_id; c++)
         {
            /**/
            d->get_sub_caption()->setText(std::unicodestring{ "Criando grupo %1..." }.arg(c));
            d->update(d->get_caption()->text());
            /**/
            for (auto i = 1; i <= m->numbers_to_group; i++)
            {
               auto p = new groups_controller{ std::unicodestring{}.sprintf("%c%03d", c, i) };
               /**/
               int max_value = int{ m->numbers + int{m->is_count_to_zero} };
               int start_value = int{ m->is_count_to_zero };
               /**/
               p->create_availables(start_value, max_value);
               /**/
               for (auto n = 1; n <= m->numbers_to_page; n++)
               {
                  p->push_back(new pages_controller{ n });
               }
               /**/
               emplace(p->m_group, p);
            }
         }
      });
   }
   //-----------------------------------------------------------------------------------------------//
   groups_controller *  data_queue_controller::search_group(std::unicodestring const & group_id)
   {
      auto founded = find(group_id);
      return (founded != end() ? founded->second : nullptr);
   }
   //-----------------------------------------------------------------------------------------------//
   bool  data_queue_controller::is_filled(std::unicodestring const & group_id)
   {
      groups_controller * g = this->search_group(group_id);
      bool enabled = false;
      //
      if (g)
      {
         std::for_each(g->begin(), g->end(), [&](auto const & value)
         {
            enabled |= !value->empty();
         });
      }
      return enabled;
   }
   //-----------------------------------------------------------------------------------------------//
   void  data_queue_controller::delete_number(std::unicodestring const & group_id,
                                              int const & page_id,
                                              int const & value)
   {
      run_and_wait([&]
      {
         auto g = search_group(group_id);
         //
         std::static_exception(g == nullptr,
                               std::unicodestring{ "Grupo " + group_id +
                                                    std::unicodestring { " com pagina %1 " }.arg(page_id) +
                                                    std::unicodestring { " e número %1 não encontrado!" }.arg(value)
                               });
         {
            auto p = g->search_page(page_id);
            //
            std::static_exception(p == nullptr,
                                  std::unicodestring{ "Pagina " + std::unicodestring{"%1"}.bind(page_id) +
                                  std::unicodestring{" com número %1 não encontrado!"}.bind(value) });
            {
               bool success = p->search_number(value);
               //
               std::static_exception(success == false, std::unicodestring{ "Número %1 não existe!" }.arg(value));
               {
                  auto r = g->m_availables_queue->lookup(value);
                  /**/
                  p->erase(r.first);
                  r.second++;
                  g->m_availables_queue->update(r);
               }
            }
         }
      });
   }
   //-----------------------------------------------------------------------------------------------//
   result_controller::pointer data_queue_controller::lookup(std::unicodestring const & group_id,
                                                            int const & page_id,
                                                            int const & number)
   {
      auto p = result_controller::pointer{ new result_controller { } };
      /**/
      if ((p->groups = search_group(group_id)) != nullptr)
      {
         p->pages = p->groups->search_page(page_id);
         p->availables = p->groups->m_availables_queue->lookup(number);
      }
      return p;
   }
   //-----------------------------------------------------------------------------------------------//
   bb::groups_controller *  data_queue_controller::lookup(std::size_t const & index)
   {
      std::static_exception((index > size() || empty()), "Index out of range!");
      auto n = 0u;
      groups_controller * g = nullptr;
      /**/
      run_and_wait([&]
      {
         auto result = std::find_if(begin(), end(), [&](auto const & value)
         {
            return (index == n++);
         });
         g = (result != end() ? result->second : nullptr);
      });
      return g;
   }
}