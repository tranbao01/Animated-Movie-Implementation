/**
 * @file IRotationSink.h
 * @author trang
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_IROTATIONSINK_H
#define CANADIANEXPERIENCE_MACHINELIB_IROTATIONSINK_H

/**
 * IRotation Sink
 */
class IRotationSink
{
public:
   /**
    * Rotate the sink
    * @param rotation
    * @param speed
    */
    virtual void Rotate(double rotation,double speed) = 0;
};
#endif //CANADIANEXPERIENCE_MACHINELIB_IROTATIONSINK_H