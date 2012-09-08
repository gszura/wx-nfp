#ifndef HEADER_E96D519BC4059816
#define HEADER_E96D519BC4059816

// ========================================================================
// ========FILE: cycleData_declarations.h ===============================
// ========================================================================
#ifndef __CYCLES_DATA_DECLARATIONS__
#define __CYCLES_DATA_DECLARATIONS__

//#include "wx_pch.h"

// ========================================================================

#define CYCLE_TYPE_NORMAL          1
#define CYCLE_TYPE_PREGNANCY       2
#define CYCLE_TYPE_AFTER_PREGNANCY 3
#define CYCLE_TYPE_PERI_MENOPAUSE  4

// basic infertile pattern (used in CYCLE_TYPE_AFTER_PREGNANCY)
#define CYCLE_BIP_AUTO   0
#define CYCLE_BIP_DRY    1
#define CYCLE_BIP_MUCUS  2

// measurement place
#define PLACE_MOUTH             1
#define PLACE_VAGINA            2
#define PLACE_RECTUM            3

// menstruation, ovulation pain, breasts tension, spotting
#define A_BIT                   1
#define STRONG                  2

// mucus - feeling, experience
#define MUCUS_DRY               1
#define MUCUS_MOIST             2
#define MUCUS_WET               3
#define MUCUS_SLIPPERY          4

// mucus - appearance
#define MUCUS_OPAQUE            1
#define MUCUS_WHITE             2
#define MUCUS_YELLOWISH         4
#define MUCUS_TACKY             8
#define MUCUS_CLEAR             16
#define MUCUS_STRETCHY          32
#define MUCUS_SEMINALRESIDUE    64
#define MUCUS_AMOUNT1           128
#define MUCUS_AMOUNT2           256
#define MUCUS_AMOUNT3           512
#define MUCUS_LENGHTOFSTRETCH1  1024
#define MUCUS_LENGHTOFSTRETCH2  2048
#define MUCUS_LENGHTOFSTRETCH3  4096

// cervix - position
#define CERVIX_HIGH             5
#define CERVIX_ABOVE_MIDDLE     4
#define CERVIX_IN_MIDDLE        3
#define CERVIX_BELOW_MEDDLE     2
#define CERVIX_LOW              1

//cervix - dilation
#define CERVIX_OPEN             3
#define CERVIX_HALF_OPEN        2
#define CERVIX_CLOSED           1

// cervix - hardness
#define CERVIX_SOFT             3
#define CERVIX_RATHER_FIRM      2
#define CERVIX_FIRM             1

// ========================================================================

// STRINGS

// cycle type
#define string_cycleTypeNormal  _( "normal" )
#define string_cycleTypePregnancy  _( "pregnancy" )
#define string_cycleTypeAfterPregnancy  _( "after pregnancy" )
#define string_cycleTypePeriMenopause  _( "peri-menopause" )

// basic infertile pattern (used in CYCLE_TYPE_AFTER_PREGNANCY)
#define string_cycle_bip_auto  _( "auto calculate" )
#define string_cycle_bip_dry  _( "dry" )
#define string_cycle_bip_mucus  _( "mucus" )

// sexual relations
#define string_sexualRelationMorning _("sexual relation in the morning")
#define string_sexualRelationDay _("sexual relation during the day")
#define string_sexualRelationEvening _("sexual relation in the evening")

// measurement place
#define string_placeMouth  _( "mouth" )
#define string_placeRectum  _( "rectum" )
#define string_placeVagina  _( "vagina" )
// mucus - feeling, experience - abbreviation
#define string_mucusDry  _( "dry" )
#define string_mucusMoist  _( "moist" )
#define string_mucusWet  _( "wet" )
#define string_mucusSlippery  _( "slip." )
// mucus - appearance - abbreviation
#define string_mucusAppearanceOpaque  _( "o" )
#define string_mucusAppearanceWhite  _( "w" )
#define string_mucusAppearanceYellowish  _( "y" )
#define string_mucusAppearanceTacky  _( "t" )
#define string_mucusAppearanceClear  _( "c" )
#define string_mucusAppearanceStretchy  _( "s" )
#define string_mucusAppearanceSeminalResidue  _( "SR" )
// cervix - hardness - abbreviation
#define string_cervixSoft  _( "soft" )
#define string_cervixRatherFirm  _( "rf" )
#define string_cervixFirm  _( "firm" )
#define string_peakDay  _( "P" )

// mucus - feeling, experience
#define string_mucusDry_long  _( "dry" )
#define string_mucusMoist_long  _( "moist" )
#define string_mucusWet_long  _( "wet" )
#define string_mucusSlippery_long  _( "slippery" )
// cervix - position
#define string_cervixHigh_long  _( "high" )
#define string_cervixAboveMiddle_long  _( "above middle" )
#define string_cervixInMiddle_long  _( "in middle" )
#define string_cervixBelowMiddle_long  _( "below middle" )
#define string_cervixLow_long  _( "low" )
//cervix - dilation
#define string_cervixOpen_long  _( "open" )
#define string_cervixHalfOpen_long  _( "half-open" )
#define string_cervixClosed_long  _( "closed" )
// cervix - hardness
#define string_cervixSoft_long  _( "soft" )
#define string_cervixRatherFirm_long  _( "rather firm" )
#define string_cervixFirm_long  _( "firm" )

#define string_fertile_phase   _( "fertile\nphase" )
#define string_infertile_phase _( "infertile\nphase" )
#define string_luteal_phase _( "luteal phase" )


// ========================================================================
// ========================================================================

#endif


#endif // header guard
