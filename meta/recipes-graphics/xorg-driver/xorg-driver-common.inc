SUMMARY = "X driver"
HOMEPAGE = "http://www.x.org"
BUGTRACKER = "https://bugs.freedesktop.org"
SECTION = "x11/drivers"
LICENSE = "MIT-X"

PE = "2"
INC_PR = "r21"

DEPENDS = "virtual/xserver xproto randrproto util-macros"

SRC_URI = "${XORG_MIRROR}/individual/driver/${BPN}-${PV}.tar.bz2"

S = "${WORKDIR}/${BPN}-${PV}"

FILES_${PN} += " ${libdir}/xorg/modules/drivers/*.so"
FILES_${PN}-dbg += " ${libdir}/xorg/modules/drivers/.debug"

inherit autotools pkgconfig

# FIXME: We don't want to include the libtool archives (*.la) from modules
# directory, as they serve no useful purpose. Upstream should fix Makefile.am
do_install_append() {
	find ${D}${libdir}/xorg/modules -regex ".*\.la$" | xargs rm -f --
}

# Function to add the relevant ABI dependency to drivers, which should be called
# from a populate_packages append/prepend.
def add_abi_depends(d, name):
    # Map of ABI names exposed in the dependencies to pkg-config variables
    abis = {
      "video": "abi_videodrv",
      "input": "abi_xinput"
    }

    output = os.popen("pkg-config xorg-server --variable=%s" % abis[name]).read()
    mlprefix = d.getVar('MLPREFIX', True) or ''
    abi = "%sxorg-abi-%s-%s" % (mlprefix, name, output.split(".")[0])

    pn = d.getVar("PN", True)
    d.appendVar('RDEPENDS_' + pn, ' ' + abi)
