/**
 * @file MachineFactory2.cpp
 * @author trang
 */
#include "pch.h"
#include "MachineFactory2.h"
#include "Machine.h"
#include "Body.h"
#include "Goal.h"
#include "HamsterAndConveyorFactory.h"
#include "Hamster.h"
#include "Conveyor.h"
#include "Pulley.h"
/// The images directory in resources
const std::wstring ImagesDirectory = L"/images";

/**
 * Constructor
 * @param resourcesDir Directory containing the machine resources
 */
MachineFactory2::MachineFactory2(std::wstring resourcesDir)
    :mResourcesDir(resourcesDir)
{
    mImagesDir = resourcesDir + ImagesDirectory;
}

/**
 * Create a machine
 *
 * @return Pointer to newly created machine
 */
std::shared_ptr<Machine> MachineFactory2::Create()
{
    auto machine = std::make_shared<Machine>(2);

    // Notice: All dimensions are in centimeters and assume
    // the Y axis is positive in the up direction.

    const double FloorWidth = 600;
    const double FloorHeight = 15;

    //
    // The floor
    //
    // The values are chosen so the top of the floor
    // is at Y=0
    //
    auto floor = std::make_shared<Body>();
    floor->Rectangle(-FloorWidth/2, -FloorHeight, FloorWidth, FloorHeight);
    floor->SetImage(mImagesDir + L"/floor.png");
    machine->AddComponent(floor);

//    HamsterAndConveyorFactory hamsterAndConveyorFactory(machine, mImagesDir);
//    hamsterAndConveyorFactory.Create(wxPoint2DDouble(240, 0), wxPoint2DDouble(100, 90));
//    hamsterAndConveyorFactory.AddBall(40);
//    auto hamster1 = hamsterAndConveyorFactory.GetHamster();
//    auto conveyor1 = hamsterAndConveyorFactory.GetConveyor();
//    hamster1->SetSpeed(-1);

    auto hamster = std::make_shared<Hamster>(mImagesDir);

    hamster->SetPosition(240,0);
    machine->AddComponent(hamster);
    hamster->SetInitiallyRunning(true);
    hamster->SetSpeed(-1);
    auto hamsterShaft = hamster->GetShaftPosition();

    auto conveyor = std::make_shared<Conveyor>(mImagesDir);
    auto conveyor3 = std::make_shared<Conveyor>(mImagesDir);

    conveyor3->SetPosition(240,50);
    auto conveyor3Shaft = conveyor3->GetShaftPosition();
    machine->AddComponent(conveyor3);
    conveyor->SetPosition(50,200);
    machine->AddComponent(conveyor);
    auto conveyorShaft = conveyor->GetShaftPosition();
    auto pulley5 = std::make_shared<Pulley>(1);
    pulley5->SetImage(mImagesDir + L"/pulley3.png");
    pulley5->SetPosition(conveyor3Shaft.m_x,conveyor3Shaft.m_y);

    // The pulley driven by the hamster
    auto pulley1 = std::make_shared<Pulley>(10);
    pulley1->SetImage(mImagesDir + L"/pulley3.png");
    pulley1->SetPosition(hamsterShaft.m_x,hamsterShaft.m_y);
    machine->AddComponent(pulley1);

    auto pulley6 = std::make_shared<Pulley>(10);
    pulley6->SetImage(mImagesDir + L"/pulley3.png");
    pulley6->SetPosition(hamsterShaft.m_x,hamsterShaft.m_y);
    machine->AddComponent(pulley6);
    hamster->GetSource()->AddSink(pulley6);

    hamster->GetSource()->AddSink(pulley1);

    auto pulley2 = std::make_shared<Pulley>(20);
    pulley2->SetImage(mImagesDir + L"/pulley3.png");
    pulley2->SetPosition(conveyorShaft.m_x,conveyorShaft.m_y);
    machine->AddComponent(pulley2);

    pulley1->Drive(pulley2);
    pulley6->Drive(pulley5);
    pulley5->GetSource()->AddSink(conveyor3);
    pulley2->GetSource()->AddSink(conveyor);

    auto basketball1 = std::make_shared<Body>();
    basketball1->Circle(12);
    basketball1->SetImage(mImagesDir + L"/basketball1.png");
    basketball1->SetInitialPosition(90, 225);
    basketball1->SetDynamic();
    basketball1->SetPhysics(1, 0.5, 0.6);
    machine->AddComponent(basketball1);

    auto hamster2 = std::make_shared<Hamster>(mImagesDir);

    hamster2->SetPosition(0,100);
    machine->AddComponent(hamster2);
    hamster2->SetInitiallyRunning(false);
    hamster2->SetSpeed(6.2);
    auto hamsterShaft2 = hamster2->GetShaftPosition();

    auto pulley3 = std::make_shared<Pulley>(20);
    pulley3->SetImage(mImagesDir + L"/pulley3.png");
    pulley3->SetPosition(hamsterShaft2.m_x,hamsterShaft2.m_y);
    machine->AddComponent(pulley3);

    hamster2->GetSource()->AddSink(pulley3);

    auto conveyor2 = std::make_shared<Conveyor>(mImagesDir);
    conveyor2->SetPosition(-100,0);
    machine->AddComponent(conveyor2);
    auto conveyorShaft2 = conveyor2->GetShaftPosition();

    auto pulley4 = std::make_shared<Pulley>(10);
    pulley4->SetImage(mImagesDir + L"/pulley3.png");
    pulley4->SetPosition(conveyorShaft2.m_x,conveyorShaft2.m_y);
    machine->AddComponent(pulley4);

    pulley3->Drive(pulley4);

    pulley4->GetSource()->AddSink(conveyor2);

//    auto basketball2 = std::make_shared<Body>();
//    basketball2->Circle(12);
//    basketball2->SetImage(mImagesDir + L"/basketball1.png");
//    basketball2->SetInitialPosition(-100, 25);
//    basketball2->SetDynamic();
//    basketball2->SetPhysics(1, 0.5, 0.6);
//    machine->AddComponent(basketball2);
    auto wedge1 = std::make_shared<Body>();
    wedge1->AddPoint(-25, 0);
    wedge1->AddPoint(25, 0);
    wedge1->AddPoint(25, 0);
    wedge1->AddPoint(-25, 50);
    wedge1->SetImage(mImagesDir + L"/wedge.png");
    wedge1->SetInitialPosition(200, 50);
    machine->AddComponent(wedge1);

    auto beam2 = std::make_shared<Body>();
    beam2->BottomCenteredRectangle(20, 300);
    beam2->SetImage(mImagesDir + L"/beam.png");
    beam2->SetInitialPosition(300, 0);
    machine->AddComponent(beam2);

    auto beam3 = std::make_shared<Body>();
    beam3->BottomCenteredRectangle(20, 300);
    beam3->SetImage(mImagesDir + L"/beam.png");
    beam3->SetInitialPosition(-300, 0);
    machine->AddComponent(beam3);

    auto wedge2 = std::make_shared<Body>();
    wedge2->AddPoint(25, 0);
    wedge2->AddPoint(-25, 0);
    wedge2->AddPoint(-25, 4.5);
    wedge2->AddPoint(25, 35);
    wedge2->SetImage(mImagesDir + L"/wedge.png");
    wedge2->SetInitialPosition(100, 0);
    machine->AddComponent(wedge2);

//    TopBeamAndRamp(machine);
    auto goal = std::make_shared<Goal>(mImagesDir);
    goal->SetPosition(270, 0);
    machine->AddComponent(goal);

    const double BeamX = -25;


    return machine;
}
void MachineFactory2::TopBeamAndRamp(std::shared_ptr<Machine> machine)
{
    const double BeamX = -25;
    auto beam1 = std::make_shared<Body>();
    beam1->BottomCenteredRectangle(400, 20);
    beam1->SetImage(mImagesDir + L"/beam.png");
    beam1->SetInitialPosition(BeamX, 300);
    machine->AddComponent(beam1);

    auto wedge1 = std::make_shared<Body>();
    wedge1->AddPoint(-25, 0);
    wedge1->AddPoint(25, 0);
    wedge1->AddPoint(25, 4.5);
    wedge1->AddPoint(-25, 25);
    wedge1->SetImage(mImagesDir + L"/wedge.png");
    wedge1->SetInitialPosition(BeamX-175, 320);
    machine->AddComponent(wedge1);

    // Basketball 1
    auto basketball1 = std::make_shared<Body>();
    basketball1->Circle(12);
    basketball1->SetImage(mImagesDir + L"/basketball1.png");
    basketball1->SetInitialPosition(BeamX-186, 353);
    basketball1->SetDynamic();
    basketball1->SetPhysics(1, 0.5, 0.6);
    machine->AddComponent(basketball1);
}