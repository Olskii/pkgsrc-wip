# $NetBSD$

DISTNAME=	renameutils-0.12.0
CATEGORIES=	sysutils converters
MASTER_SITES=	http://download.savannah.gnu.org/releases/renameutils/

MAINTAINER=	mcy@lm7.fr
HOMEPAGE=	http://www.nongnu.org/renameutils/
COMMENT=	Rename files faster and more easily
LICENSE=	gnu-gpl-v3

GNU_CONFIGURE=		yes
DEPENDS+=               coreutils-[0-9]*:../../sysutils/coreutils

.include "options.mk"
.include "../../devel/readline/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
