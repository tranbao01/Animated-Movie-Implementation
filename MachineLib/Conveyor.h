/**
 * @file Conveyor.h
 * @author trang
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_CONVEYOR_H
#define CANADIANEXPERIENCE_MACHINELIB_CONVEYOR_H
#include "Component.h"
#include "Component.h"
#include "PhysicsPolygon.h"
#include "IRotationSink.h"
#include "RotationSink.h"
class RotationSink;
class PhysicsPolygon;
class Polygon;
/**
 * The conveyor
 */
class Conveyor:public Component,public b2ContactListener,public IRotationSink
{
private:
    /// Body
    cse335::PhysicsPolygon mPhysicsPolygon;


    /// The rotation sink for this component
    RotationSink mSink;
    /// The speed
    double mSpeed = 0;

public:
    /**
    * Constructor
    *
    * @param filename
    */
    Conveyor(std::wstring filename);


    /** Copy constructor disabled */
    Conveyor(const Conveyor &) = delete;
    /** Assignment operator disabled */
    void operator=(const Conveyor &) = delete;

    /**
     * Draw the body
     * @param graphics
     */
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
    /**
     * Set Image
     * @param filename
     */
    void SetImage(std::wstring filename){
        mPhysicsPolygon.SetImage(filename);
    };
    /**
     * Get a pointer to the polygon this body uses
     * @return Pointer to the polygon object
     */
    cse335::PhysicsPolygon* GetPolygon() {return &mPhysicsPolygon;}
    /**
     * Rectangle
     * @param x
     * @param y
     * @param width
     * @param height
     */
    void Rectangle(double x, double y, double width, double height) {
        mPhysicsPolygon.Rectangle(x, y, width, height);
    }
    /**
     * Set Position
     * @param x
     * @param y
     */
    void SetPosition(double x,double y);
    /**
     * Get Position
     * @return
     */
    wxPoint2DDouble GetPosition() {return mPhysicsPolygon.GetPosition();}
    /**
     * Set Dynamic
     */
    void SetDynamic() {mPhysicsPolygon.SetDynamic();};
    /**
     * Set Kinematic
     */
    void SetKinematic() {mPhysicsPolygon.SetKinematic();};
    /**
     * Set Physics
     * @param density
     * @param friction
     * @param restitution
     */
    void SetPhysics(double density=1.0, double friction=0.5, double restitution=0.5)
    {
        mPhysicsPolygon.SetPhysics( density, friction, restitution);
    }
    /**
     * Install Physics
     * @param world
     */
    void InstallPhysics(std::shared_ptr<b2World> world) override;
    /**
     * Get Body
     * @return
     */
    b2Body* GetBody() override;
    /**
     * Set Machine
     * @param machine
     */
    void SetMachine(Machine* machine) override;
    /**
     * Update
     * @param elapsed
     */
    void Update(double elapsed) override;
    /**
     * Reset
     */
    void Reset() override;
    /**
     * Add Point
     * @param x
     * @param y
     */
    void AddPoint(double x, double y);
    /**
     * Add listener
     * @param listener
     */
    void AddListener(std::shared_ptr<ContactListener> listener) override;

    /**
     * Rotate
     * @param rotation
     * @param speed
     */
    void Rotate(double rotation,double speed) override;
    /**
     * Get Sink
     * @return
     */
    RotationSink *GetSink() {return &mSink;}
    /**
     * Begin Contact
     * @param contact
     */
    void BeginContact(b2Contact *contact) override;
    /**
     * Pre Solve
     * @param contact
     * @param oldManifold
     */
    void PreSolve(b2Contact *contact, const b2Manifold *oldManifold) override;
    /**
     * Get Shaft Position
     * @return
     */
    wxPoint2DDouble GetShaftPosition();

};

#endif //CANADIANEXPERIENCE_MACHINELIB_CONVEYOR_H
