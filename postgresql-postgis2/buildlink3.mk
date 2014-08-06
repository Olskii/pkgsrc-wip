# $NetBSD: buildlink3.mk,v 1.2 2014/08/06 17:03:46 fhajny Exp $

BUILDLINK_TREE+=	postgresql-postgis

.if !defined(POSTGRESQL_POSTGIS_BUILDLINK3_MK)
POSTGRESQL_POSTGIS_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.postgresql-postgis+=	postgresql${PGSQL_VERSION}-postgis>=1.4
BUILDLINK_PKGSRCDIR.postgresql-postgis?=	../../databases/postgresql-postgis

PGSQL_VERSIONS_ACCEPTED=	93 92 91 90

.include "../../geography/geos/buildlink3.mk"
.include "../../geography/proj/buildlink3.mk"
.include "../../mk/pgsql.buildlink3.mk"
.endif	# POSTGRESQL_POSTGIS_BUILDLINK3_MK

BUILDLINK_TREE+=	-postgresql-postgis
