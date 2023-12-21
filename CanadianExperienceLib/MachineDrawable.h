/**
 * @file MachineDrawable.h
 * @author trang
 *
 *
 */

#ifndef CANADIANEXPERIENCE_CANADIANEXPERIENCELIB_MACHINEDRAWABLE_H
#define CANADIANEXPERIENCE_CANADIANEXPERIENCELIB_MACHINEDRAWABLE_H
#include "Drawable.h"
#include <machine-api.h>
class Picture;
/**
 * Machine Drawable
 */
class MachineDrawable:public Drawable
{
private:
    /// The IMachineSystem
    std::shared_ptr<IMachineSystem> mMachineSystem = nullptr;
    /// The position of the machine
    wxPoint mPlacedPosition = wxPoint(0,0);
    /// The start time
    double mStartTime = 0;
    /// The resources directory
    std::wstring mResourcesDir;
    /// The picture this actor is associated with
    Picture *mPicture = nullptr;


public:
    /**
     * Constructor
     * @param name
     * @param resourcesdir
     */
    MachineDrawable(const std::wstring &name, const std::wstring &resourcesdir);
    virtual ~MachineDrawable() {}



    /** Copy constructor disabled */
    MachineDrawable(const MachineDrawable &) = delete;
    /**
     * Set the startime
     * @param time
     */
    void SetStartTime(double time) {mStartTime = time;}
    /**
     * Draw the machine
     * @param graphics
     */
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
    /**
     * Set the machine
     * @param machine
     */
    void SetMachine(std::shared_ptr<IMachineSystem> machine);
    /**
     * Set the actor
     * @param actor
     */
    void SetActor(Actor *actor) override;
    /**
     * Hit testing
     * @param pos
     * @return
     */
    bool HitTest(wxPoint pos) override;
    /**
     * Is movable or not
     * @return
     */
    bool IsMovable() override { return false; }
    /**
     * Set the timeline
     * @param timeline
     */
    void SetTimeline(Timeline *timeline) override;
    /**
     * Set keyframe
     */
    void SetKeyframe() override;
    /**
     * Get the keyframe
     */
    void GetKeyframe()override;
    /**
     * Set the picture
     * @param picture
     */
    void SetPicture(Picture *picture);
    /**
     * Set the machine frame rate
     * @param rate
     */
    void SetFrameRate(double rate);
    /**
     * Set the machine frame
     * @param frame
     */
    void SetMachineFrame(int frame);
    /**
     * Get the time
     * @return
     */
    double GetTime();
    /**
     * Set the machine number
     * @param number
     */
    void SetMachineNumber(int number);
    /**
     * Set the location
     * @param point
     */
    void SetLocation(wxPoint point);
    /**
     * Get the starttime
     * @return
     */
    double GetStartTime() {return mStartTime;}
    /**
     * Show the dialog box
     * @param parent
     */
    void ShowDialogBox(wxWindow* parent);

};

#endif //CANADIANEXPERIENCE_CANADIANEXPERIENCELIB_MACHINEDRAWABLE_H
