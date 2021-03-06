SUMMARY = "Augeas configuration API"
HOMEPAGE = "http://augeas.net/"
BUGTRACKER = "https://fedorahosted.org/augeas/report/1"

LICENSE = "LGPLv2.1+"
LIC_FILES_CHKSUM = "file://COPYING;md5=bbb461211a33b134d42ed5ee802b37ff"

SRC_URI = "http://download.augeas.net/${BP}.tar.gz \
           file://add-missing-argz-conditional.patch \
           file://sepbuildfix.patch \
          "

DEPENDS = "readline libxml2"

inherit autotools

PACKAGES =+ "${PN}-lenses lib${BPN} lib${BPN}-dev lib${BPN}-staticdev lib${BPN}-dbg"

FILES_${PN}-lenses = "${datadir}/augeas/lenses"
FILES_lib${BPN} = "${libdir}/lib*${SOLIBS}"
FILES_lib${BPN}-dev = "${libdir}/lib*${SOLIBSDEV} ${libdir}/*.la ${includedir} ${libdir}/pkgconfig"
FILES_lib${BPN}-staticdev = "${libdir}/*.a"
FILES_lib${BPN}-dbg = "${libdir}/.debug"

RDEPENDS_lib${BPN} += "${PN}-lenses"
RRECOMMENDS_lib${BPN} += "${PN}"

LEAD_SONAME = "libaugeas.so"

do_install_append() {
	rm -fr ${D}${datadir}/vim
}
