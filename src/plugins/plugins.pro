include(../../AppDemo.pri)

TEMPLATE  = subdirs

SUBDIRS   = \
    coreplugin \
#    vcsbase \
#    texteditor\
#    cpptools\
#    projectexplorer \
#    welcome


for(p, SUBDIRS) {
    QTC_PLUGIN_DEPENDS =
    include($$p/$${p}_dependencies.pri)
    pv = $${p}.depends
    $$pv = $$QTC_PLUGIN_DEPENDS
}


