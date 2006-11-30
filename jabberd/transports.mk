# $NetBSD: transports.mk,v 1.2 2006/11/30 06:06:07 schnoebe Exp $
#
#	definitions needed for Jabber transports and services
#
.if  !defined(JABBERD_TRANSPORTS_MK)
# multiple inclusion suppression
JABBERD_TRANSPORTS_MK=	defined

BUILD_DEFS+=		JABBERD_USER JABBERD_GROUP JABBERD_LOGDIR
BUILD_DEFS+=		JABBERD_PIDDIR JABBERD_SPOOLDIR JABBERD_TRANSDIR
PKG_SYSCONFSUBDIR=	jabberd

JABBERD_USER?=		jabberd
JABBERD_GROUP?=		jabberd
JABBERD_PIDDIR?=	/var/run/jabberd
JABBERD_LOGDIR?=	/var/log/jabberd
JABBERD_SPOOLDIR?=	/var/spool/jabberd
JABBERD_TRANSDIR?=	libexec/jabber-transports

OWN_DIRS+=		${JABBERD_PIDDIR}
OWN_DIRS+=		${JABBERD_LOGDIR}
OWN_DIRS+=		${JABBERD_SPOOLDIR}

FILES_SUBST+=		JABBERD_USER=${JABBERD_USER}
FILES_SUBST+=		JABBERD_GROUP=${JABBERD_GROUP}
FILES_SUBST+=		JABBERD_PIDDIR=${JABBERD_PIDDIR}
FILES_SUBST+=		JABBERD_LOGDIR=${JABBERD_LOGDIR}
FILES_SUBST+=		JABBERD_SPOOLDIR=${JABBERD_SPOOLDIR}
FILES_SUBST+=		JABBERD_TRANSDIR=${JABBERD_TRANSDIR}

PLIST_SUBST+=		JABBERD_TRANSDIR=${JABBERD_TRANSDIR}

PKG_GROUPS+=		${JABBERD_GROUP}
PKG_USERS+=		${JABBERD_USER}:${JABBERD_GROUP}

EGDIR=		${PREFIX}/share/examples/jabber
.endif	# JABBERD_TRANSPORTS_MK
