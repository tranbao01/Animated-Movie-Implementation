/**
 * @file Component.h
 * @author trang
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_COMPONENT_H
#define CANADIANEXPERIENCE_MACHINELIB_COMPONENT_H
#include <string>
#include <memory>
#include <b2_math.h>
#include <b2_world.h>
#include <b2_body.h>

#include "ContactListener.h"
class Machine;
class Goal;
/**
 * The Component
 */
class Component
{
private:
    /// The machine using this component
    Machine* mMachine = nullptr;

    /// The component name
    std::wstring mName;


public:
    virtual ~Component() {}

    /** Copy constructor disabled */
    Component(const Component &) = delete;
    /** Assignment operator disabled */
    void operator=(const Component &) = delete;
    /**
     * Constructor
     *
     *
     */
    Component();
//
    /**
     * Draw the component
     * @param graphics
     */
    virtual void Draw(std::shared_ptr<wxGraphicsContext> graphics) = 0;
    /**
     * Update the component through time
     * @param elapsed
     */
    virtual void Update(double elapsed) = 0;
    /**
     * Reset the component
     */
    virtual void Reset() = 0;
    /**
     * Set Machine
     * @param machine
     */
    virtual void SetMachine(Machine *machine);
    /**
     * Get the machine of this component
     * @return
     */
    Machine* GetMachine() {return mMachine;}
    /**
     * Install Physics
     * @param world
     */
    virtual void InstallPhysics(std::shared_ptr<b2World> world) = 0;
    /**
     * Add listener
     * @param listener
     */
    virtual void AddListener(std::shared_ptr<ContactListener> listener) = 0;
    /**
     * Get Body
     * @return
     */
    virtual  b2Body* GetBody() = 0;
};

#endif //CANADIANEXPERIENCE_MACHINELIB_COMPONENT_H
