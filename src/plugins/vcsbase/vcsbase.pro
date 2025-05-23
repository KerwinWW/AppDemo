DEFINES += VCSBASE_LIBRARY
include(../../AppDemoplugin.pri)
HEADERS += vcsbase_global.h \
    vcsbaseconstants.h \
    wizard/vcsconfigurationpage.h \
    wizard/vcscommandpage.h \
    wizard/vcsjsextension.h \
    vcsplugin.h \
    vcsbaseplugin.h \
    baseannotationhighlighter.h \
    diffandloghighlighter.h \
    vcsbaseeditor.h \
    vcsbasesubmiteditor.h \
    basevcseditorfactory.h \
    submiteditorfile.h \
    basevcssubmiteditorfactory.h \
    submitfilemodel.h \
    commonvcssettings.h \
    commonsettingspage.h \
    nicknamedialog.h \
    vcsoutputwindow.h \
    cleandialog.h \
    vcsbaseoptionspage.h \
    vcscommand.h \
    vcsbaseclient.h \
    vcsbaseclientsettings.h \
    vcsbaseeditorconfig.h \
    submitfieldwidget.h \
    submiteditorwidget.h \
    vcsbasediffeditorcontroller.h

SOURCES += vcsplugin.cpp \
    vcsbaseplugin.cpp \
    wizard/vcsconfigurationpage.cpp \
    wizard/vcscommandpage.cpp \
    wizard/vcsjsextension.cpp \
    baseannotationhighlighter.cpp \
    diffandloghighlighter.cpp \
    vcsbaseeditor.cpp \
    vcsbasesubmiteditor.cpp \
    basevcseditorfactory.cpp \
    submiteditorfile.cpp \
    basevcssubmiteditorfactory.cpp \
    submitfilemodel.cpp \
    commonvcssettings.cpp \
    commonsettingspage.cpp \
    nicknamedialog.cpp \
    vcsoutputwindow.cpp \
    cleandialog.cpp \
    vcsbaseoptionspage.cpp \
    vcscommand.cpp \
    vcsbaseclient.cpp \
    vcsbaseclientsettings.cpp \
    vcsbaseeditorconfig.cpp \
    submitfieldwidget.cpp \
    submiteditorwidget.cpp \
    vcsbasediffeditorcontroller.cpp

RESOURCES += vcsbase.qrc

FORMS += commonsettingspage.ui \
    nicknamedialog.ui \
    cleandialog.ui \
    submiteditorwidget.ui

