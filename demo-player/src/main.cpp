/****************************************************************************
* VLC-Qt Demo Player
* Copyright (C) 2013 Tadej Novak <tadej@tano.si>
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU Lesser General Public License as published
* by the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
*****************************************************************************/


#include <QtCore/QCoreApplication>
#include <QtCore/QTextCodec>

#include <QApplication>

#include "DemoPlayer.h"
#include "player.h"

int main(int argc, char *argv[])
{

    QApplication app(argc, argv);

//    DemoPlayer mainWindow;
//    mainWindow.show();
//    mainWindow.setUrl("http://static.61read.com/videos/2013/11/HuoMaoZiYunYiFu.mp4");
    Player p;
    //p.Play("http://static.61read.com/videos/2013/11/HuoMaoZiYunYiFu.mp4");
    p.show();

    return app.exec();
}
