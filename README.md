# Project_BattleCity

**GUIDELINES**

**Folder Structure & Naming Conventions**

- We use [this guide](https://github.com/Allar/ue4-style-guide) for creating assets

**Programming**

- Use the [quickreference guide](https://docs.unrealengine.com/en-US/Gameplay/Framework/QuickReference/index.html) to learn how UE4 is structured.
- Class [Actor](https://docs.unrealengine.com/en-US/Programming/UnrealArchitecture/Actors/index.html), this is the base class of almost ALL classes in UE4 _important_.
- Class [GameMode/GameState](https://docs.unrealengine.com/en-US/Gameplay/Framework/GameMode/index.html).
- Class [Pawn](https://docs.unrealengine.com/en-US/Gameplay/Framework/Pawn/index.html).
- Class [Controller](https://docs.unrealengine.com/en-US/Gameplay/Framework/Controller/index.html).
- For our first game we should focus on [Blueprint scripting](https://docs.unrealengine.com/en-US/Engine/Blueprints/index.html).
- We are creating a 2D game.. so [Paper2D](https://docs.unrealengine.com/en-US/Engine/Paper2D/index.html) is very important.

**Graphics**
- Sprite size: 16x16 pixels
- Collision size: 8x8 pixels
- Character size: 32x32 pixels
- Tilemap size: 26x26 sprites
- Movable Sprites need to work for 4 directions (north, east, south, west)
- For Animations UE4 uses [Flipbooks](https://docs.unrealengine.com/en-US/Engine/Paper2D/Flipbooks/index.html)

**Sounds**
- Sample Rate: 44100 Hz / 22050 Hz
- Format: .WAV
- Bit Rate: 16
- Speaker Channels: Mono, Stereo, 2.1, 4.1, 5.1, 6.1, 7.1
- _[Source](https://docs.unrealengine.com/en-US/Engine/Audio/Overview/index.html)_
