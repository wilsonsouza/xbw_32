//-----------------------------------------------------------------------------------------------//
// xbw32 for Windows (generate of numeric combinations for bingo or lotery)
//
// Created by wilsonsouza 2013, 2018
//
// WR Devinfo
// (c) 2013
//-----------------------------------------------------------------------------------------------//
#include <bb.group_data_information.hpp>
//-----------------------------------------------------------------------------------------------//
using namespace bb;
//-----------------------------------------------------------------------------------------------//
group_data_information::group_data_information()
{
   Initialize();
}
//-----------------------------------------------------------------------------------------------//
group_data_information::group_data_information(std::shared_ptr<bb::group_data_information> const & pData)
{
   Copy(pData);
}
//-----------------------------------------------------------------------------------------------//
group_data_information::group_data_information(int nPagesByGroup,
         int nNumbersByGroup, 
         int nNumbersByPage, 
         int nNumbers, 
         char cGroupID,
         char cLastGroupID,
         bool bCountByZero,
         bool bCreateAllGroups,
         bool bIsCompleted,
         std::unicodestring szCatalogName,
         std::unicodestring szTableName,
         bool bModified)
{
   m_PagesByGroup = nPagesByGroup;
   m_NumbersByGroup = nNumbersByGroup;
   m_NumbersByPage = nNumbersByPage;
   m_Numbers = nNumbers;
   m_GroupID = cGroupID;
   m_IsCountByZero = bCountByZero;
   m_IsCreateAllGroups = bCreateAllGroups;
   m_IsCompleted = bIsCompleted;
   m_CatalogName = szCatalogName;
   m_TableName = szTableName;
   m_Modified = bModified;
   m_LastGroupID = cLastGroupID;
   /**/
   CalculeLetters();
}
//-----------------------------------------------------------------------------------------------//
void group_data_information::Copy(std::shared_ptr<bb::group_data_information> const & in)
{
   m_PagesByGroup = in->m_PagesByGroup;
   m_Numbers = in->m_Numbers;
   m_NumbersByGroup = in->m_NumbersByGroup;
   m_NumbersByPage = in->m_NumbersByPage;
   m_GroupID = in->m_GroupID;
   m_IsCountByZero = in->m_IsCountByZero;
   m_IsCreateAllGroups = in->m_IsCreateAllGroups;
   m_IsCompleted = in->m_IsCompleted;
   m_CatalogName = in->m_CatalogName;
   m_TableName = in->m_TableName;
   m_Modified = in->m_Modified;
   m_LastGroupID = in->m_LastGroupID;
   /**/
   CalculeLetters();
}
//-----------------------------------------------------------------------------------------------//
int group_data_information::Calculate()
{
   return( CalculeLetters(), m_IntervalGroups * m_PagesByGroup * m_NumbersByPage );
}
//-----------------------------------------------------------------------------------------------//
void group_data_information::prepare_groups_list()
{
}
//-----------------------------------------------------------------------------------------------//
void group_data_information::Initialize()
{
   this->m_CatalogName = std::unicodestring { };
   this->m_GroupID = Qt::Key_A;
   this->m_IsCompleted = false;
   this->m_IsCountByZero = false;
   this->m_IsCreateAllGroups = false;
   this->m_LastGroupID = Qt::Key_A;
   this->m_Modified = false;
   this->m_Numbers = 0;
   this->m_NumbersByGroup = 0;
   this->m_NumbersByPage = 0;
   this->m_PagesByGroup = 0;
   this->m_TableName = std::unicodestring { };
   this->m_TitleGroup = std::unicodestring { "%1 à %2" }.
      arg( this->m_GroupID ).arg( this->m_LastGroupID );
   this->IntervalGroups = 1;
}
//-----------------------------------------------------------------------------------------------//
void group_data_information::CalculeLetters()
{
   if ( ( m_LastGroupID - m_GroupID ) == 0 )
   {
      m_IntervalGroups = 1;
   }
   else
   {
      m_IntervalGroups = int( m_LastGroupID - m_GroupID );
   }
}
//-----------------------------------------------------------------------------------------------//
