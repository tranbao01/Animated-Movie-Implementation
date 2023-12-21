/**
 * @file MachineSystem.cpp
 * @author trang
 */
#include "pch.h"
#include "MachineSystem.h"
#include "Machine.h"
#include "MachineFactory1.h"
#include "MachineFactory2.h"
MachineSystem::MachineSystem(std::wstring resourcesDir)
{
    mResourcesDir = resourcesDir;
//    auto factory1 = MachineFactory1(mResourcesDir);
//    auto factory2 = MachineFactory2(mResourcesDir);
//
//    machine1 =
//    mMachine = machine;
    SetMachineNumber(2);

}

void MachineSystem::DrawMachine(std::shared_ptr<wxGraphicsContext> graphics)
{
    mMachine->Draw(graphics);
}
/**
* Set the position for the root of the machine
* @param location The x,y location to place the machine
*/
void MachineSystem::SetLocation(wxPoint location)
{
    mMachine->SetLocation(location);
}
/**
 * Get the location of hte machine
 * @return Location x,y in pixels as a point
 */
wxPoint MachineSystem::GetLocation()
{
    return mMachine->GetLocation();
}

/**
* Set the current machine animation frame
* @param frame Frame number
*/
void MachineSystem::SetMachineFrame(int frame)
{
    mMachine->SetMachineFrame(frame);
    if(frame < mFrame)
    {
        mFrame = 0;
        mMachine->Reset();
    }
    for( ; mFrame < frame;  mFrame++)
    {
        mMachine->Update(1.0 / mFrameRate);
    }
}

/**
 * Set the expected frame rate in frames per second
 * @param rate Frame rate in frames per second
 */
void MachineSystem::SetFrameRate( double rate)
{
  mFrameRate = rate;
}

/**
* Set the machine number
* @param machine An integer number. Each number makes a different machine
*/
void MachineSystem::SetMachineNumber(int machine)
{
    mMachineNumber = machine;
    if (mMachineNumber == 1)
    {
        auto factory1 = MachineFactory1(mResourcesDir);
        mMachine = factory1.Create();

    }
    if (mMachineNumber == 2)
    {
        auto factory2 = MachineFactory2(mResourcesDir);
        mMachine =  factory2.Create();

    }
    mMachine->Reset();
}

/**
 * Get the current machine number
 * @return Machine number integer
 */
int MachineSystem::GetMachineNumber()
{
    return mMachine->GetMachine();
}

/**
 * Get the current machine time.
 * @return Machine time in seconds
 */
double MachineSystem::GetMachineTime()
{
    return mFrame/mFrameRate;
}
void MachineSystem::SetFlag(int flag)
{
    mMachine->SetFlag(flag);
}
