/**
 * @file Conveyor.cpp
 * @author trang
 */
#include "pch.h"
#include "Conveyor.h"
#include "RotationSink.h"
#include "ContactListener.h"
#include <b2_world_callbacks.h>
#include <b2_contact.h>

/// The offset from the bottom center of the conveyor
/// to the center of the drive shaft.  48
const auto ConveyorShaftOffset = wxPoint2DDouble(48, 4);

/// The size of the conveyor in cm
const auto ConveyorSize = wxSize(125, 14);

/// The conveyor image to use
const std::wstring ConveyorImageName = L"/conveyor.png";
void Conveyor::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    mPhysicsPolygon.Draw(graphics);
}
void Conveyor::InstallPhysics(std::shared_ptr<b2World> world)
{
    mPhysicsPolygon.InstallPhysics(world);
}
b2Body *Conveyor::GetBody()
{
    return nullptr;
}
void Conveyor::SetMachine(Machine *machine)
{
    Component::SetMachine(machine);
}
void Conveyor::Update(double elapsed)
{
    auto contact1 = mPhysicsPolygon.GetBody()->GetContactList();
    while(contact1 != nullptr)
    {
        if(contact1->contact->IsTouching())
        {
            contact1->other->SetLinearVelocity(b2Vec2(mSpeed, 0));
        }

        contact1 = contact1->next;
    }
}
void Conveyor::Reset()
{
    mSpeed = 0;
}
void Conveyor::AddListener(std::shared_ptr<ContactListener> listener)
{
    listener->Add(mPhysicsPolygon.GetBody(),this);
}
void Conveyor::AddPoint(double x, double y)
{

}

void Conveyor::BeginContact(b2Contact *contact)
{


}
void Conveyor::PreSolve(b2Contact *contact, const b2Manifold *oldManifold)
{
    contact->SetTangentSpeed(mSpeed);
}
Conveyor::Conveyor(std::wstring filename)
{
    mPhysicsPolygon.BottomCenteredRectangle(ConveyorSize);
    mSink.SetComponent(this);
    mPhysicsPolygon.SetImage(filename+ ConveyorImageName);
}
void Conveyor::Rotate(double rotation, double speed)
{
    mSpeed = -speed;
}
void Conveyor::SetPosition(double x, double y)
{
    mPhysicsPolygon.SetInitialPosition(x,y);
}
wxPoint2DDouble Conveyor::GetShaftPosition()
{
    return wxPoint2DDouble(mPhysicsPolygon.GetPosition().m_x+ConveyorShaftOffset.m_x,mPhysicsPolygon.GetPosition().m_y+ConveyorShaftOffset.m_y);
}
