/**
 * @file Body.h
 * @author trang
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_BODY_H
#define CANADIANEXPERIENCE_MACHINELIB_BODY_H
#include "Component.h"
#include "PhysicsPolygon.h"
#include "IRotationSink.h"
#include "RotationSink.h"

class RotationSink;
class PhysicsPolygon;
class Polygon;
/**
 * The body
 */
class Body:public Component,public IRotationSink,public b2ContactListener
{
private:
    /// Default Circle steps
    static const int DefaultCircleSteps = 32;
    /// Body
    cse335::PhysicsPolygon mPhysicsPolygon;
    /// Initial Position
    wxPoint mInitialPosition = wxPoint(0,0);
    /// Polygon
    cse335::Polygon mPolygon;

    /// The rotation sink for this component
    RotationSink mSink;

public:
    /**
     * Constructor
     *
     */
    Body()
    {
        mSink.SetComponent(this);
    }

    /** Copy constructor disabled */
    Body(const Body &) = delete;
    /** Assignment operator disabled */
    void operator=(const Body &) = delete;
    /**
     * Set initial position
     * @param x
     * @param y
     */
    void SetInitialPosition(double x, double y) {mPhysicsPolygon.SetInitialPosition(x,y); }
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
     * Circle
     * @param radius
     * @param steps
     */
    void Circle(double radius, int steps=DefaultCircleSteps){
        mPhysicsPolygon.Circle(radius, steps);
    }
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
     * Set The machine
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
     * Bottom Centered Rectangle
     * @param width
     * @param height
     */
    void BottomCenteredRectangle(double width = 0, double height = 0);
    /**
     * Add Point
     * @param x
     * @param y
     */
    void AddPoint(double x, double y);
    /**
     * Add Listener
     * @param listener
     */
    void AddListener(std::shared_ptr<ContactListener> listener) override;
    /**
     * Set Initial Position
     * @param r
     */
    void SetInitialRotation(double r) {  mPhysicsPolygon.SetInitialRotation(r); }
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



};

#endif //CANADIANEXPERIENCE_MACHINELIB_BODY_H
