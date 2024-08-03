Major features include:

* Full maphack
  * Monsters, missiles displayed on map
  * Infinite light radius
  * Configurable monster colors (see wiki for details)
  * Indicators of current level's exits
* Configurable item display features (see wiki for details)
  * Modify item names and add sockets, item levels, ethereality
  * Change colors and display items on the map
* One-click item movement
  * Shift-rightclick moves between stash/open cube and inventory
  * Ctrl-rightclick moves from stash/open cube/inventory to ground
  * Ctrl-shift-rightclick moves from stash/inventory into closed cube
* Auto-party (default hotkey: 9)
* Auto-loot (default hotkey: 7)
* Use potions directly from inventory (default hotkeys: numpad * and -)
* Display gear of other players (default hotkey: 0)
* Screen showing secondary attributes such as IAS/FHR (default hotkey: 8)
* Warnings when buffs expire (see "Skill Warning" in config file)
* Stash Export
  * Export the inventory & stash of the current character to an external file
* Experience Meter
  * Show the current %, % gained, and exp/sec above the stamina bar
* Reload configs in-game with ctrl+r or numpad 0 (numpad 0 is configurable)

Imports from LoliSquad's branch:
* Cow King and his pack now has a separate color on the minimap
* If your game name consists of word+number, it will guess your next game name to be +1 (x123 -> x124)
  * `Autofill Next Game: True`, defaults to true
* Remembers your last game's password
  * `Autofill Last Password: True`, defaults to true
* You can inspect Valkeries, Shadow Masters and Iron Golems to see what they spawned with or was made of
* Improved in-game color palette (16x16, removed an excess color square that didn't exist)

The hotkeys for all features can be changed in the config file.

Example config can be found here: [](https://github.com/planqi/bh_config)

Stash Exporting is configured through [Mustache Templates](https://mustache.github.io/mustache.5.html), see sample below:

Add this to the bottom of your BH.cfg:
```
// Stash Export
// Mustache Templates
Mustache Default:	stash
Mustache[stats]: {{#defense}}\n\n    >{{defense}} defense{{/defense}}{{#stats}}\n\n    > {{value}}{{#range}} ({{min}}-{{max}}){{/range}} {{^skill}}{{name}}{{/skill}}{{skill}}{{/stats}}
Mustache[header-unique]: {{#quality=Unique}}**{{^name}}{{type}}{{/name}}{{name}}** (L{{iLevel}}){{#sockets}}[{{sockets}}]{{/sockets}}{{/quality}}
Mustache[header-magic]: {{#quality$Magic|Rare}}**{{^name}}{{type}}{{/name}}{{name}}** (L{{iLevel}}){{#sockets}}[{{sockets}}]{{/sockets}}{{/quality}}
Mustache[header-else]: {{#quality^Unique|Magic|Rare}}{{^isRuneword}}{{^name}}{{type}}{{/name}}{{name}}{{/isRuneword}}{{#isRuneword}}**{{runeword}}** {{type}}{{/isRuneword}} (L{{iLevel}}){{#sockets}}[{{sockets}}]{{/sockets}}{{/quality}}
Mustache[header]: {{>header-unique}}{{>header-magic}}{{>header-else}}{{#count}} **x{{count}}**{{/count}}
Mustache[item]: {{>header}}{{>stats}}{{^isRuneword}}{{#socketed}}\n\n  * {{>>item}}{{/socketed}}{{/isRuneword}}\n
Mustache[stash]: {{#this}}* {{>item}}\n\n{{/this}}
```

#### Features
-  Can identify item quality
-  Can identify which unique/set/runeword the item is
-  Can identify the magix prefix/suffixes
-  Attempts to collapse known aggregate stats (all res) using the aggregate name
-  Will collapse identical items into a single entry with a count (useful for runes and gems)
-  Can exclude stats on items that are fixed so that only the important stats are shown
-  Can get stats for jewels that have been placed into a socketed item
-  See sample output further down

### D2Structs
- Adjusted some structures to better state the purpose of some previously "unknown" or unspecified bytes

### ScreenInfo
- Added display for current/added/rate of gain for experience
	 - BH Toggle: "Experience Meter"
	 
### Maphack
- Refactored the rendering pipeline for the automap objects (monsters, items, missiles, etc) so that the frames could be recycled. 
	- This allows the system to reuse calculations from previous frames and only store the draw commands.
	- This can result in a large frame rate increase on slower machines
- Added ability to display chests on the automap

### ItemDisplay
- The predicate parser will no longer use exceptions for control flow.
	- The old design was resulting in a large frame rate penalty that has been aleviated
	
## New Configuration Items & Defaults:
```
// Maphack section:
// Toggles whether or not to show chests on the automap
Show Chests:			True, VK_X
// Controls how many frames to recycle the minimap doodads for (higher values save more frames)
Minimap Max Ghost: 20

// Experience Display
Experience Meter:		True, VK_NUMPAD7

// Stash Export
// Mustache Templates
Mustache Default:	stash
Mustache[stats]: {{#defense}}\n\n    >{{defense}} defense{{/defense}}{{#stats}}\n\n    > {{value}}{{#range}} ({{min}}-{{max}}){{/range}} {{^skill}}{{name}}{{/skill}}{{skill}}{{/stats}}
Mustache[header-unique]: {{#quality=Unique}}**{{^name}}{{type}}{{/name}}{{name}}** (L{{iLevel}}){{#sockets}}[{{sockets}}]{{/sockets}}{{/quality}}
Mustache[header-magic]: {{#quality$Magic|Rare}}**{{^name}}{{type}}{{/name}}{{name}}** (L{{iLevel}}){{#sockets}}[{{sockets}}]{{/sockets}}{{/quality}}
Mustache[header-else]: {{#quality^Unique|Magic|Rare}}{{^isRuneword}}{{^name}}{{type}}{{/name}}{{name}}{{/isRuneword}}{{#isRuneword}}**{{runeword}}** {{type}}{{/isRuneword}} (L{{iLevel}}){{#sockets}}[{{sockets}}]{{/sockets}}{{/quality}}
Mustache[header]: {{>header-unique}}{{>header-magic}}{{>header-else}}{{#count}} **x{{count}}**{{/count}}
Mustache[item]: {{>header}}{{>stats}}{{^isRuneword}}{{#socketed}}\n\n  * {{>>item}}{{/socketed}}{{/isRuneword}}\n
Mustache[stash]: {{#this}}* {{>item}}\n\n{{/this}}
```

## Stash Export Sample:
Raw JSON:
````json
[
  {
    "iLevel": 4,
    "name": "Viridian Small Charm of Life",
    "quality": "Magic",
    "stats": [
      {
        "name": "maxhp",
        "value": 10
      },
      {
        "name": "poisonresist",
        "value": 7
      }
    ],
    "type": "Small Charm"
  },{
    "defense": 98,
    "iLevel": 17,
    "quality": "Rare",
    "socketed": [
      {
        "iLevel": 1,
        "isGem": true,
        "quality": "Normal",
        "type": "Ruby"
      },
      {
        "iLevel": 1,
        "isGem": true,
        "quality": "Normal",
        "type": "Sapphire"
      }
    ],
    "sockets": 2,
    "stats": [
      {
        "name": "item_armor_percent",
        "value": 29
      },
      {
        "name": "tohit",
        "value": 15
      },
      {
        "name": "normal_damage_reduction",
        "value": 1
      },
      {
        "name": "fireresist",
        "value": 10
      },
      {
        "name": "item_lightradius",
        "value": 1
      },
      {
        "name": "item_fastergethitrate",
        "value": 17
      }
    ],
    "type": "Chain Mail"
  },{
    "iLevel": 99,
    "name": "Annihilus",
    "quality": "Unique",
    "stats": [
      {
        "name": "all-stats",
        "range": {
          "max": 20,
          "min": 10
        },
        "value": 14
      },
      {
        "name": "res-all",
        "range": {
          "max": 20,
          "min": 10
        },
        "value": 16
      },
      {
        "name": "additional xp gain",
        "range": {
          "max": 10,
          "min": 5
        },
        "value": 6
      }
    ],
    "type": "Small Charm"
  },{
    "iLevel": 87,
    "name": "Wizardspike",
    "quality": "Unique",
    "type": "Bone Knife"
  },
  {
    "defense": 168,
    "iLevel": 80,
    "isRuneword": true,
    "quality": "Normal",
    "runeword": "Spirit",
    "socketed": [
      {
        "iLevel": 1,
        "isRune": true,
        "quality": "Normal",
        "type": "Tal Rune"
      },
      {
        "iLevel": 1,
        "isRune": true,
        "quality": "Normal",
        "type": "Thul Rune"
      },
      {
        "iLevel": 1,
        "isRune": true,
        "quality": "Normal",
        "type": "Ort Rune"
      },
      {
        "iLevel": 1,
        "isRune": true,
        "quality": "Normal",
        "type": "Amn Rune"
      }
    ],
    "sockets": 4,
    "stats": [
      {
        "name": "mana",
        "range": {
          "max": 112,
          "min": 89
        },
        "value": 100
      },
      {
        "name": "cast3",
        "range": {
          "max": 35,
          "min": 25
        },
        "value": 25
      },
      {
        "name": "abs-mag",
        "range": {
          "max": 8,
          "min": 3
        },
        "value": 7
      }
    ],
    "type": "Kurast Shield"
  },{
    "count": 8,
    "iLevel": 1,
    "isGem": true,
    "quality": "Normal",
    "type": "Chipped Ruby"
  },
  {
    "count": 7,
    "iLevel": 1,
    "isGem": true,
    "quality": "Normal",
    "type": "Flawed Emerald"
  }
 ]
````
Using the template above:
````
* **Viridian Small Charm of Life** (L4)

    > 10 maxhp

    > 7 poisonresist

* **Chain Mail** (L17)[2]

    >98 defense

    > 29 item_armor_percent

    > 15 tohit

    > 1 normal_damage_reduction

    > 10 fireresist

    > 1 item_lightradius

    > 17 item_fastergethitrate

  * Ruby (L1)


  * Sapphire (L1)
  

* **Annihilus** (L99)

    > 14 (10-20) all-stats

    > 16 (10-20) res-all

    > 6 (5-10) additional xp gain
    

* **Wizardspike** (L87)


* **Spirit** Kurast Shield (L80)[4]

    >168 defense

    > 100 (89-112) mana

    > 25 (25-35) cast3

    > 7 (3-8) abs-mag
    
    
* Chipped Ruby (L1) **x8**

* Flawed Emerald (L1) **x7**
````
Which renders as:
* **Viridian Small Charm of Life** (L4)

    > 10 maxhp

    > 7 poisonresist

* **Chain Mail** (L17)[2]

    >98 defense

    > 29 item_armor_percent

    > 15 tohit

    > 1 normal_damage_reduction

    > 10 fireresist

    > 1 item_lightradius

    > 17 item_fastergethitrate

  * Ruby (L1)
  * Sapphire (L1)
  

* **Annihilus** (L99)

    > 14 (10-20) all-stats

    > 16 (10-20) res-all

    > 6 (5-10) additional xp gain
    

* **Wizardspike** (L87)


* **Spirit** Kurast Shield (L80)[4]

    >168 defense

    > 100 (89-112) mana

    > 25 (25-35) cast3

    > 7 (3-8) abs-mag
    
* Chipped Ruby (L1) **x8**

* Flawed Emerald (L1) **x7**
