# $NetBSD: options.mk,v 1.1 2015/04/04 15:15:44 makoto Exp $
PKG_OPTIONS_VAR=	PKG_OPTIONS.tamago-tsunagi
PKG_SUPPORTED_OPTIONS=	freewnn canna sj3 anthy
PKG_SUGGESTED_OPTIONS=	canna sj3 anthy

.include "../../mk/bsd.options.mk"

.if !empty(PKG_OPTIONS:Mfreewnn)
DEPENDS+=	ja-FreeWnn-server>=1.11:../../inputmethod/ja-freewnn-server
.endif

.if !empty(PKG_OPTIONS:Mcanna)
DEPENDS+=	Canna-server-[0-9]*:../../inputmethod/canna-server
.endif

.if !empty(PKG_OPTIONS:Msj3)
DEPENDS+=	sj3-server-[0-9]*:../../inputmethod/sj3-server
.endif

.if !empty(PKG_OPTIONS:Manthy)
DEPENDS+=	anthy-[0-9]*:../../inputmethod/anthy
.endif


