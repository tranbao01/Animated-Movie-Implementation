/**
 * @file MachineSystem.h
 * @author trang
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_MACHINESYSTEM_H
#define CANADIANEXPERIENCE_MACHINELIB_MACHINESYSTEM_H
#include "IMachineSystem.h"
class Machine;
/**
 * The machine system
 */
class MachineSystem : public IMachineSystem
{
private:
    /// The location of the machine
    wxPoint mLocation = wxPoint(0,0);
    /// The frame
    int mFrame = 0;
    /// Framerate
    double mFrameRate = 30;
    /// The flag
    int mFlag = 0;
    /// Current time
    double mCurrentTime = 0;
    /// The number
    int mNumber = 0;
    /// The machine
    std::shared_ptr<Machine> mMachine;
    /// The resources directory
    std::wstring mResourcesDir;
    /// Machine number
    int mMachineNumber = 1;
public:
    /**
     * Constructor
     * @param resourcesDir
     */
    MachineSystem(std::wstring resourcesDir) ;

    /// Copy constructor (disabled)
    MachineSystem(const MachineSystem &) = delete;

    /// Assignment operator
    void operator=(const MachineSystem &) = delete;
    /**
     * Location Setter
     *
     */
    virtual void SetLocation(wxPoint location) override;
    /**
     * Location getter
     * @return
     */
    wxPoint GetLocation() override;
    /**
     * Draw the machine
     * @param graphics
     */
    virtual void DrawMachine(std::shared_ptr<wxGraphicsContext> graphics) ;
    /**
     * Frame setter
     *
     */
    virtual void SetMachineFrame(int frame) ;
    /**
     * Time getter
     * @return
     */
    virtual double GetMachineTime() ;
    /**
     * Framerate setter
     *
     */
    virtual void SetFrameRate(double rate) ;
    /**
     * Flag setter
     * @param flag
     */
    void SetFlag(int flag) ;

    virtual void SetMachineNumber(int machine);
    /**
     * Get the number
     * @return
     */
    virtual int GetMachineNumber();





};

#endif //CANADIANEXPERIENCE_MACHINELIB_MACHINESYSTEM_H
