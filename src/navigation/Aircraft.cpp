/***************************************************************************
 *   Copyright (C) 2019-2021 by Stefan Kebekus                             *
 *   stefan.kebekus@gmail.com                                              *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 3 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include "Aircraft.h"


Navigation::Aircraft::Aircraft(QObject *parent) : QObject(parent) {
    _cruiseSpeed = Units::Speed::fromKN(settings.value("Aircraft/cruiseSpeedInKTS", 0.0).toDouble());
    if ((_cruiseSpeed < minValidTAS) || (_cruiseSpeed > maxValidTAS)) {
        _cruiseSpeed = Units::Speed();
    }

    _descentSpeed = Units::Speed::fromKN(settings.value("Aircraft/descentSpeedInKTS", 0.0).toDouble());
    if ((_descentSpeed < minValidTAS) || (_descentSpeed > maxValidTAS)) {
        _descentSpeed = Units::Speed();
    }

    _fuelConsumption = Units::VolumeFlow::fromLPH(settings.value("Aircraft/fuelConsumptionInLPH", 0.0).toDouble());
    if ((_fuelConsumption < minValidFuelConsuption) || (_fuelConsumption > maxValidFuelConsuption)) {
        _fuelConsumption = Units::VolumeFlow();
    }
}


void Navigation::Aircraft::setCruiseSpeed(Units::Speed newSpeed) {

    if ((newSpeed < minValidTAS) || (newSpeed > maxValidTAS)) {
        newSpeed = Units::Speed();
    }
    if (newSpeed == _cruiseSpeed) {
        return;
    }

    _cruiseSpeed = newSpeed;
    emit cruiseSpeedChanged();

}


void Navigation::Aircraft::setDescentSpeed(Units::Speed newSpeed) {

    if ((newSpeed < minValidTAS) || (newSpeed > maxValidTAS)) {
        newSpeed = Units::Speed();
    }
    if (newSpeed == _descentSpeed) {
        return;
    }

    _descentSpeed = newSpeed;
    emit descentSpeedChanged();
}


void Navigation::Aircraft::setFuelConsumption(Units::VolumeFlow newFuelConsumption) {
    if ((newFuelConsumption < minValidFuelConsuption) || (newFuelConsumption > maxValidFuelConsuption)) {
        newFuelConsumption = Units::VolumeFlow();
    }

    if (!qFuzzyCompare(newFuelConsumption.toLPH(), _fuelConsumption.toLPH())) {
        _fuelConsumption = newFuelConsumption;
        emit fuelConsumptionChanged();
    }
}


void Navigation::Aircraft::setFuelConsumptionUnit(FuelConsumptionUnit newUnit)
{
    if (newUnit == _fuelConsumptionUnit) {
        return;
    }

    _fuelConsumptionUnit = newUnit;
    emit fuelConsumptionUnitChanged();
}


void Navigation::Aircraft::setHorizontalDistanceUnit(HorizontalDistanceUnit newUnit)
{
    if (newUnit == _horizontalDistanceUnit) {
        return;
    }

    _horizontalDistanceUnit = newUnit;
    emit horizontalDistanceUnitChanged();
}


void Navigation::Aircraft::setMinimumSpeed(Units::Speed newSpeed) {

    if ((newSpeed < minValidTAS) || (newSpeed > maxValidTAS)) {
        newSpeed = Units::Speed();
    }
    if (newSpeed == _minimumSpeed) {
        return;
    }

    _minimumSpeed = newSpeed;
    emit minimumSpeedChanged();
}


void Navigation::Aircraft::setName(const QString& newName) {

    if (newName == _name) {
        return;
    }

    _name = newName;
    emit nameChanged();
}


void Navigation::Aircraft::setVerticalDistanceUnit(VerticalDistanceUnit newUnit)
{
    if (newUnit == _verticalDistanceUnit) {
        return;
    }

    _verticalDistanceUnit = newUnit;
    emit verticalDistanceUnitChanged();
}

