# $NetBSD: Makefile,v 1.126 2017/05/03 08:38:45 jperkin Exp $

DISTNAME=	webkitgtk-2.18.2
PKGNAME=	${DISTNAME:S/webkitgtk/webkit-gtk/}
CATEGORIES=	www
MASTER_SITES=	https://www.webkitgtk.org/releases/
EXTRACT_SUFX=	.tar.xz

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	https://www.webkitgtk.org/
COMMENT=	GTK port of the WebKit browser engine
LICENSE=	2-clause-bsd AND gnu-lgpl-v2

# shm_open(3) and shm_unlink(3) appeared in NetBSD 7.0
NOT_FOR_PLATFORM=	NetBSD-[1-6]*-*

BUILD_DEPENDS+=	gettext-tools>=0.18:../../devel/gettext-tools

USE_CMAKE=	yes
USE_LANGUAGES=	c c++11
#USE_LIBTOOL=	yes
USE_TOOLS+=	automake bison gmake perl:build pkg-config msgfmt

GCC_REQD+=	5.0

# Using ld.gold subverts Pkgsrc wrappers, and this package also crashes buggy
# versions of ld.gold.
CMAKE_ARGS+=	-DUSE_LD_GOLD=OFF

PKGCONFIG_OVERRIDE+=	Source/JavaScriptCore/javascriptcoregtk.pc.in
PKGCONFIG_OVERRIDE+=	Source/WebKit2/webkit2gtk.pc.in
PKGCONFIG_OVERRIDE+=	Source/WebKit2/webkit2gtk-web-extension.pc.in

CMAKE_ARGS+=		-DCMAKE_BUILD_TYPE=Release
CMAKE_ARGS+=		-DPORT=GTK
CMAKE_ARGS+=		-DENABLE_X11_TARGET=ON
CMAKE_ARGS+=		-DENABLE_MINIBROWSER=ON
CMAKE_ARGS+=		-DENABLE_GEOLOCATION=OFF
CMAKE_ARGS+=		-DUSE_GSTREAMER_GL=OFF
CMAKE_ARGS+=		-DUSE_LIBHYPHEN=OFF
#CMAKE_ARGS+=		-DUSE_SYSTEM_MALLOC=ON # XXX: needs adjustements for sysinfo() stuffs in Source/WTF/wtf/RAMSize.cpp

REPLACE_PERL+=	Source/JavaScriptCore/create_hash_table \
		Source/WebCore/bindings/scripts/*.pl \
		Source/WebCore/bindings/scripts/InFilesCompiler.pm \
		Source/WebCore/bindings/scripts/InFilesParser.pm \
		Source/WebCore/css/*.pl \
		Source/WebCore/dom/*.pl \
		Source/WebCore/make-hash-tools.pl

REPLACE_PYTHON+=	Tools/gtk/*.py \
			Tools/gtk/generate-gtkdoc

.include "../../lang/ruby/rubyversion.mk"
BUILD_DEPENDS+=	${RUBY_BASE}>=${RUBY_VERSION}:${RUBY_SRCDIR}
CMAKE_ARGS+=	-DRUBY_EXECUTABLE=${RUBY}

PYTHON_FOR_BUILD_ONLY=	yes
PYTHON_VERSIONS_INCOMPATIBLE=	34 35 36 # not yet ported as of 1.10.2
.include "../../lang/python/application.mk"
CMAKE_ARGS+=	-DPYTHON_EXECUTABLE=${PYTHONBIN}

CXXFLAGS.SunOS+=	-fpermissive

.include "../../mk/compiler.mk"
.if !empty(PKGSRC_COMPILER:Mclang)
CXXFLAGS+=	-Wno-c++11-narrowing
.endif

.include "options.mk"

BUILDLINK_API_DEPENDS.glib2+= glib2>=2.32.1
.include "../../devel/glib2/buildlink3.mk"
.include "../../devel/zlib/buildlink3.mk"
.include "../../databases/sqlite3/buildlink3.mk"
# A correct Webkit build requires flex 2.5.33
.include "../../devel/flex/buildlink3.mk"
.include "../../devel/gperf/buildlink3.mk"
.include "../../devel/pango/buildlink3.mk"
.include "../../graphics/cairo-gobject/buildlink3.mk"
.include "../../graphics/freetype2/buildlink3.mk"
.include "../../graphics/libwebp/buildlink3.mk"
.include "../../mk/jpeg.buildlink3.mk"
BUILDLINK_API_DEPENDS.png+= png>=1.5.1beta08
.include "../../graphics/png/buildlink3.mk"
BUILDLINK_API_DEPENDS.gstreamer1+=	gstreamer1>=1.0.3
.include "../../multimedia/gstreamer1/buildlink3.mk"
BUILDLINK_API_DEPENDS.gst-plugins1-base+=	gst-plugins1-base>=1.0.3
.include "../../multimedia/gst-plugins1-base/buildlink3.mk"
BUILDLINK_API_DEPENDS.libsoup+= libsoup>=2.42.2nb3
.include "../../net/libsoup/buildlink3.mk"
.include "../../security/libsecret/buildlink3.mk"
.include "../../security/gnutls/buildlink3.mk"
.include "../../sysutils/libnotify/buildlink3.mk"
.include "../../textproc/icu/buildlink3.mk"
.include "../../textproc/libxslt/buildlink3.mk"
BUILDLINK_API_DEPENDS.gtk2+=	gtk2+>=2.24.17nb3
.include "../../x11/gtk2/buildlink3.mk"
.include "../../x11/gtk3/buildlink3.mk"
.include "../../x11/libXdamage/buildlink3.mk"
.include "../../x11/libXt/buildlink3.mk"
.include "../../mk/pthread.buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
