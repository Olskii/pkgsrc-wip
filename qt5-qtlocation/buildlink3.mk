# $NetBSD: buildlink3.mk,v 1.16 2017/04/22 21:03:21 adam Exp $

BUILDLINK_TREE+=	qt5-qtlocation

.if !defined(QT5_QTLOCATION_BUILDLINK3_MK)
QT5_QTLOCATION_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.qt5-qtlocation+=	qt5-qtlocation>=5.9.1
BUILDLINK_ABI_DEPENDS.qt5-qtlocation+=	qt5-qtlocation>=5.9.1
BUILDLINK_PKGSRCDIR.qt5-qtlocation?=	../../wip/qt5-qtlocation

BUILDLINK_INCDIRS.qt5-qtlocation+=	qt5/include
BUILDLINK_LIBDIRS.qt5-qtlocation+=	qt5/lib
BUILDLINK_LIBDIRS.qt5-qtlocation+=	qt5/plugins

.include "../../wip/qt5-qtdeclarative/buildlink3.mk"
.endif	# QT5_QTLOCATION_BUILDLINK3_MK

BUILDLINK_TREE+=	-qt5-qtlocation
