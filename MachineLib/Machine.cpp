/**
 * @file Machine.cpp
 * @author trang
 */

#include "pch.h"

#include <sstream>
#include "Machine.h"
#include "Component.h"
#include "DebugDraw.h"
/// Gravity in meters per second per second
const float Gravity = -9.8f;

/// Number of velocity update iterations per step
const int VelocityIterations = 6;

/// Number of position update iterations per step
const int PositionIterations = 2;




/**
 * Constructor
 */
Machine::Machine(int machine)
{
    mMachine = machine;
    mWorld = std::make_shared<b2World>(b2Vec2(0.0f, Gravity));
}

void Machine::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    if (mFlag == 1 || mFlag == 3)
    {
        graphics->PushState();
        graphics->Translate(mX, mY);
        graphics->Scale(mPixelsPerCentimeter, -mPixelsPerCentimeter);

        for(auto component : mComponents)
        {
            component->Draw(graphics);
        }
    }
    if (mFlag == 2 || mFlag == 3)
    {
        DebugDraw debugDraw(graphics);
        debugDraw.SetLineWidth(1);
        debugDraw.SetFlags(b2Draw::e_shapeBit | b2Draw::e_centerOfMassBit);
        mWorld->SetDebugDraw(&debugDraw);
        mWorld->DebugDraw();
        graphics->PopState();
    }

}

void Machine::AddComponent(std::shared_ptr<Component> component)
{
    mComponents.push_back(component);
    component->SetMachine(this);
}
void Machine::SetMachineFrame(int frame)
{
    mFrame = frame;

}
void Machine::Update(double elapsed)
{
    for (auto component : mComponents)
    {
        component->Update(elapsed);
    }
    mWorld->Step(elapsed, VelocityIterations, PositionIterations);
}
void Machine::Reset()
{
    mWorld = std::make_shared<b2World>(b2Vec2(0.0f, Gravity));
    mContactListener = std::make_shared<ContactListener>();
    mWorld->SetContactListener(mContactListener.get());
    for (auto component : mComponents)
    {
        component->InstallPhysics(mWorld);
        component->AddListener(mContactListener);
        component->Reset();
    }


}
void Machine::SetFlag(int flag)
{
    mFlag = flag;
}
