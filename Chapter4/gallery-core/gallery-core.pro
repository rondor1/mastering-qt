TEMPLATE = subdirs

SUBDIRS += \
    gallery-core \
    gallery-desktop

#Added change to ensure that gallery-core is compiled before
# gallery-desktop
gallery-desktop.depends = gallery-core
