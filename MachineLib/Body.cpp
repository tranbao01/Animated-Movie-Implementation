/**
 * @file Body.cpp
 * @author trang
 */
#include "pch.h"
#include "Body.h"
#include "RotationSink.h"

void Body::SetMachine(Machine *machine)
{
    Component::SetMachine(machine);
}
void Body::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    graphics->PushState();
    graphics->Translate(mInitialPosition.x,mInitialPosition.y);
    mPhysicsPolygon.Draw(graphics);
    graphics->PopState();
}
void Body::Update(double elapsed)
{

}
void Body::Reset()
{

}
void Body::InstallPhysics(std::shared_ptr<b2World> world)
{
    mPhysicsPolygon.InstallPhysics(world);
}
b2Body *Body::GetBody()
{
    return mPhysicsPolygon.GetBody();
}
void Body::BottomCenteredRectangle(double width, double height)
{
    mPhysicsPolygon.BottomCenteredRectangle(width,height);
}
void Body::AddPoint(double x, double y)
{
    mPhysicsPolygon.AddPoint(x,y);
}
void Body::AddListener(std::shared_ptr<ContactListener> listener)
{

}
void Body::Rotate(double rotation, double speed)
{
    SetKinematic();
    mPhysicsPolygon.SetAngularVelocity(speed);
}
