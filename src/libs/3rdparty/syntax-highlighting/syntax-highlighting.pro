include(../../../AppDemolibrary.pri)
include(autogenerated/autogenerated.pri)

QT += network

DEFINES += KSYNTAXHIGHLIGHTING_LIBRARY

RESOURCES += \
    data/themes/theme-data.qrc

HEADERS += \
    $$PWD/src/lib/abstracthighlighter.h \
    $$PWD/src/lib/abstracthighlighter_p.h \
    $$PWD/src/lib/context_p.h \
    $$PWD/src/lib/contextswitch_p.h \
    $$PWD/src/lib/definition.h \
    $$PWD/src/lib/definition_p.h \
    $$PWD/src/lib/definitiondownloader.h \
    $$PWD/src/lib/definitionref_p.h \
    $$PWD/src/lib/foldingregion.h \
    $$PWD/src/lib/format.h \
    $$PWD/src/lib/format_p.h \
    $$PWD/src/lib/htmlhighlighter.h \
    $$PWD/src/lib/keywordlist_p.h \
    $$PWD/src/lib/ksyntaxhighlighting_export.h \
    $$PWD/src/lib/matchresult_p.h \
    $$PWD/src/lib/repository.h \
    $$PWD/src/lib/repository_p.h \
    $$PWD/src/lib/rule_p.h \
    $$PWD/src/lib/state.h \
    $$PWD/src/lib/state_p.h \
    $$PWD/src/lib/syntaxhighlighter.h \
    $$PWD/src/lib/textstyledata_p.h \
    $$PWD/src/lib/theme.h \
    $$PWD/src/lib/themedata_p.h \
    $$PWD/src/lib/wildcardmatcher_p.h \
    $$PWD/src/lib/xml_p.h \

SOURCES += \
    $$PWD/src/lib/abstracthighlighter.cpp \
    $$PWD/src/lib/context.cpp \
    $$PWD/src/lib/contextswitch.cpp \
    $$PWD/src/lib/definition.cpp \
    $$PWD/src/lib/definitiondownloader.cpp \
    $$PWD/src/lib/foldingregion.cpp \
    $$PWD/src/lib/format.cpp \
    $$PWD/src/lib/htmlhighlighter.cpp \
    $$PWD/src/lib/keywordlist.cpp \
    $$PWD/src/lib/repository.cpp \
    $$PWD/src/lib/rule.cpp \
    $$PWD/src/lib/state.cpp \
    $$PWD/src/lib/syntaxhighlighter.cpp \
    $$PWD/src/lib/theme.cpp \
    $$PWD/src/lib/themedata.cpp \
    $$PWD/src/lib/wildcardmatcher.cpp \
