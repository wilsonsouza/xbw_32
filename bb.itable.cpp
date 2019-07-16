//-----------------------------------------------------------------------------------------------//
// xbw32 for Windows (generate of numeric combinations for bingo or lotery)
//
// Created by wilsonsouza 2013, 2014, 2015, 2016, 2017, 2018
//
// WR Devinfo
// (c) 2012, 2013, 2014, 2015, 2016, 2017, 2018, 2015, 2016, 2017, 2018
//-----------------------------------------------------------------------------------------------//
#include <bb.mdiframewindow.hpp>
#include <bb.custom_mdichildwindow.hpp>
#include <sql.query.hpp>
#include <sql.table.hpp>
#include <bb.table_impl.hpp>

using namespace bb;
//-----------------------------------------------------------------------------------------------//
table_impl::table_impl( custom_mdichildwindow * pChildWnd ) :m_ChildWnd( pChildWnd ),
m_Successed( false ),
m_TableName( std::unicodestring() ),
m_CatalogName( std::unicodestring() ),
m_Table( nullptr ),
m_Query( nullptr ),
m_FillMode( table_impl::RUN_OK )
{
   if ( ChildWnd )
   {
      auto q = ChildWnd->FrameWindow->GetSingleQueryLanguageHandle();
      /**/
      CatalogName = ChildWnd->CatalogName;
      FrameWindow = dynamic_cast< mdiframewindow * >( ChildWnd->FrameWindow );
      Table = std::shared_ptr < sql::Table > {new sql::Table { q->Handle }};
      Query = std::shared_ptr < sql::Query > {new sql::Query { q->GetConnectParameters() }};
      /**/
      Query->SetActiveConnection( true );
      Query->SetDataSource( CatalogName );
   }
   /**/
   Initialize();
}
//-----------------------------------------------------------------------------------------------//
table_impl::table_impl( mdiframewindow * pFrameWindow, std::unicodestring const & szCatalog ) :m_ChildWnd( nullptr ),
m_Successed( false ),
m_CatalogName( szCatalog ),
m_TableName( std::unicodestring() ),
m_Query( nullptr ),
m_Table( nullptr ),
m_FillMode( table_impl::RUN_OK ),
m_FrameWindow( pFrameWindow )
{
   if ( FrameWindow )
   {
      auto q = FrameWindow->GetSingleQueryLanguageHandle();
      /**/
      Table = std::shared_ptr < sql::Table > {new sql::Table { q->Handle }};
      Query = std::shared_ptr < sql::Query > {new sql::Query { q->GetConnectParameters() }};
      /**/
      Query->SetActiveConnection( true );
      Query->SetDataSource( szCatalog );
   }
   /**/
   Initialize();
}
//-----------------------------------------------------------------------------------------------//
table_impl::~table_impl()
{
   cancel();
   /**/
   if ( Table )
      Table.reset();

   if ( Query )
      Query.reset();
}
//-----------------------------------------------------------------------------------------------//
table_impl * table_impl::Initialize()
{
   Successed = false;
   QueryData = std::unicodestring { };
   OrderBy = std::unicodestring { };
   Constrain = std::unicodestring { };
   Commons = std::unicodestring { };
   return this;
}
//-----------------------------------------------------------------------------------------------//
std::shared_ptr<std::display_progressbar> table_impl::CreateDisplayProgressBar()
{
   auto d = std::shared_ptr<std::display_progressbar>
   {
      new std::display_progressbar( ChildWnd->FrameWindow, ChildWnd )
   };
   return d;
}
//-----------------------------------------------------------------------------------------------//
