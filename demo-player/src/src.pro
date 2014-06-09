#############################################################################
# VLC-Qt Demo Player
# Copyright (C) 2013 Tadej Novak <tadej@tano.si>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published
# by the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this program. If not, see <http://www.gnu.org/licenses/>.
#############################################################################

TARGET      = demo-player
TEMPLATE    = app

QT          += core gui widgets network webkitwidgets

CONFIG += c++11

SOURCES     += main.cpp\
               DemoPlayer.cpp \
    controls.cpp \
    player.cpp

HEADERS     += DemoPlayer.h \
    controls.h \
    player.h

FORMS       += DemoPlayer.ui \
    VideoWidget.ui

INCLUDEPATH += $${PWD}/sdk/include

CONFIG(debug,debug|release) {
 unix|win32: LIBS += -L$${PWD}/sdk/debug -lvlc-qt -lvlc-qt-widgets
}else{
 unix|win32: LIBS += -L$${PWD}/sdk/lib -lvlc-qt -lvlc-qt-widgets
}
