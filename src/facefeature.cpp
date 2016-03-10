/*
 * Copyright (C) 2016 Luiz Carlos Vieira (http://www.luiz.vieira.nom.br)
 *
 * This file is part of FLAT.
 *
 * FLAT is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * FLAT is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "facefeature.h"

#include <QApplication>

// +-----------------------------------------------------------
ft::FaceFeature::FaceFeature():
	cv::Point2f()
{
	setID(-1);
}

// +-----------------------------------------------------------
ft::FaceFeature::FaceFeature(int iID, float x, float y):
	cv::Point2f(x, y)
{
	setID(iID);
}

// +-----------------------------------------------------------
int ft::FaceFeature::getID() const
{
	return m_iID;
}

// +-----------------------------------------------------------
void ft::FaceFeature::setID(int iID)
{
	m_iID = iID;
}

// +-----------------------------------------------------------
bool ft::FaceFeature::loadFromXML(const QDomElement &oElement, QString &sMsgError)
{
// Check the element name
	if(oElement.tagName() != "Feature")
	{
		sMsgError = QString(QApplication::translate("FaceFeature", "invalid node name [%1] - expected node '%2'").arg(oElement.tagName(), "Feature"));
		return false;
	}

	QString sID = oElement.attribute("id");
	if(sID == "")
	{
		sMsgError = QString(QApplication::translate("FaceFeature", "the attribute '%1' does not exist or it contains an invalid value").arg("id"));
		return false;
	}

	QString sValueX = oElement.attribute("x");
	if(sValueX == "")
	{
		sMsgError = QString(QApplication::translate("FaceFeature", "the attribute '%1' does not exist or it contains an invalid value").arg("x"));
		return false;
	}

	QString sValueY = oElement.attribute("y");
	if(sValueY == "")
	{
		sMsgError = QString(QApplication::translate("FaceFeature", "the attribute '%1' does not exist or it contains an invalid value").arg("y"));
		return false;
	}

	m_iID = sID.toInt();
	x = sValueX.toFloat();
	y = sValueY.toFloat();
	
	return true;
}

// +-----------------------------------------------------------
void ft::FaceFeature::saveToXML(QDomElement &oParent) const
{
	QDomElement oFeature = oParent.ownerDocument().createElement("Feature");
	oParent.appendChild(oFeature);

	oFeature.setAttribute("id", m_iID);
	oFeature.setAttribute("x", x);
	oFeature.setAttribute("y", y);
}
