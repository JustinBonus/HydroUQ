#ifndef HYDRO_EVENT_SELECTION_H
#define HYDRO_EVENT_SELECTION_H

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

// Written: fmckenna
// Modified: Ajay B Harish (May 2021)
// Modified: Justin Bonus (Feb 2024)
#include <SimCenterAppWidget.h>

#include <QGroupBox>
#include <QVector>
#include <RemoteService.h>
#include <RandomVariablesContainer.h>

// #include <QHBoxLayout>
// #include <QVBoxLayout>
// #include <QStackedWidget>
// #include <QComboBox>
// #include <QSpacerItem>
// #include <QPushButton>
// #include <QJsonObject>
// #include <QJsonArray>
// #include <QLabel>
// #include <QLineEdit>
// #include <QDebug>
// #include <QFileDialog>
// #include <QPushButton>
// #include <SectionTitle.h>
// #include <GeneralInformationWidget.h>
// #include <InputWidgetExistingEvent.h>
// #include <GeoClawOpenFOAM.h>
// #include <WaveDigitalFlume.h>
class QComboBox; // WE-UQ
class QStackedWidget; // WE-UQ
class UserDefinedApplication; // WE-UQ
// class RandomVariablesContainer;

class HydroEventSelection : public  SimCenterAppWidget
{
    Q_OBJECT
public:
   //  explicit HydroEventSelection(RandomVariablesContainer *,
	// 			 GeneralInformationWidget* generalInfoWidget,
	// 			 QWidget *parent = 0);
   //  explicit HydroEventSelection(RandomVariablesContainer *,  QWidget *parent = 0); 

    explicit HydroEventSelection(RandomVariablesContainer *, RemoteService* remoteService, QWidget *parent = 0); // WE-UQ
    ~HydroEventSelection();

    bool outputToJSON(QJsonObject &rvObject);
    bool inputFromJSON(QJsonObject &rvObject);
    bool outputAppDataToJSON(QJsonObject &rvObject);
    bool inputAppDataFromJSON(QJsonObject &rvObject);
    bool copyFiles(QString &destName);
    bool supportsLocalRun() override;
    bool outputCitation(QJsonObject &jsonObject) override;  

signals:
    void statusMessage(QString message);
    void errorMessage(QString message);
    void fatalMessage(QString message);
    void typeEVT(QString type);

public slots:
   void eventSelectionChanged(int arg1);
   void eventSelectionChanged(const QString &arg1); // WE-UQ
   void sendStatusMessage(QString message); // WE-UQ
   void sendErrorMessage(QString message); // WE-UQ
   void sendFatalMessage(QString message); // WE-UQ
   void replyEventType(void);

private:
   QComboBox   *eventSelection;
   QStackedWidget *theStackedWidget;
   SimCenterAppWidget *theCurrentEvent;

   //   SimCenterAppWidget *theSHA_MotionWidget;
   SimCenterAppWidget *theGeoClawOpenFOAM;
   SimCenterAppWidget *theWaveDigitalFlume;
   SimCenterAppWidget *theCoupledDigitalTwin;
   SimCenterAppWidget *theMPM;    
   SimCenterAppWidget *theMPMEvent;
   SimCenterAppWidget *theTaichiEvent;
   SimCenterAppWidget *theCeleris;
   SimCenterAppWidget *theStochasticWaves;
   SimCenterAppWidget *theSPH;
   SimCenterAppWidget *theExistingEvents;

   RandomVariablesContainer *theRandomVariablesContainer;
};

#endif // HYDRO_EVENT_SELECTION_H
