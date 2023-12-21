/**
 * @file IRotationSource.h
 * @author trang
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_IROTATIONSOURCE_H
#define CANADIANEXPERIENCE_MACHINELIB_IROTATIONSOURCE_H


#include "IRotationSink.h"
#include <memory>
/**
 * IRotation Source
 */
class IRotationSource
{
public:
    /**
     * Add sink to the rotation sink list
     * @param rs
     */
    virtual void AddSink(std::shared_ptr<IRotationSink> rs) = 0;
    /**
     * Rotate the source
     * @param rotation
     * @param speed
     */
    virtual void RotateSource(double rotation, double speed) = 0;
};
#endif //CANADIANEXPERIENCE_MACHINELIB_IROTATIONSOURCE_H