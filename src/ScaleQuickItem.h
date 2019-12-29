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


#ifndef SCALEQUICKITEM_H
#define SCALEQUICKITEM_H

#include <QtQuick/QQuickPaintedItem>


/*! \brief QML Class implementing a scale for a Map

  This class implements a QML item that draws a scale, to be added to a map.  To
  work, the property pixelPer10km needs to be set, according to the scale of the
  map.  To use this class, export it to QML, add it to your view and make sure
  that the property pixelPer10km get set accordingly.

  The methods of this class are re-entrant, but not thread safe.
*/

class ScaleQuickItem : public QQuickPaintedItem
{
  Q_OBJECT

  /*! \brief Number of pixel that represent a distance of 10km on the map */
  Q_PROPERTY(qreal pixelPer10km READ pixelPer10km WRITE setPixelPer10km NOTIFY pixelPer10kmChanged)

public:
  /*! \brief Standard constructor */
  explicit ScaleQuickItem(QQuickItem *parent = nullptr);

  /*! \brief Getter function for the property with the same name */
  qreal pixelPer10km() const {return _pixelPer10km;}

  /*! \brief Setter function for the property with the same name */
  void setPixelPer10km(qreal _pxp10k);

  /*! \brief Re-implemented from QQuickPaintedItem to implement painting */
  void paint(QPainter *painter) override;

signals:
  /*! \brief Notification signal for property with the same name */
  void pixelPer10kmChanged();

private:
  qreal _pixelPer10km {0.0};
};

#endif // SCALE_H