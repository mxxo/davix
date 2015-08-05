/*
 * This File is part of Davix, The IO library for HTTP based protocols
 * Copyright (C) CERN 2013  
 * Author: Adrien Devresse <adrien.devresse@cern.ch>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
*/

#ifndef CHAIN_FACTORY_HPP
#define CHAIN_FACTORY_HPP

#include <bitset>

#include <fileops/httpiochain.hpp>
#include <fileops/fileutils.hpp>

namespace Davix{

const int CHAIN_POSIX = 1;

typedef std::bitset<32> CreationFlags;

class ChainFactory
{
public:
    static HttpIOChain& instanceChain(const CreationFlags & flags, HttpIOChain & c);
private:
    ChainFactory();
};


}

#endif // CHAIN_FACTORY_HPP
