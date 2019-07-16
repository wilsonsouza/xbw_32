//-----------------------------------------------------------------------------------------------//
// xbw32 for Windows (generate of numeric combinations for bingo or lotery)
//
// Created by wilsonsouza 2013, 2018
//
// WR Devinfo
// (c) 2013
//-----------------------------------------------------------------------------------------------//
#pragma once
#include <bb.group_data_information.hpp>
//-----------------------------------------------------------------------------------------------//
namespace bb
{
   class information_group: public bb::group_data_information
   {
   public:
      explicit information_group(std::shared_ptr<bb::group_data_information> const & data);
      virtual ~information_group() { }
   };
}