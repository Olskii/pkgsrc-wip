# $NetBSD: Makefile,v 1.13 2017/04/22 21:03:21 adam Exp $

DISTNAME=	qtmacextras-opensource-src-${QTVERSION}
PKGNAME=	qt5-qtmacextras-${QTVERSION}
COMMENT=	Qt5 module for Mac extras

BUILD_TARGET=		sub-src
INSTALL_ENV+=		INSTALL_ROOT=${DESTDIR}
INSTALLATION_DIRS+=	lib/pkgconfig

ONLY_FOR_PLATFORM=	Darwin-*-*

.include "../../wip/qt5-qtbase/Makefile.common"

post-install:
.for i in Qt5MacExtras.pc
	cd ${DESTDIR}${PREFIX}/lib/pkgconfig && \
	ln -f -s ${QTPREFIX}/lib/pkgconfig/${i} ${i}
.endfor

.include "../../wip/qt5-qtxmlpatterns/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
