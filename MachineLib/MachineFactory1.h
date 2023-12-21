/**
 * @file MachineFactory1.h
 * @author trang
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_MACHINEFACTORY1_H
#define CANADIANEXPERIENCE_MACHINELIB_MACHINEFACTORY1_H
#include "Body.h"
class Machine;

/**
 * Factory that creates just the parts of the machine
 * necessary for the checkpoint.
 */
class MachineFactory1
{
private:
    /// Path to the resources directory
    std::wstring mResourcesDir;

    /// Path to the images directory
    std::wstring mImagesDir;
    /// The possible domino colors
    enum class DominoColor { Black, Red, Green, Blue };

    /// Height of a Domino
    const double DominoHeight = 25;

    /// Width of a Domino
    const double DominoWidth = 5;


public:
    MachineFactory1(std::wstring resourcesDir);

    std::shared_ptr<Machine> Create();
    /**
     * Top beam and ramp
     * @param machine
     */
    void TopBeamAndRamp(std::shared_ptr<Machine> machine);
    /**
     * Create the domino stack
     * @param machine
     * @param position
     */
    void DominoStack(std::shared_ptr<Machine> machine, wxPoint2DDouble position);
    void DominoesOnBeam(std::shared_ptr<Machine> machine, wxPoint2DDouble position);
    std::shared_ptr<Body> Domino(std::shared_ptr<Machine> machine, wxPoint2DDouble position, double rotation, DominoColor color);
    void BasketballGoal(std::shared_ptr<Machine> machine);
    void BeamAndSpinningArm(std::shared_ptr<Machine> machine);
};
#endif //CANADIANEXPERIENCE_MACHINELIB_MACHINEFACTORY1_H
