//-----------------------------------------------------------------------------------------------//
// xbw32 for Windows (generate of numeric combinations for bingo or lotery)
//
// Created by wilsonsouza 2013, 2018
//
// WR Devinfo
// (c) 2012, 2013, 2014, 2015, 2016, 2017, 2018
//	Display dialog with list of sql server instances on the network
//-----------------------------------------------------------------------------------------------//
#include <std.checkbox.hpp>
#include <std.combobox.hpp>
#include <std.lineedit.hpp>
#include <std.button.hpp>
#include <std.label.hpp>
#include <bb.dialog_list_sql_server_intances.hpp>
#if(0)
#include <lm.h>
//-----------------------------------------------------------------------------------------------//
#pragma comment(lib, "netapi32.lib")
#endif
//-----------------------------------------------------------------------------------------------//
namespace bb
{
   //-----------------------------------------------------------------------------------------------//
   dialog_list_sql_server_intances::dialog_list_sql_server_intances(QWidget  * parent,
                                                                    std::unicodestring const & caption) :
      std::dialog{ parent, Qt::Dialog, caption }
   {
   }
   //-----------------------------------------------------------------------------------------------//
   bool dialog_list_sql_server_intances::create(std::dialog * dlg)
   {
      /* create sub objects */
      std::dialog::create(dlg);
      return true;
   }
   //-----------------------------------------------------------------------------------------------//
   void const  dialog_list_sql_server_intances::get_sqlserver_instances_names()
   {
   #if(0)
      using namespace std;
      LPSERVER_INFO_100 lpBuffer = NULL;
      LPSERVER_INFO_100 lpTemp;
      DWORD dwEntries;
      DWORD dwTotal;
      NET_API_STATUS nSuccess = NetServerEnum(nullptr,
                                              SV_TYPE_SQLSERVER,
                                              (LPBYTE *)&lpBuffer,
                                              MAX_PREFERRED_LENGTH,
                                              &dwEntries,
                                              &dwTotal,
                                              0x64,
                                              nullptr,
                                              0);
      DWORD dwCount = 0;

      if (nSuccess == NERR_Success || nSuccess == ERROR_MORE_DATA)
      {
         if ((lpTemp = lpBuffer) != NULL)
         {
            for (DWORD i = 0; i < dwEntries; ++i)
            {
               if (lpTemp == nullptr)
                  break;

               /* jump next address */
               lpTemp++;
               dwCount++;
            }
         }
      }

      /* free buffer */
      if (lpBuffer != nullptr)
         NetApiBufferFree(lpBuffer);
   #endif
   }
   //-----------------------------------------------------------------------------------------------//
}