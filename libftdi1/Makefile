# $NetBSD: Makefile,v 1.6 2015/01/18 07:38:34 makoto Exp $

DISTNAME=	libftdi1-1.2
CATEGORIES=	devel
MASTER_SITES=	https://www.intra2net.com/en/developer/libftdi/download/
EXTRACT_SUFX=	.tar.bz2

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	https://www.intra2net.com/en/developer/libftdi/
COMMENT=	Userland driver library for FTDI USB chips
LICENSE=	gnu-lgpl-v2.1

USE_LIBTOOL=	yes
USE_CMAKE=	yes
# false warning ? The "cmake" tool is used but not added to USE_TOOLS.
USE_TOOLS+=	pkg-config #cmake
USE_LANGUAGES=	c c++

BUILD_DEPENDS+=libusb1-[0-9]*:../../devel/libusb1
# It is better off to have doxygen, but
# clang segfaults while packaging print/luatex
#BUILD_DEPENDS+=doxygen-[0-9]*:../../devel/doxygen

#CONFIGURE_ARGS+=	--without-examples
#CONFIGURE_ARGS+=	--without-docs

PKGCONFIG_OVERRIDE+=	libftdi1.pc.in
PKGCONFIG_OVERRIDE+=	libftdipp1.pc.in

PLIST_SUBST+=   PYSITELIB=${PYSITELIB}

CMAKE_USE_GNU_INSTALL_DIRS=no

CMAKE_ARGS+=		-DCMAKE_BUILD_WITH_INSTALL_RPATH=TRUE \
CMAKE_ARGS+=		-DCMAKE_INSTALL_PREFIX=${PREFIX} \
CMAKE_ARGS+=		-DCMAKE_INSTALL_RPATH=${PREFIX}/lib \
#CMAKE_ARGS+=	-DCMAKE_INSTALL_RPATH_USE_LINK_PATH=FALSE \
CMAKE_ARGS+=		-DLIBUSB_INCLUDE_DIR=${PREFIX}/include/libusb-1.0

REPLACE_PYTHON=		python/examples/*.py


.include "../../devel/boost-headers/buildlink3.mk"
.include "../../devel/boost-libs/buildlink3.mk"
.include "../../devel/confuse/buildlink3.mk"
.include "../../devel/libusb/buildlink3.mk"
.include "../../devel/libusb1/buildlink3.mk"
.include "../../devel/swig/buildlink3.mk"
.include "../../lang/python/application.mk"
.include "../../lang/python/pyversion.mk"
.include "../../lang/${PYPACKAGE}/buildlink3.mk"

.include "../../mk/bsd.pkg.mk"
