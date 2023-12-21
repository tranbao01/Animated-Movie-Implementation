/**
 * @file Pulley.cpp
 * @author trang
 */
#include "pch.h"
#include "Pulley.h"
#include <cmath>
void Pulley::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{

    if (mDrawbelt == true)
    {
        wxPen pen1 = wxPen(*wxBLACK,2);
        graphics->SetPen(pen1);

        graphics->StrokeLine(mStartPoint1.m_x,mStartPoint1.m_y,mEndPoint1.m_x,mEndPoint1.m_y);
        graphics->StrokeLine(mStartPoint2.m_x,mStartPoint2.m_y,mEndPoint2.m_x,mEndPoint2.m_y);
    }
    graphics->PushState();
    graphics->Translate(mPosition.m_x,mPosition.m_y);
    mPolygon.DrawPolygon(graphics,0,0,mRotation);
    graphics->PopState();


}
void Pulley::Update(double elapsed)
{
    mRotation += mSpeed * elapsed;
}
void Pulley::Reset()
{
    mSpeed = 0;
}
void Pulley::SetMachine(Machine *machine)
{
    Component::SetMachine(machine);
}
void Pulley::InstallPhysics(std::shared_ptr<b2World> world)
{

}
void Pulley::AddListener(std::shared_ptr<ContactListener> listener)
{

}
b2Body *Pulley::GetBody()
{
    return nullptr;
}
void Pulley::SetPosition(double x, double y)
{
    mPosition = wxPoint2DDouble(x,y);
}
Pulley::Pulley(double radius)
{
    mRadius = radius;
    mPolygon.CenteredSquare(mRadius * 2 );
}
void Pulley::SetImage(std::wstring filename)
{
    mPolygon.SetImage(filename);
}
void Pulley::RotateSource(double rotation, double speed)
{
    mSource.RotateSource(rotation,mSpeed);
}
void Pulley::Rotate(double rotation, double speed)
{
    if (mSetSpeedFlag == false)
    {
        mSpeed = speed;
        mPulley->SetSpeed(mSpeed *  GetRadius() / mPulley->GetRadius());
    }

    RotateSource(rotation,mSpeed);
}

void Pulley::AddSink(std::shared_ptr<IRotationSink> rs)
{
    mSource.AddSink(rs);
}
void Pulley::Drive(std::shared_ptr<Pulley> p)
{

    mDrawbelt = true;
    mPulley = p;

    auto d = p->GetCenter() - GetCenter();
    auto a = mRadius*d/d.GetVectorLength();
    auto b = wxPoint2DDouble(-a.m_y,a.m_x);
    auto b2 = wxPoint2DDouble(a.m_y,-a.m_x);
    auto sintheta = (p->GetCenter().m_y - GetCenter().m_y)/d.GetVectorLength();
    auto costheta = (p->GetCenter().m_x - GetCenter().m_x)/d.GetVectorLength();
    auto sinphi = (p->GetRadius()-GetRadius())/d.GetVectorLength();
    auto cosphi = sqrt(1-sinphi*sinphi);
    auto cosb = costheta*sinphi - sintheta*cosphi;
    auto sinb = sintheta*sinphi + costheta*cosphi;
    auto cosb2 = sintheta*cosphi - costheta*sinphi;
    auto sinb2 = -costheta*cosphi - sintheta*sinphi;
    mStartPoint1 = GetCenter() + wxPoint2DDouble(mRadius*cosb,mRadius*sinb);
    mEndPoint1 = p->GetCenter() +wxPoint2DDouble(p->GetRadius()*cosb,p->GetRadius()*sinb);
//    mStartPoint1 = GetCenter()+b;
//    mEndPoint1 = p->GetCenter() +b;
//    mStartPoint2 = GetCenter() +b2;
//    mEndPoint2 = p->GetCenter() +b2;
    mStartPoint2 = GetCenter() + wxPoint2DDouble(mRadius*cosb2,mRadius*sinb2);
    mEndPoint2 = p->GetCenter() +wxPoint2DDouble(p->GetRadius()*cosb2,p->GetRadius()*sinb2);
//    p->Rotate(mRotation,mSpeed);
    mSource.AddSink(mPulley);


}
void Pulley::SetSpeed(double speed)
{
    mSetSpeedFlag = true;
    mSpeed = speed;
}
