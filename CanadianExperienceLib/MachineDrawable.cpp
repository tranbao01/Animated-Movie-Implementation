/**
 * @file MachineDrawable.cpp
 * @author trang
 */
#include "pch.h"
#include "MachineDrawable.h"
#include "Picture.h"
#include <machine-api.h>
void MachineDrawable::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    double scale = 0.75f;

    graphics->PushState();
    graphics->Translate(mPlacedPosition.x, mPlacedPosition.y);
    graphics->Scale(scale, scale);
    mMachineSystem->SetLocation(wxPoint(0,0));
    mMachineSystem->DrawMachine(graphics);
    graphics->PopState();

}
void MachineDrawable::SetLocation(wxPoint point)
{
    mPlacedPosition = point;
}
void MachineDrawable::SetActor(Actor *actor)
{

}
bool MachineDrawable::HitTest(wxPoint pos)
{
    return false;
}
void MachineDrawable::SetTimeline(Timeline *timeline)
{

}
void MachineDrawable::SetKeyframe()
{
    Drawable::SetKeyframe();
}
void MachineDrawable::GetKeyframe()
{
    Drawable::GetKeyframe();
}

MachineDrawable::MachineDrawable(const std::wstring &name, const std::wstring &resourcesdir) :
    Drawable(name)
{
    mResourcesDir = resourcesdir;
    MachineSystemFactory factory(resourcesdir);
    std::shared_ptr<IMachineSystem> machine = factory.CreateMachineSystem();

    mMachineSystem = machine;
//    MachineDialog dlg(this, mMachineSystem);
//    if (dlg.ShowModal() == wxID_OK)
//    {
//        // A new machine has been set
//    }
}
void MachineDrawable::SetPicture(Picture *picture)
{
    mPicture = picture;

    // Add the animation channel to the timeline
//    mPicture->GetTimeline()->AddChannel(&mChannel);
//
//    // Set the timeline for all drawables. This links the channels to
//    // the timeline system.
//    for (auto drawable : mDrawablesInOrder)
//    {
//        drawable->SetTimeline(mPicture->GetTimeline());
//    }
//    mMachineSystem->SetFrameRate(mPicture->GetTimeline()->GetFrameRate());
//    mMachineSystem->SetMachineFrame(mPicture->GetTimeline()->GetNumFrames());

}
void MachineDrawable::SetFrameRate(double rate)
{
    mMachineSystem->SetFrameRate(rate);
}
void MachineDrawable::SetMachineFrame(int frame)
{
    mMachineSystem->SetMachineFrame(frame);
}
double MachineDrawable::GetTime()
{
    return mMachineSystem->GetMachineTime();
}
void MachineDrawable::SetMachineNumber(int number)
{
    mMachineSystem->SetMachineNumber(number);
}
void MachineDrawable::ShowDialogBox(wxWindow* parent)
{
    MachineDialog dlg(parent, mMachineSystem);
    if (dlg.ShowModal() == wxID_OK)
    {
        mPicture->UpdateObservers();
    }
};

