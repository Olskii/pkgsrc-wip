# $NetBSD: buildlink3.mk,v 1.4 2014/08/29 14:10:28 szptvlfn Exp $

BUILDLINK_TREE+=	hs-pureMD5

.if !defined(HS_PUREMD5_BUILDLINK3_MK)
HS_PUREMD5_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.hs-pureMD5+=	hs-pureMD5>=2.1.2
BUILDLINK_ABI_DEPENDS.hs-pureMD5+=	hs-pureMD5>=2.1.2.1
BUILDLINK_PKGSRCDIR.hs-pureMD5?=	../../wip/hs-pureMD5

.endif	# HS_PUREMD5_BUILDLINK3_MK

BUILDLINK_TREE+=	-hs-pureMD5
