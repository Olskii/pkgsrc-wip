# $NetBSD$

DISTNAME=	libretro-genesis-plus-gx-20171016
CATEGORIES=	emulators
MASTER_SITES=	${MASTER_SITE_GITHUB:=libretro/}

MAINTAINER=	nia.alarie@gmail.com
HOMEPAGE=	https://wiki.libretro.com/index.php?title=Genesis_Plus_GX
COMMENT=	Libretro core based on the Genesis Plus Sega 8/16 bit emulator
LICENSE=	picodrive-license

GITHUB_PROJECT=	Genesis-Plus-GX
GITHUB_TAG=	2c8af6348ac0f808fbd965735823392d316f349d

EXTRACT_USING=	bsdtar
USE_TOOLS=	gmake

MAKE_FILE=	Makefile.libretro

BUILD_MAKE_FLAGS+=	SHARED_LIBVORBIS=1

.include "../../mk/endian.mk"

.if ${MACHINE_ENDIAN} == "big"
BUILD_MAKE_FLAGS+=	ENDIANNESS_DEFINES="-DBYTE_ORDER=BIG_ENDIAN -DCPU_IS_BIG_ENDIAN=1 -DWORDS_BIGENDIAN=1"
.endif

INSTALLATION_DIRS+=	${PREFIX}/lib/libretro

do-install:
	${INSTALL_LIB} ${WRKSRC}/genesis_plus_gx_libretro.so \
	    ${DESTDIR}${PREFIX}/lib/libretro/genesis_plus_gx_libretro.so

.include "../../audio/libvorbis/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
