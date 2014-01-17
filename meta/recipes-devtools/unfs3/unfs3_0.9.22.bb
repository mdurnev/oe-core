DESCRIPTION = "Userspace NFS server v3 protocol"
SECTION = "console/network"
LICENSE = "unfs3"
LIC_FILES_CHKSUM = "file://LICENSE;md5=9475885294e17c0cc0067820d042792e"

RDEPENDS_${PN} = "pseudo"
RDEPENDS_${PN}_class-native = "pseudo-native"
RDEPENDS_${PN}_class-nativesdk = "pseudo-nativesdk"
DEPENDS = "flex-native bison-native"
DEPENDS_class-nativesdk += "flex-nativesdk"

SRC_URI[md5sum] = "ddf679a5d4d80096a59f3affc64f16e5"
SRC_URI[sha256sum] = "482222cae541172c155cd5dc9c2199763a6454b0c5c0619102d8143bb19fdf1c"

SRC_URI = "http://sourceforge.net/projects/unfs3/files/unfs3/0.9.22/unfs3-0.9.22.tar.gz \
           file://unfs3_parallel_build.patch \
           file://alternate_rpc_ports.patch \
           file://fix_pid_race_parent_writes_child_pid.patch \
           file://fix_compile_warning.patch \
           file://rename_fh_cache.patch \
           file://relative_max_socket_path_len.patch \
           file://force_4_byte_long_on_64_bit_host.patch \
           file://fix_warnings.patch \
           file://tcp_no_delay.patch \
          "
BBCLASSEXTEND = "native nativesdk"

inherit autotools

# Turn off these header detects else the inode search
# will walk entire file systems and this is a real problem
# if you have 2 TB of files to walk in your file system
CACHED_CONFIGUREVARS = "ac_cv_header_mntent_h=no ac_cv_header_sys_mnttab_h=no"

do_configure() {
	# Skip running autoconf because it wants old m4 macros
	oe_runconf
}

# This recipe is intended for -native and -nativesdk builds only,
# not target installs:
python __anonymous () {
    import re

    pn = d.getVar("PN", True)
    if not pn.endswith('-native') and not pn.startswith('nativesdk-'):
        raise bb.parse.SkipPackage("unfs3 is intended for native/nativesdk builds only")
}
