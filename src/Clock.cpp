/***************************************************************************
 *   Copyright (C) 2019 by Stefan Kebekus                                  *
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

#include "Clock.h"

#include <QTimer>


Clock::Clock(QObject *parent) : QObject(parent)
{
    // We need to update the time regularly. I do not use a simple timer here that emits "timeChanged" once per minute, because I
    // want the signal to be emitted right after the full minute. So, I use a timer that once a minute set a single-shot time
    // that is set to fire up 500ms after the full minute. This design will also work reliably if "timer" get out of synce,
    // for instance because the app was sleeping for a while.
    auto timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Clock::setSingleShotTimer);
    timer->setInterval(60*1000);
    timer->start();

    // Start the single shot timer once manually
    setSingleShotTimer();
}


QString Clock::describeTimeDifference(QDateTime pointInTime)
{
    auto minutes = qRound(QDateTime::currentDateTime().secsTo(pointInTime)/60.0);

    bool past = minutes < 0;
    minutes = qAbs(minutes);

    if (minutes == 0)
        return tr("just now");

    auto hours = minutes/60;
    minutes = minutes%60;

    QString result = "";
    if (hours != 0)
        result += tr("%n hour(s)", "", hours);

    if ((hours != 0) && (minutes != 0))
        result += tr(" and ");
    else
        result += " ";

    if (minutes != 0)
        result += tr("%n minute(s)", "", minutes);

    if (past)
        result = tr("%1 ago").arg(result);
    else
        result = tr("in %1").arg(result);

    return result.simplified();
}


void Clock::setSingleShotTimer()
{
    QTime current = QTime::currentTime();
    int msecsToNextMinute = 60*1000 - (current.msecsSinceStartOfDay() % (60*1000));
    QTimer::singleShot(msecsToNextMinute+500, this, &Clock::timeChanged);
}


QString Clock::time() const
{
    return QDateTime::currentDateTime().toUTC().toString("H:mm");
}