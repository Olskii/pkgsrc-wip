# $NetBSD: buildlink3.mk,v 1.1.1.1 2011/04/02 22:10:45 jihbed Exp $

BUILDLINK_TREE+=	Minuit2

.if !defined(MINUIT2_BUILDLINK3_MK)
MINUIT2_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.Minuit2+=	Minuit2>=5.28.00
BUILDLINK_PKGSRCDIR.Minuit2?=	../../wip/minuit2
.endif	# MINUIT2_BUILDLINK3_MK

BUILDLINK_TREE+=	-Minuit2
