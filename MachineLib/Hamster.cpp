/**
 * @file Hamster.cpp
 * @author trang
 */
#include "pch.h"
#include "Hamster.h"
#include "Polygon.h"
#include "RotationSource.h"
/// The center point for drawing the wheel
/// relative to the bottom center of the cage
const auto WheelCenter = wxPoint2DDouble(-12, 24);

/// The size of the hamster cage in centimeters
const auto HamsterCageSize = wxSize(75, 50);

/// Size of the hamster wheel (diameter) in centimeters
const double HamsterWheelSize = 45;

/// Size of the hamster wheel (square) in centimeters
const double HamsterSize = 45;

/// How fast the hamster runs. This is now many cycles of
/// the 3 images we make per second as images 1, 2, 3, 2, ...
const double HamsterSpeed = 4.0;

/// The offset from the bottom center of the hamster cage
/// to the center of the output shaft.
const auto HamsterShaftOffset = wxPoint2DDouble(25, 40);

/// The image for the hamster cage
const std::wstring HamsterCageImage = L"/hamster-cage.png";

/// The image for the hamster wheel
const std::wstring HamsterWheelImage = L"/hamster-wheel.png";

/// The hamster images. Image 0 is sleeping, 1-3 are
/// the running hamster animation images.
const std::wstring HamsterImages[4] =
    {L"/hamster-sleep.png", L"/hamster-run-1.png",
        L"/hamster-run-2.png", L"/hamster-run-3.png"};
/// List of hamster images running
const std::wstring HamsterImagesRun[4] =
{ L"/hamster-run-1.png",
L"/hamster-run-2.png", L"/hamster-run-3.png",L"/hamster-run-2.png",};

void Hamster::SetInitialPosition(double x, double y)
{
    mCage.SetInitialPosition(x,y);
}
void Hamster::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    mCage.Draw(graphics);
    graphics->PushState();
    graphics->Translate(mPosition.m_x+WheelCenter.m_x , mPosition.m_y+WheelCenter.m_y );
    mWheel.DrawPolygon(graphics,0,0,mRotation);
    if(mSpeed < 0)
    {
        graphics->Scale(-1, 1);
    }
    if ( mRun == false)
    {
        mHamster0.DrawPolygon(graphics, 0, 0, 0);
    }
    else
    {

        if(mHamsterIndex == 0)
        {
            mHamster1.DrawPolygon(graphics, 0, 0, 0);
        }
        if(mHamsterIndex == 1)
        {
            mHamster2.DrawPolygon(graphics, 0, 0, 0);
        }
        if(mHamsterIndex == 2)
        {
            mHamster3.DrawPolygon(graphics, 0, 0, 0);
        }
        if(mHamsterIndex == 3)
        {
            mHamster2.DrawPolygon(graphics, 0, 0, 0);
        }
    }
    graphics->PopState();

}
Hamster::Hamster(std::wstring imagesDir)
{

    mHamster0.CenteredSquare(HamsterSize);
    mHamster1.CenteredSquare(HamsterSize);
    mHamster2.CenteredSquare(HamsterSize);
    mHamster3.CenteredSquare(HamsterSize);
    mWheel.CenteredSquare(HamsterWheelSize);
    mCage.SetImage(imagesDir + HamsterCageImage);
    mCage.BottomCenteredRectangle(HamsterCageSize);
    mHamster0.SetImage(imagesDir+HamsterImages[0]);
    mHamster1.SetImage(imagesDir+HamsterImages[1]);
    mHamster2.SetImage(imagesDir+HamsterImages[2]);
    mHamster3.SetImage(imagesDir+HamsterImages[3]);
    mWheel.SetImage(imagesDir+HamsterWheelImage);

}

void Hamster::AddListener(std::shared_ptr<ContactListener> listener)
{
    listener->Add(mCage.GetBody(),this);
}

/**
 * Handle a contact beginning
 *
 */
void Hamster::BeginContact(b2Contact *contact)
{
    mRun = true;
}
void Hamster::SetPosition(double x, double y)
{
    mPosition = wxPoint2DDouble(x,y);
    mCage.SetInitialPosition(x,y);
}
void Hamster::SetInitiallyRunning(bool run)
{
    mIrun = run;
}
void Hamster::InstallPhysics(std::shared_ptr<b2World> world)
{
    mCage.InstallPhysics(world);
}
void Hamster::SetMachine(Machine *machine)
{
    Component::SetMachine(machine);
}
void Hamster::Update(double elapsed)
{
    if (mRun == true)
    {
        mSource.RotateSource(mRotation,-  mSpeed);
        if(mHamsterIndex >= 0)
        {
            if(abs(mRotation) > mX)
            {
                mX += 0.1;
                if(mHamsterIndex == 3)
                {
                    mHamsterIndex = 0;
                }
                else
                {
                    mHamsterIndex += 1;
                }
            }
            mRotation += -mSpeed * elapsed;
        }

    }
}
void Hamster::Reset()
{
    mRun = mIrun;
}
b2Body *Hamster::GetBody()
{
    return nullptr;
}
void Hamster::PreSolve(b2Contact *contact, const b2Manifold *oldManifold)
{
    b2ContactListener::PreSolve(contact, oldManifold);
}
void Hamster::RotateSource(double rotation, double speed)
{
    mSource.RotateSource(mRotation,mSpeed);
}
void Hamster::AddSink(std::shared_ptr<IRotationSink> component)
{
    mSource.AddSink(component);
}
wxPoint2DDouble Hamster::GetShaftPosition()
{
    return (wxPoint2DDouble(mPosition.m_x+HamsterShaftOffset.m_x,mPosition.m_y+HamsterShaftOffset.m_y));
}
