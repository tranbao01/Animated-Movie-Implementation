/**
 * @file MachineSystemFactory.cpp
 *
 * @author Charles Owen
 *
 * You are allowed to change this file.
 */

#include "pch.h"
#include "MachineSystemFactory.h"
#include "MachineSystemStandin.h"
#include "MachineSystem.h"
#include "MachineFactory1.h"
#include "MachineFactory2.h"
#include "Machine.h"


/**
 * Constructor
 * @param resourcesDir Directory to load resources from
 */
MachineSystemFactory::MachineSystemFactory(std::wstring resourcesDir) :
    mResourcesDir(resourcesDir)
{
}


/**
 * Create a machine system object
 *
 * Do not change the return type of this function!
 *
 * @return Object of type IMachineSystem
 */
std::shared_ptr<IMachineSystem> MachineSystemFactory::CreateMachineSystem()
{


//    auto factory1 = MachineFactory1(mResourcesDir);
//    auto factory2 = MachineFactory2(mResourcesDir);
//    auto machine1 = factory1.Create();
//    machine1->Reset();
//    auto machine2 = factory2.Create();
//    machine2->Reset();
    std::shared_ptr<IMachineSystem> machinesystem =  std::make_shared<MachineSystem>(mResourcesDir);
    return machinesystem;
}


