#pragma once

#include <deque>
#include <memory>
#include <vector>

////////////////////////////////////////////////////////////////////////////////
//                          Lemon 3D Graphics Engine                          //
//                    COPYRIGHT (c) 2021 by ZACH GOETHEL                      //
//  ------------------------------------------------------------------------  //
//  Use freely.  This code is published under the MIT permissive open-source  //
//  license.  For more information, see the license file included with this   //
//  repository.  Good luck, and enjoy!                                        //
//  ------------------------------------------------------------------------  //
////////////////////////////////////////////////////////////////////////////////

/**
 * A resource management stack which allows stratification of allocated runtime
 * resources into several groups; the first group in will be the last group to
 * be deallocated.
 * 
 * For example, the base tier of the resource stack may contain vital a vital
 * engine resource or context.  Higher tiers on the stack may contain shaders
 * and other objects which are relavant to a single operation or period of time.
 * These tiers can be pushed and popped, where pushing stores the current group
 * of resources and pushes a new empty group onto the resource stack.  Popping
 * will delete all resources in the current resource group and return the stack
 * to the next lowest tier.
 * 
 * This design concept follows the idea that an application behavior over time
 * will follow that of a stack, where the application may push in and out of
 * operations.
 * 
 * @brief A tiered resource management object; a stack of groups of resources.
 * @author Zach Goethel
 */
namespace lemon
{
    class resource_stack
    {
    private:
        /**
         * This is the primary allocation stack.  This allocated memory contains
         * a stack of resource groups and may be dynamically pushed into and
         * popped out of.
         * 
         * References to managed objects are stored in buckets which are stored
         * in this stack.
         * 
         * @brief The allocation stack; a stack of collections of pointers.
         */
        std::deque<std::vector<void*>> allocation_stack;

    public:
        /**
         * This operation will push a new and empty resource group onto the
         * resource stack, thus storing the current group of resources as-is
         * until the stack is popped.
         * 
         * This represents the application entering deeper into its runtime
         * state, such as entering a specific region or window.
         * 
         * @brief Pushes the resource stack with a new resource group.
         */
        void push();

        /**
         * This operation will delete all objects in the current resource group
         * and will pop it off the stack, thus restoring the previously pushed
         * resource group.
         * 
         * This represents the application backing out of its runtime state,
         * such as backing out of a specific region or window.
         * 
         * @brief Pops the stack and destroys the current resource group.
         */
        void pop();

        /**
         * This will attribute the provided resource's pointer to the current
         * resource group.  In order for this resource to persist a call to pop
         * the resource stack, the resource stack should be pushed.  Then the
         * resource would persist until this resource group is made current and
         * a second call to pop is made.
         * 
         * @brief Adds a resource to the current resource group.
         * @param resource Resource to add to the current group; when the
         *      current group is popped, this resource will be destroyed.
         */
        void attach(void* resource);
    };
}