# $NetBSD: Makefile,v 1.15 2017/04/22 21:03:22 adam Exp $

DISTNAME=	qtwebchannel-opensource-src-${QTVERSION}
PKGNAME=	qt5-qtwebchannel-${QTVERSION}
COMMENT=	Qt5 WebChannel module

MAKE_ENV+=		QTDIR=${QTDIR}
INSTALL_ENV+=		INSTALL_ROOT=${DESTDIR}
INSTALLATION_DIRS+=	lib/pkgconfig

.include "../../wip/qt5-qtbase/Makefile.common"

post-install:
.for i in Qt5WebChannel.pc
	cd ${DESTDIR}${PREFIX}/lib/pkgconfig && \
		ln -f -s ${QTPREFIX}/lib/pkgconfig/${i} ${i}
.endfor

.include "../../wip/qt5-qtdeclarative/buildlink3.mk"
.include "../../wip/qt5-qtwebsockets/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
