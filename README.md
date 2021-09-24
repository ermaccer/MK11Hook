# MK11Hook
A plugin for Mortal Kombat 11.

# Installation

####  MK11Hook only works with latest (non DX12) Steam version!

You can download binary files from [Releases](https://github.com/ermaccer/MK11Hook/) page. Extract **mk11hook.zip**
to Binaries\Retail folder of Mortal Kombat 11.

If you are not sure how to find your Mortal Kombat 11 folder, search for it in your Steam library then right click on the entry and select Manage->Browse local files.

Archive breakdown:

 - dinput8.dll - [Ultimate ASI Loader](https://github.com/ThirteenAG/Ultimate-ASI-Loader/)
 - MK11Hook.asi 
 - MK11Hook.ini - configuration file

# Usage

If installed correctly, a notification will appear informing that the plugin was installed
and is ready to use. By default **F1** will open or close in-game menu.

![Preview](https://raw.githubusercontent.com/ermaccer/ermaccer.github.io/gh-pages/assets/mods/mk11/mk11hook/menu.jpg)


# Controller Support
Any XInput compatible gamepad should work.

## Gamepad Controls
| Button | Effect |
| --- | --- |
| L3 + R3 | Open/Close menu|
| X | Adjust menu|
| A | Select |
| B | Back |
| D-Pad | Move/ Scale menu in adjust mode |
| Left Stick | Move menu in adjust mode |

Gamepad support can be disabled in the .ini file by setting **bEnableGamepadSupport** to false.

## Features
| Feature | Description |
| --- | --- |
|Character Modifier| <ul><li>Play as NPCs - Sektor, Cyrax, Kronika and Fire God Liu Kang.</li><li>Change forced character in story mode or other modes.</li></ul>|
|Stage Modifier| <ul><li>Change stage to anything in any game mode.</li><li> Access various tournament exclusive stages (eg. EVO)</li></ul> |
|Modifiers| <ul><li>Add Tag Assists to local fights.</li><li>**Please read menu description about how to use this feature!** </li></ul> |
|Player Control| <ul><li>Change speed and scale of players.</li><li> Scale setting is *visual* only!</li></ul> |
|Speed Modifier| <ul><li>Change game speed, enjoy fights in slowmotion!</li></ul> |
|Camera Control| <ul><li>Freeze camera position & rotation.</li><li>Freely move and rotate camera with keyboard hotkeys.</li><li>Play in predefined custom camera modes: <ul><li>Injustice 2</li><li>3RD Person</li><li>1ST Person</li></ul> </ul></li> |
|Krypt Control| <ul><li>Change Krypt player model.</li></ul> |
|Cheats| All cheats can be toggled for both P1 and P2<ul><li>Infinite Health</li><li>Zero Health</li><li>1 Health</li><li>Infinite Offensive/Defensive Bar</li><li>Easy Krushing Blows</li></ul> |
|Misc.| <ul><li>Disable FightHUD</li><li>Completely disable all HUD elements</li></ul> |




![Preview](https://raw.githubusercontent.com/ermaccer/ermaccer.github.io/gh-pages/assets/mods/mk11/mk11hook/1.jpg)
![Preview](https://raw.githubusercontent.com/ermaccer/ermaccer.github.io/gh-pages/assets/mods/mk11/mk11hook/2.jpg)


# Building

MK11Hook was developed & tested using Visual Studio 2017.


# Credits/Used stuff

https://github.com/CookiePLMonster/ModUtils

https://github.com/ocornut/imgui

https://github.com/Rebzzel/kiero

D3D11 hook based on https://github.com/rdbo/ImGui-DirectX-11-Kiero-Hook
