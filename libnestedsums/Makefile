# $NetBSD: Makefile,v 1.3 2015/02/13 22:10:14 jihbed Exp $
#

DISTNAME=	nestedsums-1.4.12
PKGNAME=	lib${DISTNAME}
CATEGORIES=	math
MASTER_SITES=	http://wwwthep.physik.uni-mainz.de/~stefanw/download/

MAINTAINER=	jihbed.research@gmail.com
HOMEPAGE=	http://wwwthep.physik.uni-mainz.de/~stefanw/nestedsums/
COMMENT=	Library for the expansion of transcendental functions
LICENSE=	gnu-gpl-v2

GNU_CONFIGURE=	yes
USE_LIBTOOL=	yes
USE_TOOLS+=	pkg-config
USE_LANGUAGES=	c c++ fortran


.include "../../wip/libginac/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
