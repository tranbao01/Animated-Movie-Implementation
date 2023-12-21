/**
 * @file MachineFactory2.h
 * @author trang
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_MACHINEFACTORY2_H
#define CANADIANEXPERIENCE_MACHINELIB_MACHINEFACTORY2_H
#include "Body.h"
class Machine;

/**
 * Factory that creates just the parts of the machine
 * necessary for the checkpoint.
 */
class MachineFactory2
{
private:
    /// Path to the resources directory
    std::wstring mResourcesDir;

    /// Path to the images directory
    std::wstring mImagesDir;

public:
    MachineFactory2(std::wstring resourcesDir);

    std::shared_ptr<Machine> Create();
    /**
     * Create the top beam and ramp
     * @param machine
     */
    void TopBeamAndRamp(std::shared_ptr<Machine> machine);
};
#endif //CANADIANEXPERIENCE_MACHINELIB_MACHINEFACTORY1_H
