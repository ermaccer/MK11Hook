#include "Menu.h"

const char* szModifiers[NUM_MODIFIERS] = {
		"AcidRain",
		"AirStrike",
		"Armor",
		"BadLowGround",
		"BadSpecial",
		"Bleeding",
		"BlockingDisabled",
		"BrutalityKombat",
		"BuffedUp",
		"CoordinatesReceived",
		"DarkKombat",
		"DeadHands",
		"DiveKick",
		"Earthshaker",
		"Earthquake",
		"BloodAura",
		"ChaosAura",
		"DarkAura",
		"ElectricAura",
		"EnergyAura",
		"FireAura",
		"IceAura",
		"MagicAura",
		"PoisonAura",
		"BloodFists",
		"ChaosFists",
		"DarkFists",
		"ElectricFists",
		"EnergyFists",
		"FireFists",
		"IceFists",
		"MagicFists",
		"PoisonFists",
		"BloodFloor",
		"ChaosFloor",
		"DarkFloor",
		"ElectricFloor",
		"EnergyFloor",
		"FireFloor",
		"IceFloor",
		"MagicFloor",
		"PoisonFloor",
		"BloodShield",
		"HalfResistBlood",
		"ChaosShield",
		"HalfResistChaos",
		"DarkShield",
		"HalfResistDark",
		"ElectricShield",
		"HalfResistElectric",
		"EnergyShield",
		"HalfResistEnergy",
		"FireShield",
		"HalfResistFire",
		"IceShield",
		"HalfResistIce",
		"MagicShield",
		"HalfResistMagic",
		"PoisonShield",
		"HalfResistPoison",
		"PhysicalShield",
		"HalfResistPhysical",
		"BloodRockets",
		"BloodRockets_FriendlyFire",
		"ChaosRockets",
		"ChaosRockets_FriendlyFire",
		"DarkRockets",
		"DarkRockets_FriendlyFire",
		"ElectricRockets",
		"ElectricRockets_FriendlyFire",
		"EnergyRockets",
		"EnergyRockets_FriendlyFire",
		"FireRockets",
		"FireRockets_FriendlyFire",
		"IceRockets",
		"IceRockets_FriendlyFire",
		"MagicRockets",
		"MagicRockets_FriendlyFire",
		"PoisonRockets",
		"PoisonRockets_FriendlyFire",
		"BloodStorm",
		"ChaosStorm",
		"DarkStorm",
		"ElectricStorm",
		"EnergyStorm",
		"FireStorm",
		"IceStorm",
		"MagicStorm",
		"PoisonStorm",
		"BloodTotem",
		"ChaosTotem",
		"DarkTotem",
		"ElectricTotem",
		"EnergyTotem",
		"FireTotem",
		"IceTotem",
		"MagicTotem",
		"PoisonTotem",
		"FallingBombs",
		"FallingHeads",
		"FleetFooted",
		"GiftOfBlood",
		"CurseOfBlood",
		"GiftOfChaos",
		"CurseOfChaos",
		"GiftOfDark",
		"CurseOfDark",
		"GiftOfElectric",
		"CurseOfElectric",
		"GiftOfEnergy",
		"CurseOfEnergy",
		"GiftOfFire",
		"CurseOfFire",
		"GiftOfIce",
		"CurseOfIce",
		"GiftOfMagic",
		"CurseOfMagic",
		"GiftOfPoison",
		"CurseOfPoison",
		"GiftOfRandom",
		"CurseOfRandom",
		"PickupOfRandom",
		"GiveSupermove",
		"GroundBlade",
		"GroundMines",
		"GroundSpikes",
		"GunAttacksUp",
		"JuggleKombat",
		"BlueLightningStrikes",
		"RedLightningStrikes",
		"BlackLightningStrikes",
		"MeteorKombat",
		"Overpowered",
		"DamageBuff",
		"PanningLasers",
		"PillarsOfFlame",
		"Poisoned",
		"BadDucking",
		"BadJumping",
		"PowerOrb",
		"PowerStruggle",
		"HypoKombat",
		"HyperKombat",
		"SupermoveBuff",
		"WetSpot",
		"DamageReflectAll",
		"HealBlock",
		"BlackDragonAssist",
		"BoRaiChoAssist",
		"ErmacAssist",
		"HsuHaoAssist",
		"HydroAssist",
		"KungJinAssist",
		"MeatAssist",
		"MileenaAssist",
		"NitaraAssist",
		"OnyxAssist",
		"QuanChiAssist",
		"ReikoAssist",
		"ReptileAssist",
		"SektorAssist",
		"SmokeAssist",
		"SpecialForcesAssist",
		"StrykerAssist",
		"TakedaAssist",
		"TanyaAssist",
		"TremorAssist",
		"CyraxAssist",
		"CyraxBombsAssist",
		"KenshiAssist",
		"RainAssist",
		"ShinnokAssist",
		"BloodBuff",
		"ChaosBuff",
		"DarkBuff",
		"ElectricBuff",
		"EnergyBuff",
		"FireBuff",
		"IceBuff",
		"MagicBuff",
		"PoisonBuff",
		"PhysicalBuff",
		"DisableWeather",
		"DisableRockets",
		"DisableFloorMods",
		"DisableTotemMods",
		"FreezeDuration",
		"HealthRegen",
		"M80Assist",
		"PugglesAssist",
		"RomanCandleAssist",
		"BatsAssist",
		"BigBoom",
		"BlackCatAssist",
		"BottleRockets",
		"CannedCranberry",
		"DiveBombingTurkey",
		"FallingPumpkins",
		"Fireworks",
		"FlyingWitchAssist",
		"Gravestones",
		"GravyBubble",
		"GroundSpinner",
		"HornOfPlenty",
		"JackOLantern",
		"MashedPotatoes",
		"Pentagrams",
		"PieAssist",
		"SmokeBomb",
		"Sparklers",
		"RunningTurkeyAssist",
		"AIDisabled",
		"PhysicalOverride",
		"BloodOverride",
		"ChaosOverride",
		"DarkOverride",
		"ElectricOverride",
		"EnergyOverride",
		"FireOverride",
		"IceOverride",
		"MagicOverride",
		"PoisonOverride",
		"FStyleDisabled",
		"InvisibleKombat",
		"MomentOfOpportunity",
		"ProjectilePassThru",
		"ReducedDamage",
		"ReducedPhysicalDamage",
		"ReducedBloodDamage",
		"ReducedChaosDamage",
		"ReducedDarkDamage",
		"ReducedElectricDamage",
		"ReducedEnergyDamage",
		"ReducedFireDamage",
		"ReducedMagicDamage",
		"ReducedPoisonDamage",
		"SpecialBuff",
		"SpecialsDisabled",
		"SupermovesDisabled",
		"TimerAdjustment",
		"Weakened",
		"DeflectedGlaive",
		"DeflectedGlaiveLow",
		"WaveOfGlaives",
		"GlaiveBurst",
		"GlaiveJuggling",
		"HighLowGlaives",
		"SavageBleed",
		"SavageBleedPhase2",
		"SavageBleedPhase3",
		"SavageBleedPhase4",
		"GreenEnergyBuff",
		"SkarletHealingBlood",
		"ScytheFall",
		"BloodBall",
		"SpearFlurry",
		"FireResistance",
		"DvorahPoisonOvipositors",
		"DvorahSpiderFood",
		"DvorahOrbspinner",
		"DvorahInfest",
		"DvorahSwarmCloud",
		"RaidenStormhead",
		"RaidenLightningPillar",
		"RaidenLightningStorm",
		"KungLaoRazorHats",
		"KungLaoKungFuMaster",
		"KungLaoSpiritMaster",
		"KungLaoSpiritReinforcement",
		"KungLaoSpiritsGifts",
		"GreatKungLaosDecimation",
		"BouncingHat",
		"DragonsBreathZones",
		"DragonsBreathJump",
		"LiuKangFlowLikeWater",
		"KabalGasSaturation",
		"KabalSpeedBoost",
		"KabalHookBleed",
		"KabalGroundBladeRush",
		"FightClub",
		"BlackDragonSniper",
		"ChemicalBurns",
		"ErronBlackChainDetonator",
		"DoNothing",
};
