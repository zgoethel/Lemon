#pragma once

#include "worker_thread.h"

////////////////////////////////////////////////////////////////////////////////
//                          Lemon 3D Graphics Engine                          //
//                    COPYRIGHT (c) 2021 by ZACH GOETHEL                      //
//  ------------------------------------------------------------------------  //
//  Use freely.  This code is published under the MIT permissive open-source  //
//  license.  For more information, see the license file included with this   //
//  repository.  Good luck, and enjoy!                                        //
//  ------------------------------------------------------------------------  //
////////////////////////////////////////////////////////////////////////////////

namespace lemon
{
    /**
     * @brief Worker thread for queuing and executing tasks on the main thread.
     */
    extern worker_thread* main_thread;

    /**
     * @brief Global worker pool for multithreading across all system threads.
     */
    extern worker_pool* main_pool;
}