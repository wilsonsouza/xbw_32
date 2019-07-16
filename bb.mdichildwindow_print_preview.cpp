//-----------------------------------------------------------------------------------------------//
// xbw32 for Windows (generate of numeric combinations for bingo or lotery)
//
// Created by wilsonsouza 2013, 2018
//
// WR Devinfo
// (c) 2013
//-----------------------------------------------------------------------------------------------//
#include <std.button.hpp>
#include <std.groupbox_impl.hpp>
#include <std.layouts.hpp>
#include <std.mdiframewindowarea.hpp>
#include <bb.mdichildwindow_print_preview.hpp>
#include <bb.mdichildwindow.hpp>
#include <bb.box_list_items.hpp>
//-----------------------------------------------------------------------------------------------//
namespace bb
{
   //-----------------------------------------------------------------------------------------------//
   mdichildwindow_print_preview::mdichildwindow_print_preview(std::mdiframewindow * frame,
                                                              std::unicodestring const & caption) :
      std::mdichildwindow{ frame, caption }
   {
      ///* get and store old active child window */
      //m_ActiveChildWindow = dynamic_cast<bb::mdichildwindow *>(pFrameWnd->GetDesktop()->GetActiveMDIChildWindow());
      ///* alloc widget item list */
      //m_ItemsList = std::shared_ptr<std::map<std::unicodestring, std::widget *>>(new std::map<std::unicodestring, std::widget *>());

      ///* mount caption */
      //setWindowTitle(std::unicodestring(std::captions{}.File::PRINT_VIEW).replace("&", std::unicodestring()));
      //m_Options = new std::widget_impl<std::horizontal_box>();
      //m_Options->setWindowFlags(Qt::WindowCloseButtonHint | Qt::Widget);

      ///**/
      //m_Body = new std::widget_impl<>();
      //m_Rows = new std::widget_impl<std::vertical_box>();
      //m_ScrollArea = new QScrollArea();
      ///**/
      //SetWidget(m_vertical_box);
   }
   //-----------------------------------------------------------------------------------------------//
   bool mdichildwindow_print_preview::create(std::mdichildwindow * pWnd)
   {
      ///* draw controls on widget component */
      //m_Options->addWidget([this](std::mdichildwindow * pWnd)-> std::groupbox *
      //{
      //   std::groupbox_impl<std::horizontal_box> * pgbOptions =
      //      new std::groupbox_impl<std::horizontal_box>(std::unicodestring("Opções"), std::unicodestring());
      //   std::unique_ptr<std::IconsImplEx<>> pIconList =
      //      std::unique_ptr<std::IconsImplEx<>>(new std::IconsImplEx<>());
      //   m_Print = new std::button(std::captions{}.File::PRINT, pIconList->GetFile()->PRINT);
      //   m_Close = new std::button(std::captions{}.File::CLOSE, pIconList->GetFile()->CLOSE);
      //   /**/
      //   pgbOptions->addWidget(m_Print);
      //   pgbOptions->addWidget(m_Close);
      //   pgbOptions->addStretch();
      //   m_Close->setEnabled(true);
      //   /**/
      //   m_Print->setToolTip(std::unicodestring("Inicia impressão dos dados."));
      //   m_Close->setToolTip(std::unicodestring("Fecha esta janela."));
      //   /**/
      //   connect(m_Print, &std::button::OnClicked, [=](bool const &, std::button * pSender)
      //   {
      //      pWnd->OnNotify(nullptr, WM_PRINT, nullptr);
      //   });
      //   connect(m_Close, &std::button::OnClicked, [=](bool const &, std::button * pSender)
      //   {
      //      pWnd->close();
      //   });
      //   return pgbOptions;
      //}(this));

      //m_Body->adjustSize();

      ///* set scroll */
      //m_ScrollArea->setAutoFillBackground(true);
      //m_ScrollArea->setAcceptDrops(true);

      ///* on future set on preferences dialog */
      //m_ScrollArea->setWidgetResizable(true);
      //m_ScrollArea->setWidget(m_Body);

      ///* add widgets */
      //m_vertical_box->addWidget(m_ScrollArea, Qt::AlignCenter);
      //m_vertical_box->addStretch();
      //m_vertical_box->addWidget(m_Options, 0, Qt::AlignBottom);
      ///**/
      //m_Manager = std::shared_ptr<bb::group_manager>(new bb::group_manager(m_FrameWindow));
      //this->CreatePages();
      return true;
   }
}