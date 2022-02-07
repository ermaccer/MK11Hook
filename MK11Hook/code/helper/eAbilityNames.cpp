#include "eAbilityNames.h"
#include <algorithm>

std::vector<eAbilityNameEntry> eAbiltityNames::m_aAbilityNames;

void eAbiltityNames::Init()
{
	eAbilityNameEntry ent;

	ent.chr = "CHAR_Scorpion";
	ent.abNames[0] = "Hell Flame";
	ent.abNames[1] = "Demon Breath";
	ent.abNames[2] = "Demon Dash";
	ent.abNames[3] = "Death Spin";
	ent.abNames[4] = "Death Spear Kombo";
	ent.abNames[5] = "(Air) Sin Blade";
	ent.abNames[6] = "Burning Spear";
	ent.abNames[7] = "Misery Blade";
	ent.abNames[8] = "(Air) Demon Slam";
	ent.abNames[9] = "Hell Port Cancel";

	m_aAbilityNames.push_back(ent);
	ent = {};

	ent.chr = "CHAR_Spawn";
	ent.abNames[0] = "Gun Blazing";
	ent.abNames[1] = "Blaze Of Glory";
	ent.abNames[2] = "Plasm Pool";
	ent.abNames[3] = "Hell Chain";
	ent.abNames[4] = "(Air) Leetha Glide";
	ent.abNames[5] = "Charging Hellspawn";
	ent.abNames[6] = "Raising Hell";
	ent.abNames[7] = "Invoking The Legion";
	ent.abNames[8] = "Soul Forfeit";
	ent.abNames[9] = "(Air) Fallen Angel";
	ent.abNames[10] = "Lethal Leetha Stance";

	m_aAbilityNames.push_back(ent);
	ent = {};

	ent.chr = "CHAR_Joker";
	ent.abNames[0] = "Batsy-Poo Cancel";
	ent.abNames[1] = "KAPOW";
	ent.abNames[2] = "Batsy Pew Pew";
	ent.abNames[3] = "Puppet Parry";
	ent.abNames[4] = "Getting Lit";
	ent.abNames[5] = "Corpse Trot";
	ent.abNames[6] = "Jack In The Box";
	ent.abNames[7] = "Hostage Hop";
	ent.abNames[8] = "Jumping Jester";
	ent.abNames[9] = "BOING";

	m_aAbilityNames.push_back(ent);
	ent = {};

	ent.chr = "CHAR_Kano";
	ent.abNames[0] = "Optic Blast";
	ent.abNames[1] = "Bio-Magnetic Pull";
	ent.abNames[2] = "Bio-Magnetic Trap";
	ent.abNames[3] = "Lumbar Check";
	ent.abNames[4] = "Vege-Mighty";
	ent.abNames[5] = "Snake Bite";
	ent.abNames[6] = "Rack Off";
	ent.abNames[7] = "Molotov Cocktail";
	ent.abNames[8] = "Chemical Burn";
	ent.abNames[9] = "Manhandled";

	m_aAbilityNames.push_back(ent);
	ent = {};

	ent.chr = "CHAR_Robocop";
	ent.abNames[0] = "Active & Reactive Patrol";
	ent.abNames[1] = "Cheval Trap";
	ent.abNames[2] = "Flamethrower";
	ent.abNames[3] = "Terminal Strip";
	ent.abNames[4] = "Trick Shot";
	ent.abNames[5] = "Low Auto-9";
	ent.abNames[6] = "(Air) OCP Charge";
	ent.abNames[7] = "Upgraded";
	ent.abNames[8] = "Electric Shield";
	ent.abNames[9] = "Arm Crowd Control Cannon";

	m_aAbilityNames.push_back(ent);
	ent = {};

	ent.chr = "CHAR_Rambo";
	ent.abNames[0] = "Artillery Strike";
	ent.abNames[1] = "Claymore";
	ent.abNames[2] = "Hidden M60";
	ent.abNames[3] = "Snare Trap";
	ent.abNames[4] = "FUBAR";
	ent.abNames[5] = "Leopard Krawl";
	ent.abNames[6] = "Shoulder Roll";
	ent.abNames[7] = "M.R.E.";
	ent.abNames[8] = "Mace Trap";
	ent.abNames[9] = "Commando";

	m_aAbilityNames.push_back(ent);
	ent = {};

	ent.chr = "CHAR_Baraka";
	ent.abNames[0] = "Baraka Barrage";
	ent.abNames[1] = "Blood Lunge";
	ent.abNames[2] = "Spine Burst";
	ent.abNames[3] = "Leg Kabob";
	ent.abNames[4] = "Gutted";
	ent.abNames[5] = "Blade Charge";
	ent.abNames[6] = "War Banner Bash";
	ent.abNames[7] = "Staked";
	ent.abNames[8] = "War Banner Charge";
	ent.abNames[9] = "Baraka-Serker";

	m_aAbilityNames.push_back(ent);
	ent = {};

	ent.chr = "CHAR_ShangTsung";
	ent.abNames[0] = "Inferno Skull";
	ent.abNames[1] = "Screaming Soul";
	ent.abNames[2] = "Ground Eruption";
	ent.abNames[3] = "Force Lift";
	ent.abNames[4] = "Inferno Barrier";
	ent.abNames[5] = "Soul Well";
	ent.abNames[6] = "Explosive Corpses";
	ent.abNames[7] = "Scatter Souls";
	ent.abNames[8] = "Shake";
	ent.abNames[9] = "Slide";
	ent.abNames[10] = "Superkick";
	ent.abNames[11] = "Soul Swap";
	ent.abNames[12] = "Vile Sorcery";
	ent.abNames[13] = "Shapeshifter's Training";

	m_aAbilityNames.push_back(ent);
	ent = {};

	ent.chr = "CHAR_Cage";
	ent.abNames[0] = "Pissed Off";
	ent.abNames[1] = "Mime Time";
	ent.abNames[2] = "Low Forceball";
	ent.abNames[3] = "High Forceball";
	ent.abNames[4] = "Brass Knuckles";
	ent.abNames[5] = "Throwing Shades";
	ent.abNames[6] = "Say Cheese";
	ent.abNames[7] = "Rising Star";
	ent.abNames[8] = "Caged Rage";
	ent.abNames[9] = "Stunt Double";

	m_aAbilityNames.push_back(ent);
	ent = {};

	ent.chr = "CHAR_Noob";
	ent.abNames[0] = "Ghostball";
	ent.abNames[1] = "Spirit Ball";
	ent.abNames[2] = "Sickle Snag";
	ent.abNames[3] = "(Air) Tele-Slam";
	ent.abNames[4] = "Shadow Portals";
	ent.abNames[5] = "(Air) Sickle Port";
	ent.abNames[6] = "Sickle Toss";
	ent.abNames[7] = "Shadow Slide";
	ent.abNames[8] = "Shadow Strike";
	ent.abNames[9] = "Shadow Dive";

	m_aAbilityNames.push_back(ent);
	ent = {};

	ent.chr = "CHAR_Kabal";
	ent.abNames[0] = "Rolling Buzzsaw";
	ent.abNames[1] = "(Air) Straight Buzzin'";
	ent.abNames[2] = "Low Hook Grab";
	ent.abNames[3] = "Low Spinner";
	ent.abNames[4] = "Hook Grab";
	ent.abNames[5] = "Nomad Spin";
	ent.abNames[6] = "(Air) Slight Gas";
	ent.abNames[7] = "Flash Parry";
	ent.abNames[8] = "Extended Hook";
	ent.abNames[9] = "Gas Blast";
	ent.abNames[10] = "Dash Cancel";

	m_aAbilityNames.push_back(ent);
	ent = {};

	ent.chr = "CHAR_Kabal";
	ent.abNames[0] = "Rolling Buzzsaw";
	ent.abNames[1] = "(Air) Straight Buzzin'";
	ent.abNames[2] = "Low Hook Grab";
	ent.abNames[3] = "Low Spinner";
	ent.abNames[4] = "Hook Grab";
	ent.abNames[5] = "Nomad Spin";
	ent.abNames[6] = "(Air) Slight Gas";
	ent.abNames[7] = "Flash Parry";
	ent.abNames[8] = "Extended Hook";
	ent.abNames[9] = "Gas Blast";
	ent.abNames[10] = "Dash Cancel";

	m_aAbilityNames.push_back(ent);
	ent = {};


	ent.chr = "CHAR_Skarlet";
	ent.abNames[0] = "Dagger Dance";
	ent.abNames[1] = "Bloodport";
	ent.abNames[2] = "Cell Siphon";
	ent.abNames[3] = "Boiling Point";
	ent.abNames[4] = "Retch-Rebution";
	ent.abNames[5] = "Killer Clot";
	ent.abNames[6] = "Blood Ritual";
	ent.abNames[7] = "Krimson Shield";
	ent.abNames[8] = "Red Mist";
	ent.abNames[9] = "Red Rain";
	ent.abNames[10] = "Blood Flow";

	m_aAbilityNames.push_back(ent);
	ent = {};

	ent.chr = "CHAR_Terminator";
	ent.abNames[0] = "Ion Grenade";
	ent.abNames[1] = "Rolling Ion Grenade";
	ent.abNames[2] = "Albi Back Breaker";
	ent.abNames[3] = "(Air) Death Grip";
	ent.abNames[4] = "Infiltrator Toss";
	ent.abNames[5] = "Endo Lunge";
	ent.abNames[6] = "Terminate";
	ent.abNames[7] = "T.D.E.";
	ent.abNames[8] = "Cyber Rift";
	ent.abNames[9] = "Terraformer";
	ent.abNames[10] = "Vice Grip";
	ent.abNames[11] = "Running Man";
	ent.abNames[12] = "Incapacitator";
	ent.abNames[13] = "Endoskeleton";

	m_aAbilityNames.push_back(ent);
	ent = {};

	ent.chr = "CHAR_Cetrion";
	ent.abNames[0] = "Earthquake";
	ent.abNames[1] = "H2 P0rt";
	ent.abNames[2] = "Delay Boulder Bash";
	ent.abNames[3] = "Geyser";
	ent.abNames[4] = "Deadly Winds";
	ent.abNames[5] = "Shattering Boulder";
	ent.abNames[6] = "Circle Of Life";
	ent.abNames[7] = "Hallowing Winds";
	ent.abNames[8] = "Ring Of Fire";
	ent.abNames[9] = "Vapor Halo";
	ent.abNames[10] = "Conflux of Elements";

	m_aAbilityNames.push_back(ent);
	ent = {};

	ent.chr = "CHAR_ShaoKahn";
	ent.abNames[0] = "Skewered";
	ent.abNames[1] = "Spear Charge";
	ent.abNames[2] = "Annihilation";
	ent.abNames[3] = "Ridicule";
	ent.abNames[4] = "Ground Shatter";
	ent.abNames[5] = "(Air) Wrath Hammer";
	ent.abNames[6] = "Wrath Hammer";
	ent.abNames[7] = "Seeking Wrath Hammer";
	ent.abNames[8] = "Up Wrath Hammer";
	ent.abNames[9] = "Dark Priest";

	m_aAbilityNames.push_back(ent);
	ent = {};

	ent.chr = "CHAR_Sonya";
	ent.abNames[0] = "(Air) Ops Drop";
	ent.abNames[1] = "Krushing Kounters";
	ent.abNames[2] = "Energy Rings Charge";
	ent.abNames[3] = "(Air) Downward Energy Rings";
	ent.abNames[4] = "(Air) Soaring General";
	ent.abNames[5] = "K.A.T. Orbital Drop";
	ent.abNames[6] = "Summon K.A.T. Turret";
	ent.abNames[7] = "Turret Trauma";
	ent.abNames[8] = "(Air) Marching Orders";

	m_aAbilityNames.push_back(ent);
	ent = {};


	ent.chr = "CHAR_LiuKang";
	ent.abNames[0] = "Shaolin Stance";
	ent.abNames[1] = "Energy Parry";
	ent.abNames[2] = "Nunchaku Stance";
	ent.abNames[3] = "Low Fireball";
	ent.abNames[4] = "Dragon Fire";
	ent.abNames[5] = "Dragon's Gifts";
	ent.abNames[6] = "Dragon Parry";
	ent.abNames[7] = "Kusari Slam";
	ent.abNames[8] = "Shaolin Vanish";

	m_aAbilityNames.push_back(ent);
	ent.chr = "CHAR_FireGod";
	m_aAbilityNames.push_back(ent);
	ent = {};

	ent.chr = "CHAR_ErronBlack";
	ent.abNames[0] = "Enhanced Locked and Loaded";
	ent.abNames[1] = "Outworld Gunslinger";
	ent.abNames[2] = "Acid Pour";
	ent.abNames[3] = "Cattle Toss";
	ent.abNames[4] = "Up Peacemaker";
	ent.abNames[5] = "Down Peacemaker";
	ent.abNames[6] = "Scud Shot";
	ent.abNames[7] = "TNT Toss";
	ent.abNames[8] = "Netherbeast Trap";
	ent.abNames[9] = "Enhanced Rattle Snake Slide";

	m_aAbilityNames.push_back(ent);
	ent = {};

	ent.chr = "CHAR_Terminas";
	ent.abNames[0] = "Gauntlet Of The Ages";
	ent.abNames[1] = "Bed Of Spikes";
	ent.abNames[2] = "Shifting Sands";
	ent.abNames[3] = "Lost Time & Spare Time";
	ent.abNames[4] = "Sand Simulacrum";
	ent.abNames[5] = "Reawakened";
	ent.abNames[6] = "Reverse Time";
	ent.abNames[7] = "Stepping It Back";
	ent.abNames[8] = "Sand Pillar";

	m_aAbilityNames.push_back(ent);
	ent = {};


	ent.chr = "CHAR_Fujin";
	ent.abNames[0] = "(Air) Wind Barrier";
	ent.abNames[1] = "Sky Wakka";
	ent.abNames[2] = "Divine Wind";
	ent.abNames[3] = "Wind Push";
	ent.abNames[4] = "Airsenal";
	ent.abNames[5] = "Air Slam";
	ent.abNames[6] = "Jet Stream";
	ent.abNames[7] = "Pressure Bomb";
	ent.abNames[8] = "Turbulence";
	ent.abNames[9] = "Warped Needle";
	ent.abNames[10] = "Twister";
	ent.abNames[11] = "Deadly Winds";

	m_aAbilityNames.push_back(ent);
	ent = {};


	ent.chr = "CHAR_CyberFrost";
	ent.abNames[0] = "Ice Auger";
	ent.abNames[1] = "Burrowing Auger";
	ent.abNames[2] = "Cryogenic Crown";
	ent.abNames[3] = "Core Trap";
	ent.abNames[4] = "Core Overload";
	ent.abNames[5] = "Auger Lunge";
	ent.abNames[6] = "Arctic Barrage";
	ent.abNames[7] = "(Air) Icequake";
	ent.abNames[8] = "Glacier Calving";
	ent.abNames[9] = "Microbust";

	m_aAbilityNames.push_back(ent);
	ent = {};

	ent.chr = "CHAR_Cassie";
	ent.abNames[0] = "Control BLB-118";
	ent.abNames[1] = "(Air) Bullet Barrage";
	ent.abNames[2] = "Kneecappin'";
	ent.abNames[3] = "Flippin' Out";
	ent.abNames[4] = "Shoulder Charge";
	ent.abNames[5] = "Flying Glow Kick";
	ent.abNames[6] = "BLB-118 Advance";
	ent.abNames[7] = "BLB-118 Bullet Ricochet";
	ent.abNames[8] = "BLB-118 Energy Bounce";
	ent.abNames[9] = "BLB-118 Energy Burst";
	ent.abNames[10] = "BLB-118 Bitchin' Bubble";

	m_aAbilityNames.push_back(ent);
	ent = {};

	ent.chr = "CHAR_Raiden";
	ent.abNames[0] = "Jo Push";
	ent.abNames[1] = "Storm Cell";
	ent.abNames[2] = "Electric Burst";
	ent.abNames[3] = "Quick Charge";
	ent.abNames[4] = "Rolling Thunder";
	ent.abNames[5] = "Super Bolt";
	ent.abNames[6] = "Lightning Storm";
	ent.abNames[7] = "Electric Current";
	ent.abNames[8] = "Lightning Rod";
	ent.abNames[9] = "Sparkport";

	m_aAbilityNames.push_back(ent);
	ent = {};

	ent.chr = "CHAR_Kitana";
	ent.abNames[0] = "Fan-Nado";
	ent.abNames[1] = "(Air) Piercing Dagger";
	ent.abNames[2] = "Upward Fan Toss";
	ent.abNames[3] = "Low Fan Toss";
	ent.abNames[4] = "Dancing Fans";
	ent.abNames[5] = "(Air) Fan Flutter";
	ent.abNames[6] = "Retreating and Advancing Fan Flutter";
	ent.abNames[7] = "Edenian Twist";
	ent.abNames[8] = "Ground War";
	ent.abNames[9] = "Half Blood Stance";
	ent.abNames[10] = "Edenian Fade";
	ent.abNames[11] = "Royal Protection";
	ent.abNames[12] = "Edenian Razors";

	m_aAbilityNames.push_back(ent);
	ent = {};

	ent.chr = "CHAR_DVorah";
	ent.abNames[0] = "Deadly Swarm";
	ent.abNames[1] = "Super Swarm";
	ent.abNames[2] = "(Air) Fly By";
	ent.abNames[3] = "(Air) Ticking Time Bug";
	ent.abNames[4] = "Widow's Kiss";
	ent.abNames[5] = "Bombardier Beetle";
	ent.abNames[6] = "Strepsiptera";
	ent.abNames[7] = "Flippin' Out";
	ent.abNames[8] = "Parasite";
	ent.abNames[9] = "Mother Bug";

	m_aAbilityNames.push_back(ent);
	ent = {};

	ent.chr = "CHAR_Kollector";
	ent.abNames[0] = "Demonic Mace";
	ent.abNames[1] = "Relic Lure";
	ent.abNames[2] = "Demonic Clutch";
	ent.abNames[3] = "War-Quoit Toss";
	ent.abNames[4] = "Bag Bomb";
	ent.abNames[5] = "Vial of Sorrow";
	ent.abNames[6] = "Demonic Comet";
	ent.abNames[7] = "Fade Out";

	m_aAbilityNames.push_back(ent);
	ent = {};


	ent.chr = "CHAR_Rain";
	ent.abNames[0] = "Riptide";
	ent.abNames[1] = "Geyser Palm";
	ent.abNames[2] = "Water Ball";
	ent.abNames[3] = "Purple Pain";
	ent.abNames[4] = "Edenian Force";
	ent.abNames[5] = "Quantum Slice";
	ent.abNames[6] = "Hydroplane";
	ent.abNames[7] = "Tidal Wave";
	ent.abNames[8] = "Hydro Boost";
	ent.abNames[9] = "Quantum Rift";
	ent.abNames[10] = "Wave Dash";

	m_aAbilityNames.push_back(ent);
	ent = {};

	ent.chr = "CHAR_Nightwolf";
	ent.abNames[0] = "Rising Tomahawk";
	ent.abNames[1] = "Tomahawk Swing";
	ent.abNames[2] = "Ancestral Light";
	ent.abNames[3] = "Spirit Tracks";
	ent.abNames[4] = "Ancestral Hunter";
	ent.abNames[5] = "Grappling Stalker";
	ent.abNames[6] = "Lunar Orbit";
	ent.abNames[7] = "Moonfall";
	ent.abNames[8] = "Lightning Arrow";
	ent.abNames[9] = "Moonlight Reflector";
	ent.abNames[10] = "Spirit of Kiba";
	ent.abNames[11] = "Spirit of Komo";
	ent.abNames[12] = "Spirit of Hana";
	ent.abNames[13] = "Hana's Wrath";

	m_aAbilityNames.push_back(ent);
	ent = {};

	ent.chr = "CHAR_Jax";
	ent.abNames[0] = "Duck and Weave";
	ent.abNames[1] = "Quad Grab";
	ent.abNames[2] = "Buckshot";
	ent.abNames[3] = "Lethal Clap";
	ent.abNames[4] = "Briggs Barricade";
	ent.abNames[5] = "Ripped";
	ent.abNames[6] = "Burning Hammer";
	ent.abNames[7] = "Ground Shatter";
	ent.abNames[8] = "Expert Grappler";
	ent.abNames[9] = "Enhanced Outranked";

	m_aAbilityNames.push_back(ent);
	ent = {};

	ent.chr = "CHAR_Jacqui";
	ent.abNames[0] = "Prototype Rocket";
	ent.abNames[1] = "Grenade Launcher";
	ent.abNames[2] = "Hyper Knee";
	ent.abNames[3] = "Lethal Clinch";
	ent.abNames[4] = "Air Dive Bomb";
	ent.abNames[5] = "Air Ground Pound";
	ent.abNames[6] = "Enhanced Air Blast";
	ent.abNames[7] = "Tech-Dome";
	ent.abNames[8] = "Cybernetic Override";
	ent.abNames[9] = "Bionic Bounce";
	ent.abNames[10] = "Robo Grappler";

	m_aAbilityNames.push_back(ent);
	ent = {};

	ent.chr = "CHAR_KungLao";
	ent.abNames[0] = "Guided Hat";
	ent.abNames[1] = "Possessed Hat"; 
	ent.abNames[2] = "Z Hat"; 
	ent.abNames[3] = "Buzz Saw"; 
	ent.abNames[4] = "Vortex"; 
	ent.abNames[5] = "(Air) Teleport"; 
	ent.abNames[6] = "Spiritual Guidance";
	ent.abNames[7] = "Orbiting Hat";
	ent.abNames[8] = "Omega Hat"; 
	ent.abNames[9] = "Hat Possession";

	m_aAbilityNames.push_back(ent);
	ent = {};

	ent.chr = "CHAR_Kotal";
	ent.abNames[0] = "Grand Discus";
	ent.abNames[1] = "Directed Rays";
	ent.abNames[2] = "Tonatiuh Burst";
	ent.abNames[3] = "Amocualli Totem";
	ent.abNames[4] = "Teoyohtica Totem";
	ent.abNames[5] = "Chicahtoc Totem";
	ent.abNames[6] = "Eztli Totem";
	ent.abNames[7] = "Huehhueyi";
	ent.abNames[8] = "God Ray";
	ent.abNames[9] = "Tecuani Maul";
	ent.abNames[10] = "(Air) Tecuani Pounce";
	ent.abNames[11] = "Kahn-Cut";

	m_aAbilityNames.push_back(ent);
	ent = {};

	ent.chr = "CHAR_Sindel";
	ent.abNames[0] = "Hair Kut";
	ent.abNames[1] = "Deadly Echo";
	ent.abNames[2] = "Banshee Dash";
	ent.abNames[3] = "Low Star Screamer";
	ent.abNames[4] = "Whip & Flip";
	ent.abNames[5] = "Maleficent March";
	ent.abNames[6] = "(Air) Bellowing Banshee";
	ent.abNames[7] = "(Air) Royal Trap";
	ent.abNames[8] = "(Air) Banshee Barrage";
	ent.abNames[9] = "Enhanced Regal Presence";

	m_aAbilityNames.push_back(ent);
	ent = {};

	ent.chr = "CHAR_Sindel";
	ent.abNames[0] = "Hair Kut";
	ent.abNames[1] = "Deadly Echo";
	ent.abNames[2] = "Banshee Dash";
	ent.abNames[3] = "Low Star Screamer";
	ent.abNames[4] = "Whip & Flip";
	ent.abNames[5] = "Maleficent March";
	ent.abNames[6] = "(Air) Bellowing Banshee";
	ent.abNames[7] = "(Air) Royal Trap";
	ent.abNames[8] = "(Air) Banshee Barrage";
	ent.abNames[9] = "Enhanced Regal Presence";

	m_aAbilityNames.push_back(ent);
	ent = {};

	ent.chr = "CHAR_SubZero";
	ent.abNames[0] = "Creeping Ice";
	ent.abNames[1] = "Ground Ice";
	ent.abNames[2] = "Cold Shoulder";
	ent.abNames[3] = "Rising Ice";
	ent.abNames[4] = "Unused";
	ent.abNames[5] = "Frigid Storm";
	ent.abNames[6] = "Death-Cicle Barrage";
	ent.abNames[7] = "Air Polar Axe";
	ent.abNames[8] = "Arctic Trap";
	ent.abNames[9] = "Deep Freeze";

	m_aAbilityNames.push_back(ent);
	ent = {};

	ent.chr = "CHAR_Jade";
	ent.abNames[0] = "Razor-Rang";
	ent.abNames[1] = "Deadly Butterfly";
	ent.abNames[2] = "Temptation Parry";
	ent.abNames[3] = "Blazing Nitro Kick";
	ent.abNames[4] = "Divine Forces";
	ent.abNames[5] = "Vanishing Winds";
	ent.abNames[6] = "Deadly Assassin";

	m_aAbilityNames.push_back(ent);
	ent = {};

	ent.chr = "CHAR_Sheeva";
	ent.abNames[0] = "Queen's Punishment";
	ent.abNames[1] = "Enhanced Dragon Drop";
	ent.abNames[2] = "Shokan Snag";
	ent.abNames[3] = "Tremor";
	ent.abNames[4] = "Dragon Charge";
	ent.abNames[5] = "Death March";
	ent.abNames[6] = "Spinning Dragon";
	ent.abNames[7] = "Dragon Stance";
	ent.abNames[8] = "Battle Scars";
	ent.abNames[9] = "Shield Toss";

	m_aAbilityNames.push_back(ent);
	ent = {};

	ent.chr = "CHAR_Mileena";
	ent.abNames[0] = "Low Sai Blast";
	ent.abNames[1] = "Soaring Sai";
	ent.abNames[2] = "Sai Slide";
	ent.abNames[3] = "Vanish";
	ent.abNames[4] = "Stabyscotch";
	ent.abNames[5] = "Air Tele-Drop";
	ent.abNames[6] = "Kahnum Dash";
	ent.abNames[7] = "Rolling Thunder";
	ent.abNames[8] = "Play Time";
	ent.abNames[9] = "Square Wave";

	m_aAbilityNames.push_back(ent);
	ent = {};

}

eAbilityNameEntry eAbiltityNames::Get(const char * chrName)
{
	std::string input = chrName;
	eAbilityNameEntry result;

	for (unsigned int i = 0; i < m_aAbilityNames.size(); i++)
	{
		if (m_aAbilityNames[i].chr == input)
		{
			result = m_aAbilityNames[i];
			break;
		}
	}

	return result;
}

eAbilityNameEntry::eAbilityNameEntry()
{
	chr = "char_null";

	for (int i = 0; i < TOTAL_ABILITIES; i++)
	{
		abNames[i] = "";
	}
		
}
