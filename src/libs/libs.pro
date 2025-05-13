include(../../AppDemo.pri)

TEMPLATE  = subdirs

SUBDIRS   += \
    aggregation \
    extensionsystem \
    utils

SUBDIRS += \
    utils/process_stub.pro \
    3rdparty/syntax-highlighting \
    3rdparty/syntax-highlighting/data

for(l, SUBDIRS) {
    QTC_LIB_DEPENDS =
    include($$l/$${l}_dependencies.pri)
    lv = $${l}.depends
    $$lv = $$QTC_LIB_DEPENDS
}
win32:SUBDIRS += utils/process_ctrlc_stub.pro
