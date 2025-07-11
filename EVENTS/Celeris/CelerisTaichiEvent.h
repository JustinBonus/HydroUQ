#ifndef CELERIS_TAICHI_EVENT_H
#define CELERIS_TAICHI_EVENT_H

/* *****************************************************************************
Copyright (c) 2016-2017, The Regents of the University of California (Regents).
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

The views and conclusions contained in the software and documentation are those
of the authors and should not be interpreted as representing official policies,
either expressed or implied, of the FreeBSD Project.

REGENTS SPECIFICALLY DISCLAIMS ANY WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
THE SOFTWARE AND ACCOMPANYING DOCUMENTATION, IF ANY, PROVIDED HEREUNDER IS
PROVIDED "AS IS". REGENTS HAS NO OBLIGATION TO PROVIDE MAINTENANCE, SUPPORT,
UPDATES, ENHANCEMENTS, OR MODIFICATIONS.

*************************************************************************** */

// Written: JustinBonus (2024)

#include <SimCenterAppWidget.h>
#include <RandomVariablesContainer.h>
class RandomVariablesContainer;
class SC_DoubleLineEdit;
class SC_IntLineEdit;
class SC_StringLineEdit;
class SC_ComboBox;
class QCheckBox;
class CelerisTaichi;
class CelerisSolver;
class CelerisDomain;
class CelerisTaichiEvent : public SimCenterAppWidget
{
   Q_OBJECT
public:
   CelerisTaichiEvent(RandomVariablesContainer* random_variables, QWidget *parent = 0);
   ~CelerisTaichiEvent();

   bool inputFromJSON(QJsonObject &rvObject);
   bool outputToJSON(QJsonObject &rvObject);
   bool inputFromConfigJSON(QJsonObject &rvObject);  
   bool outputAppDataToJSON(QJsonObject &rvObject);
   bool inputAppDataFromJSON(QJsonObject &rvObject);
   bool copyFiles(QString &dirName);
   bool outputCitation(QJsonObject &jsonObject) override;
   bool supportsLocalRun() override;

signals:
   void runFinished(void);
   void redrawBathymetry(void); /**< Signal to redraw the bathymetry */
public slots:
   void clear(void);

private:
  RandomVariablesContainer* rvInputWidget; /**< Widget for inputting random
						  variables */
   CelerisTaichi  *inputCeleris;
   CelerisSolver  *theCelerisSolver;
   CelerisDomain  *theCelerisDomain;
   
   SC_ComboBox *mode;
   
   SC_DoubleLineEdit *long1Edit; /**< Longitude Lower-Left */
   SC_DoubleLineEdit *lat1Edit;  /**< Latitude Lower-Left */
   SC_DoubleLineEdit *long2Edit; /**< Longitude Upper-Right */
   SC_DoubleLineEdit *lat2Edit;  /**< Latitude Upper-Right */
   
   SC_StringLineEdit *addressEdit;
   SC_DoubleLineEdit *bufferEdit;
   SC_DoubleLineEdit *offsetLatitudeEdit;
   SC_DoubleLineEdit *offsetLongitudeEdit;
   
   SC_IntLineEdit *resolutionFactorEdit;
   SC_DoubleLineEdit *scaleFactorEdit;
   QCheckBox *enableBrailsCheckBox;
};
#endif // CELERIS_TAICHI_EVENT_H
