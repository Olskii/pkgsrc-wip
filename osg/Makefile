# $NetBSD: Makefile,v 1.55 2015/06/30 09:57:36 ryoon Exp $

DISTNAME=	OpenSceneGraph-3.4.0
PKGNAME=	osg-3.4.0
CATEGORIES=	graphics devel
MASTER_SITES=	http://www.openscenegraph.org/downloads/stable_releases/OpenSceneGraph-${PKGVERSION_NOREV}/source/
EXTRACT_SUFX=	.zip

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	http://www.openscenegraph.org/projects/osg
COMMENT=	High performance 3D graphics toolkit
LICENSE=	gnu-lgpl-v2.1

USE_CMAKE=		yes
USE_LANGUAGES=		c c++
USE_TOOLS+=		pkg-config
PKGCONFIG_OVERRIDE=	packaging/pkgconfig/openscenegraph.pc.in
PKGCONFIG_OVERRIDE+=	packaging/pkgconfig/openthreads.pc.in

CMAKE_ARGS+=		-DCMAKE_BUILD_TYPE=Release

CXXFLAGS+=	-D__STDC_CONSTANT_MACROS -D__STDC_LIMIT_MACROS

PLIST_VARS+=	quartz x11

.include "../../mk/bsd.prefs.mk"

.if ${OPSYS} == "Darwin"
PLIST.quartz=	yes
.else
PLIST.x11=	yes
.include "../../graphics/MesaLib/buildlink3.mk"
.include "../../graphics/glu/buildlink3.mk"
.include "../../graphics/png/buildlink3.mk"
.include "../../graphics/tiff/buildlink3.mk"
.include "../../x11/libX11/buildlink3.mk"
.include "../../x11/libXrandr/buildlink3.mk"
.include "../../graphics/giflib/buildlink3.mk"
.include "../../mk/jpeg.buildlink3.mk"
.endif

.include "../../devel/SDL/buildlink3.mk"
.include "../../geography/gdal-lib/buildlink3.mk"
.include "../../graphics/cairo/buildlink3.mk"
.include "../../graphics/freetype2/buildlink3.mk"
.include "../../graphics/jasper/buildlink3.mk"
.include "../../graphics/librsvg/buildlink3.mk"
.include "../../graphics/openexr/buildlink3.mk"
.include "../../www/curl/buildlink3.mk"
.include "../../mk/pthread.buildlink3.mk"
.if ${OPSYS} != "Darwin"
.include "../../multimedia/ffmpeg2/buildlink3.mk"
.endif
.include "../../mk/bsd.pkg.mk"
